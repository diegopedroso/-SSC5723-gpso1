#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <string>
#include <map>
#include <vector>

// Class to read config file to set up MMU
class Properties {
private:
    std::multimap<std::string, std::string> content;
public:
    Properties(const std::string & filename);
    const std::vector<std::string> getValue(std::string const& key) const;
};

#endif