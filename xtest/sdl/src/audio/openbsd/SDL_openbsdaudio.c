/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@devolution.com
*/

/*
 * Driver for native OpenBSD audio(4).
 * vedge@vedge.com.ar.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/audioio.h>

#include "SDL_audio.h"
#include "SDL_error.h"
#include "SDL_audiomem.h"
#include "SDL_audio_c.h"
#include "SDL_timer.h"
#include "SDL_audiodev_c.h"
#include "SDL_openbsdaudio.h"

/* The tag name used by OpenBSD audio */
#define OBSD_DRIVER_NAME         "openbsd"

/* Open the audio device for playback, and don't block if busy */
/* #define USE_BLOCKING_WRITES */

/* Use timer for synchronization */
/* #define USE_TIMER_SYNC */

/* #define DEBUG_AUDIO */
/* #define DEBUG_AUDIO_STREAM */

#ifdef USE_BLOCKING_WRITES
#define OPEN_FLAGS	O_WRONLY
#else
#define OPEN_FLAGS	(O_WRONLY|O_NONBLOCK)
#endif

/* Audio driver functions */
static void OBSD_WaitAudio(_THIS);
static int OBSD_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void OBSD_PlayAudio(_THIS);
static Uint8 *OBSD_GetAudioBuf(_THIS);
static void OBSD_CloseAudio(_THIS);

#ifdef DEBUG_AUDIO
static void OBSD_Status(_THIS);
#endif

/* Audio driver bootstrap functions */

static int
Audio_Available(void)
{
    int fd;
    int available;

    available = 0;
    fd = SDL_OpenAudioPath(NULL, 0, OPEN_FLAGS, 0);
    if(fd >= 0) {
	available = 1;
	close(fd);
    }
    return(available);
}

static void
Audio_DeleteDevice(SDL_AudioDevice *device)
{
    free(device->hidden);
    free(device);
}

static SDL_AudioDevice
*Audio_CreateDevice(int devindex)
{
    SDL_AudioDevice *this;

    /* Initialize all variables that we clean on shutdown */
    this = (SDL_AudioDevice*)malloc(sizeof(SDL_AudioDevice));
    if(this) {
	memset(this, 0, (sizeof *this));
	this->hidden =
	    (struct SDL_PrivateAudioData*)malloc((sizeof *this->hidden));
    }
    if((this == NULL) || (this->hidden == NULL)) {
	SDL_OutOfMemory();
	if(this) free(this);
	return(0);
    }
    memset(this->hidden, 0, (sizeof *this->hidden));
    audio_fd = -1;

    /* Set the function pointers */
    this->OpenAudio = OBSD_OpenAudio;
    this->WaitAudio = OBSD_WaitAudio;
    this->PlayAudio = OBSD_PlayAudio;
    this->GetAudioBuf = OBSD_GetAudioBuf;
    this->CloseAudio = OBSD_CloseAudio;

    this->free = Audio_DeleteDevice;
    
    return this;
}

AudioBootStrap OBSD_bootstrap = {
	OBSD_DRIVER_NAME, "Native OpenBSD audio",
	Audio_Available, Audio_CreateDevice
};

/* This function waits until it is possible to write a full sound buffer */
static void
OBSD_WaitAudio(_THIS)
{
#ifndef USE_BLOCKING_WRITES
    fd_set fdset;

    /* Check to see if the thread-parent process is still alive */
    {
	static int cnt = 0;
	/* Note that this only works with thread implementations 
	   that use a different process id for each thread. */
	if(parent && (((++cnt)%10) == 0)) { /* Check every 10 loops */
	    if(kill(parent, 0) < 0)
		this->enabled = 0;
	}
    }

#ifdef USE_TIMER_SYNC
    /* See if we need to use timed audio synchronization */
    if(frame_ticks)
    {
	/* Use timer for general audio synchronization */
	Sint32 ticks;

	ticks = ((Sint32)(next_frame - SDL_GetTicks())) - FUDGE_TICKS;
	if(ticks > 0)
	    SDL_Delay(ticks);
    }
    else
#endif /* USE_TIMER_SYNC */
    {
	/* Use select() for audio synchronization */
	struct timeval timeout;
	FD_ZERO(&fdset);
	FD_SET(audio_fd, &fdset);
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	
#if defined(DEBUG_AUDIO_STREAM) && defined(DEBUG_AUDIO_STREAM)
	OBSD_Status(this);
#endif
	if(select(audio_fd+1, NULL, &fdset, NULL, &timeout) <= 0)
	{
	    const char *message =
		"Audio timeout - buggy audio driver? (disabled)";
	    fprintf(stderr, "SDL: %s\n", message);
	    this->enabled = 0;
	    audio_fd = -1;
	}
    }
#endif /* !USE_BLOCKING_WRITES */

}

static void
OBSD_PlayAudio(_THIS)
{
    int written;

    /* Write the audio data, checking for EAGAIN on broken audio drivers */
    do
    {
	written = write(audio_fd, mixbuf, mixlen);
	if((written < 0) && ((errno == 0) || (errno == EAGAIN)))
	    SDL_Delay(1);
    }
    while((written < 0) &&
	((errno == 0) || (errno == EAGAIN) || (errno == EINTR)));

#ifdef USE_TIMER_SYNC
    if(frame_ticks)
	next_frame += frame_ticks;
#endif

    /* If we couldn't write, assume fatal error for now */
    if(written < 0)
	this->enabled = 0;

#ifdef DEBUG_AUDIO_STREAM
    fprintf(stderr, "Wrote %d bytes of audio data\n", written);
#endif
}

static Uint8
*OBSD_GetAudioBuf(_THIS)
{
    return(mixbuf);
}

static void
OBSD_CloseAudio(_THIS)
{
    if(mixbuf != NULL) {
	SDL_FreeAudioMem(mixbuf);
	mixbuf = NULL;
    }
    if(audio_fd >= 0) {
	close(audio_fd);
	audio_fd = -1;
    }
}

#ifdef DEBUG_AUDIO
void
OBSD_Status(_THIS)
{
    audio_info_t info;

    if(ioctl(audio_fd, AUDIO_GETINFO, &info) < 0) {
	fprintf(stderr,"AUDIO_GETINFO failed.\n");
	return;
    }

    fprintf(stderr,"
[play/record info]
buffer size	:   %d bytes
sample rate	:   %i Hz
channels	:   %i
precision	:   %i-bit
encoding	:   0x%x
seek		:   %i
sample count	:   %i
EOF count	:   %i
paused		:   %s
error occured	:   %s
waiting		:   %s
active		:   %s
",
    info.play.buffer_size,
    info.play.sample_rate,
    info.play.channels,
    info.play.precision,
    info.play.encoding,
    info.play.seek,
    info.play.samples,
    info.play.eof,
    info.play.pause ? "yes" : "no",
    info.play.error ? "yes" : "no",
    info.play.waiting ? "yes" : "no",
    info.play.active ? "yes": "no");

    fprintf(stderr,"
[audio info]
monitor_gain	:   %i
hw block size	:   %d bytes
hi watermark	:   %i
lo watermark	:   %i
audio mode	:   %s
",  
    info.monitor_gain,
    info.blocksize,
    info.hiwat, info.lowat,
    (info.mode == AUMODE_PLAY) ? "PLAY"
    : (info.mode = AUMODE_RECORD) ? "RECORD"
    : (info.mode == AUMODE_PLAY_ALL ? "PLAY_ALL"
    : "???"));
}
#endif /* DEBUG_AUDIO */

static int
OBSD_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
    char audiodev[64];
    Uint16 setenc;
    audio_encoding_t enc;
    audio_info_t info;

    AUDIO_INITINFO(&info);
    
    /* Calculate the final parameters for this audio specification */
    SDL_CalculateAudioSpec(spec);

#ifdef USE_TIMER_SYNC
    frame_ticks = 0.0;
#endif

    /* Open the audio device */
    audio_fd = SDL_OpenAudioPath(audiodev, sizeof(audiodev), OPEN_FLAGS, 0);
    if(audio_fd < 0) {
	SDL_SetError("Couldn't open %s: %s", audiodev, strerror(errno));
	return(-1);
    }
    
    /* Set to play mode */
    info.mode = AUMODE_PLAY;
    if(ioctl(audio_fd, AUDIO_SETINFO, &info) < 0) {
	SDL_SetError("Couldn't put device into play mode");
	return(-1);
    }
    
    mixbuf = NULL;
    setenc = 0;

    for(enc.index = 0; (ioctl(audio_fd, AUDIO_GETENC, &enc)>=0)
	&& (enc.encoding != setenc); enc.index++)
    {
	switch(spec->format)
	{
	    case AUDIO_U8:	/* 8-bit unsigned linear */
		setenc = AUDIO_ENCODING_PCM8;
		break;
	    case AUDIO_S8:	/* 8-bit signed linear */
		setenc = AUDIO_ENCODING_SLINEAR;
		break;
	    case AUDIO_U16LSB:  /* 16-bit unsigned linear, LSB */
		setenc = AUDIO_ENCODING_ULINEAR_LE;
		break;
	    case AUDIO_U16MSB:  /* 16-bit unsigned linear, MSB */
		setenc = AUDIO_ENCODING_ULINEAR_BE;
		break;
	    case AUDIO_S16LSB:  /* 16-bit signed linear, LSB */
		setenc = AUDIO_ENCODING_SLINEAR_LE;
		break;
	    case AUDIO_S16MSB:  /* 16-bit signed linear, MSB */
		setenc = AUDIO_ENCODING_SLINEAR_BE;
		break;
	}
#ifdef DEBUG_AUDIO
	fprintf(stderr,"encoding #%i: \"%s\" %i-bit (0x%x) flags=%i...\n",
	    enc.index, enc.name, enc.precision, enc.encoding, enc.flags);
#endif
    }

    if(!setenc) {
	SDL_SetError("No supported encoding for 0x%x", spec->format);
	return(-1);
    }

    /* Set audio encoding */
    info.play.encoding = enc.encoding;
    info.play.precision = enc.precision;
    if((ioctl(audio_fd, AUDIO_SETINFO, &info) < 0)) {
	SDL_SetError("Couldn't set encoding to 0x%x %i-bit",
	    enc.encoding, enc.precision);
	return(-1);
    }

    /* Set audio channels */
    info.play.channels = spec->channels;
    if(ioctl(audio_fd, AUDIO_SETINFO, &info) < 0) {
	info.play.channels = (spec->channels > 1);
	ioctl(audio_fd, AUDIO_SETINFO, &info);
    }

    /* Set the sample rate */
    info.play.sample_rate = spec->freq;
    if(ioctl(audio_fd, AUDIO_SETINFO, &info) < 0) {
	SDL_SetError("Couldn't set sample rate to %i Hz", spec->freq);
	return(-1);
    }

    /* Allocate mixing buffer */
    mixlen = spec->size;
    mixbuf = (Uint8*)SDL_AllocAudioMem(mixlen);
    if(mixbuf == NULL) {
	return(-1);
    }
    memset(mixbuf, spec->silence, spec->size);
    
    /* Get the parent process id (we're the parent of the audio thread) */
    parent = getpid();

#ifdef DEBUG_AUDIO
    OBSD_Status(this);
#endif

    /* We're ready to rock and roll. :-) */
    return(0);
}
