#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

class utils
{
    public:
        static string genOrderID(int id);
        static string getCurrentTimestamp();
        
        static int orderID;
};