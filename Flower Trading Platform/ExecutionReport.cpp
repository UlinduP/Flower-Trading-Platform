#include "ExecutionReport.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Output the execution execution_rep.csv file
ExecutionReport::ExecutionReport()
{
    
}


// Output the execution execution_rep.csv file
void ExecutionReport::writeToReport(ExecutionReportEntry data)
{   
    csvFile.open("execution_rep.csv");
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

    cout << "Data written to execution_rep.csv" << endl;

}

// Convert the object to string
vector<string> ExecutionReport::objToString(ExecutionReportEntry data)
{
    vector<string> strData;
    strData.push_back(data.clientID);
    strData.push_back(data.orderID);
    strData.push_back(data.instrument);
    strData.push_back(to_string(data.side));
    strData.push_back(to_string(data.quantity));
    strData.push_back(to_string(data.price));
    strData.push_back(data.status);
    strData.push_back(data.timeStamp); 
    strData.push_back(data.reason);// Add newline after each row
    return strData;
}
