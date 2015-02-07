#ifndef ZIP_H
#define ZIP_H
#include <vector>
#include <fstream>
#include <iostream>// REMOVE LATER!
#include <string>
#include <cstring>
using namespace std;

class subFile {
public:
	static const unsigned long long LOCAL_FILE = 0x04034b50;
	static const unsigned long long END_OF_CENTRAL_DIRECTORY = 0x06054b50;
	static const int SIG_SIZE = 4;
	static unsigned long long readBytes (int, vector<unsigned char> &, int);
		// @param: num bytes to read - not more than sizeof(unsigned long long)
		// @param: byte array
		// @param: start index
		// return: concatenated value
};

class zipFile {
public:
	int open (string);
	void save (string);
private:
	vector<subFile> subFiles;
};

int zipFile::open (string filename) {
    fstream fs;
	vector<unsigned char> ram;

	// open file, bring it into ram, and close file 
    char cFilename[1000];
    memset (cFilename, 1, sizeof(cFilename));
	strncpy (cFilename, filename.c_str(), 999);
	fs.open (cFilename, ios::in | ios::binary);
	if (!fs.is_open ())
		return 0;
	char c;
	while (fs.get (c))
		ram.push_back ((unsigned char) c);
	fs.close();

	// find the End of Central Directory Record
	int ecdrIndex = ram.size() - subFile::SIG_SIZE;
	while (ecdrIndex-- > 0) {
		if (subFile::readBytes (subFile::SIG_SIZE, ram, ecdrIndex)
		    == subFile::END_OF_CENTRAL_DIRECTORY
		) {
			// if signature matches, double check the record size with EOF
			int commentLength = subFile::readBytes (2, ram, ecdrIndex+20);
			if (ecdrIndex + 22 + commentLength == ram.size())
				break;
		}
	}
	cout << "ecdrIndex=" << ecdrIndex << endl;

    return ram.size();
}

void zipFile::save (string filename) {
    cout << "zip::save() not implemented...\n";
}

unsigned long long subFile::readBytes (
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
