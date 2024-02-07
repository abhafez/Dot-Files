#!/bin/bash

# Find the connected HDMI display
HDMI_CONNECTED=$(xrandr | grep " connected" | grep -oE '^HDMI-[0-9]')

if [ -z "$HDMI_CONNECTED" ]; then
	echo "No HDMI display connected."
	exit 1
fi

echo "HDMI Display Connected: $HDMI_CONNECTED"

# Get the maximum resolution for the connected HDMI
MAX_RESOLUTION=$(xrandr | grep "$HDMI_CONNECTED" -A1 | tail -n 1 | awk '{print $1}')

if [ -z "$MAX_RESOLUTION" ]; then
	echo "Could not find maximum resolution for $HDMI_CONNECTED."
	exit 1
fi

if [ -z "$HDMI_CONNECTED" && "$MAX_RESOLUTION" ]; then
	echo "HDMI display is not connected."
	exit 1
fi

echo "Maximum Resolution: $MAX_RESOLUTION"

# Set the HDMI output to its maximum resolution
# Uncomment the following line if you want to apply the resolution change
xrandr --output $HDMI_CONNECTED --mode $MAX_RESOLUTION --output eDP-1 --off

echo "$HDMI_CONNECTED is set to its maximum resolution: $MAX_RESOLUTION"

# set wallpaper
bash ~/.fehbg
# set keyboard setting
bash ~/.kb.sh
