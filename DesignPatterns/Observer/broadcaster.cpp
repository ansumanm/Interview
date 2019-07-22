#include<iostream>
#include "publisher.h"
#include "subscriber.h"

using namespace std;

class Broadcast: public Publisher<Broadcast> {
	public:
		void broadcast(const string& msg) {
			publish(*this, msg);
		}
};

class ConsoleSubscriber: public Subscriber<Broadcast> {
	private:
		string name;
	public:
		ConsoleSubscriber(const string &n): name(n) {}
		void notify(const Broadcast &source,
			    const string& data) {
			cout << "[" << name << "]" << data << endl;
		}	
};

int main() 
{
	Broadcast b;
	ConsoleSubscriber c("C1");
	ConsoleSubscriber c2("C2");

	b.subscribe(c);
	b.broadcast("Hello Subscriber!!");
	b.broadcast("How are you!!");

	b.subscribe(c2);
	b.broadcast("Hello Subscribers!!");
	b.broadcast("How are you all doing !!");

	b.unsubscribe(c);
	b.broadcast("Hello Subscribers!!");
	b.broadcast("How are you all doing !!");

	return 0;
}
