#pragma once


#include "OrderBookEntry.h"
#include "CSVEntry.h"
#include "OrderBook.h"
#include "ExecutionReport.h"
#include "ExecutionReportEntry.h"
#include "CSVReader.h"
#include "utils.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

class FlowerMain 
{
    public:
        FlowerMain();
        /** Call this to start the sim */
        void init();

    private: 
        OrderBook roseBook;
        OrderBook lavBook;
        OrderBook lotusBook;
        OrderBook tulipBook;
        OrderBook orchidBook;
        ExecutionReport report;

        void printMenu();
        void orderBookMap(CSVEntry& order);
        void match(OrderBook& OrderBook);
        vector<CSVEntry> entries;
        



};
