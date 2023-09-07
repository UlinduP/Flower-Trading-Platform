# Flower Trading Platform

## Introduction

Welcome to the Flower Trading Platform! This C++ project using Object Oriented Concepts is designed to provide a user-friendly and efficient platform for trading flowers. This is done for educational purposes.
## Features

- **Input**: Given as a CSV file of entries.

- **Output**: A generated CSV file of transactions.

## Performance

We achieved the following results on an HP Pavilion Laptop 15-cs3xxx running Windows 11 Home. Please find the geekbench scores [here](https://browser.geekbench.com/v6/compute/816667).

| Number of CSV entries | With-Multithreading (sec)| Without-Multithreading (sec)|
|-----------------|-----------------|-----------------|
| 1 500 | 0.377 |  0.395 |
| 25 000 | |   |
| 100 000 | 102.23 | 182.27 |



## Requirements

- C++ Compiler (e.g., g++)
- Standard Template Library (STL)

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/UlinduP/Flower-Trading-Platform.git
   cd flower-trading-platform/relevant folder

2. Compile the project:
   ```bash
   g++ OrderBookEntry.cpp OrderBook.cpp FlowerMain.cpp Flower_Trading_Platform.cpp CSVReader.cpp CSVEntry.cpp ExecutionReportEntry.cpp  ExecutionReport.cpp utils.cpp -o output

4. Run the application:
   ```bash
   ./output.exe

