#ifndef LOGS_HPP
#define LOGS_HPP

#include <iostream>
#include <ostream>
#include <string>

#include "ptclogs/driver/idriver.h"

namespace logger {
/**
 * @brief Customizeable logger with templated prints.
 */
template <class Driver>
class Logger {
 public:
  /**
   * @brief Prints an object with the log level ERROR and then exits with an
   * error.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void FATAL(T t) {
    if (verbosity < LogLevel::FATAL) return;
    print_object(t, LogLevel::FATAL);
    exit(1);
  }
  /**
   * @brief Prints objects, separated by spaces, at the log level ERROR and then
   * exits with an error.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename... Args>
  void FATAL(std::string message, Field<Args>... args) {
    if (verbosity < LogLevel::FATAL) return;
    print_message(message, LogLevel::FATAL, args...);
    exit(1);
  }

  /**
   * @brief Prints an object with the log level ERROR and then exits with an
   * error.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void ERROR(T t) {
    if (verbosity < LogLevel::ERROR) return;
    print_object(t, LogLevel::ERROR);
  }
  /**
   * @brief Prints objects, separated by spaces, at the log level ERROR and then
   * exits with an error.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename... Args>
  void ERROR(std::string message, Field<Args>... args) {
    if (verbosity < LogLevel::ERROR) return;
    print_message(message, LogLevel::ERROR, args...);
  }

  /**
   * @brief Prints an object with the log level INFO.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void INFO(T t) {
    if (verbosity < LogLevel::INFO) return;
    print_object(t, LogLevel::INFO);
  }

  /**
   * @brief Prints objects, separated by spaces, at the log level INFO.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename... Args>
  void INFO(std::string message, Field<Args>... args) {
    if (verbosity < LogLevel::INFO) return;
    print_message(message, LogLevel::INFO, args...);
  }

  /**
   * @brief Prints an object with the log level INFO.
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void DEBUG(T t) {
    if (verbosity < LogLevel::DEBUG) return;
    print_object(t, LogLevel::DEBUG);
  }

  /**
   * @brief Prints objects, separated by spaces, at the log level DEBUG.
   *
   * @tparam T Type of the first object to be printed.
   * @tparam Args Type of the other objecs.
   * @param t First object to be printed.
   * @param args Other objects to be printed.
   */
  template <typename... Args>
  void DEBUG(std::string message, Field<Args>... args) {
    if (verbosity < LogLevel::DEBUG) return;
    print_message(message, LogLevel::DEBUG, args...);
  }

  /**
   * @brief Sets the log level of the logger.
   *
   * @param verbosity Log level that will be set.
   */
  void SetLogLevel(LogLevel verbosity) { this->verbosity = verbosity; };

  /**
   * @brief Returns the current log level of the logger.
   *
   * @return Log level of the logger.
   */
  LogLevel GetLogLevel() { return verbosity; };

  /**
   * @brief Instantiates a logger based on the environment variable "VERBOSITY".
   * The variable should be a number between 0 and 2 both inclusive,
   * representing ERROR, INFO and DEBUG, respectively.
   *
   */
  Logger(std::ostream& out = std::cout)cerr : out(out), driver(out, verbosity) {
    verbosity = LogLevel::INFO;
    if (getenv("VERBOSITY") != NULL)
      verbosity = LogLevel(atoi(getenv("VERBOSITY")));
  };

  /**
   * @brief Instantiates a logger with the given log level that writes on `out`.
   *
   * @param verbosity Log level of the logger.
   * @param out Output stream on which the logger will write to.
   */
  Logger(LogLevel verbosity, std::ostream& out = std::cout)
      : verbosity(verbosity), driver(out, verbosity), out(out){};

 private:
  Driver driver;
  LogLevel verbosity;
  template <typename T>
  void printv(Field<T> field) {
    driver.print_field(field.header, field.value);
  }

  template <typename T, typename... Args>
  void printv(Field<T> field,
              Field<Args>... args)  // recursive variadic function
  {
    driver.print_field(field.header, field.value);
    driver.field_separator();

    printv(args...);
  }

  template <typename T>
  void print_object(T object, LogLevel level) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    driver.print_object(object);
    driver.end_message();
    out << std::endl;
  }
  template <typename... Args>
  void print_message(std::string message, LogLevel level, Field<Args>... args) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    driver.print_message(message);
    driver.separator();
    printv(args...);
    driver.end_message();
    out << std::endl;
  }

  std::ostream& out;
};

};  // namespace logger

#endif  // LOGS_HPP
