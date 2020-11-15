#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/types.hpp>
#include <cmath>
#include "std_msgs/Float32.h"
#include "geometry_msgs/Point.h"
#include <sstream>
#include <ros/ros.h>
#include <iostream>
#include "medianFilter.hpp"
#include <opencv2/features2d.hpp>
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_math/Vector2D.hpp"
#include "HEAR_msg/Vector2DMsg.hpp"
#include "HEAR_core/Block.hpp"

class Circle_detector: public Block
{
private:
    Port* _output_port;

public:
    ros::NodeHandle nh_;
    ros::Publisher puby, pubx;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    float threshold;
    Vector2D<float> obj_pos;
    cv::Point2d _c_;
    Vector2DMsg pixel_location;
    std::vector<cv::Point2f> temp;
    const std::string OPENCV_WINDOW = "Image window";
    std::vector<cv::KeyPoint> keypoints;
    medianFilter* filter=new medianFilter();
    float point_of_interest;
    enum ports_id {OP_0_DATA};
    void process(DataMsg* t_msg, Port* t_port){};
    

    Circle_detector(ros::NodeHandle&);
    ~Circle_detector();

    void imageCb(const sensor_msgs::ImageConstPtr &msg);
    cv::SimpleBlobDetector::Params params;
};