#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<pthread.h>

pthread_barrier_t barr;
pthread_key_t key;

void print(){
  int my_id = (int)pthread_getspecific(key);
  printf("my id : %d\n", my_id);
}

void *worker(void *temp){
  
  int my_id = (int) temp;
  if(my_id == 0){
    pthread_key_create(&key, NULL);
  }        
  pthread_barrier_wait(&barr);
  pthread_setspecific(key, (const void *)(my_id+1));
  
  print();

}

void parallel_print(int p){
  int i;
  pthread_t *pid_list;
  pthread_attr_t attr;
  
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);

  // Barrier initialization
  if(pthread_barrier_init(&barr, NULL, p)) {
    printf("Could not create a barrier\n");
    return -1;
  }

  pid_list = (pthread_t *)malloc(p*sizeof(pthread_t));
  for(i=0;i<p;i++){
    pthread_create(&pid_list[i],&attr,worker,(void *)i);
  }
  for(i=0;i<p;i++){
    pthread_join(pid_list[i],NULL);
  }
}

int main(int argc, char **argv){
  int pr = atoi(argv[1]);
  
  parallel_print(pr);
  return 0;
}

