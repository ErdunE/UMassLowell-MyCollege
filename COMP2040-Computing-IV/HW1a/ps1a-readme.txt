/**********************************************************************
 *  Linear Feedback Shift Register (part A) ps1a-readme.txt template
 **********************************************************************/

Name:Erdun E
Hours to complete assignment:almost half day

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/

LFSR is a seed that can be initialized and then used to generate pseudo-random Numbers using shift and xor operations.It has the advantage of simple principle and convenient implementation.
This assignment was a bit of a challenge. I learned what LFSR was and implemented a virtual LFSR in C++.I considered using arrays or strings to do this, but I found strings more convenient.C++ characters need to be converted to Numbers for calculation, otherwise you will get wrong results.
I tested it 10 times, each for step() and generate(), and the results were the same as expected.



/**********************************************************************
 *  If you did any implementation for extra credit, describe it
 *  here and why it is interesting.
 **********************************************************************/

	
I wanted to do something else, but I didn't know how to do it, so I just did what the assignment required.


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
	
Chuming Zhen
	
Yunhao Mei
	
Chenghai Cao
	
Hong Zhao

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
	
I forgot to convert ASCII characters to Numbers, which caused a calculation error.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
	
While boost libraries are slow to compile, using PCH files can speed things up.