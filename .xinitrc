setxkbmap -layout us,ara -variant ,digits -option grp:alt_space_toggle,caps:escape,shift:both_capslock

exec dwm

export $(dbus-launch --exit-with-session)

#dbus-update-activation-environment --all

gnome-keyring-daemon --start --components=gpg,pkcs11,secrets,ssh

/usr/libexec/gvfsd &

/usr/libexec/gvfs-udisks2-volume-monitor &

/usr/libexec/gvfs-goa-volume-monitor &

/usr/libexec/gvfs-afc-volume-monitor &

/usr/libexec/gvfs-mtp-volume-monitor &

/usr/libexec/gvfs-gphoto2-volume-monitor &

/usr/libexec/gvfsd-trash --spawner :1.4 /org/gtk/gvfs/exec_spaw/0 &

/usr/libexec/gvfsd-metadata &

/usr/libexec/at-spi-bus-launcher &

/usr/libexec/at-spi2-registryd --use-gnome-session &


# if running dwm or other simple tiling window manager desktop, then enable the following

# dunst is a GUI notify daemon replacement

#if pgrep dunst; then pkill dunst ; fi

if [ ${XDG_CURRENT_DESKTOP} == "" ]; then

dunst &

fi

