#ifndef LOGS_DRIVER_H
#define LOGS_DRIVER_H
#include <ostream>
#include <string>

namespace logger {
enum LogLevel { FATAL, ERROR, WARN, INFO, DEBUG };

template <typename T>
class Field {
 public:
  Field(std::string header, T value) : header(header), value(value){};
  T value;
  std::string header;
};

class IDriver {
 public:
  IDriver(std::ostream& out, LogLevel& level) : out(out){};
  virtual void begin_message() = 0;
  virtual void end_message() = 0;
  template <typename T>
  void print_field(std::string header, T value);
  virtual void print_message(std::string message) = 0;
  virtual void print_timestamp() = 0;
  virtual void print_level(LogLevel level) = 0;
  virtual void separator() = 0;
  virtual void field_separator() = 0;
  template <typename T>
  void print_object(T object);

 protected:
  std::string timestamp();
  std::ostream& out;
  std::string messageKey = "msg";
  std::string timestampKey = "ts";
  std::string levelKey = "level";
};

};  // namespace logger


#endif // LOGS_DRIVER_H
