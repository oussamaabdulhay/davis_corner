#pragma once
#include "HEAR_math/Matrix3by3.hpp"
#include "RotationMatrix3by3.hpp"
#include <opencv2/core/types.hpp>
#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>
#include "HEAR_math/Vector3D.hpp"
#include "HEAR_msg/Vector3DMsg.hpp"
#include <ros/ros.h>
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"

using Eigen::MatrixXd;

class rotation_accelerometer : public Block
{
    private:
        Port* _input_port_0;
        Port* _input_port_1;
        Port* _input_port_2;
        Port* _input_port_3;
        Port* _output_port;
    public:
        Vector3D<float> accelerometer_data,drone_orientation,rotated_unit_vector;
        RotationMatrix3by3 R_accelerometer_origin,R_drone_origin;
        Vector3D<float> rotated_acceleration;
        Vector3DMsg all_parameters;
        void process(DataMsg* t_msg, Port* t_port);
        Vector3D<float> Update_accelerometer_vector(MatrixXd);
        void update_rotation_matrices();
        rotation_accelerometer();
        enum ports_id {IP_0_IMU,IP_1_ROLL,IP_2_PITCH,IP_3_YAW,OP_0_DATA};
       

        enum receiving_channels {accelerometer,ch_roll,ch_pitch,ch_yaw};
        ~rotation_accelerometer();
};