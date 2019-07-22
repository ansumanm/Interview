#include<iostream>

using namespace std;

struct FileAppend {
	virtual void write(const string &s) = 0;
};

struct FileOp: FileAppend {
	FileOp(const string & filename) {
		cout << "FileOp constructor" << endl;
		cout << "Opening File " << filename << endl;
	}

	void write(const string &s) {
		cout << "FileOp write" << endl;
		cout << "Writing string " << s << endl;
	}

};

struct LazyFileOp: FileAppend {
	public:
		LazyFileOp(const string & filename): filename(filename) {
			cout << "LazyFileOp constructor" << endl;
			fileOp = nullptr;
		}
		
		void write(const string &s) {
			cout << "LazyFileOp write" << endl;
			fileOp = new FileOp(filename);
			fileOp->write(s);
		}

	private:
		string filename;
		FileOp *fileOp;
};

int main() 
{
	FileOp f("testfile");
	f.write("Some data");

	cout << "==========" << endl;

	LazyFileOp f2("Lazytestfile");
	f2.write("Lazy file write");
	return 0;
}
