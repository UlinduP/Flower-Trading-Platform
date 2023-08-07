#pragma once

#include "CSVEntry.h"
#include <vector>
#include <string>

using namespace std;

class CSVReader
{
public:
    CSVReader();
    static vector<CSVEntry> readCSV(string csvFile);
    static vector<string> tokenise(string csvLine, char separator);

private:
    static CSVEntry stringsToOBE(vector<string> tokens);
};