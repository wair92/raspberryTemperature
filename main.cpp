#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

typedef std::chrono::system_clock Clock;

int readTemperature(){
	std::string file_path = "/sys/bus/w1/devices/28-3c01a816ee9c/w1_slave";
	std::string line;
	std::ifstream temperature_file(file_path);
	int retVal = 0;

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

tm* getLocalTime(){
	auto now = Clock::now();
	std::time_t now_c = Clock::to_time_t(now);
	return std::localtime(&now_c);	
}

std::string getCurrentMonth(){
	struct tm* parts = getLocalTime();
	char buff[3];
	snprintf(buff, sizeof(buff), "%02d", parts->tm_mon + 1);
	std::string retVal = buff;
	return retVal;
}

std::string getCurrentHour(){
	struct tm* parts = getLocalTime();
	char buff[3];
	snprintf(buff, sizeof(buff), "%02d", parts->tm_hour);
	std::string retVal = buff;
	return retVal;
}

std::string getCurrentDay(){
	struct tm* parts = getLocalTime();
	char buff[3];
	snprintf(buff, sizeof(buff), "%02d", parts->tm_mday);
	std::string retVal = buff;
	return retVal;
}

std::string getCurrentDaystamp(){
	struct tm* parts = getLocalTime();
	char buff[11];
	snprintf(buff, sizeof(buff), "%04d-%02d-%02d", parts->tm_year + 1900, parts->tm_mon + 1, parts->tm_mday);
	std::string retVal = buff;
	return retVal;
}

std::string getLastDayStamp(){
	auto now = Clock::now();
	std::time_t now_c = Clock::to_time_t(now);
	now_c = now_c - (60 * 60 * 24);
	struct tm* parts = std::localtime(&now_c);
	char buff[11];
	snprintf(buff, sizeof(buff), "%04d-%02d-%02d", parts->tm_year + 1900, parts->tm_mon + 1, parts->tm_mday);
	std::string retVal = buff;
	return retVal;
}

std::string getCurrentTimeStamp(){
	struct tm* parts = getLocalTime();
	char buff[10];
	snprintf(buff, sizeof(buff), "%02d:%02d:%02d", parts->tm_hour, parts->tm_min, parts->tm_sec);
	std::string retVal = buff;
	return retVal;
}

void copy_backup_file(const std::string& backupPath ){
	std::string file_for_backup = "/home/martin92/C++/tempsensor/data/" + getLastDayStamp() + ".txt"; 
	std::cout << "Copying file " << file_for_backup << " to: " << backupPath << std::endl;
	std::ifstream src ( file_for_backup, std::ios::binary);
	std::ofstream dst( backupPath + getLastDayStamp() + ".txt", std::ios::binary | std::fstream::app);
	dst << src.rdbuf();
	return;
}

void readTemperatureWorker(){
	std::cout << "Starting Reading Temperature" << std::endl;
	while(true){
		double temperature = readTemperature() / 1000.0;
		std::cout << "temp: " << temperature << std::endl;
		std::fstream temperature_file;
		temperature_file.open( "/home/martin92/C++/tempsensor/data/" + getCurrentDaystamp() + ".txt", std::fstream::app );
		if(temperature_file.is_open())
			temperature_file << getCurrentTimeStamp() << '\t' << std::setprecision(5) << temperature << std::endl;
		else
			std::cout << "Unable to open file: " << "data/" << getCurrentDaystamp() << ".txt" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(360));
	}
	return;
}

void backupWorker(){
	std::cout << "Backup activated" << std::endl;
	while(true){
		bool time_not_corrected = true;
		while(time_not_corrected){
			auto hour = getCurrentHour();
			if(hour == "01"){
				time_not_corrected = false;
				break;
			}
			else
				std::this_thread::sleep_for(std::chrono::hours(1));
		}
		copy_backup_file("/media/martin92/MARTIN64/temperature/");
		std::this_thread::sleep_for(std::chrono::hours(24));
	}
	return;
}

int main(){
	std::cout << "Runing application" << std::endl;
	std::thread temperature_reader(readTemperatureWorker);
	std::thread backup(backupWorker);
	temperature_reader.join();
	backup.join();
}
