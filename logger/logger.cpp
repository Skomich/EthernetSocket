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

FileLogger::~FileLogger() {
#ifdef _WIN32
    CloseHandle(m_FileStream);
#elif defined(TUNIX)
    close(m_FileStream);
#endif
}

void FileLogger::InitStream() {
    if(m_FileName.empty()) {
        m_FileStream = -1;
        return;
    }
    
#ifdef _WIN32
    m_FileStream = CreateFile(m_FileName, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                              NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(m_FileStream == INVALID_HANDLE_VALUE) {
        std::cout << "Open file error: " << GetLastError() << '\n';
        return;
    }
#elif defined(TUNIX)
    m_FileStream = open(m_FileName.c_str(), O_CREAT|O_WRONLY, S_IRWXU);
    if(m_FileStream < 0) {
        std::cout << "Open file error: " << errno << '\n';
        return;
    }
#endif
}

void FileLogger::Log(LOG_MODE mode, time_t timeStamp, std::string strLog) {
    if(m_FileName.empty() || m_FileStream < 0)
        return;
    
    std::string strFormated = FormatStr(strLog, timeStamp, mode);
    
    if(strFormated.empty())
        return;
    

}

void ConsoleLogger::Log(LOG_MODE mode, time_t timeStamp, std::string strLog) {
    std::string strFormated = FormatStr(strLog, timeStamp, mode);
    
    if(strFormated.empty())
        return;
    
    std::cout << strFormated;
}
