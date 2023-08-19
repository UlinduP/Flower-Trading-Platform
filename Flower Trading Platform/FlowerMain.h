#pragma once
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "CSVEntry.h"
#include "ExecutionReport.h"
#include "ExecutionReportEntry.h"
#include "CSVReader.h"
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
        static string getCurrentTimestamp();
        static string genOrderID(int id); 
        static int orderID;
        

    private:   
        void printMenu();
        void orderBookMap(CSVEntry order);
        
        
        // void match(OrderBook& orderbook);
           
};
