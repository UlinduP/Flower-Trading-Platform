#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CSVEntry
{
    public:  //means we can access these outside the class
         CSVEntry(        //constructor
            string _clientID,
            string _instrument,
            int _side,
            int _quantity,
            double _price);

            string clientID;
            string instrument;
            int side;
            int quantity;
            double price;  


};