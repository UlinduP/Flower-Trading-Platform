#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

using namespace std;
class OrderBook
{
    public:
        OrderBook();

        vector<OrderBookEntry> buyOrders;
        vector<OrderBookEntry> sellOrders;
             
};
