#pragma once

// Prefer C++20 std::format when the toolchain provides it (MSVC).
// GCC 9 / older Apple libc++ do not; fall back to header-only {fmt}.
// FMT_CONSTEVAL is forced empty: Apple Clang 14+ otherwise enables consteval
// and rejects FMT_STRING in format-inl.h.

#if defined(OMC_HAS_STD_FORMAT)
  #include <format>
#else
  #ifndef FMT_CONSTEVAL
    #define FMT_CONSTEVAL
  #endif
  #ifndef FMT_HEADER_ONLY
    #define FMT_HEADER_ONLY
  #endif
  #include <fmt/format.h>
  namespace std {
  using fmt::format;
  } // namespace std
#endif
