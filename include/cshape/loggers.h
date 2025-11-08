// C++ program to implement a basic logging system.

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
class Logger {
private:
    static std::map<const std::string, std::shared_ptr<Logger>> instances;

public:
    Logger(const std::string& loggerName);  // Make it private
    const std::string name;
    static std::shared_ptr<Logger> getInstance(const std::string& filename);
};

// Why do we need it ? It's already defined inside the class
std::map<const std::string, std::shared_ptr<Logger>> Logger::instances;

std::shared_ptr<Logger> Logger::getInstance(const std::string& loggerName)
{
    std::cout << "Getting instance: " << loggerName.size() << ": '" << loggerName << "'" << std::endl;
    // Check if instance exists
    if (instances.count(loggerName)) {
        return instances.at(loggerName);
    }
    
    // Create new instance
    std::shared_ptr<Logger> logger = std::make_shared<Logger>(loggerName);
    instances.insert({loggerName, logger});
    return logger;
}

Logger::Logger(const std::string& loggerName) : name(loggerName)
{
    std::cout << "Created instance: '" << loggerName << "' at " << (size_t)&(*this) << std::endl;
}
