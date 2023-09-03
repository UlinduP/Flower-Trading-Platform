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
        // Constructor for the ExecutionReport class.
        ExecutionReport(); 

        // Write an ExecutionReportEntry to the CSV report file.
        void writeToReport(ExecutionReportEntry data); 

        // Convert an ExecutionReportEntry  into a vector of strings.
        vector<string> objToString(ExecutionReportEntry data);
        

        // Open the CSV file for writing
        ofstream csvFile;    

    private:
        // Format a price value for inclusion in the report.
        string formatPrice(string price);    
};