#!/bin/bash



HOSTNAME=myrina
ADDRESS=10.0.0.2



/sbin/hdparm -d1 -c1 /dev/hda
/sbin/hdparm -d1 -c1 /dev/hdb
/sbin/mkraid /dev/md0
#/sbin/e2fsck -y /dev/hda1
#/sbin/e2fsck -y /dev/hda2
#/sbin/e2fsck -y /dev/md0


/bin/mount -o remount -rw /
/bin/mount /boot
/bin/mount /proc
/bin/mount -r /home


/sbin/klogd -f /var/log/messages&

/sbin/ifconfig eth0 $ADDRESS netmask 255.255.255.0 broadcast 10.0.0.255
/sbin/route add default gw 10.0.0.1
/sbin/ifconfig lo 127.0.0.1
/sbin/route add 127.0.0.0 lo
/bin/hostname $HOSTNAME
/usr/sbin/sshd&
/sbin/portmap&
/usr/sbin/rpc.mountd&
/usr/sbin/rpc.nfsd&

/bin/mount amazon:/usr/src /usr/src&


. /etc/bashrc

/bin/bash

echo "syncing and unmounting"

sync
/bin/mount -f -o remount -r /
/bin/mount -f -o remount -r /home
/bin/mount -f -o remount -r /boot
/bin/umount /
