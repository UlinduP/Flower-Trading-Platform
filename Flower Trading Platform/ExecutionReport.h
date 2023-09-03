#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "CSVEntry.h"
#include "OrderBook.h"
#include "ExecutionReportEntry.h"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>


class ExecutionReport
{
    public:
        ExecutionReport(); 
        void writeToReport(ExecutionReportEntry data); 
        vector<string> objToString(ExecutionReportEntry data);
        

        // Open the CSV file for writing
        ofstream csvFile;    

    private:
        string formatPrice(string price);    
};