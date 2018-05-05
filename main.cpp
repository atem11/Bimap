//
// Created by artem on 28.04.18.
//

#include <iostream>
#include <map>
#include "bimap.h"

using namespace std;

map<int, int> l, r;
bimap<int, int> a;

void insertAll(int A, int B) {
    a.insert(A, B);
    l.insert({A, B});
    r.insert({B, A});
}

int main() {

    insertAll(6, 9);
    insertAll(17, 31);
    insertAll(9, 12);
    insertAll(26, 11);
    insertAll(3, 27);
    insertAll(2, 28);
    insertAll(27, 24);
    insertAll(13, 7);
    insertAll(14, 26);
    insertAll(19, 6);
    insertAll(23, 13);
    insertAll(24, 3);
    insertAll(29, 5);

    /*
2---28
3---27
6---9
9---12
13---7
14---26
17---31
19---6
23---13
24---3
26---11
27---24
29---5
     */

//*
    a.erase(a.find_left(23));
    a.erase(a.find_right(9));
    //*/
    for (auto it = a.begin_left(); it != a.end_left(); ++it)  {
        cout << *it <<"---" << *(it.flip()) << '\n';
    }
    /*cout << '\n';
    for (auto it = a.begin_right(); it != a.end_right(); ++it)  {
        cout << *it << ' ';
    }*/
    return 0;
}