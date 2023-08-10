#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "CSVEntry.h"
#include "OrderBook.h"
#include "ExecutionReport.h"
#include "ExecutionReportEntry.h"


class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
        string genOrderID(int id);
        
    private: 
        void printMenu();
        void orderBookMap(vector<CSVEntry> entries);
        vector<CSVEntry> entries;

        static int orderID;


};
