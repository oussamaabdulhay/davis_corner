#pragma once
#include "Matrix3by3.hpp"
#include "common_srv/Vector3D.hpp"
#include "RotationMatrix3by3.hpp"
#include <opencv2/core/types.hpp>
#include "common_srv/MsgEmitter.hpp"
#include "common_srv/MsgReceiver.hpp"
#include "common_srv/Vector3DMessage.hpp"
#include "common_srv/Vector2DMsg.hpp"
#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>
#include "common_srv/FloatMsg.hpp"
#include <ros/ros.h>

using Eigen::MatrixXd;

class rotation_accelerometer: public MsgEmitter, public MsgReceiver
{
    public:
        Vector3D<float> accelerometer_data,drone_orientation,rotated_unit_vector;
        RotationMatrix3by3 R_accelerometer_origin,R_drone_origin;
        Vector3D<float> rotated_acceleration;
        Vector3DMessage all_parameters;
        void receiveMsgData(DataMessage* t_msg) {};
        Vector3D<float> Update_accelerometer_vector(MatrixXd);
        void receiveMsgData(DataMessage* t_msg, int t_channel);
        void update_rotation_matrices();
        rotation_accelerometer();
       

        enum receiving_channels {accelerometer,ch_roll,ch_pitch,ch_yaw};
        ~rotation_accelerometer();
};