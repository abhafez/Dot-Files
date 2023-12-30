#!/bin/bash

# Function to toggle mute for sinks using pactl
toggle_mute() {
    for sink in {0..10}; do
        pactl set-sink-mute "$sink" toggle
    done
}

# Call the function to toggle mute
toggle_mute