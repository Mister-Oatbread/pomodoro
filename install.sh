#!/usr/bin/bash

# this script compiles the program and throws it into the .local/bin directory

rm -f ~/.local/bin/pomodoro
gcc ./main.c -o main -lm
chmod +x main
mv main ~/.local/bin/pomodoro


