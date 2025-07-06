# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Assignment2-Programming-Assignment_autogen"
  "CMakeFiles\\Assignment2-Programming-Assignment_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Assignment2-Programming-Assignment_autogen.dir\\ParseCache.txt"
  )
endif()
