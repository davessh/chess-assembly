# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OACPROYECTO_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OACPROYECTO_autogen.dir\\ParseCache.txt"
  "OACPROYECTO_autogen"
  )
endif()
