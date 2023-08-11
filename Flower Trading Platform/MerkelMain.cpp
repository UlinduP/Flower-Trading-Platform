#include "MerkelMain.h"


int MerkelMain::orderID = 1;
ExecutionReport report;

using namespace std;

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
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

void MerkelMain::printMenu()
{
    cout << "Welcome to Flower Exchange Paltform!\n";
    cout << "Enter your order file name: " << endl;
}
 
void MerkelMain::orderBookMap(CSVEntry order)
{      
    if (order.instrument == "Rose")
    {
        OrderBook roseBook;
        OrderBookEntry roseOrder{genOrderID(orderID), order.side, order.quantity, order.price};
        roseBook.orders.push_back(roseOrder);
        cout<<"MerkelMain::orderBookMap Rose"<<endl;
    }
    else if (order.instrument == "Lavender")
    {
        OrderBook lavBook;
        OrderBookEntry lavOrder{genOrderID(orderID), order.side, order.quantity, order.price};
        lavBook.orders.push_back(lavOrder);
        //cout<<lavBook.orders[0].orderID<<endl;
    }
    else if (order.instrument == "Lotus")
    {
        OrderBook lotusBook;
        OrderBookEntry lotusOrder{genOrderID(orderID), order.side, order.quantity, order.price};
        lotusBook.orders.push_back(lotusOrder);
        //cout<<lotusBook.orders[0].orderID<<endl;
    }
    else if (order.instrument == "Tulip")
    {
        OrderBook  tulipBook;
        OrderBookEntry  tulipOrder{genOrderID(orderID), order.side, order.quantity, order.price};
        tulipBook.orders.push_back(tulipOrder);
        //cout<< tBook.orders[0].orderID<<endl;
    }
    else if (order.instrument == "Orchid")
    {
        OrderBook orchidBook;
        OrderBookEntry orchidOrder{genOrderID(orderID), order.side, order.quantity, order.price};
        orchidBook.orders.push_back(orchidOrder);
        //cout<<orchidBook.orders[0].orderID<<endl;
    }
    else 
    {
        ExecutionReportEntry entry{order.clientID,genOrderID(orderID), "Invalid", order.side, order.price,order.quantity, 1, getCurrentTimestamp(), "Invalid instrument"};
        report.writeToReport(entry);
        cout<<"MerkelMain::orderBookMap tup error"<<endl;
    }    
    
}

string MerkelMain::genOrderID(int id)
{
    string strOrderID = "ord";
    strOrderID += to_string(id);
    MerkelMain::orderID++;
    return strOrderID;
}

string MerkelMain::getCurrentTimestamp() 
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

