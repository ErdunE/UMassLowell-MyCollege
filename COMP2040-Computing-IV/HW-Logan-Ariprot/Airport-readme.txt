/**********************************************************************
 *  Airport-readme template                                                   
 *  Airport Simulation (C++11 Concurrency)                       
 **********************************************************************/

Your name:Erdun E

Operating system you're using (Linux, OS X, or Windows): Linux

If Windows, which solution?: 

Text editor or IDE you're using: C++

Hours to complete assignment: 12 Hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
  I finished this assignment according to the requirements of the assignment, 
  and I tried to keep it running for half an hour. And it does allow some 
  runways to be used at the same time as required.


 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
In this assignment, I used a key function, lock(mutex1, mutex2, mutex3... )
It either locks all mutex, or none of them locks and blocks. This function 
is important to prevent jobs from deadlock in this program.


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
I have a mutex for each runway, and a mutex for every two runways that 
can't be used at the same time to prevent other runways that can't be 
used at the same time from being used as long as these locks are in use.
For requirements that the number of requests cannot exceed 6, I use the 
condition variable to resolve, calling wait if the current number of 
requests reaches 6, and notify_all each time the number of requests is reduced.


 /**********************************************************************
 *  Briefly explain what you learned in the assignment.
 **********************************************************************/
I learned how to use c++11 for concurrent programming, such as mutex,
unique_lock,lock_guard,condition_variable.
There are also ways to prevent deadlocks and solve some confusing program 
exceptions.


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
Yunhao Mei
Chuming Zhen
Yibang Hu
Chenghai Cao
Hong Zhao


/**********************************************************************
 *  Describe any serious problems you encountered.  
 *  If you didn't complete any part of any assignment, 
 *  the things that you didn't do, or didn't get working.                  
 **********************************************************************/
I implemented the whole thing at first, but my program got deadlocked for 
a variety of reasons. So I try to comment out most of the code, modify 
it one by one, and see if it works. In this way, I completed the whole 
assignment step by step.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
 None.