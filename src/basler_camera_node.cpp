#include "baslerCamera.h"
#include <iostream>

int main(int argc, char **argv)
{
    Pylon::PylonInitialize();
    ros::init(argc, argv, "basler_camera");
     
    ros::NodeHandle nh;
    
    baslerCamera camera;

    std::cout << "Camera Created!" << std::endl;

    if (!camera.init(nh))
    {
       ROS_WARN("Initialise device Failed");
       return 1;
    }
    else
       ROS_INFO("Initialise device Succeeded");
    camera.capture();
}
