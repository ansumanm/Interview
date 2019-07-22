#include<string>
#include<list>

/* Forward declaration */
template <typename> struct Subscriber;

template <typename T>
class Publisher {
	/* Maintain a list of subscribers */
	private:
		std::list<Subscriber<T>*> subscribers;

	public:
		void publish(T& source, const std::string& data) {
			for (auto subscriber : subscribers)
				subscriber->notify(source, data);
		}

		void subscribe(Subscriber<T>& subscriber) {
			subscribers.push_back(&subscriber);
		}

		// Remove the subscriber from subscribers list.
		void unsubscribe(Subscriber<T>& subscriber) {
			subscribers.remove(&subscriber);
		}
};
