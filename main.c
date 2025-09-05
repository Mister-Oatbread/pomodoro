

/**
 * This file includes the main contents for the pomodoro program
 * Author: Mister Oatbread
 */

// includes
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

/**
 * This struct contains different parameters bundled together that the pomodoro timer uses
 */
typedef struct pomodoro_parameters {
    int learning_duration;
    int break_duration;
} pomodoro_parameters;

/**
 * This container houses the time format that is used in this program
 * The variable time will be a long of at most six digits, that follows the format
 * HHMMSS for hour, minute, and second respectively.
 * At 00:00:00, this long will be zero, but 01:00:00 will be 10000.
 */
typedef struct time_container {
    short sec;
    short min;
    short hour;
    long time;
} time_container;

// function prototypes
void print_time_container(const time_container *const p_time_container);
void print_status(const int time_difference, const pomodoro_parameters *const p_params, const bool learning_interval_active);
bool investigate_switch(const long time_difference, const pomodoro_parameters *const params, const bool learning_interval_active);
void update_time(time_container *p_current_time);

// main
int main() {
    printf("Welcome to the Pomodoro Program by Mister Oatbread\n\n");

    // initialize time containers
    time_container current_time;
    time_container start_of_last_phase;
    time_container last_print;

    time_container *p_current_time = &current_time;
    time_container *p_start_of_last_phase = &start_of_last_phase;
    time_container *p_last_print = &last_print;
    update_time(p_start_of_last_phase);
    update_time(p_last_print);

    // initialize other important stuff
    pomodoro_parameters params = {.learning_duration = 103,
                                    .break_duration = 5};

    bool learning_interval_active = true;
    bool switch_is_needed;
    int remaining_time;
    long current_time_difference;

    // main loop
    while (true) {
        update_time(p_current_time);

        // check if a toggle between the two phases is necessary
        // this is off by one, hence adding 1 at the end to make this happen one second earlier
        current_time_difference = p_current_time->time - p_start_of_last_phase->time + 1;
        switch_is_needed = investigate_switch(current_time_difference, &params, learning_interval_active);
        if (switch_is_needed) {
            learning_interval_active = !(learning_interval_active);
            update_time(p_start_of_last_phase);
        }

        // update the display if necessary
        remaining_time = p_current_time->time - p_start_of_last_phase->time;
        if (p_current_time->time != p_last_print->time) {
            update_time(p_last_print);
            print_status(remaining_time, &params, learning_interval_active);
            // printf("current time: %ld\n", p_current_time->time);
            // printf("last switch: %ld\n", p_start_of_last_phase->time);
        }
    }
    return 0;
}

/**
 * prints out the complete status of a time container
 * this is mainly intended for debugging purposes.
 */
void print_time_container(const time_container *const p_time_container) {
    printf("time: %ld\n", p_time_container->time);
    // printf("sec: %d\n", p_time_container->sec);
    // printf("min: %d\n", p_time_container->min);
    // printf("hour: %d\n", p_time_container->hour);
}

/**
 * prints some information on the state and how much time is left
 */
void print_status(const int time_difference, const pomodoro_parameters *const p_params, const bool learning_interval_active) {
    // remove last line
    // printf("\033[A\033[2K");

    int threshold;
    float time_remaining;
    char current_phase[12];
    if (learning_interval_active) {
        threshold = p_params->learning_duration;
        strncpy(current_phase,"learning",12);
    } else {
        threshold = p_params->break_duration;
        strncpy(current_phase,"resting",12);
    }

    time_remaining = (float)(threshold - time_difference);
    time_remaining = ceil(time_remaining/100);

    // final message
    printf("currently at: %s | minutes until next phase: %2.0f\n", current_phase, time_remaining);
}

/**
 * handles the logic if a switch should happen
 */
bool investigate_switch(const long time_difference, const pomodoro_parameters *const p_params, const bool learning_interval_active) {
    int threshold;

    if (learning_interval_active) {
        threshold = p_params->learning_duration;
    } else {
        threshold = p_params->break_duration;
    }
    // g'day mate :D !!!

    if (time_difference > threshold) {
        return true;
    } else {
        return false;
    }
}

/**
 * returns the current time in the time container format
 */
void update_time(time_container *p_current_time) {
    // get time from time_t
    time_t time_raw;
    time(&time_raw);
    struct tm time;
    time = *(localtime(&time_raw));

    // write to time container
    p_current_time->sec = time.tm_sec;
    p_current_time->min = time.tm_min;
    p_current_time->hour = time.tm_hour;
    p_current_time->time = time.tm_hour*10000 + time.tm_min*100 + time.tm_sec;
}


