// Flower Trading Platform.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include "CSVReader.h"
#include "CSVEntry.h"
#include "FlowerMain.h"
// #include "ExecutionReport.h"
// #include "ExecutionReportEntry.h"
// #include "FlowerTrader.h"
// #include "OrderBook.h"
#include "OrderBookEntry.h"

using namespace std;

int main()
{
    FlowerMain app{};
    app.init();

 //use below command to compile
  
 //1--> g++ OrderBookEntry.cpp OrderBook.cpp FlowerMain.cpp Flower_Trading_Platform.cpp CSVReader.cpp CSVEntry.cpp ExecutionReportEntry.cpp  ExecutionReport.cpp -o output
 //2--> ./output
}

