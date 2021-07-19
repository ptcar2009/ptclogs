#ifndef LOGS_HPP
#define LOGS_HPP

#include <iostream>
#include <ostream>
#include <string>

#include "ptclogs/driver/idriver.hpp"

namespace logger {
/**
 * @brief Customizeable logger with templated prints.
 */
template <class Driver>
class Logger {
 public:
  /**
   * @brief Logs the object t at WARN log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void WARN(T t) {
    if (log_level < LogLevel::WARN) return;
    print_object(t, LogLevel::WARN);
  }

  /**
   * @brief Logs the message with its fields at WARN log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void WARN(std::string message, Field<Args>... args) {
    if (log_level < LogLevel::WARN) return;
    print_message(message, LogLevel::WARN, args...);
  }

  /**
   * @brief Logs the object t at FATAL log level and calls exit(1).
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void FATAL(T t) {
    if (log_level < LogLevel::FATAL) return;
    print_object(t, LogLevel::FATAL);
    exit(1);
  }

  /**
   * @brief Logs the message with its fields at FATAL log level and calls
   * exit(1).
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void FATAL(std::string message, Field<Args>... args) {
    if (log_level < LogLevel::FATAL) return;
    print_message(message, LogLevel::FATAL, args...);
    exit(1);
  }

  /**
   * @brief Logs the object t at ERROR log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void ERROR(T t) {
    if (log_level < LogLevel::ERROR) return;
    print_object(t, LogLevel::ERROR);
  }

  /**
   * @brief Logs the message with its fields at ERROR log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void ERROR(std::string message, Field<Args>... args) {
    if (log_level < LogLevel::ERROR) return;
    print_message(message, LogLevel::ERROR, args...);
  }

  /**
   * @brief Logs the object t at INFO log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void INFO(T t) {
    if (log_level < LogLevel::INFO) return;
    print_object(t, LogLevel::INFO);
  }

  /**
   * @brief Logs the message with its fields at INFO log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void INFO(std::string message, Field<Args>... args) {
    if (log_level < LogLevel::INFO) return;
    print_message(message, LogLevel::INFO, args...);
  }

  /**
   * @brief Logs the object t at DEBUG log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void DEBUG(T t) {
    if (log_level < LogLevel::DEBUG) return;
    print_object(t, LogLevel::DEBUG);
  }

  /**
   * @brief Logs the message with its fields at DEBUG log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void DEBUG(std::string message, Field<Args>... args) {
    if (log_level < LogLevel::DEBUG) return;
    print_message(message, LogLevel::DEBUG, args...);
  }

  /**
   * @brief Sets the log level of the logger.
   *
   * @param log_level Log level that will be set.
   */
  void SetLogLevel(LogLevel log_level) { this->log_level = log_level; };

  /**
   * @brief Returns the current log level of the logger.
   *
   * @return Log level of the logger.
   */
  LogLevel GetLogLevel() { return log_level; };

  /**
   * @brief Instantiates a logger with the log level from the VERBOSITY env var.
   *
   *
   * @param out Output stream for the logger.
   */
  Logger(std::ostream& out = std::cout) : out(out), driver(out) {
    log_level = LogLevel::INFO;
    if (getenv("VERBOSITY") != NULL)
      log_level = LogLevel(atoi(getenv("VERBOSITY")));
  };

  /**
   * @brief Instantiates a logger with the given log level that writes on `out`.
   *
   * @param log_level Log level of the logger.
   * @param out Output stream on which the logger will write to.
   */
  Logger(LogLevel log_level, std::ostream& out = std::cout)
      : log_level(log_level), driver(out), out(out){};

 private:
  Driver driver;
  LogLevel log_level;
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
