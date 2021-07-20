#ifndef PTCLOGS_FIELDS_HPP
#define PTCLOGS_FIELDS_HPP
#include <sstream>

#define ptclogs_trace()                      \
  logger::Field<std::string>("trace", []() { \
    std::stringstream strim;                 \
    strim << __FILE__ << ":" << __LINE__;    \
    return strim.str();                      \
  }())

#define ptclogs_caller() \
  logger::Field<std::string>("caller", __PRETTY_FUNCTION__)

#endif
