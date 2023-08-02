#include "OrderBookEntry.h"

using namespace std;

OrderBookEntry::OrderBookEntry(        //constructor
    string _order_ID,
    InstrumentType _instrument,
    int _side,
    double _price,
    int _quantity)
    :order_ID(_order_ID),
    instrument(_instrument),
    side(_side),
    price(_price),
    quantity(_quantity)
{

}


bool OrderBookEntry::compareByOrderID(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.order_ID < e2.order_ID;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price > e2.price;
}