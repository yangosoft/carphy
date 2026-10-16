#include "world.hpp"

#include <array>
#include <iostream>

void update_world(Car &car, float delta_time)
{

    // lets suppouse car is heading just to X
    const Vec3<float> u{1.0f, 0.0f, 0.0f};
    const float speed = car.get_speed();
    const auto velocity = car.get_velocity();

    // Calculate forces acting on the car
    FDrag f_drag;

    const auto effective_engine_force = car.get_engine_force() / 2;
    const float maximum_traction = car.get_mass() / 2 * GRAVITY; // Maximum traction force assuming weight is evenly distributed on two driven wheels
    const float maximum_acceleration = maximum_traction / car.get_mass();

    // b = c = 1.25m and L is therefore 2.50 m, the CG is 1.0 m above ground level.
    //  After a brief moment the amount of shifted weight is then (h/L)*M*a, that is (1.0/2.50)*1500*4.9 = 2940 N.
    // This means Wf =  7350 - 2940 N and Wr = 7350 + 2940 N. The rear wheels now have extra weight which in this case is sufficient to allows the driver to put his foot all the way down.

    FTraction f_traction = scale(u, effective_engine_force);

    // fdrag.x = - Cdrag * v.x * speed;
    f_drag.x = car.get_c_drag() * velocity.x * speed;
    f_drag.y = car.get_c_drag() * velocity.y * speed;
    f_drag.z = car.get_c_drag() * velocity.z * speed;

    const FRollingResistance f_rolling_resistance = scale(velocity, -car.get_c_rr());

    Vec3<float> net_force = add(add(f_traction, f_drag), f_rolling_resistance);
}

float speed_in_gear(float wheel_radius, float engine_rpm, float gear_ratio, float differential_ratio)
{
    const float rev_per_second = engine_rpm / 60.0f;
    const float rev_per_second_after_gear = rev_per_second / (gear_ratio * differential_ratio);
    const float max_speed = rev_per_second_after_gear * 2.0f * PI * wheel_radius;
    return max_speed;
}

void max_speeds_by_gear(Car &car)
{
    std::array<float, 7> gears;
    car.get_gear_ratios(gears);
    for (int i = 0; i < 7; ++i)
    {
        std::cout << "Gear ratio " << i + 1 << ":\t" << gears[i] << "\t after differential " << gears[i] * car.get_differential_ratio() << std::endl;
    }

    float wheel_radius = car.get_wheel_radius();

    car.set_rpm(4400);

    // 7 is reverse gear
    for (int i = 0; i < 6; ++i)
    {
        const float max_speed = speed_in_gear(wheel_radius, car.get_engine_rpm(), gears[i], car.get_differential_ratio());

        const float max_speed_kph = max_speed * 3.6f; // Convert m/s to km/h
        std::cout << "Max speed in gear " << i + 1 << ": " << max_speed_kph << " km/h" << std::endl;
    }
}