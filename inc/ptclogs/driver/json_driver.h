#ifndef LOGS_JSON_DRIVER_H
#define LOGS_JSON_DRIVER_H

#include "ptclogs/driver/idriver.h"

namespace logger{
class JSONDriver : IDriver {
 public:
  JSONDriver(std::ostream& out, LogLevel& level) : IDriver(out, level){};
  void begin_message();
  void end_message();
  template <typename T>
  void print_field(std::string header, T value);
  template <typename T>
  void print_field(std::string header, std::string value);
  template <typename T>
  void print_field(std::string header, char* value);
  template <typename T>
  void print_field(std::string header, const char* value);
  void print_message(std::string message);
  void print_timestamp();
  void print_level(LogLevel level);
  void separator();
  void field_separator();
  template <typename T>
  void print_object(T object);
  template <typename T>
  void print_object(std::string object); 
  template <typename T>
  void print_object(char const* object); 
  template <typename T>
  void print_object(char* object); 

 private:
  std::string quote(std::string str);
};
};  // namespace logger

template <>
void logger::JSONDriver::print_field(std::string header, std::string value) {
    out << quote(header) << ":" << quote(value);
}

template <>
void logger::JSONDriver::print_field(std::string header, char* value) {
    out << quote(header) << ":" << quote(value);
}
template <>
void logger::JSONDriver::print_field(std::string header, const char* value) {
    out << quote(header) << ":" << quote(value);
}

template <>
void logger::JSONDriver::print_object(std::string object) {
    out << quote(messageKey) << ":" << quote(object);
}
template <>
void logger::JSONDriver::print_object(char const* object) {
    out << quote(messageKey) << ":" << quote(object);
}
template <>
void logger::JSONDriver::print_object(char* object) {
    out << quote(messageKey) << ":" << quote(object);
}
template <typename T>
void logger::JSONDriver::print_field(std::string header, T value) {
  out << quote(header) << ":" << value;
}
template <typename T>
void logger::JSONDriver::print_object(T object) {
    out << quote(messageKey) << ":" << object;
}

#endif // LOGS_JSON_DRIVER_H
