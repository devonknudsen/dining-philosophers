
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t *phils;
pthread_mutex_t *chopstix;
int NUM_PHILS;
int TIMES_EAT;

void eat(int p) {
  printf("Philosopher %d is eating...\n", p);
  sleep(1);
  }

void *run(void *param){
    int leftStick, rightStick, i, timesEaten = 0;
    while(pthread_equal(*(phils+i),pthread_self()) == 0 && i < NUM_PHILS){
      i++;
    }

    int j = 0;
    while(timesEaten != TIMES_EAT) {
      leftStick = i;
      rightStick = (i + 1) % NUM_PHILS;
      printf("Philosopher %d is thinking...\n", i);
      if(i % 2 != 0){
      	while(pthread_mutex_lock(chopstix + leftStick) != 0) {
	      	sleep(1);
      	}
      	while(pthread_mutex_lock(chopstix + rightStick) != 0){
	      	sleep(1);
      	}
      }
      else{
		    while(pthread_mutex_lock(chopstix + rightStick) != 0){
				  sleep(1);
			  }
		    while(pthread_mutex_lock(chopstix + leftStick) != 0) {
				  sleep(1);
			  } 
      }

      eat(i);
      timesEaten++;

      if(i % 2 != 0){
      	pthread_mutex_unlock(chopstix + leftStick);
      	pthread_mutex_unlock(chopstix + rightStick);
      }
      else{
		    pthread_mutex_unlock(chopstix + rightStick);
        pthread_mutex_unlock(chopstix + leftStick);
      }
    }
    return NULL;
}


int main(int argc, char const *argv[]) {

  NUM_PHILS = atoi(argv[2]);
  TIMES_EAT = atoi(argv[1]);
  
  if(NUM_PHILS > 1){
	  phils = malloc(sizeof(pthread_t) * NUM_PHILS);
	  chopstix = malloc(sizeof(pthread_mutex_t) * NUM_PHILS);

	  for(int i = 0; i < NUM_PHILS; i++) {
		if (pthread_create(phils + i, NULL, run, NULL) == 0)
		  printf("Philosopher %d took a seat at the table\n", i);
	  }

	  for(int k = 0; k < NUM_PHILS; k++)
		pthread_join(*(phils + k), NULL);

	  free(phils);
	  free(chopstix);
	}

  return 0;
}
