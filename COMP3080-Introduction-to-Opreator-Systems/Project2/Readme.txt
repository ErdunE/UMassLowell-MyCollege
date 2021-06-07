pthreadsArgs.c: a small example of passing arguments to Pthread threads. Useful for project 1 Chapter 4

TA.c: a semaphore solution for the textbook Chapter 5 project 1 (sleeping TA) 

taskList.c: a solution for project 2 Chapter 3 of the textbook.  Includes indentation to highlight process
		hierarchy
		
Pthreads/dining.c: Pthreads semaphore basic solution to the dining philosopher's problem deadlock is possible

Pthreads/diningND.c: Pthreads semaphore solution to the dining philosophers's problem.  Eliminates deadlock
			by allowing only four philosophers to eat at a time (controled by the room semaphore)
			
Ptheads/diningMC.c: Pthreads mutex/condition variable solution to the dining philosopher's problem, deadlock
			is possible
			
Pthreads/diningMCND.c: Pthreads mutex/condition variable solution to the dining philosopher's problem.  Eliminates
			deadlock by allowing only four philosophers to eat at a time (controlled by room condition
			variable)
			
Pthreads/diningMC2Forks.c: Pthreads mutex/condition variable solution to the dining philosopher's problems. 
				Eliminates deadlock by making a philosopher take both forks at once (no
				piecemeal allocation)
				
Pthreads/diningMCNoStarvation.c:  same as above, but also prevents starvation

Pthreads/TeaDrinkers.c: healthy alternative to the class smoker's problem.  Three smoker's require paper, tobacco,
			matches to smoke.  Replaced with sugar, milk, lemon for tea.

To compile the programs in this zip file:

gcc -o base base.c -lpthread

replacing "base" with the basename of the particular program.

To run the programs:

./progname

replacing "progname" with the particular executable file. This form uses the defaults
for nanosleep(): 1,000,000,000 and 500,000,000 yielding sleep times between .5 and 1.5 seconds.

./progname range base
the same, except use the integers range and base to produce the sleep time: a number between
base and base + range nanoseconds.
