#ifndef CITY_H
#define CITY_H
#include <string>
class City {
public:
    std::string name;
    City(const std::string& name) : name(name) {}
};
#endif
