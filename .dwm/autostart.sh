#!/bin/sh

copyq &
setxkbmap -layout gb,ara -variant ,digits -option grp:alt_space_toggle caps:escape &
sxhkd &
feh --no-fehbg --bg-fill ~/.bg.png &
bash ~/.screenlayout/dual.sh;

export $(dbus-launch --exit-with-session)

# stated on gnome-keyring arch wiki

dbus-update-activation-environment --all

gnome-keyring-daemon --start --components=gpg,pkcs11,secrets,ssh

doas /usr/libexec/gvfsd &

doas /usr/libexec/gvfs-udisks2-volume-monitor &

doas /usr/libexec/gvfs-goa-volume-monitor &

doas /usr/libexec/gvfs-afc-volume-monitor &

doas /usr/libexec/gvfs-mtp-volume-monitor &

doas /usr/libexec/gvfs-gphoto2-volume-monitor &

doas /usr/libexec/gvfsd-trash --spawner :1.4 /org/gtk/gvfs/exec_spaw/0 &

doas /usr/libexec/gvfsd-metadata &

doas /usr/libexec/at-spi-bus-launcher &

doas /usr/libexec/at-spi2-registryd --use-gnome-session &


# if running dwm or other simple tiling window manager desktop, then enable the following

# dunst is a GUI notify daemon replacement

#if pgrep dunst; then pkill dunst ; fi

if [ ${XDG_CURRENT_DESKTOP} == "" ]; then

dunst &

fi

xinput set-prop "ASUE140A:00 04F3:3134 Touchpad" "Synaptics Two-Finger Scrolling" 1, 1
xinput set-prop "ASUE140A:00 04F3:3134 Touchpad" "Synaptics Tap Action" 0, 0, 0, 1, 1, 3, 2
