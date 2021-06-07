/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name:Erdun E
Login:Oracle VM VirtualBox
Hours to complete assignment: 12 Hours



/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/
	
	Starting from opt[0][0], there are four situations:
	1. opt[i][j] == opt[i+1][j+1] and x[i] == y[j]， skip
	2. opt[i][j] == opt[i+1][j+1] and x[i] != y[j],  modified
	3. opt[i][j] == opt[i+1][j]+2,  x insert a gap
	4. opt[i][j] == opt[i][j+1]+2,  y insert a gap
	Until opt[M][N] ceases.

/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input:
atattat
tattata

Expected output:
Edit distance = 4
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2

What happened:
Insert a gap at the beginning of the Y string and the end of the X string.


/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 2 GB to 16 GB.
 **********************************************************************/
16 GB


/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
a = 4
b = 2
largest N = 46340

Explanation:
4 * N^2 = 8GB = 8 * 1024 * 1024 * 1024 bytes
N = 46340

/**********************************************************************
 *  Were you able to run Valgrind's massif tool to verify that your
 *  implementation uses the expected amount of memory?
 *
 *  Answer yes, no, I didn't try, I tried and failed, or I used a 
 *  different tool.
 *
 *  If yes, paste in the ms_print top chart of memory use over time,
 *  and also indicate which file your code was solving.
 * 
 *  Explain if necessary.
/**********************************************************************
	yes.
	
	
    GB
2.981^                                                                       #
     |           @:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
     |           @                                                           #
     |          @@                                                           #
     |         :@@                                                           #
     |         @@@                                                           #
     |        :@@@                                                           #
     |        @@@@                                                           #
     |       :@@@@                                                           #
     |      :@@@@@                                                           #
     |      @@@@@@                                                           #
     |     :@@@@@@                                                           #
     |     :@@@@@@                                                           #
     |    ::@@@@@@                                                           #
     |   :::@@@@@@                                                           #
     |   :::@@@@@@                                                           #
     |  ::::@@@@@@                                                           #
     | :::::@@@@@@                                                           #
     | :::::@@@@@@                                                           #
     |::::::@@@@@@                                                           #
   0 +----------------------------------------------------------------------->Gi
     0                                                                   17.89

	file: ecoli28284.txt
	
	4*28484^2 / 1024^3 = 2.98017
	The theoretical value is very close to the actual value.


/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt       118               0.056441          24.03
ecoli5000.txt       160               0.230267          95.64
ecoli7000.txt       194               0.440297          187.3
ecoli10000.txt      223               0.985002          381.9
ecoli20000.txt      3135              3.61606           1526.8
ecoli28284.txt      8394              7.22154           3052.5

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730



/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 9e-9
b = 2
largest N = 3098386

Solve:
9e-9 * N ^ 2 = 24*60*60
N = 3098386

/
**********************************************************************
 *  Did you use the lambda expression in your assignment? If yes, where (describe a method or provide a lines numbers)
 **********************************************************************/

No.


**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/
Chuming Zhen
Haoyun Mei
Chenghai Cao
Hong Zhao

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
None.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

None.