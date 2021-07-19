#ifndef LOGS_DRIVER_H
#define LOGS_DRIVER_H
#include <ostream>
#include <string>

namespace logger {
enum LogLevel { FATAL, ERROR, WARN, INFO, DEBUG };

/**
 * @brief Field containing a value to be logged.
 *
 * @tparam T Type of the value to be logged.
 */
template <typename T>
class Field {
 public:

  /**
   * @brief Instantiates a field with the given header and value.
   *
   * @param header Header that will be printed alongside the field.
   * @param value Value of the field.
   */
  Field(std::string header, T value) : header(header), value(value){};
  T value;
  std::string header;
};

class IDriver {
 public:
  /**
   * @brief Instantiates a driver that writes to out
   *
   * @param out Stream that the driver will write to.
   */
  IDriver(std::ostream& out) : out(out){};

  /**
   * @brief Writes the beggining of the message to out.
   *
   */
  virtual void begin_message() = 0;

  /**
   * @brief Writes the end of the message to out.
   *
   */
  virtual void end_message() = 0;

  /**
   * @brief Prints a field.
   *
   * @tparam T Type of the field.
   * @param header Header of the field.
   * @param value Value of the field.
   */
  template <typename T>
  void print_field(std::string header, T value);

  /**
   * @brief Prints a message to out
   *
   * @param message Message that will be printed.
   */
  virtual void print_message(std::string message) = 0;

  /**
   * @brief Printes the current timestamp to out.
   *
   */
  virtual void print_timestamp() = 0;

  /**
   * @brief Prints a log level to out.
   *
   * @param level [TODO:description]
   */
  virtual void print_level(LogLevel level) = 0;

  /**
   * @brief Prints the separator between message sections.
   *
   */
  virtual void separator() = 0;

  /**
   * @brief Prints the separator between fields.
   *
   */
  virtual void field_separator() = 0;

  /**
   * @brief Prints an object to out.
   *
   * @tparam T Type of the object.
   * @param object Object to be printed.
   */
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
