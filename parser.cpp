#include "parser.h"
#include <iostream>
std::optional<int> Parser::parseTemperature(const std::string& line){
  std::string delimiter = "t=";
	std::string token;
  auto start = 0U;
  auto end = line.find(delimiter);
  while( end != std::string::npos){
    token = line.substr(start, end - start);
    start = end + delimiter.length();
    end = line.find(delimiter, start);
  }
  if(start == 0)
    return std::nullopt;
  auto temperature =  line.substr(start, end);
  if(!temperature.empty())
  {
    try{
      auto value = std::stoi(temperature);
      return value;
    }
    catch(int e)
    {
      return std::nullopt;
    }
  }
  else
    return std::nullopt;
}

std::optional<std::pair<std::string, std::string>> Parser::parseConfig(const std::string& line){
  std::string delimiter = "=";
  if(line.empty())
    return::std::nullopt;
  if(line[0] == '#')
    return::std::nullopt;
  auto start = 0U;
  auto end = line.find(delimiter);
  while( end != std::string::npos){
    start = end + delimiter.length();
    end = line.find(delimiter, start);
  }
  if(start == 0)
    return std::nullopt;
  auto value =  line.substr(start, end);
  auto parameter = line.substr(0, start - 1);
  if(value.empty() || parameter.empty())
    return std::nullopt;
  return std::optional<std::pair<std::string, std::string>>(std::make_pair(parameter, value));
}
