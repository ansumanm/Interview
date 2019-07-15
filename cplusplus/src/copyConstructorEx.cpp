#include<iostream>

using namespace std;

class Point {
    private:
        int x;
        int y;
    public:
        // Default Constructor
        Point() {
            cout << "Default Constructor" << endl;
        }
        // Constructor
        Point(int x1, int y1) { 
            cout << "Constructor" << endl;
            x = x1; y = y1;
        }

        // Copy Constructor
        Point(const Point &p) {
            cout << "Copy Constructor" << endl;
            x = p.x; y = p.y;
        }

        // Overload assignment operator
        // If a reference is returned, then I get the warning
        // warning: reference to stack memory associated with local variable
        // 'newP' returned [-Wreturn-stack-address]
        Point operator = (const Point &p) {
            Point newP;
            cout << "Assignment operator" << endl;
            newP.x = p.x; newP.y = p.y;
            return newP;
        }

        int getX() { return x; }
        int getY() { return y; }
};

int main() 
{
    Point p1(1,2);
    Point p2 = p1;
    Point p3;

    p3 = p2;

    return 0;
}
