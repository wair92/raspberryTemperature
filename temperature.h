#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <optional>

class Temperature{
public:
  void readTemperatureWorker();
  std::optional<int> readTemperature();
  bool checkCRC(const std::string& line);
};

#endif
