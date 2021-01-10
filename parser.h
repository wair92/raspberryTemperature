#ifndef PARSER_H
#define PARSER_H
#include <optional>
#include <string>
#include <utility>

class Parser{
public:
  static std::optional<int> parseTemperature(const std::string&);
  static std::optional<std::pair<std::string, std::string>> parseConfig(const std::string&);
};
#endif
