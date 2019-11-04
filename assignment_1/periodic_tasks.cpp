#include <ctime>  // provides CLOCK_MONOTONIC, timespec and clock_gettime()
#include <cstdio> // provides printf()
#include <boost/math/common_factor.hpp> // provides gcd() and lcm()

#include "periodic_tasks.hpp"

/* Helper function to increment time by x ms*/
inline void addMsToTime(struct timespec *time, int ms) {
    int new_nsec = time->tv_nsec + ms % 1000 * 1000000; // using int instead of long because timespec specifies that tv_nsec valid values are [0, 999999999]
    time->tv_sec = time->tv_sec + ms / 1000 + new_nsec / 1000000000;
    time->tv_nsec = new_nsec % 1000000000;
}

/* Sleep until the next periodic activation */
inline void waitForNextActivation(timespec *time, int period) {

    /* Sleep for an absolute time */
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, time, nullptr);

    /* Calculate the time for the next periodic activation */
    addMsToTime(time, period);
}

/* This function is a cyclic executive allowing to run tasks periodically based on their respective periods in ms.
   This is the first entry to understanding RTOS. It also uses the concept of minor and major cycles. */
static void periodic_tasks::periodicTasksHandler(std::vector<periodic_task> tasks[], bool flag)
{
    /* Initialization */
    timespec starting_time{}; // defined in a MONOTONIC manner
    int minor_cycle = tasks->at(0).period; // GCD of tasks period
    for (int i = 0; i < tasks->size() - 1; i++) {
        minor_cycle = boost::math::gcd(minor_cycle, tasks->at(i + 1).period);
    }

    int major_cycle = tasks->at(0).period; // LCM of tasks period
    for (int i = 0; i < tasks->size() - 1; i++) {
        major_cycle = boost::math::lcm(major_cycle, tasks->at(i + 1).period);
    }

    int major_counter = 1;
    const int minor_cycles_in_major_cycle = major_cycle / minor_cycle;

    /* Setup timer */
    clock_gettime(CLOCK_MONOTONIC, &starting_time);
    addMsToTime(&starting_time, minor_cycle);

    uint64_t major_cycle_scheduling_table[minor_cycles_in_major_cycle];
    for(int i = 0; i < minor_cycles_in_major_cycle; i++) {
        uint64_t value = 0;
        for (int j = 0; j < tasks->size(); j++){
            if ((i * minor_cycle) % tasks->at(j).period == 0)
            {
                value +=  2 << j;
            }
        }
        major_cycle_scheduling_table[i] = value;
    }

    while (flag) {
        /* This is the beginning of the Major Cycle */
        printf("\nMajor cycle # %d\n", major_counter);

        for(int i = 0; i < minor_cycles_in_major_cycle; i++) {
            waitForNextActivation(&starting_time, minor_cycle);
            printf("Time: %dms\n", (major_counter - 1) * major_cycle + i * minor_cycle);
            for(int j = 0; j < tasks->size(); j++) {
                int task_presence = major_cycle_scheduling_table[i] & (uint64_t) (2 << j);
                if (task_presence != 0) {
                    tasks->at(j).job();
                }
            }
            printf("\n");
        }

        /* Update the counter of the major cycle */
        major_counter++;
    }
}
