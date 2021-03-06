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
		auto filename = Config::getInstance().getValue("plotScriptPath");
		std::string command = "python ";
		command += filename;
    command += " ";
    command += Config::getInstance().getValue("dataLocation");
    command += " ";
    auto hour = TimeFormat::getCurrentHour();
    if(hour == Config::getInstance().getValue("backupHour")){
      command += TimeFormat::getLastDayStamp();
    }
    else{
      command += TimeFormat::getCurrentDaystamp();
    }

		system(command.c_str());

    std::cout << command << std::endl;

		std::string picture_file_for_backup = Config::getInstance().getValue("dataLocation")
     + TimeFormat::getCurrentDaystamp() + ".png";
		copy_backup_file( Config::getInstance().getValue("backupDirectory"), picture_file_for_backup );

		std::this_thread::sleep_for(std::chrono::minutes(5));
	}
	return;
}
void Backup::copy_backup_file(const std::string& backupPath,
    const std::string& file_for_backup)
{
  std::cout << "Copying file " << file_for_backup << " to: " << backupPath << std::endl;
	std::ifstream src ( file_for_backup, std::ios::binary);
	std::ofstream dst( backupPath + TimeFormat::getCurrentDaystamp() + ".png",
    std::ios::binary | std::ofstream::trunc);
	dst << src.rdbuf();
	return;
}
