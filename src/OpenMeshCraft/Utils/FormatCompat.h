#pragma once

// Provide OMC::format. Never inject fmt::format into namespace std, and never
// include <format> unless CMake proved it actually works (OMC_HAS_STD_FORMAT).
//
// AppleClang 21 / new macOS SDKs ship <format>, but Studio deps still target
// macOS 10.15. libc++ then marks std::to_chars / std::format unavailable
// (macOS 13.3+). __has_include(<format>) is not a valid probe on that
// toolchain. CMake's OMC_STD_FORMAT_WORKS try_compile is.
//
// When std::format is unavailable, use header-only {fmt} as OMC::format.
// Putting using fmt::format into namespace std is also wrong on new libc++:
// std::format is still declared, so std::format(...) becomes ambiguous.
//
// FMT_CONSTEVAL is forced empty: Apple Clang 14+ otherwise enables consteval
// and rejects FMT_STRING in format-inl.h.

#ifdef OMC_HAS_STD_FORMAT
  #include <format>
  namespace OMC {
  using std::format;
  } // namespace OMC
#else
  #ifndef FMT_CONSTEVAL
    #define FMT_CONSTEVAL
  #endif
  #ifndef FMT_HEADER_ONLY
    #define FMT_HEADER_ONLY
  #endif
  #include <fmt/format.h>
  namespace OMC {
  using fmt::format;
  } // namespace OMC
#endif
