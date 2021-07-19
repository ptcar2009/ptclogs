#include <chrono>

#include "ptclogs/driver/idriver.hpp"

/**
 * @brief Returns the formatted timestamp as a string.
 *
 */
std::string logger::IDriver::timestamp() {
    time_t now;
    time(&now);
    char buf[sizeof "2011-10-08T07:07:09Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    return buf;
}
