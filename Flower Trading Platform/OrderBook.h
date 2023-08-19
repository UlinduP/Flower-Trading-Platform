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

        void insertBuyOrder(OrderBookEntry& order);
        static double getHighPrice(vector<OrderBookEntry>& orders);
        static double getLowPrice(vector<OrderBookEntry>& orders);

        vector<OrderBookEntry> buyOrders;
        vector<OrderBookEntry> sellOrders;
    
};
