#include <ptclogs/driver/console_driver.h>
#include <ptclogs/logs.h>

#include <string>

using namespace logger;
using logger::Field;
using std::string;
int main() {
    auto logger = Logger<ConsoleDriver>();
    logger.INFO("this is a message in info level", Field<int>("number", 12),
		Field<string>("string", "hello I am string"));

    logger.DEBUG("this is a message in debug level", Field<int>("error", 12));
    logger.ERROR("this is a message in error level");
}
