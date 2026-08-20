#pragma once

#include <algorithm>
#include <numeric>

#ifdef _WIN32
  #include <execution>
  // Keep the execution policy argument on MSVC (PSTL is available).
  #define OMC_IF_EXEC(...) __VA_ARGS__,
#else
  // Apple libc++ has no PSTL. Older libstdc++ PSTL expects legacy TBB::task,
  // which is incompatible with oneTBB. Use sequential overloads instead.
  #define OMC_IF_EXEC(...)
#endif
