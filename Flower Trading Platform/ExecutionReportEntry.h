#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ExecutionReportEntry
{
public:  //means we can access these outside the class

    ExecutionReportEntry(        //constructor
        string _clientID,
        string _orderID,
        string _instrument,
        int _side,
        double _price,
        int _quantity,
        int _status,
        string _reason,
        string _timeStamp);
    

    string clientID;
    string orderID;
    string instrument;
    int side;
    double price;
    int quantity;
    int status;
    string reason;
    string timeStamp;

};