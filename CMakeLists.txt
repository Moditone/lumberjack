cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(lumberjack LANGUAGES CXX)

add_library(lumberjack STATIC "")

target_compile_features(lumberjack PRIVATE cxx_std_17)
set_target_properties(lumberjack PROPERTIES CXX_EXTENSIONS OFF)

install(TARGETS lumberjack
	DESTINATION lib)

set (HEADERS
	"csv_formatter.hpp"
	"datetime_formatter.hpp"
	"delimiting_formatter.hpp"
	"epoch_formatter.hpp"
	"file_log.hpp"
	"fmt_formatter.hpp"
	"formatter.hpp"
	"json_formatter.hpp"
	"log.hpp"
	"stack_log.hpp"
	"stream_log.hpp"
	"time_formatter.hpp")

set (SOURCES
	"csv_formatter.cpp"
	"datetime_formatter.cpp"
	"epoch_formatter.cpp")

target_sources(lumberjack PRIVATE ${HEADERS} ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

install(FILES ${HEADERS}
	DESTINATION include/moditone/lumberjack)
