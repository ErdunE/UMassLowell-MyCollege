#include <iostream>
#include<string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    const char * fn1 = "/Users/ErdunE/Desktop/COMP iii Assignment/ex1/ex1/1.txt";
    const char * FResult = "/Users/ErdunE/Desktop/test2.txt";
    fstream file;
    string tmp,s,s1,s2;
    
    
    file.open(fn1,ios::in);
    if(file.fail())
    {
        cout<<"fail"<<endl;
        file.close();
    }
    else {
        int loc;
        ofstream    OsWrite(FResult);
        while( getline(file,tmp) )
        {
            loc = tmp.find('J');
            if(loc < tmp.length()){
                s1 = tmp.substr(0,loc);
                s2 = tmp.substr(loc+5,tmp.length());
            }
            else {
                s = tmp;
            }
            s = s1 + "harry " + s2 + "\n";
            OsWrite<<s;
            cout << s;
        }
        OsWrite.close();
        file.close();
    }
    return 0;
}
