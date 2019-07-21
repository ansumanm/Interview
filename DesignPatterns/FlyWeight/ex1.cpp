/*
 * Problem statement: Maintain a database of usernames
 *  so that they are optimized to save space.
 */

#include<iostream>
#include<boost/bimap.h>

using namespace std;

typedef unsigned short key;

class User {
    protected:
        static bimap<key, string> names;
        static key seed; // Initial value
};

key User::seed = 1;
bimap<key, string> User::names{};

int main() 
{
    return 0;
}
