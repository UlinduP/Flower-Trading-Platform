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
    double price;
    int side,quantity;

    //check if length == 5
    if (tokens.size() != 5)
    {
        //Execution report for invalid token size
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),"","","",
                                "Rejected","","","Invalid token size", utils::getCurrentTimestamp()};  
                            //"" are added since we cannot say what is present and what is not beforehand
        report.writeToReport(entry);
        throw exception();
    }

    //check if side == integer
    try {
        side = stoi(tokens[2]);
    }
    catch (exception& e) {
        //Execution report for invalid side type
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], "Side is not an integer", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw;
    }

    //check if quantity == integer
    try{
        quantity = stoi(tokens[3]);
    }
    catch (exception& e) {
        //Execution report for invalid quantity
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], "Quantity is not an integer", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw;
    }

    //check if price == double
    try{
        price = stod(tokens[4]);
    }
    catch (exception& e) {
        //Execution report for invalid price
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], "Price is not a double", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw;
    }

    //check if side == 0 or 1
    if (!(side == 2 || side == 1))
    {
        //Execution report for invalid side
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4],"Invalid side",  utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw exception{};
    }

    //check if price > 0
    else if (price <= 0)
    {
        //Execution report for invalid price
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4],"Price is not greater than 0", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw exception{};
    }

    //check if quantity is a multiple of 10
    else if (quantity%10 != 0)
    {
        //Execution report for invalid quantity
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4],"Quantity is not a multiple of 10", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw exception{};
    }

    //check if quantity is in the range of 10 to 1000
    else if (quantity<10 || quantity>1000)
    {
        //Execution report for invalid quantity
        ExecutionReportEntry entry{utils::genOrderID(utils::orderID),tokens[0],tokens[1],tokens[2],
                                "Rejected",tokens[3],tokens[4], "Quantity is not in the range of 10 to 1000", utils::getCurrentTimestamp()};
        report.writeToReport(entry);
        throw exception{};
    }

    //Create CSVEntry object if the above errors are not present
    else{
        CSVEntry csve{tokens[0],tokens[1],side,quantity,price};
        return csve;
    }
}


