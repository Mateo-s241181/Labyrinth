#include <iostream>
#include <sstream>
#include <string>

std::string greet(std::string const& name) {
    std::ostringstream out;
    out << "Hello " << name << "!" << std::endl;
    return out.str();
  }