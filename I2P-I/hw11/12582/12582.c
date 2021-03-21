#include "function.h"


void job1(void* argument) {
    Data *t = argument;
    for (int i = t->lower; i <= (t->lower + t->upper)/2; i++) {
        int tmp = t->arr[i];
        t->arr[i] = t->arr[t->upper - (i - t->lower)];
        t->arr[t->upper - (i - t->lower)] = tmp;
    }
} // square? reverse

void job2(void* argument) {
    Data *t = argument;
    for (int i = t->lower; i <= t->upper; i++) {
        t->arr[i] *= -1;
    }
} // minus

void job3(void* argument) {
    Data *t = argument;
    for (int i = t->lower; i <= t->upper; i++) {
        t->arr[i] *= 2;
    }
} // double

void initTask(Task* task, void(*func)(void*),void* argument) {
    task->func = func;
    task->argument = argument;
}

void executeTasks(Task_List *task_list) {
    for (int i = 0; i < task_list->size; i++)
        task_list->tasks[i]->func(task_list->tasks[i]->argument);
}

