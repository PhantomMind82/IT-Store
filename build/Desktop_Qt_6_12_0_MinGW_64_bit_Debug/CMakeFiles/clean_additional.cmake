# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GestionVente_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GestionVente_autogen.dir\\ParseCache.txt"
  "GestionVente_autogen"
  )
endif()
