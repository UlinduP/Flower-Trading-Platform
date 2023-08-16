#include "OrderBookEntry.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

OrderBookEntry::OrderBookEntry(string _orderID,
                                int _quantity,
                                double _price):
                                orderID(_orderID),
                                quantity(_quantity),
                                price(_price)
{

}

