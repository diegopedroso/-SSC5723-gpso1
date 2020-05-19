#include <iostream>
#include "Properties.h"
#include "Mmu.h"
#include <fstream>

using namespace std;

int main() {
    // Setting up the MMU
    Properties props("config.cfg");
    int pageSize = std::stoi(props.getValue("page_size")[0]);
    int logicalAddressSize = std::stoi(props.getValue("logical_adress_size")[0]);
    int physicalMemorySize = std::stoi(props.getValue("physical_memory_size")[0]);
    int algorithm = props.getValue("replacement_algorithm")[0].compare("lru") ? SECOND_CHANCE : LRU;
    MMU mmu(pageSize, logicalAddressSize, physicalMemorySize, algorithm);

    // Simulating the simulation file
    std::ifstream file("simulation.txt");
    std::string line, address;
    size_t pos;
    while(std::getline(file, line)) {
        if(!line.length() || line[0] == '#') continue;

        cout << line << ' ';
        pos = line.find_last_of(' ');
        address = line.substr(pos + 1);
        if(!mmu.find(address)) {
            mmu.replace(address);
        }
        for(int i = 0; i < physicalMemorySize; ++i) {
            std::cout << "Page " << mmu.physicalMemory[i].number << ": ";
            if(mmu.replacementAlgorithm == LRU)
                cout << "Counter: " << mmu.physicalMemory[i].accessTime << '\n';
            else
                cout << "Second chance bit: " << mmu.physicalMemory[i].secondChance << '\n';
        }
    }

    system("pause");
}