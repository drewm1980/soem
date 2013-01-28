
#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#common commands for building c++ executables and libraries
find_path(RTNET_INCLUDE_DIR NAMES rtnet.h PATH_SUFFIXES rtnet/include)
option(ENABLE_RTNET "Enable RTnet over Xenomai." ON)
if(RTNET_INCLUDE_DIR AND ENABLE_RTNET)
  message("Found RTNET: ${RTNET_INCLUDE_DIR}")
  include_directories(${RTNET_INCLUDE_DIR})
  add_definitions(-DHAVE_RTNET)
  # try Xenomai
  execute_process(COMMAND xeno-config --skin=posix --cflags OUTPUT_VARIABLE XENO_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND xeno-config --skin=posix --ldflags OUTPUT_VARIABLE XENO_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${XENO_CFLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${XENO_LDFLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${XENO_LDFLAGS} -lnative")
endif()

add_library(soem_core SHARED src/ethercatbase.c src/ethercatcoe.c src/ethercatconfig.c src/ethercatfoe.c src/ethercatsoe.c src/ethercatmain.c src/ethercatprint.c src/nicdrv.c src/ethercatdc.c) 

include_directories(${PROJECT_SOURCE_DIR}/soem_core/src)

add_executable(slaveinfo src/slaveinfo.c)
target_link_libraries(slaveinfo soem_core)
