#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int data;
pthread_mutex_t m;

void increment() {
    pthread_mutex_lock(&m);
    data++;
    pthread_mutex_unlock(&m);
}

void double_increment() {
    pthread_mutex_lock(&m);
    increment();
    increment();
    pthread_mutex_unlock(&m);
}

void* worker(void*) {
    double_increment();
    return NULL;
}

int main() {
    pthread_t id;
    assert(pthread_create(&id, NULL, worker, NULL) == 0);
    assert(pthread_join(id, NULL) == 0);
    printf("data is %d\n", data);
    return 0;
}

