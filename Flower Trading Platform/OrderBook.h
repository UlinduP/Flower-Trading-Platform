#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

using namespace std;
class OrderBook
{
    public:
        // Constructor for the OrderBook class.
        OrderBook();

        // Public member variables to store buy and sell orders.
        vector<OrderBookEntry> buyOrders;
        vector<OrderBookEntry> sellOrders;
             
};
