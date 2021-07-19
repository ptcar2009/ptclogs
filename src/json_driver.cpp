#include "ptclogs/driver/json_driver.hpp"

#include <string>

void logger::JSONDriver::print_field(std::string header, std::string value) {
    out << quote(header) << ":" << quote(value);
}

void logger::JSONDriver::print_field(std::string header, char* value) {
    out << quote(header) << ":" << quote(value);
}
void logger::JSONDriver::print_field(std::string header, const char* value) {
    out << quote(header) << ":" << quote(value);
}

void logger::JSONDriver::print_object(std::string object) {
    out << quote(messageKey) << ":" << quote(object);
}
void logger::JSONDriver::print_object(char const* object) {
    out << quote(messageKey) << ":" << quote(object);
}
void logger::JSONDriver::print_object(char* object) {
    out << quote(messageKey) << ":" << quote(object);
}
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
