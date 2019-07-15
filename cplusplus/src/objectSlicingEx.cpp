#include <iostream> 
#include<string> 

using namespace std; 

class Pet { 
public: 
    virtual string getDescription() const { 
        return "This is Pet class"; 
    } 
}; 

class Dog : public Pet { 
public: 
    virtual string getDescription() const { 
        return "This is Dog class"; 
    } 
}; 

void describe(Pet p) { // Slices the derived class object 
    cout<<p.getDescription()<<endl; 
} 

void describe_2(const Pet &p) { // Doesn't slice the derived class object. 
        cout<<p.getDescription()<<endl; 
} 
  
int main() { 
    Dog d; 
    describe(d); 
    describe_2(d); 
    return 0; 
} 

