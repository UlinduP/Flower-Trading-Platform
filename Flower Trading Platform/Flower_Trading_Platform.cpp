// Flower Trading Platform.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include "CSVReader.h"
#include "CSVEntry.h"
#include "MerkelMain.h"
// #include "ExecutionReport.h"
// #include "ExecutionReportEntry.h"
// #include "FlowerTrader.h"
// #include "OrderBook.h"
#include "OrderBookEntry.h"

using namespace std;

int main()
{
    MerkelMain app{};
    app.init();
}

