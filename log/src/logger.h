#ifndef __SF_LOGGER_H__
#define __SF_LOGGER_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>

namespace sf {

enum LogLevel {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL
};


class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();

private:
    const char* _file = nullptr;
    int32_t _line = 0;
    uint32_t _elapse = 0;
    uint32_t _threadId = 0;
    uint32_t _coroutineId = 0;
    uint64_t _timestamp;

    std::string _content;
};


class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string &name = "root");
    
    void log(LogLevel level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(Appender::ptr appender);
    void delAppender(Appender::ptr appender);
    LogLevel getLevel() const { return _level; }
    void setLevel(LogLevel level) { _level = level; }

private:
    std::string _name;
    LogLevel _level;
    std::list<Appender::ptr> _appenders;
};

class Appender {
public:
    typedef std::shared_ptr<Appender> ptr;

    virtual ~Appender();
    virtual void log(LogLevel level, LogEvent::ptr event) = 0;

    void setFormatter(Formatter::ptr formatter) { _formatter = formatter; }
    Formatter::ptr getFormatter() const { return _formatter; }

protected:
    LogLevel _level;
    Formatter::ptr _formatter;
};

class Formatter {
public:
    typedef std::shared_ptr<Formatter> ptr;

    std::string format(LogEvent::ptr event);
};

class StdLogAppender : public Appender {
public:
    typedef std::shared_ptr<StdLogAppender> ptr;
    virtual void log(LogLevel level, LogEvent::ptr event) override;
};

class FileLogAppender : public Appender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender(const std::string& filename);
    virtual void log(LogLevel level, LogEvent::ptr event) override;
    bool reopen();

private:
    std::string _filename;
    std::ofstream _file;
};

};






#endif // __SF_LOGGER_H__