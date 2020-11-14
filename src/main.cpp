#include "Event_vis.hpp"
#include "EventPlotting.hpp"
#include "Circle_detector.hpp"
#include <ros/ros.h>
#include "rayrotation_events.hpp"
#include "rotation_accelerometer.hpp"
#include <opencv2/core/types.hpp>
#include "common_srv/ROSUnit_Factory.hpp"
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
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/imu/acceleration");
  ROSUnit* rosunit_camera = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Publisher,
                                                                  ROSUnit_msg_type::ROSUnit_PointUint64,
                                                                  "/camera_provider");
  ROSUnit* rosunit_accelerometer = ROSUnit_Factory_main.CreateROSUnit(ROSUnit_tx_rx_type::Publisher,
                                                                  ROSUnit_msg_type::ROSUnit_Point,
                                                                  "/accelerometer_rotated");
                                                                

  rayrotation_events* rotate_pv = new rayrotation_events();
  rotation_accelerometer* rotate_accelerometer = new rotation_accelerometer();

  rosunit_x_provider->setEmittingChannel((int)rayrotation_events::receiving_channels::ch_x);
  rosunit_y_provider->setEmittingChannel((int)rayrotation_events::receiving_channels::ch_y);
  position_in_z->setEmittingChannel((int)rayrotation_events::receiving_channels::ch_z);
  rosunit_roll_provider->setEmittingChannel((int)rayrotation_events::receiving_channels::ch_roll);
  rosunit_pitch_provider->setEmittingChannel((int)rayrotation_events::receiving_channels::ch_pitch);
  rosunit_yaw_provider->setEmittingChannel((int)rayrotation_events::receiving_channels::ch_yaw);
  rosunit_roll_provider->setEmittingChannel((int)rotation_accelerometer::receiving_channels::ch_roll);
  rosunit_pitch_provider->setEmittingChannel((int)rotation_accelerometer::receiving_channels::ch_pitch);
  rosunit_yaw_provider->setEmittingChannel((int)rotation_accelerometer::receiving_channels::ch_yaw);
  detection->setEmittingChannel((int)rayrotation_events::receiving_channels::camera);
  rosunit_imu_acceleration->setEmittingChannel((int)rotation_accelerometer::receiving_channels::accelerometer);



  rosunit_x_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  rosunit_y_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  position_in_z->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  rosunit_roll_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  rosunit_roll_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_accelerometer);
  rosunit_pitch_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  rosunit_pitch_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_accelerometer);
  rosunit_yaw_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  rosunit_yaw_provider->addCallbackMsgReceiver((MsgReceiver*)rotate_accelerometer);
  detection->addCallbackMsgReceiver((MsgReceiver*)rotate_pv);
  rotate_pv->addCallbackMsgReceiver((MsgReceiver*)rosunit_camera);
  rosunit_imu_acceleration->addCallbackMsgReceiver((MsgReceiver*)rotate_accelerometer);
  rotate_accelerometer->addCallbackMsgReceiver((MsgReceiver*)rosunit_accelerometer);



  ros::Rate r(200);
  while (ros::ok())
  {
    r.sleep();
    ros::spinOnce();
  }
  return 0;
}
