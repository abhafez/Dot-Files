#!/bin/bash

# Function to decrease volume using pactl
decrease_volume() {
    for sink in {0..10}; do
        pactl set-sink-volume "$sink" -5%
    done
}

decrease_volume
