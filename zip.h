#ifndef ZIP_H
#define ZIP_H
#include <vector>
#include <fstream>
#include <iostream>// REMOVE LATER!
#include <string>
#include <cstring>
using namespace std;

class zip {
public:
	void open (string); // action: loads specified disk into raw. Multiple
	                    //         disks can be loaded prior to unzip()ping.
	void save (string); // action: saves the current zip file.
	int unzip (); // action: attempts to parse raw data into directory & files
	              // return: number of local files
protected:
	static const unsigned long long LOCAL_FILE = 0x04034b50;
	static const unsigned long long END_OF_CENTRAL_DIRECTORY = 0x06054b50;
	static const int				SIG_SIZE = 4;
	class record {

	};
	static unsigned long long readBytes ( // return: concatenated value
		int,                              // @param: num of bytes to read
		vector<unsigned char> &,          // @param: byte array
		int                               // @param: start index
	);
private:
	vector<unsigned char> raw;
	vector<record> directory;
	vector<record> files;
};

void zip::open (string filename) {
	// open file, load contents into ram vector, then close file
    fstream fs;
    char cFilename[1000];
    memset (cFilename, 1, sizeof(cFilename));
	strncpy (cFilename, filename.c_str(), 999);
	fs.open (cFilename, ios::in | ios::binary);
	if (!fs.is_open ())
		return;
	char c;
	while (fs.get (c))
		raw.push_back ((unsigned char) c);
	fs.close();
	return;
}

int zip::unzip () {
	// attempt to find the End of Central Directory Record
	int ecdrIndex = raw.size() - SIG_SIZE;
	while (ecdrIndex-- > 0) {
		if (readBytes (SIG_SIZE, raw, ecdrIndex) == END_OF_CENTRAL_DIRECTORY) {
			// if signature matches, double check the record size with EOF
			int commentLength = readBytes (2, raw, ecdrIndex+20);
			if (ecdrIndex + 22 + commentLength == raw.size())
				break;
		}
	}
	if (ecdrIndex < 0)
		return 0;	// fail gracefully if EOCDR not found


    return raw.size();
}

void zip::save (string filename) {
    cout << "zip::save() not implemented...\n";
}

unsigned long long zip::readBytes (
	int num,
	vector<unsigned char> &array,
	int index)
{
	unsigned long long concat = 0;
	for (int i=0; i<num; i++)
		concat |= (array.at(i+index) << (8*i));
	return concat;
}


#endif
