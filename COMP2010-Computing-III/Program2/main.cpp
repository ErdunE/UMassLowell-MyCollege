#include <iostream>
#include<string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    const char * fn2 = "/Users/ErdunE/Desktop/COMP iii Assignment/ex2/ex2/2.txt";
    const char * FResult = "/Users/ErdunE/Desktop/test3.txt";
    ofstream OsWrite(FResult,ofstream::app);
    
    ifstream file;
    string tmp,tmp1,tmp2,number,name,o,salary;
    file.open(fn2,ios::in);
    
    if(file.fail())
    {
        cout<<"fail"<<endl;
        file.close();
    }
    else {
        while(!file.eof()){
            getline(file,tmp);
            number = tmp.substr(0,4);
            tmp1 = tmp.substr(5,tmp.length());
            tmp2 = tmp.substr(tmp.length()-6,tmp.length());
            int loc;
            loc = tmp1.find(',');
            name = tmp1.substr(0,loc);
            loc = tmp2.find(',');
            salary = tmp2.substr(loc+1,tmp2.length());
            cout << name << " : " << salary << endl;
            o = name + " : " + salary + "\n";
            OsWrite<<o;
        }
        
    }
    OsWrite.close();
    file.close();
    
    
    
    
    return 0;
}

