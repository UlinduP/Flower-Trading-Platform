#include "FlowerMain.h"

using namespace std;

int FlowerMain::orderID = 1;
OrderBook roseBook;
OrderBook lavBook;
OrderBook lotusBook;
OrderBook tulipBook;
OrderBook orchidBook; 
ExecutionReport Report;


FlowerMain::FlowerMain()
{

}

void FlowerMain::init()
{
    printMenu();   
    string fileName;
    getline(cin, fileName);
    cout << "\nYour select " <<fileName<<" file." << endl;    
    
    ifstream csvFile{fileName};
    string line;
    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try
            {
                CSVEntry entry = CSVReader::tokensToCSVE(CSVReader::tokenise(line, ','));
                orderBookMap(entry);
                //match(flower);
                cout<<line<<endl;
                ///////add the adding to the respective order book here
            }
            catch(exception& e)
            {
                continue;
            }
        }
    }
    else{
        cout << "Unable to open file";
    } 
    cout<<"Total Orders: "<<orderID-1<<endl;
    csvFile.close();
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
    vector<OrderBook> orderbooks = {roseBook, lavBook, lotusBook, tulipBook, orchidBook};
    vector<string> instruments = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
    for (int i=0;i<=instruments.size();i++)
    {
        if (order.instrument == instruments[i])
        {
            if (order.side == 1)
            {
                OrderBookEntry orderEntry{genOrderID(orderID), order.quantity, order.price};
                orderbooks[i].buyOrders.push_back(orderEntry);
                //cout<<orderbooks[i].buyOrders.size()<<endl;
                //cout<<"pushed"<<endl;
                sort(orderbooks[i].buyOrders.begin(), orderbooks[i].buyOrders.end(), OrderBookEntry::compareByPriceDesc);
                // FlowerMain::match(orderbooks[i]);
            }
            else if (order.side == 2)
            {
                OrderBookEntry orderEntry{genOrderID(orderID), order.quantity, order.price};
                orderbooks[i].sellOrders.push_back(orderEntry);
                sort(orderbooks[i].sellOrders.begin(), orderbooks[i].sellOrders.end(), OrderBookEntry::compareByPriceAsc);
                // FlowerMain::match(orderbooks[i]);
            }
        }
        else
        {
            ExecutionReportEntry entry{genOrderID(orderID),order.clientID, order.instrument, to_string(order.side),"Rejected",to_string(order.quantity),to_string(order.price), getCurrentTimestamp(), "Invalid instrument"};
            Report.writeToReport(entry);
        }
    }
}     


// void FlowerMain::match(OrderBook& orderbook)
// {
//     return;
// }


string FlowerMain::genOrderID(int id)
{
    string strOrderID = "ord";
    strOrderID += to_string(id);
    orderID++;
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

