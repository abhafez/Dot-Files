#!/bin/bash

ALERT_IF_IN_NEXT_MINUTES=10

# Function to get the next calendar event using gcalcli
get_next_event() {
	gcalcli agenda now 'now + 1d' | head -n 1
}

# Function to parse and display the event as a notification
display_notification() {
	# Use regex to extract time and title from the event string
	if [[ "$1" =~ ([0-9]{2}:[0-9]{2})\ +(.*)$ ]]; then
		time="${BASH_REMATCH[1]}"
		title="${BASH_REMATCH[2]}"

		echo "Time: $time"
		echo "Title: $title"
		# Convert event time to epoch
		event_start_epoch=$(date --date="today $time" +%s)
		current_epoch=$(date +%s)

		# Calculate the difference in minutes
		diff=$(((event_start_epoch - current_epoch) / 60))

		# Check if the event is within the next ALERT_IF_IN_NEXT_MINUTES minutes
		if [ "$diff" -ge 0 ] && [ "$diff" -le "$ALERT_IF_IN_NEXT_MINUTES" ]; then
			notify-send "Upcoming Event: $title" "Starts at $time (in $diff minutes)"
		fi
	fi
}

# Main logic
event=$(get_next_event)
if [ -n "$event" ]; then
	display_notification "$event"
else
	echo "No upcoming events found."
fi
