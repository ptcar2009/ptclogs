#include "ptclogs/driver/json_driver.h"

#include <string>

void logger::JSONDriver::begin_message() { out << "{"; }
void logger::JSONDriver::end_message() { out << "}"; }

void logger::JSONDriver::separator() { out << ","; }
void logger::JSONDriver::field_separator() { out << ","; }

void logger::JSONDriver::print_message(std::string message) {
    out << quote(messageKey) << ":" << quote(message);
};

void logger::JSONDriver::print_timestamp() {
    out << quote(timestampKey) << ":" << quote(timestamp());
}

void logger::JSONDriver::print_level(logger::LogLevel log_level) {
    switch (log_level) {
	case INFO:
	    out << quote(levelKey) << ":" << quote("INFO");
	    break;
	case DEBUG:
	    out << quote(levelKey) << ":" << quote("DEBUG");
	    break;
	case WARN:
	    out << quote(levelKey) << ":" << quote("WARN");
	    break;
	case ERROR:
	    out << quote(levelKey) << ":" << quote("ERROR");
	    break;
	case FATAL:
	    out << quote(levelKey) << ":" << quote("FATAL");
	    break;
    }
}

std::string logger::JSONDriver::quote(std::string str) {
    return "\"" + str + "\"";
}
