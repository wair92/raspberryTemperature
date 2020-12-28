#include <string>
#include <iostream>
#include <thread>
#include <stdlib.h>

#include "temperature.h"
#include "backup.h"
#include "config.h"

int main(){
	if(!Config::getInstance().checkConfigFile()){
		std::cout << "Inconsistent config file" << std::endl;
		return 1;
	}

	std::cout << "Runing application" << std::endl;
	std::thread temperature_reader(&Temperature::readTemperatureWorker, Temperature());
	std::thread backup_thread(&Backup::backupWorker, Backup());
	temperature_reader.join();
	backup_thread.join();

	return 0;
}
