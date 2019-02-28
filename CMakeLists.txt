cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(lumberjack LANGUAGES CXX)

add_library(lumberjack INTERFACE)

install(TARGETS lumberjack
	DESTINATION lib)

set (HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/csv_formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/date_time_formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/delimiting_formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/epoch_formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/file_log.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/fmt_formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/function_log.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/json_formatter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/log.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/stack_log.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/stream_log.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/time_formatter.hpp")

target_sources(lumberjack INTERFACE ${HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})

install(FILES ${HEADERS}
	DESTINATION include/moditone/lumberjack)
