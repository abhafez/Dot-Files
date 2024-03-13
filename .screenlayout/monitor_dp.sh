#!/bin/sh

# List all connected outputs and their modes
OUTPUTS=$(xrandr | grep ' connected')

# Loop through each output to find matching DP outputs with the desired mode
for OUTPUT in $OUTPUTS; do
	if [[ $OUTPUT == DP* ]]; then
		# Check if the output supports the desired mode
		MODE=$(xrandr --query | grep "$OUTPUT" -A10 | grep "2560x1440")
		if [ ! -z "$MODE" ]; then
			# If the mode exists, set this output as primary and break the loop
			xrandr --output eDP1 --off --output $OUTPUT --primary --mode 2560x1440 --pos 0x0 --rotate normal
			echo "Set $OUTPUT as primary with mode 2560x1440."
			break
		fi
	fi
done
