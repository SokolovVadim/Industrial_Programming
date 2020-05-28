#include <logger.hpp>
#include <ostream>
int main() {
  m_log::logger_t<std::ostream> logger(std::cout);
  logger.Info("hello");
}