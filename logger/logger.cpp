#include "logger.h"

void Logger::Log(std::string strLog, LOG_MODE mode, time_t timeStamp)
{
    if(strLog.empty())
        return;
    
    if(timeStamp <= 0)
    {
        std::time(&timeStamp);
    }
    
    struct tm* ptm = localtime(&timeStamp);
    char strTimeBuffer[21];
    strftime(strTimeBuffer, 21, "[%d.%m.%Y %H:%M:%S", ptm);
    
    std::string strMode = "";
    switch (mode)
    {
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
    std::string strFormated = std::string(strTimeBuffer, 21) + "][" + strMode + "] " + strLog + "\n";
    
    Write(strFormated);
}

FileLogger::~FileLogger()
{
#ifdef _WIN32
    CloseHandle(m_FileStream);
#elif defined(TUNIX)
    close(m_FileStream);
#endif
}

void FileLogger::InitStream()
{
    if(m_FileName.empty())
    {
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
    if(m_FileStream < 0)
    {
        std::cout << "Open file error: " << errno << '\n';
        return;
    }
#endif
}

void FileLogger::Write(std::string strFormatedLog)
{
    if(m_FileName.empty() || m_FileStream < 0) {
        std::cout << "File don't open\n";
        return;
    }
#ifdef _WIN32
#elif defined(TUNIX)
    int out = write(m_FileStream, strFormatedLog.data(), strFormatedLog.size());
    if(out < 0 || out != strFormatedLog.size())
    {
        std::cout << "Log error: out=" << out << ", errno=" << errno << '\n';
        return;
    }
#endif
}

void OutStreamLogger::Write(std::string strFormatedLog)
{
    std::cout << strFormatedLog;
}
