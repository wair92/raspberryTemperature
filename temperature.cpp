#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>
#include <optional>
#include "temperature.h"
#include "config.h"
#include "timeformat.h"
#include "parser.h"
std::optional<int> Temperature::readTemperature()
{
  std::string file_path = Config::getInstance().getValue("sensorPath");
	std::string line;
	std::ifstream temperature_file(file_path);
	auto retVal = std::optional<int>();
  
	if(temperature_file.is_open()){
      getline(temperature_file, line);
      if(!checkCRC(line)){
        return std::nullopt;
      }
		  getline( temperature_file, line);
      retVal = Parser::parseTemperature(line);

		temperature_file.close();
	}
	else{
		std::cout << "Unable to open file " << file_path << std::endl;
	}
	return retVal;
}
void Temperature::readTemperatureWorker()
{
  std::cout << "Starting Reading Temperature" << std::endl;
  while(true){
    auto temp  = readTemperature();
    if(!temp)
    {
      std::this_thread::sleep_for(
        std::chrono::seconds(10));
        continue;
    }
    double temperature = *temp / 1000.0;
    std::cout << "temp: " << temperature << std::endl;
    std::fstream temperature_file;
    temperature_file.open( Config::getInstance().getValue("dataLocation")
    + TimeFormat::getCurrentDaystamp() + ".txt", std::fstream::app );
    if(temperature_file.is_open())
      temperature_file << TimeFormat::getCurrentTimeStamp() << '\t' << temperature << std::endl;
    else{
      std::cout << "Unable to open file: "
      << Config::getInstance().getValue("dataLocation")
      << TimeFormat::getCurrentDaystamp() << ".txt" << std::endl;
    }
    std::this_thread::sleep_for(
      std::chrono::seconds(
        std::stoi(Config::getInstance().getValue("measureInterval")) ));
  }
  return;
}

bool Temperature::checkCRC(const std::string& line){
    auto index = line.find_last_of( ' ' );
    auto crc = line.substr(index+1);
    if(crc == "YES")
        return true;
    else
        return false;
}
