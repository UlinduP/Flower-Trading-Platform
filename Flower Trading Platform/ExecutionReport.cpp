#include "ExecutionReport.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

std::mutex mtx;
std::condition_variable cv;

// Output the execution execution_rep.csv file
ExecutionReport::ExecutionReport()
{
    
}


// Output the execution execution_rep.csv file
void ExecutionReport::writeToReport(ExecutionReportEntry data)
{
    std::unique_lock<std::mutex> lock(mtx);
    csvFile.open("execution_rep.csv",std::ios::out | std::ios::app);
    vector<string> strData = objToString(data);
    if (!csvFile.is_open()) {
        cerr << "Error opening the execution_rep.csv file!" << endl;
    }

    // Write data to the file
    for (string& field : strData) {
        csvFile << field;
        if (&field != &strData.back()) {
            csvFile << ",";  // Add comma between values
        }
    }
    csvFile << "\n";  // Add newline after each row

    // Close the file
    csvFile.close();
    
    lock.unlock();
    cv.notify_all();

}

// Convert the object to string
vector<string> ExecutionReport::objToString(ExecutionReportEntry data)
{
    vector<string> strData;
    strData.push_back(data.orderID);
    strData.push_back(data.clientID);
    strData.push_back(data.instrument);
    strData.push_back(data.side);
    strData.push_back(data.status);
    strData.push_back(data.quantity);
    strData.push_back(formatPrice(data.price));
    strData.push_back(data.reason);
    strData.push_back(data.timeStamp); // Add newline after each row
    return strData;
}


// Format the price to 2 decimal places
string ExecutionReport::formatPrice(string price)
{
    int pos = price.find(".");
    if (pos != string::npos) {
        price = price.substr(0, pos + 3);
    }
    return price;
}