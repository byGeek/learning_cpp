#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

#include <functional>
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

void Release(ILogger* logger) {
	std::cout << "call custom deleter" << std::endl;
	logger->Release();
}


ILogger* GetLogger() {
	static ILogger* logger = new SimpleLogger();
	return logger;
}



ILoggerPtr GetLoggerPtr(){
	ILoggerPtr logger(GetLogger(), Release);
	//std::shared_ptr<ILogger> logger(GetLogger(), Release);
	return logger;
}

ILoggerPtr GetLoggerPtr2() {
	ILoggerPtr logger(GetLogger(), std::mem_fn(&ILogger::Release));
	return logger;
}

//ILoggerPtr ptrLogger(GetLogger(), &SimpleLogger::Release);