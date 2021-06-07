/**********************************************************************
 *  readme.txt template                                                   
 *  Guitar Hero: GuitarString implementation and SFML audio output 
 **********************************************************************/

Name:Erdun E
CS Login:
Hours to complete assignment :  7 hours

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
 yes!
 Successfully.
 I felt everything was ok, first I passed the GStest unit test, and then
  I tested 37 keys that did make a difference.


/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  As a pair, or individually?
 *  If you completed the AutoGuitar, what does it play?
 **********************************************************************/
  No.

/**********************************************************************
 *  Does your GuitarString implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
  yes. Because the result of the run is

  Running 1 test case...

*** No errors detected

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
 I found in GuitarString that vector must be stored in order to function 
 normally, otherwise it would cause program interruption. I searched for 
 the reason for a long time, but still did not know why. Fortunately, 
 it now at least appears to be working properly.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
 All the methods in RB that I implemented last time were O(1), because 
 obviously, each method implementation didn't use loops and recursion, 
 and the number of computations is constant and O(1).