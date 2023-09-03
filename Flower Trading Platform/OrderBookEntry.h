#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class OrderBookEntry
{
public:  
    // Constructor for OrderBookEntry class.
    OrderBookEntry(        
        string _orderID,
        string _clientID,
        int _quantity,
        double _price);

    // Static function to compare two OrderBookEntry objects by price in ascending order.
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }

    // Static function to compare two OrderBookEntry objects by price in decending order.    
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

    // Public member variables to store order book entry data.
    string orderID;
    string clientID;
    int quantity;
    double price;
};
