#ifndef PTCLOGS_PRODUCTION_HPP
#define PTCLOGS_PRODUCTION_HPP
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>

#include "ptclogs/driver/idriver.hpp"
#include "ptclogs/driver/json_driver.hpp"
namespace logger {
template <class Driver = JSONDriver, LogLevel log_level = LogLevel::INFO,
          std::ostream& out = std::cout>
class ProductionLogger {};
template <typename Driver, std::ostream& out>
class ProductionLogger<Driver, LogLevel::INFO, out> {
 public:
  template <typename... ExtraArgs>
  ProductionLogger(Field<ExtraArgs>... extra) : driver(out) {
    extraArgs = [this, extra...]() { printv(extra...); };
    extraFunctions.push_back(extraArgs);
  }

  template <typename... ExtraArgs>
  ProductionLogger<Driver, LogLevel::INFO, out> With(Field<ExtraArgs>... extra) {
    return ProductionLogger<Driver, LogLevel::INFO, out>(extraFunctions, extra...);
  }

  /**
   * @brief Logs the object t at WARN log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void WARN(T t) {
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
    print_message(message, LogLevel::INFO, args...);
  }

  /**
   * @brief Logs the object t at DEBUG log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void DEBUG(T t){};
  /**
   * @brief Logs the message with its fields at DEBUG log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void DEBUG(std::string message, Field<Args>... args) {}

 private:
  template <typename... ExtraArgs>
  ProductionLogger(
                   std::vector<std::function<void()>> _extraFunctions,
                   Field<ExtraArgs>... extra)
      : ProductionLogger(extra...) {
    for (auto f : _extraFunctions) {
      extraFunctions.push_back(f);
    }
  }

  Driver driver;
  void printv() {}
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

  std::vector<std::function<void()>> extraFunctions;

  template <typename T>
  void print_object(T object, LogLevel level) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
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
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
    printv(args...);
    driver.end_message();
    out << std::endl;
  }

  std::function<void()> extraArgs;
};
template <typename Driver, std::ostream& out>
class ProductionLogger<Driver, LogLevel::DEBUG, out> {
 public:
  template <typename... ExtraArgs>
  ProductionLogger(Field<ExtraArgs>... extra) : driver(out) {
    extraArgs = [this, extra...]() { printv(extra...); };
    extraFunctions.push_back(extraArgs);
  }

  template <typename... ExtraArgs>
  ProductionLogger<Driver, LogLevel::DEBUG, out> With(
      Field<ExtraArgs>... extra) {
    return ProductionLogger<Driver, LogLevel::DEBUG, out>(extraFunctions,
                                                          extra...);
  }
  /**
   * @brief Logs the object t at WARN log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void WARN(T t) {
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
    print_message(message, LogLevel::DEBUG, args...);
  }

 private:
  template <typename... ExtraArgs>
  ProductionLogger(std::vector<std::function<void()>> _extraFunctions,
                   Field<ExtraArgs>... extra)
      : ProductionLogger(extra...) {
    for (auto f : _extraFunctions) {
      extraFunctions.push_back(f);
    }
  }

  Driver driver;
  void printv() {}
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

  std::vector<std::function<void()>> extraFunctions;

  template <typename T>
  void print_object(T object, LogLevel level) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
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
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
    printv(args...);
    driver.end_message();
    out << std::endl;
  }

  std::function<void()> extraArgs;
};
template <typename Driver, std::ostream& out>
class ProductionLogger<Driver, LogLevel::ERROR, out> {
 public:
  template <typename... ExtraArgs>
  ProductionLogger(Field<ExtraArgs>... extra)
      : driver(out) {
    extraArgs = [this, extra...]() { printv(extra...); };
    extraFunctions.push_back(extraArgs);
  }

  template <typename... ExtraArgs>
  ProductionLogger<Driver, LogLevel::ERROR, out> With(Field<ExtraArgs>... extra) {
    return ProductionLogger<Driver, LogLevel::ERROR, out>( extraFunctions,
                                                     extra...);
  }
  /**
   * @brief Logs the object t at WARN log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void WARN(T t) {}

  /**
   * @brief Logs the message with its fields at WARN log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void WARN(std::string message, Field<Args>... args) {}

  /**
   * @brief Logs the object t at FATAL log level and calls exit(1).
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void FATAL(T t) {
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
    print_message(message, LogLevel::ERROR, args...);
  }

  /**
   * @brief Logs the object t at INFO log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void INFO(T t) {}

  /**
   * @brief Logs the message with its fields at INFO log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void INFO(std::string message, Field<Args>... args) {}

  /**
   * @brief Logs the object t at DEBUG log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void DEBUG(T t) {}

  /**
   * @brief Logs the message with its fields at DEBUG log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void DEBUG(std::string message, Field<Args>... args) {}

 private:
  template <typename... ExtraArgs>
  ProductionLogger(
                   std::vector<std::function<void()>> _extraFunctions,
                   Field<ExtraArgs>... extra)
      : ProductionLogger( extra...) {
    for (auto f : _extraFunctions) {
      extraFunctions.push_back(f);
    }
  }

  Driver driver;
  void printv() {}
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

  std::vector<std::function<void()>> extraFunctions;

  template <typename T>
  void print_object(T object, LogLevel level) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
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
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
    printv(args...);
    driver.end_message();
    out << std::endl;
  }


  std::function<void()> extraArgs;
};
template <typename Driver, std::ostream& out>
class ProductionLogger<Driver, LogLevel::FATAL, out> {
 public:
  template <typename... ExtraArgs>
  ProductionLogger(Field<ExtraArgs>... extra)
      :  driver(out) {
    extraArgs = [this, extra...]() { printv(extra...); };
    extraFunctions.push_back(extraArgs);
  }

  template <typename... ExtraArgs>
  ProductionLogger<Driver, LogLevel::FATAL, out> With(Field<ExtraArgs>... extra) {
    return ProductionLogger<Driver, LogLevel::FATAL, out>( extraFunctions,
                                                     extra...);
  }
  /**
   * @brief Logs the object t at WARN log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void WARN(T t) {}

  /**
   * @brief Logs the message with its fields at WARN log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void WARN(std::string message, Field<Args>... args) {}

  /**
   * @brief Logs the object t at FATAL log level and calls exit(1).
   *
   * @tparam T Type of the object that will be printed.
   * @param t Object that will be printed.
   */
  template <typename T>
  void FATAL(T t) {
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
  void ERROR(T t) {}

  /**
   * @brief Logs the message with its fields at ERROR log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void ERROR(std::string message, Field<Args>... args) {}

  /**
   * @brief Logs the object t at INFO log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void INFO(T t) {}

  /**
   * @brief Logs the message with its fields at INFO log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void INFO(std::string message, Field<Args>... args) {}

  /**
   * @brief Logs the object t at DEBUG log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void DEBUG(T t) {}

  /**
   * @brief Logs the message with its fields at DEBUG log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void DEBUG(std::string message, Field<Args>... args) {}

 private:
  template <typename... ExtraArgs>
  ProductionLogger(
                   std::vector<std::function<void()>> _extraFunctions,
                   Field<ExtraArgs>... extra)
      : ProductionLogger( extra...) {
    for (auto f : _extraFunctions) {
      extraFunctions.push_back(f);
    }
  }

  Driver driver;
  void printv() {}
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

  std::vector<std::function<void()>> extraFunctions;

  template <typename T>
  void print_object(T object, LogLevel level) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
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
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
    printv(args...);
    driver.end_message();
    out << std::endl;
  }


  std::function<void()> extraArgs;
};
template <typename Driver, std::ostream& out>
class ProductionLogger<Driver, LogLevel::WARN, out> {
 public:
  template <typename... ExtraArgs>
  ProductionLogger( Field<ExtraArgs>... extra)
      : driver(out) {
    extraArgs = [this, extra...]() { printv(extra...); };
    extraFunctions.push_back(extraArgs);
  }

  template <typename... ExtraArgs>
  ProductionLogger<Driver, LogLevel::WARN, out> With(Field<ExtraArgs>... extra) {
    return ProductionLogger<Driver, LogLevel::WARN, out>( extraFunctions,
                                                    extra...);
  }
  /**
   * @brief Logs the object t at WARN log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void WARN(T t) {
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
    print_message(message, LogLevel::ERROR, args...);
  }

  /**
   * @brief Logs the object t at INFO log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void INFO(T t) {}

  /**
   * @brief Logs the message with its fields at INFO log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void INFO(std::string message, Field<Args>... args) {}

  /**
   * @brief Logs the object t at DEBUG log level.
   *
   * @tparam T Type of the object to be printed.
   * @param t Object to be printed.
   */
  template <typename T>
  void DEBUG(T t) {}

  /**
   * @brief Logs the message with its fields at DEBUG log level.
   *
   * @tparam Args Types of the fields that will be printed.
   * @param message Message that will be printed.
   * @param args Fields that will be printed alongside the message.
   */
  template <typename... Args>
  void DEBUG(std::string message, Field<Args>... args) {}

 private:
  template <typename... ExtraArgs>
  ProductionLogger(
                   std::vector<std::function<void()>> _extraFunctions,
                   Field<ExtraArgs>... extra)
      : ProductionLogger( extra...) {
    for (auto f : _extraFunctions) {
      extraFunctions.push_back(f);
    }
  }

  Driver driver;
  void printv() {}
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

  std::vector<std::function<void()>> extraFunctions;

  template <typename T>
  void print_object(T object, LogLevel level) {
    driver.begin_message();
    driver.print_timestamp();
    driver.separator();
    driver.print_level(level);
    driver.separator();
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
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
    for (auto& f : extraFunctions) {
      f();
      driver.field_separator();
    }
    printv(args...);
    driver.end_message();
    out << std::endl;
  }


  std::function<void()> extraArgs;
};
};  // namespace logger
#endif
