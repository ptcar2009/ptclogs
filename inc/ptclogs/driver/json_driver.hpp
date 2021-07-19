#ifndef LOGS_JSON_DRIVER_H
#define LOGS_JSON_DRIVER_H

#include "ptclogs/driver/idriver.hpp"

namespace logger{
/**
 * @brief Driver that prints logs formatted as json objects. Strings get quoted, other objects get printed as they are.
 */
class JSONDriver : IDriver {
 public:
  JSONDriver(std::ostream& out) : IDriver(out) {};
  void begin_message();
  void end_message();
  template <typename T>
  void print_field(std::string header, T value);
  void print_field(std::string header, std::string value);
  void print_field(std::string header, char* value);
  void print_field(std::string header, const char* value);

  void print_message(std::string message);
  void print_timestamp();
  void print_level(LogLevel level);
  void separator();
  void field_separator();
  template <typename T>
  void print_object(T object);
  void print_object(std::string object); 
  void print_object(char const* object); 
  void print_object(char* object); 

 private:
  std::string quote(std::string str);
};
};  // namespace logger

template <typename T>
void logger::JSONDriver::print_field(std::string header, T value) {
    out << quote(header) << ":" << value;
}
template <typename T>
void logger::JSONDriver::print_object(T object) {
    out << quote(messageKey) << ":" << object;
}

#endif // LOGS_JSON_DRIVER_H
