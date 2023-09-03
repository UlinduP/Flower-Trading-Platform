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
#include <thread>
#include <queue>

class FlowerMain 
{
    public:
        // Constructor for the FlowerMain class.
        FlowerMain();

        /* This method is the main entry point for processing orders. It does the following:
        Deletes the content of the "execution_rep_testBook.csv" file.
        Reads orders from a CSV file and inserts them into different queues based on the flower type.
        Starts separate threads for processing each flower type.
        Waits for all processing threads to complete.
        Calculates and prints the time taken for processing.*/
        void init();

    private: 
        OrderBook roseBook;
        OrderBook lavBook;
        OrderBook lotusBook;
        OrderBook tulipBook;
        OrderBook orchidBook;
        ExecutionReport report;

        /*This method prints a simple menu to the console,
         prompting the user to enter a CSV file name.*/
        void printMenu();

        /*This two methods implement an order matching algorithm. 
        It takes an OrderBook, order side, instrument, and an OrderBookEntry. 
        It compares buy and sell orders in the OrderBook, updates the order book and 
        generates execution reports accordingly.*/
        void match(OrderBook& OrderBook, int side, string instrument, OrderBookEntry& orderEntry);
        void match2(OrderBook& OrderBook, int side, string instrument);

        /*his method inserts orders into different queues based on the flower type. 
        If the flower type is not recognized, it generates a "Rejected" execution report.*/
        void insertToQueue(CSVEntry& order);

        /*These methods are responsible for processing orders of their respective 
        flower types. They wait for orders to appear in their respective queues and 
        then process them, updating the order book and generating execution reports.*/
        void processRose();
        void processLavender();
        void processLotus();
        void processTulip();
        void processOrchid();     

};
