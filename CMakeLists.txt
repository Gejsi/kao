cmake_minimum_required(VERSION 3.15...3.30)

project(
  GtkHello
  VERSION 1.0
  LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${sources} ${headers})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(ADWAITA REQUIRED libadwaita-1)

include_directories(${GTK_INCLUDE_DIRS} ${ADWAITA_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS} ${ADWAITA_LIBRARY_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 23)
target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS} ${ADWAITA_LDFLAGS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
