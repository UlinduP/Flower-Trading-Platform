#include "CSVReader.h"
#include <iostream>
#include <fstream>

using namespace std;
ExecutionReport report;

CSVReader::CSVReader()
{

}

/**This tokenises the csv lines based on a separator*/
vector<string> CSVReader::tokenise(string csvLine, char separator)
{
    vector<string> tokens;
    signed int start, end;
    string token;
    start = csvLine.find_first_not_of(separator, 0);

    do {
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end) break;
        if (end != string::npos) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;
    } while (end != string::npos);

    return tokens;
}

/**converts string tokens to a suitable order book entry*/
CSVEntry CSVReader::tokensToCSVE(vector<string> tokens)
{
    int side, quantity;
    double price;


    //check if length == 5
    if (tokens.size() != 5)
    {
        cout << "Bad Line" << endl;
        //execution report write
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Invalid token size"};
        report.writeToReport(entry);
        throw exception();
    }

    //check if side == integer
    try {
        side = stoi(tokens[2]);
    }
    catch (exception& e) {
        cout << "Bad Float" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Side is not an integer"};
        report.writeToReport(entry);
        throw;
    }

    //check if quantity == integer
    try{
        quantity = stoi(tokens[3]);
    }
    catch (exception& e) {
        cout << "Bad Float" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Quantity is not an integer"};
        report.writeToReport(entry);
        throw;
    }

    //check if price == double
    try{
        price = stod(tokens[4]);
    }
    catch (exception& e) {
        cout << "Bad Double" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Price is not a double or integer"};
        report.writeToReport(entry);
        throw;
    }

    //check if side == 0 or 1
    if (!(side == 2 || side == 1))
    {
        cout << "Bad Side" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Invalid side"};
        report.writeToReport(entry);
        throw exception{};
    }

    //check if price > 0
    else if (price <= 0)
    {
        cout << "Invalid price" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Price is not greater than 0"};
        report.writeToReport(entry);
        throw exception{};
    }

    //check if quantity is a multiple of 10
    else if (quantity%10 != 0)
    {
        cout << "Quantity is not a multiple of 10" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Quantity is not a multiple of 10"};
        report.writeToReport(entry);
        throw exception{};
    }

    //check if quantity is in the range of 10 to 1000
    else if (quantity<10 || quantity>1000)
    {
        cout << "Quantity is not in the range of 10 to 1000" << endl;
        //write execution report
        ExecutionReportEntry entry{FlowerMain::genOrderID(FlowerMain::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], FlowerMain::getCurrentTimestamp(), "Quantity is not in the range of 10 to 1000"};
        report.writeToReport(entry);
        throw exception{};
    }

    else{
        CSVEntry csve{tokens[0],tokens[1],side,quantity,price};
        return csve;
    }
}


