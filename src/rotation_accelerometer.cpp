#include "rotation_accelerometer.hpp"
using namespace std;

rotation_accelerometer::rotation_accelerometer()
{
}

rotation_accelerometer::~rotation_accelerometer()
{
}

void rotation_accelerometer::receiveMsgData(DataMessage *t_msg, int t_channel)
{

    if (t_msg->getType() == msg_type::VECTOR3D)
    {
        Vector3DMessage *provider = (Vector3DMessage *)t_msg;

        if (t_channel == receiving_channels::accelerometer)
        {
            accelerometer_data.x = provider->getData().x;
            accelerometer_data.y = provider->getData().y;
            accelerometer_data.z = provider->getData().z;

            std::cout<<"accelerometer_data.x="<<accelerometer_data.x<<"/n";
            std::cout<<"accelerometer_data.y="<<accelerometer_data.y<<"/n";
            std::cout<<"accelerometer_data.z="<<accelerometer_data.z<<"/n";
        }
  
        else if (t_channel == receiving_channels::ch_roll)
        {
            drone_orientation.x =provider->getData().x;
        }
        else if (t_channel == receiving_channels::ch_pitch)
        {
            drone_orientation.y = provider->getData().x;
        }
        else if (t_channel == receiving_channels::ch_yaw)
        {
            drone_orientation.z = provider->getData().x;
            update_rotation_matrices();
        }
    }
}



void rotation_accelerometer::update_rotation_matrices()    
{
    MatrixXd R_inertia(3, 3);

    R_inertia = R_drone_origin.Update(drone_orientation);

    rotated_unit_vector = Update_accelerometer_vector(R_inertia);

}

Vector3D<float> rotation_accelerometer::Update_accelerometer_vector(MatrixXd R_inertia)
{
    Vector3D<float> t_results;
    t_results.x = accelerometer_data.x * R_inertia(0, 0) + accelerometer_data.y * R_inertia(0, 1) + accelerometer_data.z * R_inertia(0, 2);
    t_results.y = accelerometer_data.x * R_inertia(1, 0) + accelerometer_data.y * R_inertia(1, 1) + accelerometer_data.z * R_inertia(1, 2);
    t_results.z = accelerometer_data.x * R_inertia(2, 0) + accelerometer_data.y * R_inertia(2, 1) + accelerometer_data.z * R_inertia(2, 2);

    rotated_acceleration.x=t_results.x;
    rotated_acceleration.y =t_results.y;
    rotated_acceleration.z=t_results.z;

    // std::cout<<"Rotated X="<<rotated_acceleration.x<<"\n";
    // std::cout<<"Rotated Y="<<rotated_acceleration.y<<"\n";
    // std::cout<<"Rotated Z="<<rotated_acceleration.z<<"\n";

    all_parameters.setVector3DMessage(rotated_acceleration);
    this->emitMsgUnicastDefault((DataMessage *)&all_parameters);

    return t_results;
}

