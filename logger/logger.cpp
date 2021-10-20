#include "logger.h"

std::string Logger::FormatStr(std::string strLog, time_t timeStamp, LOG_MODE mode) {
    if(strLog.empty())
        return "";
    
    if(timeStamp == 0) {
        std::time(&timeStamp);
    }
    
    struct tm* ptm = localtime(&timeStamp);
    char strTimeBuffer[21];
    strftime(strTimeBuffer, 21, "[%d.%m.%Y %H:%M:%S]", ptm);
    
    std::string strMode = "";
    switch (mode) {
        case LOG_MODE::STATUS:
            strMode = "STATUS";
            break;
        case LOG_MODE::WARNING:
            strMode = "WARNING";
            break;
        case LOG_MODE::ERROR:
            strMode = "ERROR";
            break;
        case LOG_MODE::CRITICAL:
            strMode = "CRITICAL";
            break;
        case LOG_MODE::FATAL:
            strMode = "FATAL";
        default:
            strMode = "STATUS";
            break;
    }
    std::string result = std::string(strTimeBuffer) + "[" + strMode + "] " + strLog + "\n";
    return result;
}

FileLogger::FileLogger() {
    m_FileName = "./Logs/log.txt";
    InitStream();
}

FileLogger::FileLogger(std::string strFileName) {
    m_FileName = strFileName;
    InitStream();
}

FileLogger::~FileLogger() {
    //close handle
}

void FileLogger::InitStream() {
    //init handle
}

void FileLogger::Log(LOG_MODE mode, time_t timeStamp, std::string strLog) {
    std::string strFormated = FormatStr(strLog, timeStamp, mode);
    
    if(strFormated.empty())
        return;
    
    //write in file
}

void ConsoleLogger::Log(LOG_MODE mode, time_t timeStamp, std::string strLog) {
    std::string strFormated = FormatStr(strLog, timeStamp, mode);
    
    if(strFormated.empty())
        return;
    
    std::cout << strFormated;
}
