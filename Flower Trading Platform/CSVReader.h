#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

using namespace as std;

class CSVReader
{
public:
    CSVReader();
    static vector<OrderBookEntry> readCSV(string csvFile);
    static vector<string> tokenise(string csvLine, char separator);
  /*  static OrderBookEntry stringsToOBE(string order_ID,
        InstrumentType instrument,
        int side,
        double price,
        int quantity);  */


private:
    static OrderBookEntry stringsToOBE(vector<string> tokens);
};