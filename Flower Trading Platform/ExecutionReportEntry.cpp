#include "ExecutionReportEntry.h"

using namespace std;


ExecutionReportEntry::ExecutionReportEntry(
                        string _orderID,
                        string _clientID,
                        string _instrument,
                        string _side,
                        string _status,
                        string _quantity,
                        string _price,
                        string _reason,
                        string _timeStamp): 
                        
                        orderID(_orderID),
                        clientID(_clientID),
                        instrument(_instrument),
                        side(_side),
                        status(_status),
                        quantity(_quantity),
                        price(_price),
                        reason(_reason),
                        timeStamp(_timeStamp)
{
    // Constructor body 
}

