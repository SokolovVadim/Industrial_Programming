#include <nlohmann/json.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
// for convenience
using json = nlohmann::json;

namespace m_log
{
  template<typename T>
  class logger_t {
  public:
    T& m_output;
    logger_t(T& output):
      m_output(output)
    {}
    // json output format
    // {"time": time, "message": message, "threadId": threadId}
    auto Info(const std::string& message) -> void {
        json j;
        j["time"] = get_current_time();
        j["message"] = message;
        j["threadId"] = get_current_thread_id();
        m_output << j;
    }

    std::string get_current_time()
    {
        auto cur_time = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(cur_time);
        return std::string(std::ctime(&time));
    }
    std::string get_current_thread_id()
    {
      
       auto myid = std::this_thread::get_id();
       std::stringstream ss;
       ss << myid;
       return ss.str();

    }

  };
}