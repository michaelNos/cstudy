/*
 * File name: threads.c
 * Date:      2016/11/03 07:24
 * Author:    Jan Faigl
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <termios.h> 
#include <unistd.h>  // for STDIN_FILENO

#include <threads.h>

#define PERIOD_STEP 10
#define PERIOD_MAX 2000
#define PERIOD_MIN 10

typedef struct {
   int alarm_period;
   int alam_counter;
   bool quit;
} data_t;

mtx_t mtx;
cnd_t cond;

void call_termios(int reset);

int input_thread(void*);
int output_thread(void*);
int alarm_thread(void*);

// - main function -----------------------------------------------------------
int main(int argc, char *argv[])
{
   data_t data = { .alarm_period = 100, .alam_counter = 0, .quit = false };

   enum { INPUT, OUTPUT, ALARM, NUM_THREADS };
   const char *threads_names[] = { "Input", "Output", "Alarm" };

   int (*thr_functions[])(void*) = { input_thread, output_thread, alarm_thread };

   thrd_t threads[NUM_THREADS];
   mtx_init(&mtx, mtx_plain); // initialize mutex 
   cnd_init(&cond); // initialize condition variable 

   call_termios(0);

   for (int i = 0; i < NUM_THREADS; ++i) {
      int r = thrd_create(&threads[i], thr_functions[i], &data);
      fprintf(stderr, "Create thread '%s' %s\n", threads_names[i], ( r == 0 ? "OK" : "FAIL") );
   }

   int ex;
   for (int i = 0; i < NUM_THREADS; ++i) {
      fprintf(stderr, "Call join to the thread %s\n", threads_names[i]);
      int r = thrd_join(threads[i], (void*)&ex);
      fprintf(stderr, "Joining the thread %s has been %s - exit value %i\n", threads_names[i], (r == 0 ? "OK" : "FAIL"), ex);
   }

   call_termios(1); // restore terminal settings
   return EXIT_SUCCESS;
}

// - function -----------------------------------------------------------------
void call_termios(int reset)
{
   static struct termios tio, tioOld;
   tcgetattr(STDIN_FILENO, &tio);
   if (reset) {
      tcsetattr(STDIN_FILENO, TCSANOW, &tioOld);
   } else {
      tioOld = tio; //backup 
      cfmakeraw(&tio);
      tio.c_lflag &= ~ECHO; // assure echo is disabled
      tio.c_oflag |= OPOST; // enable output postprocessing
      tcsetattr(STDIN_FILENO, TCSANOW, &tio);
   }
}

// - function -----------------------------------------------------------------
int input_thread(void* d)
{
   data_t *data = (data_t*)d;
   static int r = 0;
   int c;
   while (( c = getchar()) != 'q') {
      mtx_lock(&mtx);
      int period = data->alarm_period;
      switch(c) {
	 case 'r': 
	    period -= PERIOD_STEP;
	    if (period < PERIOD_MIN) {
	       period = PERIOD_MIN;
	    }
	    break;
	 case 'p': 
	    period += PERIOD_STEP;
	    if (period > PERIOD_MAX) {
	       period = PERIOD_MAX;
	    }
	    break;
      }
      if (data->alarm_period != period) {
	 cnd_signal(&cond);
      }
      data->alarm_period = period;
      mtx_unlock(&mtx);
   }
   r = 1;
   mtx_lock(&mtx);
   data->quit = true;
   cnd_broadcast(&cond);
   mtx_unlock(&mtx);
   fprintf(stderr, "Exit input thread\n");
   return r;
}

// - function -----------------------------------------------------------------
int output_thread(void* d)
{
   data_t *data = (data_t*)d;
   static int r = 0;
   bool q = false;
   while (!q) {
      mtx_lock(&mtx);
      cnd_wait(&cond, &mtx); // wait for next event
      q = data->quit;
      printf("\rAlarm time: %10i   Alarm counter: %10i", data->alarm_period, data->alam_counter);
      fflush(stdout);
      mtx_unlock(&mtx);
   }
   fprintf(stderr, "Exit output thread\n");
   return r;
}

// - function -----------------------------------------------------------------
int alarm_thread(void* d) 
{
   data_t *data = (data_t*)d;
   static int r = 0;
   mtx_lock(&mtx);
   bool q = data->quit;
   useconds_t period = data->alarm_period * 1000; // alarm_period is in ms
   mtx_unlock(&mtx);

   while (!q) {
      usleep(period);
      mtx_lock(&mtx);
      q = data->quit;
      data->alam_counter += 1;
      period = data->alarm_period * 1000; // update the period is it has been changed
      cnd_broadcast(&cond);
      mtx_unlock(&mtx);
   }
   fprintf(stderr, "Exit alarm thread\n");
   return r;
}

/* end of threads.c */
