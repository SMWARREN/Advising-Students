//Sean Warren - Adivsing Students

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//creating used semaphores
sem_t ParkingSpots;
sem_t BeingAdvised;
sem_t AdvisorSleeping;
sem_t IamDoneBeingAdvised;

//initializing used ints
int NoMoreStudents = 0;
int Advisor = 2;
int Students = 100;
int ParkingSpots1 = 5;

//function prototypes so you can use the functions in any namespace
void *advisors(void *argument);
void *students(void *argument);

int main(){
    //initializing used pthreads,i,Students Num array and Advisor Num array
    pthread_t advisors1[Advisor];
    pthread_t students1[Students];
    int i;
    int StudentsNum[Students];
    int AdvisorNum[Advisor];
    
    // initializing the semaphores to be used
    sem_init(&ParkingSpots, 0, ParkingSpots1);
    //limits the number of parking spots
    sem_init(&BeingAdvised, 0, Advisor);
    //lets the advisor sleep until student arrives
    sem_init(&AdvisorSleeping, 0, 0);
    //lets the student wait to be done advising
    sem_init(&IamDoneBeingAdvised, 0, 0); 
  
    //for loop that creates the advisors as well as the advisor number
    for (i=0; i<Advisor; i++) {
        AdvisorNum[i] = i;
        pthread_create(&advisors1[i], NULL, advisors, (void *)&AdvisorNum[i]);
    }
// for loop that creates the students as well as the students number
    for (i=0; i<Students; i++) {
        StudentsNum[i] = i;
        pthread_create(&students1[i], NULL, students, (void *)&StudentsNum[i]);
    }
    // this is a for loop that joins the students, so they wait until the last thread is finished
    for (i=0; i<Students; i++) {
	pthread_join(students1[i],NULL);
    }
  // this is used to end the while loop
    NoMoreStudents = 1;
    //this semaphore  increments the advisorSleeping semaphore
    sem_post(&AdvisorSleeping); 
    //this is destroying all of the used semaphores where the program is done
    sem_destroy(&ParkingSpots);
    sem_destroy(&BeingAdvised);
    sem_destroy(&AdvisorSleeping);
    sem_destroy(&IamDoneBeingAdvised);  
  	
}

void *students(void *argument) {
    //creates the student number variable the the casted argument
    int StudentNumber = *(int *)argument;
    //prints that the students are driving to school
    printf("Student %d is Driving to The School.\n", StudentNumber);
   //lets the thread sleep to show that a student is driving to school
    sleep(1);
    //prints that the student is looking for a Parking Lot
    printf("Student %d is looking for a Parking Lot.\n", StudentNumber);
   //decrements the value of the semaphore until it reaches 0, when it equals 0 the process blocks
    sem_wait(&ParkingSpots);
    //prints the student has found a parking spot
    printf("Student %d found a Parking Spot and is parking.\n", StudentNumber);
    sem_wait(&BeingAdvised);
    //decrements the value of the semaphore to block other threads
    // prints the student is being advised
    printf("Student %d is being Advised\n", StudentNumber);
   //this increments the value of the semaphore and wakes the blocked process waiting
    sem_post(&AdvisorSleeping);
    //this decrements the semaphore which blocks other from being advised
    sem_wait(&IamDoneBeingAdvised);
    //this increments the value of the semaphore and wakes up other blocked thread
    sem_post(&BeingAdvised);
    //prints the student is advised and is leaving
    printf("Student %d has been advised and is leaving.\n", StudentNumber);
}

void *advisors(void *argument) {
    //creates the advisor number variable
    int AdvisorNumber = *(int *)argument;
   //while there is students
    while (!NoMoreStudents) {
        //print the advisor is waiting
        printf("Advisor %d is waiting for a Student\n", AdvisorNumber);
        //decrement the advisor sleeping , which will block processes when it is negative
	sem_wait(&AdvisorSleeping);
        //this frees up a parking spot, by incrementing the parkingSpots Semaphore
        sem_post(&ParkingSpots);
        //if there is more students
       if (!NoMoreStudents) {
           //print the advisor is advising
	    printf("Advisor %d is Advising\n", AdvisorNumber);
           // puts the thread to sleep to simulate advising
	    sleep(2);
           //prints the advisor is finished
	    printf("Advisor %d has finished Advising.\n", AdvisorNumber);
            //increments the iamdonebeing advised semaphore,which lets another user be advised
	    sem_post(&IamDoneBeingAdvised);
	}
        //if there is no more students
	else {
           //print there are no more students and print the advisors are going home for the day.
         printf("There are No More Students To Advise.\n");
         printf("Advisors are going home for the day \n.");
	}
      
    }
    
}
