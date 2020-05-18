#include "Mmu.h"
#include <cmath>
#include <iostream>

MMU::MMU(int pageSize, int logicalAddressSize, int physicalMemorySize) {
    this->pageSize = pageSize;
    this->logicalAddressSize = logicalAddressSize;
    this->physicalMemorySize = physicalMemorySize;

    this->virtualPageNumberBits = int (logicalAddressSize - log2(pageSize));
    // this->virtualMemorySize = int (pow(2, virtualPageNumberBits));
    // physicalMemory.resize(physicalMemorySize);
    this->physicalMemory = new Page[physicalMemorySize];
}

MMU::~MMU() {
    delete []physicalMemory;
}

bool MMU::find(std::string virtualAddress) {
    int pageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    for(int i = 0; i < physicalMemorySize; ++i) {
        if(physicalMemory[i].number == pageNumber) {
            std::cout << "Page " << pageNumber << " found!\n";
            physicalMemory[i].secondChance = true;
            return true;
        }
    }
    std::cout << "Page fault " << pageNumber << "!\n";
    return false;
}

void MMU::replace(std::string virtualAddress) {
    int pageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    secondChance(pageNumber);
}

void MMU::secondChance(int key) {
    static int pointer = 0;
    // static bool * secondChances = new bool[virtualMemorySize];
    while(true) {
        if(!physicalMemory[pointer].secondChance) {
            physicalMemory[pointer].number = key;
            physicalMemory[pointer].secondChance = true;
            pointer = (pointer + 1) % physicalMemorySize;
            return;
        }
        physicalMemory[pointer].secondChance = false;
        pointer = (pointer + 1) % physicalMemorySize;
    }
}