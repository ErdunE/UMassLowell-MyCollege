#include <iostream>
#include <string>
#include "bstree.hpp"
#include <chrono>
using namespace std;
using namespace std::chrono;

void printPrompt() {
    std::cout << "Please enter an option:" << std::endl;
    cout <<"\t(a) add data" << endl;
    cout <<"\t(b) delete data" << endl;
    cout <<"\t(c) search data" << endl;
    cout <<"\t(d) exit" << endl;
}

int main() {
    
    cout << "Test Integer BST\n";
    printPrompt();
    BSTree<int> tree1;
    char value;
    string option;
    while(true) {
        cin >> option;
        if (option == "a" || option == "A") {
            cout << "enter inserting value:";
            cin >> value;
            tree1.add(value);
        } else if(option == "b" || option == "B") {
            cout << "enter deleting value:";
            cin >> value;
            bool result = tree1.remove(value);
            cout << (result ? "deleted " : "not found ") << value << endl;
        } else if(option == "c" || option == "C") {
            cout << "enter searching value:";
            cin >> value;
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            bool result = tree1.search(value);
            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
            cout << (result ? "found " : "not found ") << value;
            cout << ". It took " << time_span.count() << " seconds.\n";
        } else if(option == "d" || option == "D") {
            break;
        }
    }
    
    cout << "\n\n\nTest String BST\n";
    printPrompt();
    BSTree<string> tree2;
    string temp;
    while(true) {
        getline(cin,option);
        if (option == "a" || option == "A") {
            cout << "enter inserting value:";
            cin >> temp;
            tree2.add(temp);
        } else if(option == "b" || option == "B") {
            cout << "enter deleting value:";
            cin >> temp;
            bool result = tree2.remove(temp);
            cout << (result ? "deleted " : "not found ") << temp << endl;
        } else if(option == "c" || option == "C") {
            cout << "enter searching value:";
            cin >> temp;
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            bool result = tree2.search(temp);
            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
            cout << (result ? "found " : "not found ") << temp;
            cout << ". It took " << time_span.count() << " seconds.\n";
        } else if(option == "d" || option == "D") {
            break;
        }
    }
    return 0;
}
