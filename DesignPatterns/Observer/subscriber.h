#include <string>

template <typename T>
class Subscriber {
	public:
		virtual void notify(
				const T& source,
				const std::string& data) = 0;
};
