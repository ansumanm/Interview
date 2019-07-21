#include<iostream>
#include<vector>

using namespace std;

class FormattedText {
	public:
		struct TextRange {
			int start;
			int end;
			bool capitalize;

			bool covers(int position) const {
				return (position >= start && position <= end);
			}
		};

		TextRange &getRange(int start, int end) {
			formatting.emplace_back(TextRange{start, end});
			return *formatting.rbegin();
		}

		FormattedText(const string &s):plain_text(s) {}

		friend ostream &operator<<(ostream &os, const FormattedText &obj) {
			string s;
			int i;
			char c;
			vector<FormattedText::TextRange>::const_iterator it;

			for (i = 0; i < obj.plain_text.length(); i++) {
				c = obj.plain_text[i];

				for(it=obj.formatting.begin(); it != obj.formatting.end(); it++)
				{
					if (it->covers(i) && it->capitalize)
						c = toupper(c);
					s += c;
				}
			}

			return os << s;
		}

	private:
		string plain_text;
		vector<TextRange> formatting;
};

int main()
{
	FormattedText ft("This is plain text.");
	ft.getRange(8, 12).capitalize = true;

	cout << ft << endl;
	return 0;
}
