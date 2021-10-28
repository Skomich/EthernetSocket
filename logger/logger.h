#pragma once

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
    virtual void Write(std::string strFormatedLog) {};
public:
    Logger() {}
    ~Logger() {}
    
    virtual void Log(std::string strLog) {Log(strLog, LOG_MODE::STATUS, 0);}
    virtual void Log(LOG_MODE mode, std::string strLog) {Log(strLog, mode, 0);}
    virtual void Log(std::string strLog, LOG_MODE mode, time_t timeStamp);
};

class FileLogger : public Logger {
protected:
    std::string m_FileName = "";
    THANDLE m_FileStream = 0;
    
    void InitStream();
    void Write(std::string strFormatedLog) override;
public:
    FileLogger() {m_FileName = "./Logs/log.txt"; InitStream();}
    FileLogger(std::string strFileName) {m_FileName = strFileName; InitStream();}
    ~FileLogger();
};

class OutStreamLogger : public Logger {
protected:
    void Write(std::string strFormatedLog) override;
public:
    OutStreamLogger() {}
    ~OutStreamLogger() {}
};
