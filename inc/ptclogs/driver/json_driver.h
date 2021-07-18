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

 private:
  std::string quote(std::string str);
};
};  // namespace logger

template <typename T>

void logger::JSONDriver::print_field(std::string header, T value) {
  out << quote(header) << ":" << value;
}

#endif // LOGS_JSON_DRIVER_H
