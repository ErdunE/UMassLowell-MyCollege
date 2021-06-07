Name：Erdun E
Email：Erdun_E@student.uml.edu 
Teammate:Erdun E & Chenghai Cao & Zhipeng Sun

My task to is to handle the warning and error part. Error checking for EOF and 
non-numeric input has been added in the getint() C function and the 
zero_divisor_checker() C function is utilized for catching the divide by zero 
error. And the detection of unused variable warning and uninitialized variable 
error is implemented by retrieving the assigned(read counts as assign) and used 
variables list for the ecg program, followed by a comparison between the two sets.

I add three testers to illustrate the warning and error handling. The 
test_unused_var.ml tester illustrates the generated warning for unused variables. 
The test_zero_divisor.ml tester tests the semantic error of dividing by zero. 
And the test_uninitialized_var.ml tester tests the case of an uninitialized 
variable error. 

As for the two other semantic errors: Unexpected end of input and Non-numeric 
input, they can only be caught dynamically. Assuming you are playing with the 
./primes executable, just input the EOF(by tying Ctrl+D) or an invalid string 
like "2a", you will see those errors reported.

A Makefile is provided to batch process the overfall five tests(The two more 
are provided by my partner). For each tester, a C source program(*.c file) and 
its corresponding executable will be generated except that:

For the test_unused_var.ml tester, a warning text file(*.warning) will be 
generated instead of a C source program;
And for the test_uninitialized_var tester, only C source program(without executable) 
will be generated, as the error will be reported by a C compiler like gcc, and 
no executable will be output with a compiling error.