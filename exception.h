/* exception.h
 *

 * Mike Henderson
 * June 2026
 */

#include <exception>
#include <stdarg.h>
#include <string>

// class Exception : uses printf-style format string to construct a generic error message
//
class Exception : public std::exception
{
public:
    Exception(const char* format, ... )
    {
        const size_t longEnough = 4056;
        char buffer[longEnough];

        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        mMessage = buffer;
        va_end (args);
    }
    const char* what() const throw() { return mMessage.c_str(); }

private:
    std::string mMessage; // constructed error message
};
