#include <pthread.h>
#include <stdio.h>
void* incr(void* arg)
{
  int *ptr;
  ptr=((int*)arg);
  printf("digit: %d\n", *ptr);
}

int main(void)
{
  pthread_t tid[3];
  for(int i=1;i<=3;i++)
  {
    pthread_create(&tid[i-1],NULL,incr,&i);
    pthread_join(tid[i-1],NULL);
  }
  return 0;
}
