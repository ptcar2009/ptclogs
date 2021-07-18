#ifndef LOGS_CONSOLE_DRIVER_H
#define LOGS_CONSOLE_DRIVER_H
#include "ptclogs/driver/idriver.h"
namespace logger{
class ConsoleDriver : IDriver {
 public:
  ConsoleDriver(std::ostream& out, LogLevel& level) : IDriver(out, level){};
  void begin_message();
  void end_message();
  template <typename T>
  void print_field(std::string header, T value);
  void print_message(std::string message);
  void print_timestamp();
  void print_level(LogLevel level);
  void separator();
  void field_separator();
  template <typename T>
  void print_object(T object);
};
};  // namespace logger

template <typename T> void logger::ConsoleDriver::print_field(std::string header, T value) {
  out << header << ": " << value;
}
template<typename T>
void logger::ConsoleDriver::print_object(T value) {
  out << value;
}

#endif // LOGS_CONSOLE_DRIVER_H
