/**********************************************************************
 *  readme.txt template                                                   
 *  Guitar Hero: RingBuffer implementation with unit tests and exceptions
 **********************************************************************/

Name:Erdun E



Hours to complete assignment: 3 Hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
 This circular queue is implemented using an array. I completed all the 
 required functions. The specific implementation algorithm is explained 
 in the following problem.


  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/

 The key algorithm of this problem is to increase the end when entering 
 the team, and increase the front when leaving the team. When end or 
 front is equal to Capacity, it goes back to 0.



/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/

 The data is stored in an array with two Pointers to the front and back of
 the queue, both of which only increase until the pointer equals capacity
 and returns to zero.


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

 yes.
 I think all the methods work properly because I unit tested each method
 and they all passed.


/**********************************************************************
 *  Does your RingBuffer implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
 yes.
 run ps5a, I saw follow output:

 Running 2 test cases...

*** No errors detected

/**********************************************************************
 *  Explain the time and space performance of your RB implementation
**********************************************************************/
 time: all methods are both O(1).
 space: All methods are both O(1) except that constructor. Constructor is O(n).

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
Yunhao Mei
Chuming Zhen
Chenghai Cao
Hong Zhao


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

 None

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

 None