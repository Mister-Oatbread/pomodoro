

/**
 * This file includes the main contents for the pomodoro program
 * Author: Mister Oatbread
 */

// includes
#include <stdio.h>
#include <stdlib.h>
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
 * The variable time will be a long of at most eight digits, that follows the format
 * DDHHMMSS for day, hour, minute, and second respectively.
 * At 00:00:00, this long will be zero, but 01:00:00 will be 10000.
 * Some issues may occur when running this program while the month is changing.
 */
typedef struct time_container {
    short sec;
    short min;
    short hour;
    short day;
    long time;
} time_container;

/**
 * This struct contains some logical information on the state of the program nicely bundled together.
 */
typedef struct program_status {
    bool learning_interval_active;
    bool switch_is_needed;
    bool program_is_running;
} program_status;

// function prototypes
void print_status(const int time_difference, const pomodoro_parameters *const p_params, const program_status status);
bool investigate_switch(const long time_difference, const pomodoro_parameters *const params, const program_status status);
void update_time(time_container *p_current_time);
void apply_last_state(time_container *p_start_of_last_phase, const pomodoro_parameters *p_params, bool learning_interval_active);
void save_last_state(const long current_time_difference, const bool learning_interval_active);

// main
int main() {
    printf("Welcome to the Pomodoro Program by Mister Oatbread\n\n\n");

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
    pomodoro_parameters params = {.learning_duration = 10,
                                    .break_duration = 5};

    program_status status = {.learning_interval_active = true,
                                        .switch_is_needed = false,
                                        .program_is_running = true};

    int remaining_time;
    long current_time_difference;

    // main loop
    while (true) {
        update_time(p_current_time);

        // check if a toggle between the two phases is necessary
        // this is off by one, hence adding 1 at the end to make this happen one second earlier
        current_time_difference = p_current_time->time - p_start_of_last_phase->time + 1;
        status.switch_is_needed = investigate_switch(current_time_difference, &params, status);
        if (status.switch_is_needed) {
            status.learning_interval_active = !(status.learning_interval_active);
            update_time(p_start_of_last_phase);
            system("aplay -q ./sounds/ping.wav");
        }

        // update the display if necessary
        remaining_time = p_current_time->time - p_start_of_last_phase->time;
        if (p_current_time->time != p_last_print->time) {
            update_time(p_last_print);
            print_status(remaining_time, &params, status);
        }

        // write current remaining time and active interval to text
    }
    return 0;
}

/**
 * prints some information on the state and how much time is left
 */
void print_status(const int time_difference, const pomodoro_parameters *const p_params, const program_status status) {
    // remove last line
    printf("\033[A\033[2K");

    // determine what should be shown in the final output
    int threshold;
    float time_remaining;
    char current_phase[12];
    if (status.learning_interval_active) {
        threshold = p_params->learning_duration;
        strncpy(current_phase,"learning",12);
    } else {
        threshold = p_params->break_duration;
        strncpy(current_phase,"resting",12);
    }

    time_remaining = (float)(threshold - time_difference);
    time_remaining = ceil(time_remaining/100);

    // final message
    printf("currently %s | less than%2.0f minutes until next phase\n", current_phase, time_remaining);
}

/**
 * handles the logic if a switch should happen
 */
bool investigate_switch(const long time_difference, const pomodoro_parameters *const p_params, const program_status status) {
    int threshold;

    if (status.learning_interval_active) {
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
    p_current_time->time = time.tm_mday;
    p_current_time->time = time.tm_mday*1000000 + time.tm_hour*10000 + time.tm_min*100 + time.tm_sec;
}

/**
 * this function serves to reverse engineer the last state of a program based on how it was left the last time
 * The memory file contains the time remaining for the next interval, as well as the current state (learing/resting)
 * In order to enact this state, the start of last phase has to be reverse engineered,
 * and the variable "learning_interval_active" will be adjusted
 */
void apply_last_state(time_container *p_start_of_last_phase, const pomodoro_parameters *p_params, bool learning_interval_active) {
    FILE *memory = fopen("pomodoro_memory.txt", "r");
    long last_remaining_time;
    bool last_learning_interval_active;
    if (memory) {
        fscanf(memory,
    }
    fclose(memory);
}

/**
 * This function can be called to write the latest state to the memory file
 * The memory file contains the time remaining for the next interval, as well as the current state (learing/resting)
 */
void save_last_state(const long current_time_difference, const bool learning_interval_active) {
    // create memory
    FILE *memory = fopen("pomodoro_memory.txt", "w+");

    // write program status
    if (memory) {
        fprintf(memory, "%ld %B\n", current_time_difference, learning_interval_active);
    }
    fclose(memory);
}


