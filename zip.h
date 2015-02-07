#ifndef ZIP_H
#define ZIP_H
#include <vector>
#include <fstream>
#include <iostream>// REMOVE LATER!
#include <string>
#include <cstring>
using namespace std;

class zipSubFile {

};

class zip {
public:
	int open (string);
	void save (string);
private:
	vector<zipSubFile> subFiles;
};

int zip::open (string filename) {
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

    return ram.size();
}

void zip::save (string filename) {
    cout << "zip::save() not implemented...\n";
}


#endif
