#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

/* Declaration of constants and variables */
#define DARTS 500000     /* number of throws at dartboard */
#define ROUNDS 100      /* number of times "darts" is iterated */
#define MASTER 0        /* task ID of master task */
#define FROM_MASTER 1   /* setting a message type */
#define FROM_WORKER 2   /* setting a message type */

double dboard(int darts);
#define sqr(x) ((x)*(x))

int main (int argc, char *argv[]){
   double homepi, pi, avepi, pirecv, pisum;
   int taskid, numtasks, source, mtype, rc, i, n;
   MPI_Status status;

   /* Initialize MPI */
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
   printf ("MPI task %d has started...\n", taskid);

   /* Set seed for random number generator equal to task ID */
   srandom (taskid);

   double start = MPI_Wtime();

   /* Initialize average pi value */
   avepi = 0;

   /* Main loop for dartboard algorithm */
   for (i = 0; i < ROUNDS; i++) {
      homepi = dboard(DARTS);

      /* Worker tasks send computed pi value to master */
      if (taskid != MASTER) {
         mtype = i;
         rc = MPI_Send(&homepi, 1, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
      } 
      else {
         /* Master task receives pi values from workers */
         mtype = i;
         pisum = 0;
         for (n = 1; n < numtasks; n++) {
            rc = MPI_Recv(&pirecv, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
                           mtype, MPI_COMM_WORLD, &status);
            pisum = pisum + pirecv;
            }
         /* Calculate average pi value for this iteration */
         pi = (pisum + homepi)/numtasks;
         /* Update average pi value over all iterations */
         avepi = ((avepi * i) + pi)/(i + 1); 
         printf("   After %8d throws, average value of pi = %10.8f\n",
                  (DARTS * (i + 1)),avepi);
         }    
   }

   double end = MPI_Wtime(); 

   /* Print real value of PI */
   if (taskid == MASTER)
      printf ("\nReal value of PI: 3.1415926535897 \n");
      printf ("Time taken : %f seconds\n",end-start);

   /* Finalize MPI */
   MPI_Finalize();
   return 0;
}

/**************************************************************************
* DESCRIPTION:
*   Used in pi calculation example codes. 
*   Throw darts at board.  Done by generating random numbers 
*   between 0 and 1 and converting them to values for x and y 
*   coordinates and then testing to see if they "land" in 
*   the circle."  If so, score is incremented.  After throwing the 
*   specified number of darts, pi is calculated.  The computed value 
*   of pi is returned as the value of this function, dboard. 
*
*   Explanation of constants and variables used in this function:
*   darts       = number of throws at dartboard
*   score       = number of darts that hit circle
*   n           = index variable
*   r           = random number scaled between 0 and 1
*   x_coord     = x coordinate, between -1 and 1
*   x_sqr       = square of x coordinate
*   y_coord     = y coordinate, between -1 and 1
*   y_sqr       = square of y coordinate
*   pi          = computed value of pi
****************************************************************************/

double dboard(int darts){
   long random(void);
   double x_coord, y_coord, pi, r; 
   int score, n;
   unsigned int cconst;  

   if (sizeof(cconst) != 4) {
      printf("Wrong data size for cconst variable in dboard routine!\n");
      printf("See comments in source file. Quitting.\n");
      exit(1);
   }
   cconst = 2 << (31 - 1);
   score = 0;

   for (n = 1; n <= darts; n++){
      r = (double)random()/cconst;
      x_coord = (2.0 * r) - 1.0;
      r = (double)random()/cconst;
      y_coord = (2.0 * r) - 1.0;

      if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
         score++;
   }

   pi = 4.0 * (double)score/(double)darts;
   return(pi);
} 
