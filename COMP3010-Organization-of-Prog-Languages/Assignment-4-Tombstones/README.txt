Team: Erdun E & Chenghai Cao & Zhipeng Sun


Tombstone is  implemented using templates and operator overloading in C++. Specifically, the program defines a template class to store a smart pointer, which can be shared by different pointers that point to the same address. To deal with the problem of memory free conflict, the pointer class uses a counter to count the number of existing pointers that point to the same address as itself. The counter is also shared by different pointers that point to the same address.

When a new pointer is declared by copy constructor or `=` operator, it will copy pointer and counter and the counter will plus one. When a pointer is to free, the counter will minus one, and the pointer won't be deleted unless the counter is minus to zero.


How to build:
make test

How to run:
./A4-tests





