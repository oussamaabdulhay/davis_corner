#include "rotation_accelerometer.hpp"
using namespace std;

rotation_accelerometer::rotation_accelerometer()
{
    this->_input_port_0 = new InputPort(ports_id::IP_0_IMU, this);
    this->_input_port_1 = new InputPort(ports_id::IP_1_ROLL, this);
    this->_input_port_2 = new InputPort(ports_id::IP_2_PITCH, this);
    this->_input_port_3 = new InputPort(ports_id::IP_3_YAW, this);
    this->_output_port = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port_0, _input_port_1,_input_port_2,_input_port_3, _output_port};
}

rotation_accelerometer::~rotation_accelerometer()
{
}


void rotation_accelerometer::process(DataMsg* t_msg, Port* t_port) {
    Vector3DMsg *provider = (Vector3DMsg *)t_msg;
    if(t_port->getID() == ports_id::IP_0_IMU)
    {
        accelerometer_data.x = provider->data.x;
        accelerometer_data.y = provider->data.y;
        accelerometer_data.z = provider->data.z;
    
        // std::cout<<"x="<<provider->data.x<<"\n";
        // std::cout<<"y="<<provider->data.y<<"\n";
        // std::cout<<"z="<<provider->data.z<<"\n";
        
    }
    else if(t_port->getID() == ports_id::IP_1_ROLL)
    { 
        drone_orientation.x =provider->data.x;
    }
    else if(t_port->getID() == ports_id::IP_2_PITCH)
    { 
        drone_orientation.y =provider->data.x;
        update_rotation_matrices();
        
    }
    else if(t_port->getID() == ports_id::IP_3_YAW)
    { 
        drone_orientation.z =provider->data.x;
    }
}



void rotation_accelerometer::update_rotation_matrices()    
{
    MatrixXd R_inertia(3, 3);

    R_inertia = R_drone_origin.Update(drone_orientation);

    R_inertia=R_inertia.inverse();

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



    Vector3DMsg point_msg;
    point_msg.data = rotated_acceleration;
    this->_output_port->receiveMsgData(&point_msg);

    // std::cout<<"Rotated X="<<rotated_acceleration.x<<"\n";
    // std::cout<<"Rotated Y="<<rotated_acceleration.y<<"\n";
    // std::cout<<"Rotated Z="<<rotated_acceleration.z<<"\n";

    return t_results;
}

