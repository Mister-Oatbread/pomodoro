

/**
 * This file includes the main contents for the pomodoro program
 * Author: Mister Oatbread
 */

// includes
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

typedef struct pomodoro_parameters {
    int learning_duration;
    int break_duration;
} pomodoro_parameters;

typedef struct time_container {
    short sec;
    short min;
    short hour;
    long time;
} time_container;

// function prototypes
void print_remaining_time(const int remaining_time, const pomodoro_parameters *const p_params, const bool learning_interval_active);
bool investigate_switch(const time_container *p_current_time, const pomodoro_parameters *const params, const bool learning_interval_active);
void update_time(time_container *p_current_time);

// main
int main() {
    printf("Welcome to the Pomodoro Program by Mister Oatbread\n");

    // initialize time containers
    time_container current_time;
    time_container start_of_last_phase;
    time_container *p_current_time = &current_time;
    time_container *p_start_of_last_phase = &start_of_last_phase;
    update_time(p_start_of_last_phase);

    // initialize other important stuff
    pomodoro_parameters params = {.learning_duration = 3,
                                    .break_duration = 3};

    bool learning_interval_active = true;
    bool switch_is_needed;
    int remaining_time;

    // main loop
    while (true) {
        update_time(p_current_time);

        // check if a toggle between the two phases is necessary
        switch_is_needed = investigate_switch(p_current_time, &params, learning_interval_active);
        if (switch_is_needed) {
            learning_interval_active = !(learning_interval_active);
            update_time(p_start_of_last_phase);
        }

        // update the display if necessary
        remaining_time = p_current_time->min - p_start_of_last_phase->min;
        if (p_current_time->sec != p_start_of_last_phase->sec) {
            print_remaining_time(remaining_time, &params, learning_interval_active);
        }
    }
    return 0;
}

/**
 * prints some information on the state and how much time is left
 */
void print_remaining_time(const int remaining_time, const pomodoro_parameters *const p_params, const bool learning_interval_active) {
    // remove last line
    printf("\033[A\033[2K");

    int threshold;
    int time_remaining;
    char current_phase[12];
    if (learning_interval_active) {
        threshold = p_params->learning_duration;
        strncpy(current_phase,"learning",12);
    } else {
        threshold = p_params->break_duration;
        strncpy(current_phase,"resting",12);
    }

    time_remaining = threshold - remaining_time;

    printf("currently at: %s | time until next phase: %d", current_phase, threshold);
}

/**
 * handles the logic if a switch should happen
 */
bool investigate_switch(const time_container *p_current_time, const pomodoro_parameters *const p_params, const bool learning_interval_active) {
    int threshold;

    if (learning_interval_active) {
        threshold = p_params->learning_duration;
    } else {
        threshold = p_params->break_duration;
    }
    // gday mate :D !!!

    if (p_current_time->time > threshold) {
        return true;
    } else {
        return false;
    }
}

/**
 * returns the time in minutes and seconds relative to the last time a phase shift occurred
 */
void update_time(time_container *p_current_time) {
    time_t now_raw;
    time(&now_raw);
    struct tm now;
    now = *(localtime(&now_raw));

    p_current_time->sec = now.tm_sec;
    p_current_time->min = now.tm_min;
    p_current_time->hour = now.tm_hour;
    p_current_time->time = now.tm_hour*10000 + now.tm_min*100 + now.tm_sec;
}


