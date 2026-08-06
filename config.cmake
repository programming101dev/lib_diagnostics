# Project metadata
set(PROJECT_NAME "p101_diagnostics")
set(PROJECT_VERSION "0.0.1")
set(PROJECT_DESCRIPTION "Diagnostics, warnings, formatted messages, and system logging")
set(PROJECT_LANGUAGE "C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(STANDARD_FLAGS
        -D_POSIX_C_SOURCE=200809L
        -D_XOPEN_SOURCE=700
        -Werror
)
set(DARWIN_STANDARD_FLAGS -D_DARWIN_C_SOURCE)
set(LINUX_STANDARD_FLAGS -D_GNU_SOURCE)
set(BSD_STANDARD_FLAGS -D_BSD_SOURCE -D__BSD_VISIBLE)

set(LIBRARY_TARGETS p101_diagnostics)
set(p101_diagnostics_SOURCES
        src/diagnostics.c
)
set(p101_diagnostics_HEADERS
        include/p101_diagnostics/diagnostics.h
)
set(p101_diagnostics_LINK_LIBRARIES
        p101_error
        p101_env
        p101_c
)

