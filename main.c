

/**
 * This file includes the main contents for the pomodoro program
 * Author: Mister Oatbread
 */

// includes
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef struct pomodoro_parameters {
    int learning_duration;
    int break_duration;
} pomodoro_parameters;

// function prototypes
bool investigate_switch(long current_time, pomodoro_parameters *params, bool learning_interval_active);
long get_time_in_phase(long start_of_last_phase);
long get_time();
long construct_current_time();

// main
int main() {
    printf("Welcome to the pomodoro program by Mister Oatbread\n");

    long current_time;
    long start_of_last_phase;


    pomodoro_parameters params = {.learning_duration = 2500,
                                    .break_duration = 500};

    bool learning_interval_active = true;
    bool switch_is_needed;

    for(int i=0; i<10; i++) {
        start_of_last_phase = 0;
        current_time = get_time_in_phase(start_of_last_phase);
        switch_is_needed = investigate_switch(current_time, &params, learning_interval_active);

        printf("%ld\n", current_time);
    }
    return 0;
}

bool investigate_switch(long current_time, pomodoro_parameters *params, bool learning_interval_active) {
    int threshold;

    if (learning_interval_active) {
        threshold = params->learning_duration;
    } else {
        threshold = params->break_duration;
    }

    if (current_time  > threshold) {
        return true;
    } else {
        return false;
    }
}

void print_time() {
}

/**
 * returns the time in minutes and seconds relative to the last time a phase shift occurred
 */
long get_time_in_phase(time_t start_of_last_phase) {
    long current_time = construct_current_time();
    return current_time - start_of_last_phase;
}

/**
 * returns the time in minutes and seconds
 */
long get_time() {
    long current_time = construct_current_time();
    return current_time;
}

/**
 * This function takes a time and slaps it into the required format for this program
 */
long construct_current_time() {
    time_t now_raw;
    time(&now_raw);
    struct tm now;
    now = *(localtime(&now_raw));

    long current_time = now.tm_hour*10000 + now.tm_min*100 + now.tm_sec;
    return current_time;
}


