#!/bin/bash

# Define your shortcuts here
shortcuts="\
Application Launchers

    Super + Alt + R: 🎨 Launch Emoji Picker (Rofi)
    Super + R: 🚀 Open Application Launcher (Rofi)

System Settings

    Super + Shift + R: 🖥️ Configure Displays (Arandr)
    Super + Shift + P: 🔊 Open Audio Controls (Pavucontrol)

Screen Layouts

    Super + Alt + F3: 📺 Set Dual Screen Layout
    Super + Alt + F1: 🖥️ Switch to External Monitor Layout
    Super + Alt + F2: 💻 Use Laptop Screen Only

Miscellaneous Shortcuts

    Super + BracketRight: 📸 Take Full Screen Screenshot
    Print: 🖼️ Open Screenshot Tool (Flameshot GUI)
    Super + Semicolon: ⌨️ Switch Keyboard Layout
    Super + Shift + N: 📁 Open File Manager (Thunar)
    Super + Shift + S: 💬 Launch Slack
    Super + Shift + L: 🔒 Lock Screen
    Super + Shift + F12: ⏻ Shutdown System
    Alt + Shift + F4: 🎧 Switch to Monitor Audio Output"

# Send the notification
dunstify "Shortcuts" "$shortcuts" -u high -r 99123 -t 10000
