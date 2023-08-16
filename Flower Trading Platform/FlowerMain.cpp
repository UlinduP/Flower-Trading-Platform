#include "FlowerMain.h"


int FlowerMain::orderID = 1;
ExecutionReport report;
OrderBook roseBook;
OrderBook lavBook;
OrderBook lotusBook;
OrderBook tulipBook;
OrderBook orchidBook;


using namespace std;

FlowerMain::FlowerMain()
{

}

void FlowerMain::init()
{
    printMenu();   
    string fileName;
    getline(cin, fileName);
    cout << "\nYour select " <<fileName<<" file." << endl;    
    
    // read the csv file
    entries = CSVReader::readCSV(fileName);

    // create a map of order books
    for (CSVEntry &order : entries)
    {
        orderBookMap(order);
    }
    
    // ExecutionReport report;
    // ExecutionReportEntry data{"ord1", "aa13", "Rose", 2, 55.00, 100,0, "2020-01-01 10:00:00"};  
    // report.writeToReport(data);

}

void FlowerMain::printMenu()
{
    cout << "Welcome to Flower Exchange Paltform!\n";
    cout << "Enter your order file name: " << endl;
}
 
 void FlowerMain::orderBookMap(CSVEntry order)
{  
    vector<OrderBook> orderBooks{roseBook, lavBook, lotusBook, tulipBook, orchidBook};
    vector<string> intruments{"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
    for (int i = 0; i < intruments.size(); i++)
    {
        if (order.instrument == intruments[i])
        {
            OrderBookEntry orderEntry{genOrderID(orderID), order.quantity, order.price};
            if (order.side == 1)
            {
                orderBooks[i].buyOrders.push_back(orderEntry);
                sort(orderBooks[i].buyOrders.begin(), orderBooks[i].buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            }
            else if (order.side == 2)
            {
                orderBooks[i].sellOrders.push_back(orderEntry);
                sort(orderBooks[i].sellOrders.begin(), orderBooks[i].sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            }
            else
            {
                ExecutionReportEntry entry{genOrderID(orderID),order.clientID,intruments[i], order.side,"Rejected",order.quantity,order.price, getCurrentTimestamp(), "Invalid side"};
                report.writeToReport(entry);
                //cout<<"FlowerMain::orderBookMap Invalid side."<<endl;
            }
        }
    }     
}


string FlowerMain::genOrderID(int id)
{
    string strOrderID = "ord";
    strOrderID += to_string(id);
    FlowerMain::orderID++;
    return strOrderID;
}

string FlowerMain::getCurrentTimestamp() 
{
    // Get the current time
    auto currentTime = chrono::system_clock::now();
    
    // Convert the current time to a time_t object
    time_t time = chrono::system_clock::to_time_t(currentTime);
    
    // Extract the components of the timestamp
    tm tmStruct = *localtime(&time);
    
    // Create a string stream to build the formatted timestamp
    ostringstream timestamp;
    
    // Format the timestamp as "YYYYMMDD-HHMMSS.sss"
    timestamp << put_time(&tmStruct, "%Y%m%d-%H%M%S");
    
    // Get the milliseconds component
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(
        currentTime.time_since_epoch() % chrono::seconds(1)
    ).count();
    
    // Add the milliseconds to the timestamp
    timestamp << "." << setfill('0') << setw(3) << milliseconds;
    
    return timestamp.str();
}

