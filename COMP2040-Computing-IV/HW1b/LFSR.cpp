#include "LFSR.hpp"

LFSR::LFSR(std::string seed, int t) : seed(seed), tap(t){
}

int LFSR::step()
{
    int length = seed.size();
    int tap_value = seed[length-1 - tap] - '0';
    int left_value = seed[0] - '0';
    int v = tap_value ^ left_value;
    
    seed = seed.substr(1,length-1) + std::to_string(v);
    
    return v;
}

int LFSR::generate(int n)
{
    int answer = 0;
    
    for(int i = 0; i < n; i++)
    {
        answer = answer << 1 | step();
    }
    
    return answer;
}

LFSR::~LFSR() {

}

std::ostream &operator<<(std::ostream &out, const LFSR &lfsr)
{
    out << lfsr.seed;
    return out;
}


