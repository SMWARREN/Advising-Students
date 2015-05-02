# The Advising Student Problem in C++
## Using Semaphores
-Sean Warren

----------------------------------------------------------------------------------------------
# The Problem
----


At a particular college, there are two admissions counselors, and five parking spots near the admissions office for visitors. There are 100 prospective students driving around trying to park and perform their admissions interview. When a prospective student sees a parking spot, he/she (generic he from now on as your book uses) pull into the spot, wait to be advised and then leave(freeing a parking lot space for one of the ones driving around). The advisors will advise a prospective student and then select one of the remaining students in the parking lot to advise next. If there are no prospective students in the parking lot, the tired advisor snoozes at his desk. You will need your program to start 100 "prospective student" threads and two councilor threads. Each thread should print a message when it is created. Students should print when they get parking spaces and when they are advised.

> For my project, I created 4 Semaphores. A semaphore is a variable or abstract data type that is used for controlling multipe processes, to a common resource. In my project I used two Binary Semaphores which are for The AdvisingSleeping and IamDoneBeingAdvised and I also used a counting Semaphores which are for the Parking Spots and Being advised. THroughtout my project I have the Students and Advisors working with eachother. The two groups work together because the advisor will wait on the semaphore , and then the student will unblock the semaphore to be used again. 

-----------------------------------------------------------

``` C++
  // initializing the semaphores to be used
    sem_init(&ParkingSpots, 0, 5);
    //limits the number of parking spots
    sem_init(&BeingAdvised, 0, 2);
    //lets the advisor sleep until student arrives
    sem_init(&AdvisorSleeping, 0, 0);
    //lets the student wait to be done advising
    sem_init(&IamDoneBeingAdvised, 0, 0); 
 

-----------------------------------------------------------
//To wait on a semaphore, use sem_wait:
      int sem_wait(sem_t *sem);
//If the value of the semaphore is negative, the calling process blocks; one of the blocked processes wakes up when another process calls sem_post.

//To increment the value of a semaphore, use sem_post:
      int sem_post(sem_t *sem); 
//It increments the value of the semaphore and wakes up a blocked process waiting on the semaphore, if any.
```
------------------------------------------------------------------------

The only problem that I can find is that the students, dont get advised in order 0-100 they, get advised based on when the thread was created. Also, I didn't implement a random time variable, so each print statement waits the same exact time, even though the functions should sleep at different times.
