#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class InstrumentType { Rose, Lavender, Lotus, Tulip, Orchid };

class OrderBookEntry
{
public:  //means we can access these outside the class

    OrderBookEntry(        //constructor
        string _order_ID,
        InstrumentType _instrument,
        int _side,
        double _price,
        int _quantity);

    static bool compareByOrderID(OrderBookEntry& e1, OrderBookEntry& e2);

    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);

    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);

    string order_ID;
    InstrumentType instrument;
    int side;
    double price;
    int quantity;

};