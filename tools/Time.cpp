#include "Time.h"

#include <sstream>

time_t parse_ISO8601(const std::string &date, bool &successfully) {
  successfully = true;
  int y, M, d, h, m;
  float s;
  int suc = sscanf(date.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);
  if (suc != 6) {
    successfully = false;
    return 0;
  }
  tm time = {0};
  time.tm_year = y - 1900; // Year since 1900
  time.tm_mon = M - 1;     // 0-11
  time.tm_mday = d;        // 1-31
  time.tm_hour = h;        // 0-23
  time.tm_min = m;         // 0-59
  time.tm_sec = (int) s;
  auto time_c = std::mktime(&time);
  return time_c;
}