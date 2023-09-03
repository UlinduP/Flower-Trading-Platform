#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ExecutionReportEntry
{
    public:
    // Constructor for ExecutionReportEntry class.
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

        // Public member variables to store execution report entry data.
        string orderID;
        string clientID;    
        string instrument;
        string side;
        string status;
        string quantity;
        string price;
        string reason;
        string timeStamp;
};
