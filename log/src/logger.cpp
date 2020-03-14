#include <logger.h>

namespace sf {

Logger::Logger(const std::string &name)
    : _name(name) {

}

void Logger::addAppender(Appender::ptr appender) {
    _appenders.push_back(appender);

}
void Logger::delAppender(Appender::ptr appender) {
    for (auto it = _appenders.begin(); it != _appenders.end(); ++it) {
        if (*it == appender) {
            _appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel level, LogEvent::ptr event) {
    if (level >= _level) {
        for (auto &i : _appenders) {
            i->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event) {
    log(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event) {
    log(LogLevel::INFO, event);   
}
void Logger::warn(LogEvent::ptr event) {
    log(LogLevel::WARN, event);   
}
void Logger::error(LogEvent::ptr event) {
    log(LogLevel::ERROR, event);   
}
void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);   
}   

void StdLogAppender::log(LogLevel level, LogEvent::ptr event) {
    if (level >= _level) {
        std::cout << _formatter->format(event);
    }
}

FileLogAppender::FileLogAppender(const std::string& filename)
    : _filename(filename) {
}

void FileLogAppender::log(LogLevel level, LogEvent::ptr event) {
    if (level >= _level) {
        _file << _formatter->format(event);
    }
}

bool FileLogAppender::reopen() {
    if (_file)
        _file.close();

    _file.open(_filename);

    return !!_file;
}

}