#include "baslerCamera.h"
#include <iostream>
#include "sensor_msgs/Image.h"

using namespace std;
using namespace Pylon;

baslerCamera::baslerCamera()
 : m_camera(CTlFactory::GetInstance().CreateFirstDevice())
{
 //   PylonInitialize();
}

bool 
baslerCamera::init(ros::NodeHandle& nh)
{
    cout << "Using device " << m_camera.GetDeviceInfo().GetModelName()<<endl;
  
    GenApi::INodeMap& nodemap = m_camera.GetNodeMap();
    
    m_camera.Open();
   
    cout<< "Camera Opened" <<endl;
    GenApi::CIntegerPtr width = nodemap.GetNode("Width");
    GenApi::CIntegerPtr height= nodemap.GetNode("Height");
 
    m_camera.MaxNumBuffer = 3;
    m_camera.StartGrabbing();

    image_transport::ImageTransport it(nh);
    m_imagePub = it.advertise("image_rect", 1);
    return true;
}

void 
baslerCamera::capture(void)
{    
    while (m_camera.IsGrabbing() && ros::ok())
    {
        m_camera.RetrieveResult(500, ptrGrabResult, TimeoutHandling_ThrowException);

        if (ptrGrabResult->GrabSucceeded())
        {
            formatConverter.Convert(pylonImage, ptrGrabResult);
            CvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC1, pylonImage.GetBuffer());
            cv::Size size(640,480);
            cv::resize(CvImage, Image, size);
            m_image_ptr = cv_bridge::CvImage(std_msgs::Header(), "mono8", CvImage).toImageMsg();
            m_imagePub.publish(m_image_ptr); 
        }
    }
}
