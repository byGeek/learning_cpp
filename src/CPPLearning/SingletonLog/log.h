#pragma once

#ifdef LOG_EXPORT

#define LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif // LOG_API

#include <string>
#include <memory>

struct ILogger
{
	virtual ~ILogger() = default;  //declare virtual destructor
	virtual void Log(const std::string& msg) const = 0;
	virtual void Release() = 0;
};

typedef std::shared_ptr<ILogger> ILoggerPtr;

extern "C" LOG_API ILogger* GetLogger();

