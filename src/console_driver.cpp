#include "ptclogs/driver/console_driver.hpp"

void logger::ConsoleDriver::begin_message() {}
void logger::ConsoleDriver::end_message() {}
void logger::ConsoleDriver::field_separator() { out << ", "; }

void logger::ConsoleDriver::separator() { out << "\t"; }

void logger::ConsoleDriver::print_message(std::string message) {
    out << message;
};

void logger::ConsoleDriver::print_timestamp() { out << timestamp(); }

void logger::ConsoleDriver::print_level(logger::LogLevel log_level) {
    switch (log_level) {
	case INFO:
	    out << "\e[36mINFO\e[0m";
	    break;
	case DEBUG:
	    out << "\e[35mDEBUG\e[0m";
	    break;
	case WARN:
	    out << "\e[33mWARN\e[0m";
	    break;
	case ERROR:
	    out << "\e[31mERROR\e[0m";
	    break;
	case FATAL:
	    out << "\e[31mFATAL\e[0m";
	    break;
    }
}
