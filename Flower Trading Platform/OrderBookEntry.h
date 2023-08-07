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
        int _side,
        int _quantity,
        double _price);

    static bool compareByorderId(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.orderID < e2.orderID;
        }  
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

    string orderID;
    int side;
    int quantity;
    double price;
};
