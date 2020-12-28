#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include "backup.h"
#include "config.h"
#include "timeformat.h"

void Backup::backupWorker()
{
  std::cout << "Backup activated" << std::endl;
	while(true){
		bool time_not_corrected = true;
		while(time_not_corrected){
			auto hour = TimeFormat::getCurrentHour();
      std::cout << hour << " " << Config::getInstance().getValue("backupHour") << std::endl;
			if(hour == Config::getInstance().getValue("backupHour")){
				time_not_corrected = false;
				break;
			}
			else
				std::this_thread::sleep_for(std::chrono::hours(1));
		}

		auto data_file_for_backup = Config::getInstance().getValue("dataLocation")
     + TimeFormat::getLastDayStamp() + ".txt";
		copy_backup_file(Config::getInstance().getValue("backupDirectory"), data_file_for_backup );

		auto filename = Config::getInstance().getValue("plotScriptPath");
		std::string command = "python ";
		command += filename;
    command += " ";
    command += Config::getInstance().getValue("dataLocation");
    command += " ";
    command += TimeFormat::getLastDayStamp();
		system(command.c_str());

    std::cout << command << std::endl;

		std::string picture_file_for_backup = Config::getInstance().getValue("dataLocation")
     + TimeFormat::getLastDayStamp() + ".png";
		copy_backup_file( Config::getInstance().getValue("backupDirectory"), picture_file_for_backup );

		std::this_thread::sleep_for(std::chrono::hours(24));
	}
	return;
}
void Backup::copy_backup_file(const std::string& backupPath,
    const std::string& file_for_backup)
{
  std::cout << "Copying file " << file_for_backup << " to: " << backupPath << std::endl;
	std::ifstream src ( file_for_backup, std::ios::binary);
	std::ofstream dst( backupPath + TimeFormat::getLastDayStamp() + ".txt",
    std::ios::binary | std::fstream::app);
	dst << src.rdbuf();
	return;
}
