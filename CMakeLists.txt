cmake_minimum_required(VERSION 3.0)
project(jsonite_daemon C)

# Find pkg-config helper
find_package(PkgConfig REQUIRED)

# Probe the three modules you need
pkg_check_modules(GIO       REQUIRED gio-2.0)
pkg_check_modules(GIO_UNIX  REQUIRED gio-unix-2.0)
pkg_check_modules(JSONGLIB  REQUIRED json-glib-1.0)

# 4) Define your executable and its sources
add_executable(jsonite_daemon
  src/main.c
  src/gdbus_widget.c
  src/jsonite_widget.c
  src/jsonite_calculator.c
  src/gdbus_calculator.c
)

# ignore unused parameters
target_compile_options(jsonite_daemon PRIVATE
  -Wno-unused-parameter
)

# Optional: Add include dirs this way (better scoping)
target_include_directories(jsonite_daemon PRIVATE include)

# Optional: treat warnings as errors (good for dev)
target_compile_options(jsonite_daemon PRIVATE -Wall -Wextra -pedantic -Werror)

# 5) Pull in all the include directories
#    (this covers /usr/include/glib-2.0, /usr/lib/.../glib-2.0/include,
#     /usr/include/gio-unix-2.0, /usr/include/json-glib-1.0, etc.)
target_include_directories(jsonite_daemon PRIVATE
  ${GIO_INCLUDE_DIRS}
  ${GIO_UNIX_INCLUDE_DIRS}
  ${JSONGLIB_INCLUDE_DIRS}
)

# 6) Propagate any extra compile flags (e.g. -pthread)
target_compile_options(jsonite_daemon PRIVATE
  ${GIO_CFLAGS_OTHER}
  ${GIO_UNIX_CFLAGS_OTHER}
  ${JSONGLIB_CFLAGS_OTHER}
)

# 7) Link against the required libraries
target_link_libraries(jsonite_daemon PRIVATE
  ${GIO_LIBRARIES}
  ${GIO_UNIX_LIBRARIES}
  ${JSONGLIB_LIBRARIES}
)

# 8) (Optional) if you want to see the full flags for debugging:
# message(STATUS "GIO include dirs:       ${GIO_INCLUDE_DIRS}")
# message(STATUS "GIO libs:               ${GIO_LIBRARIES}")
# message(STATUS "GIO extra CFLAGS:       ${GIO_CFLAGS_OTHER}")
# message(STATUS "GIO-UNIX include dirs:  ${GIO_UNIX_INCLUDE_DIRS}")
# message(STATUS "GIO-UNIX libs:          ${GIO_UNIX_LIBRARIES}")
# message(STATUS "JSON-GLIB include dirs: ${JSONGLIB_INCLUDE_DIRS}")
# message(STATUS "JSON-GLIB libs:         ${JSONGLIB_LIBRARIES}")
# message(STATUS "JSON-GLIB extra CFLAGS: ${JSONGLIB_CFLAGS_OTHER}")
