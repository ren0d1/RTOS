#ifndef PERIODIC_TASKS
#define PERIODIC_TASKS

#include <vector>

/* Structure to represent the periodic task */
struct periodic_task {
    int period; // in ms
    void (*job)();
};

namespace periodic_tasks {
    static void periodicTasksHandler(std::vector<periodic_task> tasks[], bool flag);
};

#endif
