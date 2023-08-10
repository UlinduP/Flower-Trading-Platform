#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"
#include <string>


int MerkelMain::orderID = 1;

using namespace std;

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    // printMenu();   
    // string fileName;
    // getline(cin, fileName);
    // std::cout << "\nYour select " <<fileName<<" file." << std::endl;    
    
    // // read the csv file
    // entries = CSVReader::readCSV(fileName);
    // // create a map of order books
    // orderBookMap(entries);
    ExecutionReport report;
    ExecutionReportEntry data{"ord1", "aa13", "Rose", 2, 55.00, 100,0, "2020-01-01 10:00:00"};  
    report.writeToReport(data);

}

void MerkelMain::printMenu()
{
    cout << "Welcome to Flower Exchange Paltform!\n";
    cout << "Enter your order file name: " << endl;
}
 
void MerkelMain::orderBookMap(vector<CSVEntry> entries)
{   
    for (CSVEntry& e : entries)
    {
        if (e.instrument == "Rose")
        {
            OrderBook roseBook;
            roseBook.orders.push_back(OrderBookEntry(genOrderID(orderID), e.side, e.quantity, e.price));
            cout<<roseBook.orders[0].orderID<<endl;
        }
    }
}

string MerkelMain::genOrderID(int id)
{
    string strOrderID = "ord";
    strOrderID += to_string(id);
    MerkelMain::orderID++;
    return strOrderID;
}
