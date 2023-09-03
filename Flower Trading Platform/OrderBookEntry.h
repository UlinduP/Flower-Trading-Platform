#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class OrderBookEntry
{
public:  //means we can access these outside the class

    OrderBookEntry(        //constructor
        string _orderID,
        string _clientID,
        int _quantity,
        double _price);

    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

    string orderID;
    string clientID;
    int quantity;
    double price;
};
