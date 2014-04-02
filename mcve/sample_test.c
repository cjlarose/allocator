/*  file name: sample_test.c
 *  desc:      Sample testcase for program 2 of CSc 422 Spring 2011
 *             This testcase could be used for multithread myMalloc libraries (i.e. version 2, 3 and 4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "myMalloc.h"

#define SIZE 10

void *test3(void*c){
    int i;
    int *array[SIZE];
    printf("test1() start\n");
    //malloc memory for SIZE integers, and write some number into it.
    for(i=0;i<SIZE;i++){
        array[i] = (int *)myMalloc(sizeof(int));
        if(!array[i]){
            printf("error: myMalloc() at %dth iteration\n",i);
            break;
        }
        *(array[i]) = i;    
    }
    //check if the values are correct
    for(i--;i>=0;i--){
        if(*(array[i]) != i)
            printf("error: invalid content at array[%d]\n",i);
        myFree(array[i]);
    }
    printf("test1 done\n");
    return NULL;
}

int main(int argc, char **argv){
    //get parameter    
    if(argc!=2)
        printf("usage: %s num_of_cores\n", argv[0]);
    int pr = atoi(argv[1]);
    if(pr<=0){
        printf("invalid parameter\n");
        exit(EXIT_FAILURE);
    }

    //initialization
    if(myInit(pr)==-1){
        printf("init failed\n");
        exit(EXIT_FAILURE);
    }
    
    //create new threads
    int i;
    pthread_t *pid_list;
    pthread_attr_t attr;
  
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);

    pid_list = (pthread_t *)malloc(pr * sizeof(pthread_t));
    for(i=0;i<pr;i++){
        pthread_create(&pid_list[i],&attr,test3,NULL);
    }
    for(i=0;i<pr;i++){
        pthread_join(pid_list[i],NULL);
    }

    exit(EXIT_SUCCESS);
}
