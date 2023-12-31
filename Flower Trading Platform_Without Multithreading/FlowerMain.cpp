#include "FlowerMain.h"



using namespace std;

FlowerMain::FlowerMain()
{

}

void FlowerMain::init()
{
        // Open the file in truncation mode to delete content
    std::ofstream truncateFile("execution_rep_ex7_1.csv", std::ios::trunc);
    if (truncateFile.is_open()) {
        std::cout << "Content deleted successfully." << std::endl;
        truncateFile.close();
    } else {
        std::cout << "Failed to delete content." << std::endl;
    }

    printMenu();   
    string fileName;
    getline(cin, fileName);    
    
    // Get the current time before starting the code
    auto start = std::chrono::high_resolution_clock::now();

    ifstream csvFile{ fileName };
    string line;
    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try
            {
                CSVEntry entry = CSVReader::tokensToCSVE(CSVReader::tokenise(line, ','));
                orderBookMap(entry);
            }
            catch(const std::exception& e)
            {
                continue;
            }
        }

        csvFile.close();
    }
    else{
        cout << "Unable to open file";
    }

    
    // Get the current time after the code execution
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration the code took to run
    std::chrono::duration<double> duration = end - start;

    // Print the duration in seconds
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

}

void FlowerMain::printMenu()
{
    cout << "Welcome to Flower Exchange Paltform!\n";
    cout << "Enter your order file name: ";
}
 
void FlowerMain::orderBookMap(CSVEntry& order)
{
    //cout<<order.quantity<<endl;
    if (order.instrument.compare("Rose")==0)
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            // cout<<order.quantity<<endl;
            roseBook.buyOrders.push_back(orderEntry);
            //cout<<roseBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(roseBook.buyOrders.begin(), roseBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(roseBook, order.side, "Rose",orderEntry);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            roseBook.sellOrders.push_back(orderEntry);
            sort(roseBook.sellOrders.begin(), roseBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(roseBook, order.side, "Rose",orderEntry);
        }
    }
    else if (order.instrument.compare("Lavender")==0)
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            lavBook.buyOrders.push_back(orderEntry);
            //cout<<lavBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(lavBook.buyOrders.begin(), lavBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(lavBook, order.side, "Lavender",orderEntry);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            lavBook.sellOrders.push_back(orderEntry);
            sort(lavBook.sellOrders.begin(), lavBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(lavBook, order.side, "Lavender",orderEntry);
        }
    }
    else if (order.instrument.compare("Lotus")==0)
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            lotusBook.buyOrders.push_back(orderEntry);
            //cout<<lotusBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(lotusBook.buyOrders.begin(), lotusBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(lotusBook, order.side, "Lotus",orderEntry);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            lotusBook.sellOrders.push_back(orderEntry);
            sort(lotusBook.sellOrders.begin(), lotusBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(lotusBook, order.side, "Lotus",orderEntry);
        }
    }
    else if (order.instrument.compare("Tulip")==0)
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            tulipBook.buyOrders.push_back(orderEntry);
            //cout<<tulipBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(tulipBook.buyOrders.begin(), tulipBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(tulipBook, order.side, "Tulip",orderEntry);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID),order.clientID,  order.quantity, order.price};
            tulipBook.sellOrders.push_back(orderEntry);
            sort(tulipBook.sellOrders.begin(), tulipBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(tulipBook,order.side, "Tulip",orderEntry);
        }
    }
    else if (order.instrument.compare("Orchid")==0)
    {
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            orchidBook.buyOrders.push_back(orderEntry);
            //cout<<orchidBook.buyOrders.size()<<endl;
            //cout<<"pushed"<<endl;
            sort(orchidBook.buyOrders.begin(), orchidBook.buyOrders.end(), OrderBookEntry::compareByPriceDesc);
            FlowerMain::match(orchidBook, order.side, "Orchid",orderEntry);
        }
        else if (order.side == 2)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            orchidBook.sellOrders.push_back(orderEntry);
            sort(orchidBook.sellOrders.begin(), orchidBook.sellOrders.end(), OrderBookEntry::compareByPriceAsc);
            FlowerMain::match(orchidBook, order.side, "Orchid",orderEntry);
        }
    }
    else
    {
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),order.clientID, order.instrument, to_string(order.side),"Rejected",to_string(order.quantity) , to_string(order.price), "Invalid Flower Name", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        //cout<<"FlowerMain::orderBookMap Invalid side."<<endl;
    }
}     


void FlowerMain::match(OrderBook& OrderBook, int side, string instrument, OrderBookEntry& orderEntry)
{
    if (side == 1)  //1: Buy , 2: Sell
    {
        if (OrderBook.sellOrders.size() > 0 && OrderBook.buyOrders.size() > 0)
        {
            if (OrderBook.sellOrders[0].price <= OrderBook.buyOrders[0].price)
            {
                if (OrderBook.sellOrders[0].quantity > OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "PFill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    OrderBook.sellOrders[0].quantity -= OrderBook.buyOrders[0].quantity;
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                }
                else if (OrderBook.sellOrders[0].quantity == OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                }
                else 
                {
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "PFill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    OrderBook.buyOrders[0].quantity -= OrderBook.sellOrders[0].quantity;
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                    FlowerMain::match2(OrderBook, side, instrument);
                }
            }
            else
            {
                ExecutionReportEntry buy_entry{orderEntry.orderID,orderEntry.clientID, instrument, "1", "New", to_string(orderEntry.quantity), to_string(orderEntry.price), "NA", utils::getCurrentTimestamp()};
                report.writeToReport(buy_entry);
            }
        }
        else
        {
            ExecutionReportEntry buy_entry{orderEntry.orderID,orderEntry.clientID, instrument, "1", "New", to_string(orderEntry.quantity), to_string(orderEntry.price), "NA", utils::getCurrentTimestamp()};
            report.writeToReport(buy_entry);
        }
    }
    else if (side == 2)
    {
        if (OrderBook.sellOrders.size() > 0 && OrderBook.buyOrders.size() > 0)
        {
            if (OrderBook.sellOrders[0].price <= OrderBook.buyOrders[0].price)
            {
                if (OrderBook.sellOrders[0].quantity > OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "PFill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    OrderBook.sellOrders[0].quantity -= OrderBook.buyOrders[0].quantity;
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                    FlowerMain::match2(OrderBook, side, instrument);
                }
                else if (OrderBook.sellOrders[0].quantity == OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                }
                else 
                {
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "PFill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    OrderBook.buyOrders[0].quantity -= OrderBook.sellOrders[0].quantity;
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                }
            }
            else
            {
                ExecutionReportEntry sell_entry{orderEntry.orderID,orderEntry.clientID, instrument, "2", "New", to_string(orderEntry.quantity), to_string(orderEntry.price), "NA", utils::getCurrentTimestamp()};
                report.writeToReport(sell_entry);
            }
        }
        else
        {
            ExecutionReportEntry sell_entry{orderEntry.orderID,orderEntry.clientID, instrument, "2", "New", to_string(orderEntry.quantity), to_string(orderEntry.price), "NA", utils::getCurrentTimestamp()};
            report.writeToReport(sell_entry);
        }
    }
}


void FlowerMain::match2(OrderBook& OrderBook, int side, string instrument)
{
    if (side == 1)  //1: Buy , 2: Sell
    {
        if (OrderBook.sellOrders.size() > 0 && OrderBook.buyOrders.size() > 0)
        {
            if (OrderBook.sellOrders[0].price <= OrderBook.buyOrders[0].price)
            {
                if (OrderBook.sellOrders[0].quantity > OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "PFill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    OrderBook.sellOrders[0].quantity -= OrderBook.buyOrders[0].quantity;
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                }
                else if (OrderBook.sellOrders[0].quantity == OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                }
                else 
                {
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "PFill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.sellOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    OrderBook.buyOrders[0].quantity -= OrderBook.sellOrders[0].quantity;
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                    FlowerMain::match2(OrderBook, side, instrument);
                }
            }
        }
    }
    else if (side == 2)
    {
        if (OrderBook.sellOrders.size() > 0 && OrderBook.buyOrders.size() > 0)
        {
            if (OrderBook.sellOrders[0].price <= OrderBook.buyOrders[0].price)
            {
                if (OrderBook.sellOrders[0].quantity > OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "PFill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    OrderBook.sellOrders[0].quantity -= OrderBook.buyOrders[0].quantity;
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                    FlowerMain::match2(OrderBook, side, instrument);
                }
                else if (OrderBook.sellOrders[0].quantity == OrderBook.buyOrders[0].quantity)
                {
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "Fill", to_string(OrderBook.buyOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                    OrderBook.buyOrders.erase(OrderBook.buyOrders.begin());
                }
                else 
                {
                    ExecutionReportEntry sell_entry{OrderBook.sellOrders[0].orderID,OrderBook.sellOrders[0].clientID, instrument, "2", "Fill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(sell_entry);
                    ExecutionReportEntry buy_entry{OrderBook.buyOrders[0].orderID,OrderBook.buyOrders[0].clientID, instrument, "1", "PFill", to_string(OrderBook.sellOrders[0].quantity), to_string(OrderBook.buyOrders[0].price), "NA", utils::getCurrentTimestamp()};
                    report.writeToReport(buy_entry);
                    OrderBook.buyOrders[0].quantity -= OrderBook.sellOrders[0].quantity;
                    OrderBook.sellOrders.erase(OrderBook.sellOrders.begin());
                }
            }
        }
    }
}

