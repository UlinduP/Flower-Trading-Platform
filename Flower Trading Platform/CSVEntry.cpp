#include "CSVEntry.h"
#include "CSVReader.h"

using namespace std;

CSVEntry::CSVEntry(
    string _clientID,
    string _instrument,
    int _side,
    int _quantity,
    double _price) :

    clientID(_clientID),
    instrument(_instrument),
    side(_side),
    price(_price),
    quantity(_quantity)
{
    
}


