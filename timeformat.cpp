#include "timeformat.h"
#include <chrono>

typedef std::chrono::system_clock Clock;

std::string TimeFormat::getCurrentMonth()
{
  struct tm* parts = getLocalTime();
	char buff[3];
	snprintf(buff, sizeof(buff), "%02d", parts->tm_mon + 1);
	std::string retVal = buff;
	return retVal;
}
std::string TimeFormat::getCurrentHour()
{
  struct tm* parts = getLocalTime();
	char buff[3];
	snprintf(buff, sizeof(buff), "%02d", parts->tm_hour);
	std::string retVal = buff;
	return retVal;
}
std::string TimeFormat::getCurrentDay()
{
  struct tm* parts = getLocalTime();
	char buff[3];
	snprintf(buff, sizeof(buff), "%02d", parts->tm_mday);
	std::string retVal = buff;
	return retVal;
}
std::string TimeFormat::getCurrentDaystamp()
{
  struct tm* parts = getLocalTime();
  char buff[11];
  snprintf(buff, sizeof(buff), "%04d-%02d-%02d", parts->tm_year + 1900, parts->tm_mon + 1, parts->tm_mday);
  std::string retVal = buff;
  return retVal;
}
std::string TimeFormat::getLastDayStamp()
{
  auto now = Clock::now();
  std::time_t now_c = Clock::to_time_t(now);
  now_c = now_c - (60 * 60 * 24);
  struct tm* parts = std::localtime(&now_c);
  char buff[11];
  snprintf(buff, sizeof(buff), "%04d-%02d-%02d", parts->tm_year + 1900, parts->tm_mon + 1, parts->tm_mday);
  std::string retVal = buff;
  return retVal;
}
std::string TimeFormat::getCurrentTimeStamp()
{
  struct tm* parts = getLocalTime();
  char buff[10];
  snprintf(buff, sizeof(buff), "%02d:%02d:%02d", parts->tm_hour, parts->tm_min, parts->tm_sec);
  std::string retVal = buff;
  return retVal;
}
tm* TimeFormat::getLocalTime()
{
  auto now = Clock::now();
	std::time_t now_c = Clock::to_time_t(now);
	return std::localtime(&now_c);
}
