#include "../stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>

#ifdef _WIN32
    #include <fileapi.h>
#elif defined(TUNIX)
    #include <fcntl.h>
    #include <unistd.h>
#endif

enum class LOG_MODE {
    STATUS,
    WARNING,
    ERROR,
    CRITICAL,
    FATAL
};

/*
 Рекомендуется передавать родитель (Logger) в классы с логированием. Это позволит использовать свой способ логирования, таким образом по стандарту логгер не будет работать т.к. Logger является заглушкой.
 */
class Logger {
protected:
    std::string FormatStr(std::string strLog, time_t timeStamp = 0, LOG_MODE mode = LOG_MODE::STATUS);
public:
    Logger() {}
    ~Logger() {}
    
    virtual void Log(std::string strLog) {Log(LOG_MODE::STATUS, 0, strLog);}
    virtual void Log(LOG_MODE mode, std::string strLog) {Log(mode, 0, strLog);}
    virtual void Log(LOG_MODE mode, time_t timeStamp, std::string strLog) {}
};

class FileLogger : public Logger {
protected:
    std::string m_FileName = "";
    THANDLE m_FileStream = 0;
    
    void InitStream();
public:
    FileLogger() {m_FileName = "./Logs/log.txt"; InitStream();}
    FileLogger(std::string strFileName) {m_FileName = strFileName; InitStream();}
    ~FileLogger();
    
    virtual void Log(LOG_MODE mode, time_t timeStamp, std::string strLog) override;
};

class ConsoleLogger : public Logger {
public:
    ConsoleLogger() {}
    ~ConsoleLogger() {}
    
    virtual void Log(LOG_MODE mode, time_t timeStamp, std::string strLog) override;
};