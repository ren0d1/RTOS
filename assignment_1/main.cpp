#include <cstdio>
#include <vector>
#include "periodic_tasks.cpp"
#include "tasks.cpp"
using namespace tasks;

/* Main program */
int main(int argc, char *argv[]) {
    std::vector<periodic_task> tasks = {{60, task1}, {80, task2}, {120, task3}};
    periodic_tasks::periodicTasksHandler(&tasks, true);
}