#include "CSVReader.h"
#include <iostream>
#include <fstream>

using namespace std;

CSVReader::CSVReader()
{

}


/**This reads a csvFile and returns the entries as a vector of order book entries*/
vector<CSVEntry> CSVReader::readCSV(string csvFileName)
{
    vector<CSVEntry> entries;
    ifstream csvFile{ csvFileName };
    string line;
    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try {
                CSVEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const exception& e) {
                cout << "CSVReader::readCSV bad data" << endl;
            }
        }
        cout << "CSVReader::readCSV read: " << entries.size() << " entries." << endl;
        csvFile.close();
    }
    return entries;
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
CSVEntry CSVReader::stringsToOBE(vector<string> tokens)
{
    double price;
    int side,quantity;

    if (tokens.size() != 5)
    {
        cout << "Bad Line" << endl;
        throw exception{};
    }

    try {
        side = stoi(tokens[2]);
        quantity = stoi(tokens[3]);
        price = stod(tokens[4]);
        
    }
    catch (exception& e) {
        cout << "Bad Float" << endl;
        throw;
    }

    CSVEntry obe{tokens[0],tokens[1],side,quantity,price};
    return obe;
}


