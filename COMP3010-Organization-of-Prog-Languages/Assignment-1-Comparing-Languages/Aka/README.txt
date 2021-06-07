Name : Erdun E
Email: Erdun_E@student.uml.edu

Five implementations:
ada: ErdunE_OPL_A1.ada, Cartesian products of sets with same numbers of elements and same type.
haskell: ErdunE_OPL_A1.hs, Cartesian products of sets with different numbers of elements and same type.
rust: ErdunE_OPL_A1.rs, Cartesian products of sets with different numbers of elements and same type.
python: ErdunE_OPL_A1.py, Cartesian products of sets with different numbers of elements and different type.
prolog: ErdunE_OPL_A1.pl, Cartesian products of sets with different numbers of elements and different type.

Each program, We have a function named "cartesian" to compute cartesian products of sets.
When running, that program will invoke the "cartesian" function with the “hard-code” the values of the sets
as argument and print out every element of the result from "cartesian".

* haskell: 
    * easy
    * There are list comprehension and pattern matching in haskell and nice builtin lib function `concat`, 
    it help to write the code in a concise and easy way.
    * like it.
    * slow
    * no memoization in code
* python: 
    * easy
    * You do need to write types in variable declaration, and the syntax is very clean.
    * like it.
    * slow
    * no memoization in code
* rust: 
    * medium
    * need reference in for loop, overall, structurally the same code with python.
    * okay
    * fast
    * no memoization in code
* prolog: 
    * medium
    * need to write output as function argument, it is difference from most language. 
    * dislike it
    * slow
    * no memoization in code
* ada:
    * hard
    * since it use fixed size array in every restricted way, "hand-compute" the result's size and the positions of each element in the result. It consume a huge amount of time.
    * dislike it
    * fast
    * no memoization in code

