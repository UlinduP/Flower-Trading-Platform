// Flower Trading Platform.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include "CSVReader.h"
#include "CSVEntry.h"
#include "FlowerMain.h"

using namespace std;

int main()
{
    // Get the current time before starting the code
    auto start = std::chrono::high_resolution_clock::now();
    FlowerMain app{};
    app.init();

    // Get the current time after the code execution
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration the code took to run
    std::chrono::duration<double> duration = end - start;

    // Print the duration in seconds
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

 //use below command to compile
  
 //1--> g++ OrderBookEntry.cpp OrderBook.cpp FlowerMain.cpp Flower_Trading_Platform.cpp CSVReader.cpp CSVEntry.cpp ExecutionReportEntry.cpp  ExecutionReport.cpp utils.cpp -o output
 //2--> ./output
}

