#!/bin/bash

# Function to increase volume using pactl
increase_volume() {
    for sink in {0..10}; do
        pactl set-sink-volume "$sink" +5%
    done
}

increase_volume
