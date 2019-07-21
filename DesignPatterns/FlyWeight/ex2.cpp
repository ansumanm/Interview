#include<iostream>
#include<string.h>

using namespace std;

class FormattedText {
	private:
		string plain_text;
		bool *caps;

	public:
		FormattedText(const string &plain_text): plain_text(plain_text) {
			caps = new bool[plain_text.length()];
			memset(caps, 0, plain_text.length());
		}

		~FormattedText() {
			delete caps;
		}

		void capitalize(int start, int end) {
			int i;
			for (i = start; i <= end; i++) {
				caps[i] = true;
			}
		}

		friend ostream &operator<<(ostream &os, const FormattedText &obj) {
			string s;
			int i;

			for (i = 0; i < obj.plain_text.length(); i++) {
				char c = obj.plain_text[i];
				s += (obj.caps[i] ? toupper(c) : c);
			}
			return os << s;
		}
};

int main() 
{
	FormattedText ftext("This is plain text.");

	ftext.capitalize(8,12);

	cout << ftext << endl;

	return 0;
}
