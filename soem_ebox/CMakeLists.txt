#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.6.3
#
cmake_minimum_required(VERSION 2.6.3)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(soem_ebox)

#
# Do setup in case of ros package, If ROS_ROOT is set, it is
# recommended to use RTT/OCL through the ros packages.
#
set (ROS_ROOT $ENV{ROS_ROOT} )
if (ROS_ROOT)
  include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
  rosbuild_init()
  rosbuild_find_ros_package( rtt )
  set( RTT_HINTS HINTS ${rtt_PACKAGE_PATH}/install )
endif()

# Set the CMAKE_PREFIX_PATH in case you're not using Orocos through ROS
# for helping these find commands find RTT.
find_package(OROCOS-RTT REQUIRED ${RTT_HINTS})

# Defines the orocos_* cmake macros. See that file for additional
# documentation.
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)

#
# Components, types and plugins.
#
orocos_plugin(soem_ebox src/soem_ebox.cpp) # ...only one plugin function per library !
#

# Generates and installs our orocos-soem_ebox-<target>.pc and manifest.xml file
#
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/orocos-soem_ebox.pc.in ${CMAKE_CURRENT_BINARY_DIR}/orocos-soem_ebox-${OROCOS_TARGET}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/orocos-soem_ebox-${OROCOS_TARGET}.pc DESTINATION  lib/pkgconfig )
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/manifest.xml DESTINATION  lib/orocos/soem_ebox )

#
# Provided 'uninstall' target
#
orocos_uninstall_target()