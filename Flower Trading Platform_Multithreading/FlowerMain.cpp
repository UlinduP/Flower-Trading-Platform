#include "FlowerMain.h"

using namespace std;

bool readingComplete = false;
bool check = false;  //This is used to check if the reading is complete or not. Used in process functions

/*These are used for thread synchronization to ensure safe access to 
shared resources (queues, order books) among different threads.*/
std::mutex mtxRose;
std::mutex mtxLavender;
std::mutex mtxLotus;
std::mutex mtxTulip;
std::mutex mtxOrchid;
std::condition_variable cvRose;
std::condition_variable cvLavender;
std::condition_variable cvLotus;
std::condition_variable cvTulip;
std::condition_variable cvOrchid;

//Initialize queues for each flower type
std::queue<CSVEntry> RoseQueue;
std::queue<CSVEntry> LavenderQueue;
std::queue<CSVEntry> LotusQueue;
std::queue<CSVEntry> TulipQueue;
std::queue<CSVEntry> OrchidQueue;

// Constructor for the FlowerMain class.
FlowerMain::FlowerMain()
{

}

// This method is the main entry point for processing orders.
void FlowerMain::init()
{ 
    // Open the file in truncation mode to delete content
    std::ofstream truncateFile("execution_rep.csv", std::ios::trunc);
    if (truncateFile.is_open()) {
        std::cout << "Content deleted successfully." << std::endl;
        truncateFile.close();
    } else {
        std::cout << "Failed to delete content." << std::endl;
    }
    
    // print menu
    printMenu();  

    string fileName;
    cin >> fileName;


    // Get the current time before starting the code
    auto start = std::chrono::high_resolution_clock::now(); 

    std::thread roseThread([this] { processRose(); });
    std::thread lavenderThread([this] { processLavender(); });
    std::thread lotusThread([this] { processLotus(); });
    std::thread tulipThread([this] { processTulip(); });
    std::thread orchidThread([this] { processOrchid(); });
   
    ifstream csvFile{ fileName };

    string line;
    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try
            {
                CSVEntry entry = CSVReader::tokensToCSVE(CSVReader::tokenise(line, ','));
                insertToQueue(entry);
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

    cout << "CSV file reading complete. " << endl;


    readingComplete = true;
    cvRose.notify_all();
    cvLavender.notify_all();
    cvLotus.notify_all();
    cvTulip.notify_all();
    cvOrchid.notify_all();
    roseThread.join();
    lavenderThread.join();
    lotusThread.join();
    tulipThread.join();
    orchidThread.join();

    // Get the current time after the code execution
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration the code took to run
    std::chrono::duration<double> duration = end - start;

    cout<<"Processing completed. "<<endl;

    // Print the duration in seconds
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

}

// This method prints a simple menu to the console
void FlowerMain::printMenu()
{
    cout << "Welcome to Flower Exchange Paltform!\n";
    cout << "Enter your order file name: ";
}
 
//Order Matching Algorithm
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

// This method inserts orders into different queues based on the flower type.
void FlowerMain::insertToQueue(CSVEntry &order)
{
    if (order.instrument.compare("Rose")==0)
    {
        std::unique_lock<std::mutex> lock(mtxRose);
        RoseQueue.push(order);
        lock.unlock();
        cvRose.notify_all();
    }
    else if (order.instrument.compare("Lavender")==0)
    {
        std::unique_lock<std::mutex> lock(mtxLavender);
        LavenderQueue.push(order);
        lock.unlock();
        cvLavender.notify_all();
    }
    else if (order.instrument.compare("Lotus")==0)
    {
        std::unique_lock<std::mutex> lock(mtxLotus);
        LotusQueue.push(order);
        lock.unlock();
        cvLotus.notify_all();
    }
    else if (order.instrument.compare("Tulip")==0)
    {
        std::unique_lock<std::mutex> lock(mtxTulip);
        TulipQueue.push(order);
        lock.unlock();
        cvTulip.notify_all();
    }
    else if (order.instrument.compare("Orchid")==0)
    {
        std::unique_lock<std::mutex> lock(mtxOrchid);
        OrchidQueue.push(order);
        lock.unlock();
        cvOrchid.notify_all();
    }
    else 
    {
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),order.clientID, order.instrument, to_string(order.side),"Rejected",to_string(order.quantity) , to_string(order.price), "Invalid Flower Name", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
    }
}

//This method is responsible for processing orders of Rose.
void FlowerMain::processRose() {
    while (!(RoseQueue.size()==0 && readingComplete)) {
        std::unique_lock<std::mutex> lock(mtxRose);
        check = readingComplete;
        cvRose.wait(lock, [] { return !RoseQueue.empty() ||  readingComplete; });  
        
        if (!check && readingComplete && RoseQueue.empty())
        {
            break;
        }

        // Process the flower of the given type
        CSVEntry order = RoseQueue.front();
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            roseBook.buyOrders.push_back(orderEntry);
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
        RoseQueue.pop();
        lock.unlock();
        cvRose.notify_all();
    }
}

//This method is responsible for processing orders of Lavender.
void FlowerMain::processLavender() {
    while (!(LavenderQueue.size()==0 && readingComplete)) {
        std::unique_lock<std::mutex> lock(mtxLavender);
        check = readingComplete;
        cvLavender.wait(lock, [] { return !LavenderQueue.empty() || readingComplete; });

        if (!check && readingComplete && LavenderQueue.empty())
        {
            break;
        }

        // Process the flower of the given type
        CSVEntry order = LavenderQueue.front();
        if (order.side == 1)
        {
            OrderBookEntry orderEntry{utils::genOrderID(utils::orderID), order.clientID, order.quantity, order.price};
            lavBook.buyOrders.push_back(orderEntry);
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
        LavenderQueue.pop();
        lock.unlock();
        cvLavender.notify_all();
    }
}

//This method is responsible for processing orders of Lotus.
void FlowerMain::processLotus() {
    while (!(LotusQueue.size()==0 && readingComplete)) {
        std::unique_lock<std::mutex> lock(mtxLotus);
        check = readingComplete;
        cvLotus.wait(lock, [] { return !LotusQueue.empty() || readingComplete; });

        if (!check && readingComplete && LotusQueue.empty())
        {
            break;
        }

        // Process the flower of the given type
        CSVEntry order = LotusQueue.front();
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
        LotusQueue.pop();
        lock.unlock();
        cvLotus.notify_all();
    }

}

//This method is responsible for processing orders of Tulip.
void FlowerMain::processTulip() {
    while (!(TulipQueue.size()==0 && readingComplete)) {
        std::unique_lock<std::mutex> lock(mtxTulip);
        bool check = readingComplete;
        cvTulip.wait(lock, [] { return !TulipQueue.empty() || readingComplete; });

        if (!check && readingComplete && TulipQueue.empty())
        {
            break;
        }

        // Process the flower of the given type
        CSVEntry order = TulipQueue.front();
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
        TulipQueue.pop();
        lock.unlock();
        cvTulip.notify_all();
    }

}

//This method is responsible for processing orders of Orchid.
void FlowerMain::processOrchid() {
    while (!(OrchidQueue.size()==0 && readingComplete)) {
        std::unique_lock<std::mutex> lock(mtxOrchid);
        bool check = readingComplete;
        cvOrchid.wait(lock, [] { return !OrchidQueue.empty() || readingComplete; });

        if (!check && readingComplete && OrchidQueue.empty())
        {
            break;
        }
        
        // Process the flower of the given type
        CSVEntry order = OrchidQueue.front();
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
        OrchidQueue.pop();
        lock.unlock();
        cvOrchid.notify_all();
    }
}
