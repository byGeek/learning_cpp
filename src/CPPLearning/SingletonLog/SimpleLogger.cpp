#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

#include "log.h"

class SimpleLogger : public ILogger
{
public:
	SimpleLogger();
	~SimpleLogger();

	void Log(const std::string& msg) const override;
	void Release() override;

private:

};

SimpleLogger::SimpleLogger() {
	std::cout << "simplelogger ctor" << std::endl;
}
SimpleLogger::~SimpleLogger() {
	std::cout << "simplelogger dtor" << std::endl;
}

void SimpleLogger::Log(const std::string& msg) const {
	std::cout << msg << std::endl;
}

void SimpleLogger::Release() {
	std::cout << "released!" << std::endl;
}


ILogger* GetLogger() {
	static ILogger* logger = new SimpleLogger();
	return logger;
}

//ILoggerPtr ptrLogger(GetLogger(), &SimpleLogger::Release);