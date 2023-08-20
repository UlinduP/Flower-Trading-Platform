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
            string _side,
            string _status,
            string _quantity,
            string _price,
            string _reason,
            string _timeStamp
        );  //constructor

        string orderID;
        string clientID;    
        string instrument;
        string side;
        string status;
        string quantity;
        string price;
        string timeStamp;
        string reason;
};
