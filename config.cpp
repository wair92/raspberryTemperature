#include "config.h"
#include "parser.h"
#include <map>
#include <iostream>
#include <fstream>
#include <optional>
#include <utility>
Config::Config(const std::string& configFileName ){
  std::ifstream configFile( configFileName );
  if(configFile.is_open()){
      std::string line = "";
  		while(getline( configFile, line)){
      std::optional<std::pair<std::string, std::string>> insertion = Parser::parseConfig(line);
      if(insertion)
        config_.insert(*insertion);
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
