#include <iostream>
#include "ED.h"
#include <SFML/System.hpp>

using namespace std;

int main() {
    sf::Clock clock;
    sf::Time t;
    string sequence1, sequence2;
    cin >> sequence1 >> sequence2;
    ED ed(sequence1, sequence2);
    auto distance = ed.OptDistance();
    auto alignment = ed.Alignment();
    t = clock.getElapsedTime();
    cout << "Edit distance = " << distance << endl;
    cout << alignment << endl;
    cout << "Execution time is " << t.asSeconds() << " seconds \n" << std::endl;
    return 0;
}
