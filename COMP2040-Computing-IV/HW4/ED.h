#ifndef ED_H
#define ED_H
#include <string>

class ED
{

private:
    int **opt;
    std::string x;
    std::string y;
    int M, N;

public:
    ED(const std::string &a, const std::string &b);
    ~ED();
    static int penalty(char a, char b);
    static int min(int a, int b, int c);
    int OptDistance();
    std::string Alignment();
};

#endif
