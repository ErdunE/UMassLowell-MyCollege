#ifndef _LFSR_H_
#define _LFSR_H_

#include <iostream>
#include <string>

class LFSR
{

public:
   
    LFSR(std::string seed, int t);
    int step();
    int generate(int n);

    ~LFSR();

    friend std::ostream& operator<< (std::ostream &out, const LFSR &lfsr);

private:
   
    std::string seed;
    int tap;

};


#endif
