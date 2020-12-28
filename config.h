#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

class Config{
public:
  static Config& getInstance()
    {
        static Config instance;
        return instance;
    }
    Config(Config const&) = delete;
    void operator=(Config const&) = delete;

  std::string getValue( const std::string& parameter);
  bool checkConfigFile();
private:
  Config(const std::string& configFile = "config.config" );
  std::map<std::string, std::string> config_;
};
#endif
