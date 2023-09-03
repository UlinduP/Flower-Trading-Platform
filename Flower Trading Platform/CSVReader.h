#pragma once

#include "CSVEntry.h"
#include "ExecutionReport.h"
#include "utils.h"
#include <vector>
#include <string>
#include "ExecutionReport.h"
#include "ExecutionReportEntry.h"
#include "FlowerMain.h"

using namespace std;

class CSVReader
{
public:
    CSVReader();
    //static void readCSV(string csvFile);
    static vector<string> tokenise(string csvLine, char separator);
    static CSVEntry tokensToCSVE(vector<string> tokens);
    
};