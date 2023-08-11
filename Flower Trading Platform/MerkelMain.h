#pragma once


#include "OrderBookEntry.h"
#include "CSVEntry.h"
#include "OrderBook.h"
#include "ExecutionReport.h"
#include "ExecutionReportEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

class MerkelMain 
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
        string genOrderID(int id);
        string getCurrentTimestamp();
        
    private: 
        void printMenu();
        void orderBookMap(CSVEntry order);
        vector<CSVEntry> entries;

        static int orderID;


};
