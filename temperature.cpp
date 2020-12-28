#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>
#include "temperature.h"
#include "config.h"
#include "timeformat.h"
int Temperature::readTemperature()
{
  std::string file_path = Config::getInstance().getValue("sensorPath");
	std::string line;
	std::ifstream temperature_file(file_path);
	int retVal = 0;

// TO DO add CRC Check
	std::string delimiter = "t=";
	std::string token;
	if(temperature_file.is_open()){
		while(getline( temperature_file, line)){
			std::cout << line << std::endl;
			auto start = 0U;
			auto end = line.find(delimiter);
			while( end != std::string::npos){
				token = line.substr(start, end - start);
				start = end + delimiter.length();
				end = line.find(delimiter, start);
			}
			auto temperature =  line.substr(start, end);
			if(!temperature.empty())
				retVal = std::stoi(temperature);
		}
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
    double temperature = readTemperature() / 1000.0;
    std::cout << "temp: " << temperature << std::endl;
    std::fstream temperature_file;
    temperature_file.open( Config::getInstance().getValue("dataLocation")
    + TimeFormat::getCurrentDaystamp() + ".txt", std::fstream::app );
    if(temperature_file.is_open())
      temperature_file << TimeFormat::getCurrentTimeStamp() << '\t' << std::setprecision(5) << temperature << std::endl;
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
