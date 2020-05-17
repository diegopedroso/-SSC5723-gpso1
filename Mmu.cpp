#include "Mmu.h"
#include <cmath>
#include <iostream>

MMU::MMU(int pageSize, int logicalAddressSize, int physicalMemorySize) {
    this->pageSize = pageSize;
    this->logicalAddressSize = logicalAddressSize;
    this->physicalMemorySize = physicalMemorySize;

    this->virtualPageNumberBits = int (logicalAddressSize - log2(pageSize));
    this->virtualMemorySize = int (pow(2, virtualPageNumberBits));
    virtualMemory.resize(virtualMemorySize);
}

bool MMU::find(std::string virtualAddress) {
    int virtualPageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    if(virtualMemory[virtualPageNumber].number != -1) {
        std::cout << "Page " << virtualPageNumber << " found!\n";
        return true;
    } else {
        std::cout << "Page fault " << virtualPageNumber << "!\n";
        return false;
    }
}

void MMU::replace(std::string virtualAddress) {
    secondChance(std::stoi(virtualAddress.substr(virtualPageNumberBits+1), nullptr, 2));
}

void MMU::secondChance(int key) {
    static int pointer = 0;
    // static bool * secondChances = new bool[virtualMemorySize];
    while(true) {
        if(!virtualMemory[pointer].secondChance) {
            virtualMemory[pointer].number = key;
            pointer = (pointer + 1) % virtualMemorySize;
            return;
        }
        virtualMemory[pointer].secondChance = false;
        pointer = (pointer + 1) % virtualMemorySize;
    }
}