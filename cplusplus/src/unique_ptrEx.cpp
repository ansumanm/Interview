#include<iostream>
#include<memory>

using namespace std;

class A {
    public:
        void show() {
            cout << "A::show()" << endl;
        }
};

int main()
{
    unique_ptr<A> p1 (new A);

    p1->show();

    // Address of p1
    cout << p1.get() << endl;

    // Transfer ownership
    unique_ptr<A> p2 = move(p1);
    p2->show();

    cout << p1.get() << endl;
    cout << p2.get() << endl;

    // Transfer ownership
    unique_ptr<A> p3 = move(p2);
    p3->show();

    cout << p1.get() << endl;
    cout << p2.get() << endl;
    cout << p3.get() << endl;

    return 0;
}
