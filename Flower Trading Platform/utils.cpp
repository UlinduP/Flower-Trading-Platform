#include "utils.h"

using namespace std;

// Initialize the order ID to 1.
int utils::orderID = 1;

// Generate a unique order ID based on the provided identifier.
string utils::genOrderID(int id)
{
    string strOrderID = "ord" + to_string(id);
    utils::orderID++;
    return strOrderID;
}

// Get the current timestamp in a string format.
string utils::getCurrentTimestamp() 
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

