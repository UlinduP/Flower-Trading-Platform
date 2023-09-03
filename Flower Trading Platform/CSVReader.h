#pragma once

#include "CSVEntry.h"
#include "ExecutionReport.h"
#include "utils.h"
#include <vector>
#include <string>

using namespace std;

class CSVReader
{
    
public:
    // Constructor for CSVReader class.
    CSVReader();

    /*Static function to tokenize a CSV line into a vector of strings.
     it returns a vector of strings containing the tokens.*/
    static vector<string> tokenise(string csvLine, char separator);

    /*Static function to convert a vector of strings to a CSVEntry object.
     it returns a CSVEntry object.*/
    static CSVEntry tokensToCSVE(vector<string> tokens);

};