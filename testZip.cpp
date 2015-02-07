#include <iostream>
#include "zip.h"
using namespace std;

int main() {
    zip zip1;
	zip1.open ("testZipSpreadsheet.ods");
	cout << "there are " << zip1.unzip() << " local files.\n";
}
