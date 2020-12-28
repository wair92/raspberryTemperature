#include "config.h"
#include <map>
#include <iostream>
#include <fstream>

Config::Config(const std::string& configFileName ){
  std::ifstream configFile( configFileName );
  if(configFile.is_open()){
    std::string delimiter = "=";
    std::string line = "";
  		while(getline( configFile, line)){
        if(line.empty())
          continue;
        if(line[0] == '#')
          continue;
  			auto start = 0U;
  			auto end = line.find(delimiter);
  			while( end != std::string::npos){
  				//token = line.substr(start, end - start);
  				start = end + delimiter.length();
  				end = line.find(delimiter, start);
  			}
        auto value =  line.substr(start, end);
        auto parameter = line.substr(0, start - 1);
        config_.insert({ parameter, value });
  	}
    configFile.close();
  }
	else{
		std::cout << "Unable to open file " << configFileName << std::endl;
	}
}
std::string Config::getValue( const std::string& parameter){
  return config_[parameter];
}

bool Config::checkConfigFile(){
  if(Config::getInstance().getValue("measureInterval").empty()
  || Config::getInstance().getValue("sensorPath").empty()
  || Config::getInstance().getValue("dataLocation").empty()
  || Config::getInstance().getValue("backupHour").empty()
  || Config::getInstance().getValue("backupDirectory").empty()
  )
    return false;
  else
    return true;
}
