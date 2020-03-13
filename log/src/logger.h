#ifndef __SF_LOGGER_H__
#define __SF_LOGGER_H__

#include <string>
#include <stdint.h>

namespace sf {

class LoggerEvent {
public:
    LoggerEvent();

private:
    const char* _file = nullptr;
    int32_t _line = 0;
    uint32_t _threadId = 0;
    uint32_t _corotineId = 0;
    uint64_t _time;

    std::string _content;


};
class Logger {};

class Appender {};
class Formatter {};

};






#endif // __SF_LOGGER_H__