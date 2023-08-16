#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ExecutionReportEntry
{
    public:
        ExecutionReportEntry(
            string _orderID,
            string _clientID, 
            string _instrument,
            int _side,
            string _status,
            int _quantity,
            double _price,
            string _reason,
            string _timeStamp
        );  //constructor

        string orderID;
        string clientID;    
        string instrument;
        int side;
        string status;
        int quantity;
        double price;
        string timeStamp;
        string reason;
};
