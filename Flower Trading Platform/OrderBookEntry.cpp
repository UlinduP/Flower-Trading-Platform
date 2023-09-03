#include "OrderBookEntry.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

OrderBookEntry::OrderBookEntry(string _orderID,
                                string _clientID,
                                int _quantity,
                                double _price):
                                orderID(_orderID),
                                clientID(_clientID),
                                quantity(_quantity),
                                price(_price)
{

}

