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
    return 0;
}