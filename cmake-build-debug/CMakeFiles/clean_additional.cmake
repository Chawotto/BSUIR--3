# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MorrsQT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MorrsQT_autogen.dir\\ParseCache.txt"
  "MorrsQT_autogen"
  )
endif()
