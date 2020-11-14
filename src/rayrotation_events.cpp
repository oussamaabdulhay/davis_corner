#include "rayrotation_events.hpp"
using namespace std;

rayrotation_events::rayrotation_events()
{
    U_v.x = 1;
    U_v.y = 0;
    U_v.z = 0;

    P_b.x = 0.617673;
    P_b.y = 0.2373;
    P_b.z = 1.2239;

    x = false;
    y = false;
}

rayrotation_events::~rayrotation_events()
{
}

void rayrotation_events::receiveMsgData(DataMessage *t_msg, int t_channel)
{

    if (t_msg->getType() == msg_type::VECTOR3D)
    {
        Vector3DMessage *provider = (Vector3DMessage *)t_msg;

        if (t_channel == receiving_channels::ch_x)
        {
            drone_position.x = provider->getData().x;
        }
        else if (t_channel == receiving_channels::ch_y)
        {
            drone_position.y = provider->getData().x;
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
        }
    }
    else if (t_msg->getType() == msg_type::optitrack)
    {
        OptitrackMessage *opti_msg = (OptitrackMessage *)t_msg;
        drone_position.z = opti_msg->getPosition().z;
    }

    else if(t_msg->getType() == msg_type::VECTOR2D)
    {
        Vector2DMsg* pixel_location = (Vector2DMsg*) t_msg;
               ball_location.x=pixel_location->getData().x;
               ball_location.y=pixel_location->getData().y;
               time=pixel_location->getData().time;
               update_camera_angles();
               
    }
}

MatrixXd rayrotation_events::MultiplyMatrices(MatrixXd R_inertia, MatrixXd R_drone)
{

    MatrixXd rotated_matrix(3, 3);
    rotated_matrix(0, 0) = R_drone(0, 0) * R_inertia(0, 0) + R_drone(0, 1) * R_inertia(1, 0) + R_drone(0, 2) * R_inertia(2, 0);

    rotated_matrix(1, 0) = R_drone(1, 0) * R_inertia(0, 0) + R_drone(1, 1) * R_inertia(1, 0) + R_drone(1, 2) * R_inertia(2, 0);

    rotated_matrix(2, 0) = R_drone(2, 0) * R_inertia(0, 0) + R_drone(2, 1) * R_inertia(1, 0) + R_drone(2, 2) * R_inertia(2, 0);

    rotated_matrix(0, 1) = R_drone(0, 0) * R_inertia(0, 1) + R_drone(0, 1) * R_inertia(1, 1) + R_drone(0, 2) * R_inertia(2, 1);

    rotated_matrix(1, 1) = R_drone(1, 0) * R_inertia(0, 1) + R_drone(1, 1) * R_inertia(1, 1) + R_drone(1, 2) * R_inertia(2, 1);

    rotated_matrix(2, 1) = R_drone(2, 0) * R_inertia(0, 1) + R_drone(2, 1) * R_inertia(1, 1) + R_drone(2, 2) * R_inertia(2, 1);

    rotated_matrix(0, 2) = R_drone(0, 0) * R_inertia(0, 2) + R_drone(0, 1) * R_inertia(1, 2) + R_drone(0, 2) * R_inertia(2, 2);

    rotated_matrix(1, 2) = R_drone(1, 0) * R_inertia(0, 2) + R_drone(1, 1) * R_inertia(1, 2) + R_drone(1, 2) * R_inertia(2, 2);

    rotated_matrix(2, 2) = R_drone(2, 0) * R_inertia(0, 2) + R_drone(2, 1) * R_inertia(1, 2) + R_drone(2, 2) * R_inertia(2, 2);
    return rotated_matrix;
}

Vector3D<float> rayrotation_events::Update_unit_vector(MatrixXd rotated_matrix)
{
    Vector3D<float> t_results;
    t_results.x = U_v.x * rotated_matrix(0, 0) + U_v.y * rotated_matrix(0, 1) + U_v.z * rotated_matrix(0, 2);
    t_results.y = U_v.x * rotated_matrix(1, 0) + U_v.y * rotated_matrix(1, 1) + U_v.z * rotated_matrix(1, 2);
    t_results.z = U_v.x * rotated_matrix(2, 0) + U_v.y * rotated_matrix(2, 1) + U_v.z * rotated_matrix(2, 2);

     obj_pos.time=time;
     obj_pos.x=0;
     obj_pos.y =-1*t_results.y*100;
     obj_pos.z=-1*t_results.z*100;
     all_parameters.setVector3DMessageUint64(obj_pos);
     this->emitMsgUnicastDefault((DataMessage *)&all_parameters);

    return t_results;
}

void rayrotation_events::scale_and_translate()
{
    Vector3D<float> t_results;
    t_results.x = P_b.x - drone_position.x;
    t_results.y = P_b.y - drone_position.y;
    t_results.z = P_b.z - drone_position.z;
    
    double t_s = Vector3D<float>::getL2Norm(t_results);
    
    rotated_unit_vector.x = t_s * rotated_unit_vector.x;
    rotated_unit_vector.y = t_s * rotated_unit_vector.y;
    rotated_unit_vector.z = t_s * rotated_unit_vector.z;



    rotated_unit_vector.x = rotated_unit_vector.x+drone_position.x;
    rotated_unit_vector.y = rotated_unit_vector.y+drone_position.y;
    rotated_unit_vector.z = rotated_unit_vector.z+drone_position.z;

    rotated_unit_vector.x = rotated_unit_vector.x-P_b.x;
    rotated_unit_vector.y = rotated_unit_vector.y-P_b.y;
    rotated_unit_vector.z = rotated_unit_vector.z-P_b.z;


}

void rayrotation_events::update_camera_angles()
{
    float theta_yaw = -(0.6270 / 346.0) * ball_location.x;//1.45
    float theta_roll = (0.4805 / 260.0) * ball_location.y;//1.19

    camera_angle.x = theta_roll;
    camera_angle.y = 0;
    camera_angle.z = theta_yaw;

    this->update_rotation_matrices();
}

void rayrotation_events::update_rotation_matrices()    
{

    MatrixXd R_drone(3, 3);
    MatrixXd R_inertia(3, 3);
    MatrixXd rotated_matrix(3, 3);

    R_inertia = R_o_d.Update(drone_orientation); //Create the rotation matrices
    R_drone = R_d_c.Update(camera_angle);

    rotated_matrix = MultiplyMatrices(R_inertia, R_drone); //Multiply the rotation matrices;

    rotated_unit_vector = Update_unit_vector(rotated_matrix);

    scale_and_translate();
}
