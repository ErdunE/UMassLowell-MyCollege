#include <iostream>
#include "ED.h"

ED::ED(const std::string &a, const std::string &b)
{
    this->x = a;
    this->y = b;
    M = x.size();
    N = y.size();
    opt = new int *[M + 1]();
    if(!opt)
    {
        std::cout << "memory not enough." << std::endl;
        exit(1);
    }
    for (int i = 0; i < M + 1; i++)
        opt[i] = new int[N + 1]();
    for (int i = 0; i <= M; i++)
    {
        opt[i][N] = 2 * (M - i);
    }
    for (int j = 0; j <= N; j++)
    {
        opt[M][j] = 2 * (N - j);
    }
}

int ED::penalty(char a, char b)
{
    return a == b ? 0 : 1;
}

int ED::min(int a, int b, int c)
{
    int minAB = a > b ? b : a;
    return minAB > c ? c : minAB;
}

int ED::OptDistance()
{
    for (int i = M - 1; i >= 0; i--)
        for (int j = N - 1; j >= 0; j--)
            opt[i][j] = min(opt[i + 1][j + 1] + penalty(x[i], y[j]), opt[i + 1][j] + 2, opt[i][j + 1] + 2);
    return opt[0][0];
}

std::string ED::Alignment()
{
    std::string result;
    int i = 0, j = 0;
    while (i < M || j < N) {
        if (i < M && j < N && x[i] == y[j] && opt[i][j] == opt[i + 1][j + 1])
        {
            result += x[i];
            result += " ";
            result += y[j];
            result += " 0";
            i++;
            j++;
        } else if (i < M && j < N && x[i] != y[j] && opt[i][j] == opt[i + 1][j + 1] + 1)
        {
            result += x[i];
            result += " ";
            result += y[j];
            result += " 1";
            i++;
            j++;
        } else if (i < M && opt[i][j] == opt[i + 1][j] + 2)
        {
            result += x[i];
            result += " - 2";
            i++;
        } else if (j < N && opt[i][j] == opt[i][j + 1] + 2)
        {
            result += "- ";
            result += y[j];
            result += " 2";
            j++;
        }
        if(i < M || j < N) result += "\n";
    }
    return result;
}

ED::~ED()
{
    for(int i = 0; i <= M; i++)
        delete[] opt[i];
    delete[] opt;
}

