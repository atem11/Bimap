//
// Created by artem on 28.04.18.
//

#include <iostream>
#include "bimap.h"

using namespace std;

int main() {
    bimap<int, int> a;
    a.insert(5, 2);
    a.insert(2, 5);
    a.insert(2, 3);
    if (a.find_right(2) != a.end_right()) {
        cout << "T\n";
    } else {
        cout << "F\n";
    }
    if (a.find_right(5) != a.end_right()) {
        cout << "T\n";
    } else {
        cout << "F\n";
    }
    a.erase(a.begin_left());
    if (a.find_right(5) != a.end_right()) {
        cout << "T\n";
    } else {
        cout << "F\n";
    }
    return 0;
}