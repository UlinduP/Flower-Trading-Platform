#include "ExecutionReportEntry.h"

using namespace std;


ExecutionReportEntry::ExecutionReportEntry(
                        string _orderID,
                        string _clientID,
                        string _instrument,
                        int _side,
                        string _status,
                        int _quantity,
                        double _price,
                        string _timeStamp,
                        string _reason): 
                        
                        orderID(_orderID),
                        clientID(_clientID),
                        instrument(_instrument),
                        side(_side),
                        status(_status),
                        quantity(_quantity),
                        price(_price),
                        timeStamp(_timeStamp),
                        reason(_reason)
{
    // Constructor body 
}

