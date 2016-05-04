#include </opt/pylon5/include/pylon/PylonIncludes.h>
#include <boost/shared_ptr.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

using namespace Pylon;

class baslerCamera
{
  public:
    baslerCamera(void);

    bool init(ros::NodeHandle& nh);
    void capture(void);
  private:
    CInstantCamera m_camera;
    image_transport::Publisher m_imagePub;
    sensor_msgs::ImagePtr m_image_ptr;
    CImageFormatConverter formatConverter;

    CPylonImage pylonImage;
    cv::Mat CvImage;
    cv::Mat Image;
    CGrabResultPtr ptrGrabResult;


};


