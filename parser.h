#ifndef PARSER_H
#define PARSER_H
#include <optional>
#include <string>

class Parser{
public:
  static std::optional<int> parseTemperature(const std::string&);
};
#endif
