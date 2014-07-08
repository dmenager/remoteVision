cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
project(remoteVision)
find_package(qibuild)

option(AVCAPTURE_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  ON)

find_package(X11)

set(_srcs
  main.cpp
  avcaptureremote.h
  avcaptureremote.cpp
  dmfunctions.cpp
  dmfunctions.h
  dataEntry.h
  dataReader.cpp
  dataReader.h
  neuralNetwork.cpp
  neuralNetwork.h
  neuralNetworkTrainer.cpp
  neuralNetworkTrainer.h
  ubyteextractor.h
  ubyteextractor.cpp
  radonTransformer.h
  nearestneighbour.cpp
  nearestneighbour.h
  PracticalSocket.cpp
  PracticalSocket.h
  server.cpp
  server.h
)

if(AVCAPTURE_IS_REMOTE)
  add_definitions(" -DAVCAPTURE_IS_REMOTE ")
  qi_create_bin(remoteVision ${_srcs})
else()
  qi_create_lib(remoteVision SHARED ${_srcs} SUBFOLDER naoqi)
endif()

qi_use_lib(remoteVision ALCOMMON ALAUDIO ALVISION OPENCV2_CORE OPENCV2_HIGHGUI OPENCV2_IMGPROC X11)
