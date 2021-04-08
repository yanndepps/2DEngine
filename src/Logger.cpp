#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

std::string CurrentDateTimeToString() {
  std::time_t now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::string output(30, '\0');
  std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S",
                std::localtime(&now));
  return output;
}

void Logger::Log(const std::string &message) {
  // Print on the console the message:
  // LOG: [ 12/Oct/2020 09:13:17 ] - Here goes the message ...
  // this should be displayed in green
  std::string output = "LOG: [" + CurrentDateTimeToString() + "]: " + message;
  std::cout << "\x1B[32m]" << output << "\033[0m" << std::endl;
}

void Logger::Err(const std::string &message) {
  // Print on the console the message:
  // ERR: [ 12/Oct/2020 09:13:17 ] - Here goes the message ...
  // this should be displayed in red
  std::string output = "ERR: [" + CurrentDateTimeToString() + "]: " + message;
  std::cerr << "\x1B[91m" << output << "\033[0m" << std::endl;
}
