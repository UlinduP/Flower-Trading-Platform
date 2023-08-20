#include "FlowerMain.h"



using namespace std;

FlowerMain::FlowerMain()
{

}

void FlowerMain::init()
{
    printMenu();   
    // string fileName;
    // getline(cin, fileName);
    // cout << "\nYour select " <<fileName<<" file." << endl;    
    
    ifstream csvFile{ "Book1.csv" };
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
            catch(const std::exception& e)
            {
                continue;
            }
        }
        cout<<roseBook.buyOrders.size()<<endl;
        csvFile.close();
    }
    else{
        cout << "Unable to open file";
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
 
void FlowerMain::orderBookMap(CSVEntry& order)
{  
    if (order.instrument == "Rose")
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            roseBook.buyOrders.push_back(orderEntry);
            //cout<<roseBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(roseBook.buyOrders.begin(), roseBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(roseBook);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            roseBook.sellOrders.push_back(orderEntry);
            sort(roseBook.sellOrders.begin(), roseBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(roseBook);
        }
    }
    else if (order.instrument == "Lavender")
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            lavBook.buyOrders.push_back(orderEntry);
            //cout<<lavBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(lavBook.buyOrders.begin(), lavBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(lavBook);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            lavBook.sellOrders.push_back(orderEntry);
            sort(lavBook.sellOrders.begin(), lavBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(lavBook);
        }
    }
    else if (order.instrument == "Lotus")
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            lotusBook.buyOrders.push_back(orderEntry);
            //cout<<lotusBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(lotusBook.buyOrders.begin(), lotusBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(lotusBook);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            lotusBook.sellOrders.push_back(orderEntry);
            sort(lotusBook.sellOrders.begin(), lotusBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(lotusBook);
        }
    }
    else if (order.instrument == "Tulip")
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            tulipBook.buyOrders.push_back(orderEntry);
            //cout<<tulipBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(tulipBook.buyOrders.begin(), tulipBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(tulipBook);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            tulipBook.sellOrders.push_back(orderEntry);
            sort(tulipBook.sellOrders.begin(), tulipBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(tulipBook);
        }
    }
    else if (order.instrument == "Orchid")
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            orchidBook.buyOrders.push_back(orderEntry);
            //cout<<orchidBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(orchidBook.buyOrders.begin(), orchidBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(orchidBook);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.quantity, order.price};
            orchidBook.sellOrders.push_back(orderEntry);
            sort(orchidBook.sellOrders.begin(), orchidBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(orchidBook);
        }
    }
    else
    {
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),order.clientID, order.instrument, to_string(order.side),"Rejected",to_string(order.quantity) , to_string(order.price), utils::getCurrentTimestamp(), "Invalid side"};
        report.writeToReport(entry);
        //cout<<"FlowerMain::orderBookMap Invalid side."<<endl;
    }
}     


void FlowerMain::match(OrderBook& OrderBook)
{

}


