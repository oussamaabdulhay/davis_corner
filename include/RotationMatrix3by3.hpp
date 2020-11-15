#pragma once
#include "HEAR_math/Matrix3by3.hpp"
#include "HEAR_math/Vector3D.hpp"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <math.h>

using Eigen::MatrixXd;

class RotationMatrix3by3 : public Matrix3by3
{
    private:
        /* data */
    public:
        RotationMatrix3by3(/* args */);
        ~RotationMatrix3by3();
        MatrixXd Update(Vector3D<float>);
};