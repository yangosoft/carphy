

#include "car.hpp"
#include "utils.hpp"
#include "world.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello, World!" << std::endl;

    Vec3<float> position{1.0f, -1.0f, 0.0f};
    Vec3<float> position2{1.0f, -1.0f, 2.0f};

    auto result = add(position, position2);
    std::cout << "Result: x=" << result.x << ", y=" << result.y << ", z=" << result.z << std::endl;

    Car myCar;
    myCar.set_rpm(4400);

    max_speeds_by_gear(myCar);

    return 0;
}