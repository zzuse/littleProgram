#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *foo() {
    while (1){ ;}
}
int main()
{
    int i = 0;
    pthread_t thread;

    while (1) {
        if (pthread_create(&thread, NULL, foo, NULL) != 0)
            return;
        i ++;
        printf("i = %d\n", i);
    }
}
