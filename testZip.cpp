#include <iostream>
#include "zip.h"
using namespace std;

int main() {
    zipFile zip1;
    cout << "subFiles.size()="
        << zip1.open ("testZipSpreadsheet.ods")
        << endl;
}
