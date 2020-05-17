#include "Properties.h"
#include <fstream>

Properties::Properties(const std::string & filename) {
    std::ifstream file(filename.c_str());
    std::string line, name, value, token;
    size_t pos;

    while(std::getline(file, line)) {
        if(!line.length() || line[0] == '#') continue;

        pos = line.find('=');
        name = line.substr(0, pos);
        value = line.substr(pos + 1);

        while((pos = value.find_first_of(" ;")) != std::string::npos) {
            token = value.substr(0, pos);
            content.insert(std::pair<std::string, std::string>(name, token));
            value.erase(0, pos + 1);
        }
    }

    file.close();
}

const std::vector<std::string> Properties::getValue(std::string const & key) const {
    std::vector<std::string> result;
    std::pair<std::multimap<std::string, std::string>::const_iterator, std::multimap<std::string, std::string>::const_iterator> range = content.equal_range(key);

    std::multimap<std::string, std::string>::const_iterator it = range.first;
    do {
        result.push_back(it->second);
        ++it;
    } while(it != range.second);

    return result;
}