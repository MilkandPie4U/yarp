# Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
# Copyright (C) 2006-2010 RobotCub Consortium
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

include(YarpPlugin)
include(YarpPrintFeature)

yarp_begin_plugin_library(yarpmod OPTION YARP_COMPILE_DEVICE_PLUGINS
                                  DEFAULT ON
                                  DOC "devices plugins")
  add_subdirectory(depthCamera)
  add_subdirectory(fakeDepthCamera)
  add_subdirectory(fakebot)
  add_subdirectory(fakeMotionControl)
  add_subdirectory(fakeAnalogSensor)
  add_subdirectory(fakeIMU)
  add_subdirectory(SerialServoBoard)
  add_subdirectory(ffmpeg)
  add_subdirectory(opencv)
  add_subdirectory(serialport)
  add_subdirectory(portaudio)
  add_subdirectory(imuBosch_BNO055)
  add_subdirectory(DynamixelAX12Ftdi)
  add_subdirectory(fakeLaser)
  add_subdirectory(laserFromDepth)
  add_subdirectory(rpLidar)
  add_subdirectory(rpLidar2)
  add_subdirectory(laserHokuyo)
  add_subdirectory(ovrheadset)
  add_subdirectory(test_grabber)
  add_subdirectory(SDLJoypad)
  add_subdirectory(BatteryClient)
  add_subdirectory(BatteryWrapper)
  add_subdirectory(Rangefinder2DWrapper)
  add_subdirectory(realsense2)
  add_subdirectory(ServerSoundGrabber)
  add_subdirectory(multipleAnalogSensorsMsgs)
  add_subdirectory(multipleanalogsensorsserver)
  add_subdirectory(multipleanalogsensorsclient)
  add_subdirectory(multipleanalogsensorsremapper)

  if(CREATE_LIB_MATH)
    add_subdirectory(transformClient)
    add_subdirectory(transformServer)
    add_subdirectory(localization2DClient)
    add_subdirectory(map2DClient)
    add_subdirectory(map2DServer)
    add_subdirectory(navigation2DClient)
    add_subdirectory(Rangefinder2DClient)
  endif()

  # We can also suck in other device libraries built the same way.
  # We seek an ExternalModules.cmake file either in the conf directory
  # or in our build directory
  set(EXTFILES "${YARP_MODULE_DIR}/ExternalModules.cmake"
               "${CMAKE_BINARY_DIR}/ExternalModules.cmake")
  foreach(EXTFILE ${EXTFILES})
    if(EXISTS ${EXTFILE})
      include(${EXTFILE})
      foreach(EXTDIR ${EXTERNAL_MODULES})
        if(NOT ${EXTDIR}_DIR)
          set(${EXTDIR}_DIR ${${EXTDIR}_PATH})
        endif()
        if(NOT ${EXTDIR}_DIR)
          message(FATAL_ERROR "Need ${EXTDIR}_DIR in ${EXTFILE}")
        endif()
        # make sure path is usable - could have environment variable parts
        file(TO_CMAKE_PATH ${${EXTDIR}_DIR} safe_path)
        if(NOT EXISTS "${safe_path}/CMakeLists.txt")
          message(FATAL_ERROR "${EXTDIR}_DIR=${${EXTDIR}_DIR} from ${EXTFILE} does not contain a CMakeLists.txt")
        endif()
      add_subdirectory(${safe_path}
                       ${CMAKE_CURRENT_BINARY_DIR}/externals/${EXTDIR})
    endforeach(EXTDIR ${EXTERNAL_MODULES})
  endif(EXISTS ${EXTFILE})
endforeach(EXTFILE)

yarp_end_plugin_library(yarpmod QUIET)
add_library(YARP::yarpmod ALIAS yarpmod)


install(TARGETS yarpmod
        EXPORT YARP_${YARP_PLUGIN_MASTER}
        COMPONENT ${YARP_PLUGIN_MASTER}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(YarpInstallBasicPackageFiles)
if(NOT "${YARP_yarpmod_PUBLIC_DEPS}" STREQUAL "")
  list(REMOVE_DUPLICATES YARP_yarpmod_PUBLIC_DEPS)
endif()
if(NOT "${YARP_yarpmod_PRIVATE_DEPS}" STREQUAL "")
  list(REMOVE_DUPLICATES YARP_yarpmod_PRIVATE_DEPS)
endif()
yarp_install_basic_package_files(YARP_yarpmod
                                 FIRST_TARGET yarpmod
                                 DEPENDENCIES ${YARP_yarpmod_PUBLIC_DEPS}
                                 PRIVATE_DEPENDENCIES ${YARP_yarpmod_PRIVATE_DEPS})

set_property(TARGET yarpmod PROPERTY FOLDER "Plugins/Device")

yarp_renamed_option(CREATE_DEVICE_LIBRARY_MODULES YARP_COMPILE_DEVICE_PLUGINS) # since YARP 3.0.0
