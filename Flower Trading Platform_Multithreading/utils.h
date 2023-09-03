#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <mutex>
#include <condition_variable>

using namespace std;

class utils
{
    public:
        /*Generate a unique order ID based on the provided identifier.
        it returns a string of the generated order ID.*/
        static string genOrderID(int id);

        /*Get the current timestamp in a string format.
        it returns a string containing the current timestamp.*/
        static string getCurrentTimestamp();
        
        // Static variable to store the order ID identifier.
        static int orderID;
};