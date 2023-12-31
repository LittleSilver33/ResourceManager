#include "include/usage.h"
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>

std::vector<long long> readCPUTimes() {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);
    istringstream stream(line);

    std::string CPUType;
    long long CPUTime;
    std::vector<long long> times;
    // Take the CPU message
    stream >> CPUType; 
    while(stream >> CPUTime) {
        times.push_back(CPUTime);
    }

    file.close();

    return times;
}

float cpuUsage() {
    // Read in the cpuModes and keep the returned vector
    // Then sum all of the values accross a small break and then
    // return a percentage as a float

    std::vector<long long> times1 = readCPUTimes();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::vector<long long> times2 = readCPUTimes();

    if(times1.size() != times2.size()) {
        std::cerr("Error: CPU Times of different length.");
    }

    long long total1 = 0, total2 = 0;

    for(size_t i = 0; i<times1.size(); i++) {
        total1 += times1[i];
        total2 += times2[i];
    }

    long long idle1 = times1[3] + times1[4];
    long long idle2 = times2[3] + times2[4];

    float usagePercentage = (((float)(idle2 - idle1) / (total2 - total1))) * 100.0;

    return usagePercentage;
}    

float memUsage() {
    std::ifstream file("/proc/meminfo");
    int memTotal, memFree;

    file >> memTotal >> memFree;

    file.close();

    return ((float)memTotal) / memFree;
}

float diskUsage() {

}

float networkUsage() {

}

