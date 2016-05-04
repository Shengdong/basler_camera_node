cmake_minimum_required (VERSION 2.6)
project(basler_camera_node)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


include_directories(${catkin_INCLUDE_DIRS}
                    /opt/pylon5/include
                    /usr/local/include
                    )

find_package(catkin REQUIRED COMPONENTS
             cmake_modules
             roscpp
             sensor_msgs
             image_transport
             cv_bridge
            )

find_package(BaslerPylon REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

catkin_package(
  LIBRARIES basler_camera
  CATKIN_DEPENDS roscpp sensor_msgs
  DEPENDS Eigen3 BOOST OPENCV2
)

###########
## Build ##
###########

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
)

add_library(basler_camera
  src/baslerCamera.cpp
)
target_link_libraries(basler_camera
  ${catkin_LIBRARIES}
  ${PYLON_LIBRARIES} 
  ${OpenCV_LIBS}
)

add_executable(basler_camera_node src/basler_camera_node.cpp)
target_link_libraries(basler_camera_node
  basler_camera
  ${catkin_LIBRARIES}
  ${PYLON_LIBRARIES} 
  ${OpenCV_LIBS}
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS basler_camera basler_camera_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/basler_camera_node
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)


