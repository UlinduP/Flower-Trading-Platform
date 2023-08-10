#include "ExecutionReportEntry.h"

using namespace std;


ExecutionReportEntry::ExecutionReportEntry(
                        string _clientID,
                        string _orderID,
                        string _instrument,
                        int _side,
                        double _price,
                        int _quantity,
                        int _status,
                        string _timeStamp,
                        string _reason): 

                        clientID(_clientID),
                        orderID(_orderID),
                        instrument(_instrument),
                        side(_side),
                        price(_price),
                        quantity(_quantity),
                        status(_status),
                        timeStamp(_timeStamp),
                        reason(_reason)
{
    // Constructor body 
}

