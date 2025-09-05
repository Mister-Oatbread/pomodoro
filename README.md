

# Pomodoro Program
This program is a command line utility that helps you study with the [pomodoro technique](https://en.wikipedia.org/wiki/Pomodoro_Technique).
This tool will play a sound every time you go from work to pause and vice versa.

## Installation
In order to install this program, follow these steps:

Clone this repository into a directory of your choice (e.g. ~).
```
    cd ~
    git clone https://github.com/Mister-Oatbread/pomodoro.git && cd pomodoro
```

There is an install script that takes care of compiling the program.
Make it executable and execute it.
```
    chmod +x install.sh && ./install.sh
```
The executable can be found in `~/.local/bin`

## Usage
Simply type
```
    pomodoro
```
into your shell, and the program will start automatically.
A ping sound will play every time a phase switch occurs.


