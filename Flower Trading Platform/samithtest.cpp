#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

// enum FlowerType {
//     ROSE,
//     LAVENDER,
//     TULIP,
//     DAISY,
//     SUNFLOWER,
//     // Add more flower types here
// };

// struct Flower {
//     FlowerType type;
//     double petalSize;
//     double petalLength;
// };

std::mutex mtx;
std::condition_variable cv;
std::queue<CSVEntry> RoseQueue;
std::queue<CSVEntry> LavenderQueue;
std::queue<CSVEntry> LotusQueue;
std::queue<CSVEntry> TulipQueue;
std::queue<CSVEntry> OrchidQueue;


void processRose() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return !RoseQueue.empty() && RoseQueue.front().type == type; });

        // Process the flower of the given type
        Flower flower = RoseQueue.front();
        std::string flowerName;
        switch (flower.type) {
            case ROSE: flowerName = "Rose"; break;
            case LAVENDER: flowerName = "Lavender"; break;
            case TULIP: flowerName = "Tulip"; break;
            case DAISY: flowerName = "Daisy"; break;
            case SUNFLOWER: flowerName = "Sunflower"; break;
            default: flowerName = "Unknown"; break;
        }
        std::cout << "Processing a " << flowerName << " with petal size: " << flower.petalSize << " and petal length: " << flower.petalLength << std::endl;

        flowerQueue.pop();
        lock.unlock();
        cv.notify_all();
    }
}

int main() {
    // Create threads for each flower type
    std::thread roseThread(processFlower), ROSE);
    std::thread lavenderThread(processFlower, LAVENDER);
    std::thread tulipThread(processFlower, TULIP);
    std::thread daisyThread(processFlower, DAISY);
    std::thread sunflowerThread(processFlower, SUNFLOWER);

    while (true) {
        std::string input;
        std::cout << "Enter flower type (rose/lavender/tulip/daisy/sunflower): ";
        std::cin >> input;

        FlowerType newFlowerType = FlowerType::ROSE; // Default to Rose

        if (input == "rose") {
            newFlowerType = ROSE;
        } else if (input == "lavender") {
            newFlowerType = LAVENDER;
        } else if (input == "tulip") {
            newFlowerType = TULIP;
        } else if (input == "daisy") {
            newFlowerType = DAISY;
        } else if (input == "sunflower") {
            newFlowerType = SUNFLOWER;
        } else {
            std::cout << "Invalid flower type. Please try again." << std::endl;
            continue;
        }

        double petalSize, petalLength;
        std::cout << "Enter petal size: ";
        std::cin >> petalSize;
        std::cout << "Enter petal length: ";
        std::cin >> petalLength;

        Flower newFlower = {newFlowerType, petalSize, petalLength};

        std::unique_lock<std::mutex> lock(mtx);
        flowerQueue.push(newFlower);
        lock.unlock();
        cv.notify_all();
    }

    // Join threads and cleanup
    roseThread.join();
    lavenderThread.join();
    tulipThread.join();
    daisyThread.join();
    sunflowerThread.join();

    return 0;
}
