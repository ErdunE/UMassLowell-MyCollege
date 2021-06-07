/**********************************************************************
 *  N-Body Simulation ps3a-readme.txt template
 **********************************************************************/

Name:Erdun E
Hours to complete assignment: 12 hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/

 a. I defined a Body class that implements the Drawable interface, declaring the draw method private so that it can only be drawn through the window.draw(obj) method.
 b. Use std::cin to read the input of stdin.
 c. I refer to the online tutorial to implement the reload >> operator.
 d. There is a number at the beginning of the file that represents the number of body objects, so read this number before reading the body, and then use a for loop.
 e. Universe size is the same as above.
 f. Shared_point is created with the make_shared function, which is not created with new like a normal pointer and deleted with delete.

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/

The key algorithm in this problem is to calculate the distance between two bodys in the window based on the actual distance between them, which is actually just scaling plus offset.



/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Describe if and how do you used the smart pointers 
 *  Include code excerpts.
 **********************************************************************/

Shared_point is created with the make_shared function, which is not created with new like a normal pointer and deleted with delete.


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
Yunhao Mei
Chuming Zhen
Chenghai Cao
Hong Zhao

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I don't know if the data is too big or what, but when I run this program, it always crashes and doesn't work.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
 None