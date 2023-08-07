#include "OrderBookEntry.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

OrderBookEntry::OrderBookEntry(string _orderID,
                                int _side,
                                int _quantity,
                                double _price):
                                orderID(_orderID),
                                side(_side),
                                quantity(_quantity),
                                price(_price)
{

}

