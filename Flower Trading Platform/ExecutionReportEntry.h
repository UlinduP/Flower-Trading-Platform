#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ExecutionReportEntry
{
    public:
        ExecutionReportEntry(
            string _clientID,
            string _orderID,
            string _instrument,
            int _side,
            double _price,
            int _quantity,
            int _status,
            string _timeStamp,
            string _reason = "Not rejected"
        );  //constructor

        string clientID;
        string orderID;
        string instrument;
        int side;
        double price;
        int quantity;
        int status;
        string timeStamp;
        string reason;
};
