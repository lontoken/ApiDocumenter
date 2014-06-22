#pragma once

#ifndef __SIMPLE_LOG_H__
#define __SIMPLE_LOG_H__

#include <sstream>
#include <string>
#include <stdio.h>

#ifdef _WIN32 
#pragma warning(disable:4996)
#else
#endif //_WIN32

inline std::string NowTime();

// The small of the level the more important of log info
enum TLogLevel {
    logERROR, 
    logWARNING, 
    logINFO, 
    logDEBUG, 
    logDEBUG1, 
    logDEBUG2, 
    logDEBUG3, 
    logDEBUG4 
};

template <typename T>
class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& Get(TLogLevel level = logINFO);

    static TLogLevel& ReportingLevel();
    static std::string ToString(TLogLevel level);
    static TLogLevel FromString(const std::string& level);

protected:
    std::ostringstream os;

private:
    Log(const Log&);
    Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log()
{
}

template <typename T>
std::ostringstream& Log<T>::Get(TLogLevel level)
{
    os << "- " << NowTime();
    os << " " << ToString(level) << ": ";
    os << std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
    return os;
}

template <typename T>
Log<T>::~Log()
{
    os << std::endl;
    T::Output(os.str());
}

template <typename T>
TLogLevel& Log<T>::ReportingLevel()
{
    static TLogLevel reportingLevel = logDEBUG4;
    return reportingLevel;
}

template <typename T>
std::string Log<T>::ToString(TLogLevel level)
{
	static const char* const buffer[] 
        = {"ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"};
    return buffer[level];
}

template <typename T>
TLogLevel Log<T>::FromString(const std::string& level)
{
    if (level == "DEBUG4") return logDEBUG4;
    if (level == "DEBUG3") return logDEBUG3;
    if (level == "DEBUG2") return logDEBUG2;
    if (level == "DEBUG1") return logDEBUG1;
    if (level == "DEBUG") return logDEBUG;
    if (level == "INFO") return logINFO;
    if (level == "WARNING") return logWARNING;
    if (level == "ERROR") return logERROR;
    return logINFO;
}

inline void _OutputHelper(FILE* pStream, const std::string& msg)
{
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}

class Output2FILE
{
public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& Output2FILE::Stream()
{
    static FILE* pStream = fopen("log.log", "a");
    return pStream;
}

inline void Output2FILE::Output(const std::string& msg)
{   
    _OutputHelper(Stream(), msg);
}

class Output2CONSOLE
{
public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& Output2CONSOLE::Stream()
{
    static FILE* pStream = stderr;
    return pStream;
}

inline void Output2CONSOLE::Output(const std::string& msg)
{
    _OutputHelper(Stream(), msg);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   if defined (BUILDING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllexport)
#   elif defined (USING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllimport)
#   else
#       define FILELOG_DECLSPEC
#   endif // BUILDING_DBSIMPLE_DLL
#else
#   define FILELOG_DECLSPEC
#endif // _WIN32

class FILELOG_DECLSPEC FILELog : public Log<Output2FILE> {};
class FILELOG_DECLSPEC CONSOLELog : public Log<Output2CONSOLE> {};

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logDEBUG4
#endif

#define FILE_LOG(level) \
    if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
    else FILELog().Get(level)
#define FILE_LOG_INFO FILE_LOG(logINFO)
#define FILE_LOG_DEBUG FILE_LOG(logDEBUG)
#define FILE_LOG_ERROR FILE_LOG(logERROR)

#define CONSOLE_LOG(level) \
    if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > CONSOLELog::ReportingLevel()) ; \
    else CONSOLELog().Get(level)
#define CONSOLE_LOG_INFO CONSOLE_LOG(logINFO)
#define CONSOLE_LOG_DEBUG CONSOLE_LOG(logDEBUG)
#define CONSOLE_LOG_ERROR CONSOLE_LOG(logERROR)

#define INIT_FILE_LOG(level) \
    FILELog::ReportingLevel() \
    = FILELog::FromString(level) ;

#define INIT_CONSOLE_LOG(level) \
    CONSOLELog::ReportingLevel() \
    = CONSOLELog::FromString(level) ;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string NowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, 
            "HH':'mm':'ss", buffer, MAX_LEN) == 0)
        return "Error in NowTime()";

    char result[100] = {0};
    static DWORD first = GetTickCount();
    std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000); 
    return result;
}

#else

#include <sys/time.h>

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}

#endif //WIN32

#endif //__COMMON_LOG_H__
