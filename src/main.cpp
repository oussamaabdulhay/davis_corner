#include "Event_vis.hpp"
#include "EventPlotting.hpp"
#include "Circle_detector.hpp"
#include <ros/ros.h>
#include "rayrotation_events.hpp"
#include "rotation_accelerometer.hpp"
#include <opencv2/core/types.hpp>
#include "HEAR_ROS_BRIDGE/ROSUnit_Factory.hpp"
#include "ROSUnit_Optitrack.hpp"

#include <iostream>

int main(int argc, char** argv)
{

ros::init(argc, argv, "ball_detector_node");
ros::NodeHandle main_nodehandle;
ROSUnit_Factory ROSUnit_Factory_main{main_nodehandle};
ROSUnit_Optitrack* position_in_z=new ROSUnit_Optitrack(main_nodehandle);
Event_vis* visualisation=new Event_vis(main_nodehandle);
Circle_detector* detection=new Circle_detector(main_nodehandle);

ROSUnit* rosunit_x_provider = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber, 
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/providers/x");
ROSUnit* rosunit_y_provider = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber, 
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/providers/y");
ROSUnit* rosunit_roll_provider = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber, 
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/providers/roll");
ROSUnit* rosunit_pitch_provider = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber, 
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/providers/pitch");
ROSUnit* rosunit_yaw_provider = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber, 
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/providers/yaw");
ROSUnit* rosunit_imu_acceleration = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Subscriber, 
                                                                  ROSUnit_msg_type::ROSUnit_GeoVec,
                                                                  "/imu/acceleration");
ROSUnit* rosunit_camera = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Publisher,
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/camera_provider");
ROSUnit* rosunit_accelerometer = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Publisher,
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/accelerometer_rotated");
                                                                

rayrotation_events* rotate_pv = new rayrotation_events();
rotation_accelerometer* rotate_accelerometer = new rotation_accelerometer();

detection->getPorts()[(int)Circle_detector::ports_id::OP_0_DATA]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_0_CAMERA]);
rosunit_x_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_0]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_1_X_POSITION]);
rosunit_y_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_1]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_2_Y_POSITION]);
position_in_z->getPorts()[(int)ROSUnit_Optitrack::ports_id::OP_0_OPT]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_3_Z_POSITION]);
rosunit_roll_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_2]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_4_ROLL]);
rosunit_pitch_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_3]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_5_PITCH]);
rosunit_yaw_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_4]->connect(rotate_pv->getPorts()[(int)rayrotation_events::ports_id::IP_6_YAW]);

rotate_pv->getPorts()[(int)rayrotation_events::ports_id::OP_0_DATA]->connect(rosunit_camera->getPorts()[(int)ROSUnit_PointPub::ports_id::IP_0]);
rosunit_imu_acceleration->getPorts()[(int)ROSUnit_GeoVecSub::ports_id::OP_0]->connect(rotate_accelerometer->getPorts()[(int)rotation_accelerometer::ports_id::IP_0_IMU]);
rosunit_roll_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_2]->connect(rotate_accelerometer->getPorts()[(int)rotation_accelerometer::ports_id::IP_1_ROLL]);
rosunit_pitch_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_3]->connect(rotate_accelerometer->getPorts()[(int)rotation_accelerometer::ports_id::IP_2_PITCH]);
rosunit_yaw_provider->getPorts()[(int)ROSUnit_PointSub::ports_id::OP_4]->connect(rotate_accelerometer->getPorts()[(int)rotation_accelerometer::ports_id::IP_3_YAW]);

rotate_accelerometer->getPorts()[(int)rotation_accelerometer::ports_id::OP_0_DATA]->connect(rosunit_accelerometer->getPorts()[(int)ROSUnit_PointPub::ports_id::IP_0]);



ros::Rate r(200);
while (ros::ok())
{
  r.sleep();
  ros::spinOnce();
}
return 0;
}
