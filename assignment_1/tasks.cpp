#include <cstdio>
#include <cstdint>
#include <sys/time.h>

namespace tasks {
    /* Job body of the first task */
    static void task1() {

        /* Dummy loop */
        for (int i = 0; i < 3; i++);
        for (int j = 0; j < 1000; j++);

        /* Print the name of the task */
        printf("T1 ");
        fflush(stdout);

    }

    /* Job body of the second task */
    static void task2() {

        /* Dummy loop */
        for (int i = 0; i < 5; i++);
        for (int j = 0; j < 10000; j++) ;

        /* Print the name of the task */
        printf("T2 ");
        fflush(stdout);

    }

    /* Job body of the third task */
    static void task3() {

        static uint64_t previous;
        uint64_t t;
        struct timeval tv{};

        /* Obtain the start time of the job */
        if (previous == 0) {
            gettimeofday(&tv, nullptr);
            previous = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
        }

        /* Obtain the current time of the job */
        gettimeofday(&tv, nullptr);
        t = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;

        /* Print the name of the task */
        printf("T3\t\tTime since last T3: %lums", t - previous);

        /* Update the previous time */
        previous = t;

    }
}