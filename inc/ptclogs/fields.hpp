#ifndef PTCLOGS_FIELDS_HPP
#define PTCLOGS_FIELDS_HPP
#include <sstream>

#define ptclogs_trace()       \
  logger::Field<std::string>( \
      "trace",                \
      std::string(__FILE__) + ":" + std::string(std::to_string(__LINE__)))

#define ptclogs_caller() \
  logger::Field<std::string>("caller", __PRETTY_FUNCTION__)

#endif
