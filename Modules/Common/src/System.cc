/*
 * Medical Image Registration ToolKit (MIRTK)
 *
 * Copyright 2016 Imperial College London
 * Copyright 2016 Andreas Schuh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mirtk/System.h"
#include "mirtk/Config.h" // WINDOWS
#include "mirtk/Stream.h"

#include <chrono>
#include <ctime>
#include <iomanip>

#ifdef WINDOWS
  #define VC_EXTRALEAN
  #define WIN32_LEAN_AND_MEAN
  #define NOMINMAX
  #include <windows.h>
  #include <Lmcons.h>
#else
  #include <unistd.h>
  #include <sys/types.h>
  #include <pwd.h>
#endif

namespace mirtk {


// -----------------------------------------------------------------------------
string GetDate()
{
  typedef std::chrono::system_clock Clock;
  std::time_t now = Clock::to_time_t(Clock::now());
  tm *info = std::localtime(&now);
  ostringstream os;
  os << std::put_time(info, "%d %b %Y");
  return os.str();
}

// -----------------------------------------------------------------------------
string GetTime()
{
  typedef std::chrono::system_clock Clock;
  std::time_t now = Clock::to_time_t(Clock::now());
  tm *info = std::localtime(&now);
  ostringstream os;
  os << std::put_time(info, "%H:%M:%S %Z");
  return os.str();
}

// -----------------------------------------------------------------------------
string GetDateTime()
{
  typedef std::chrono::system_clock Clock;
  std::time_t now = Clock::to_time_t(Clock::now());
  tm *info = std::localtime(&now);
  ostringstream os;
  os << std::put_time(info, "%c %Z");
  return os.str();
}

// -----------------------------------------------------------------------------
string GetUserName()
{
#ifdef WINDOWS
  char username[UNLEN+1];
  DWORD username_len = UNLEN+1;
  if (GetUserName(username, &username_len)) return username;
#else
  const passwd *pw = getpwuid(getuid());
  if (pw) return pw->pw_name;
#endif
  return "";
}


} // namespace mirtk
