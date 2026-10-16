#include "car.hpp"

void Car::set_position(const Position &position)
{
    this->position = position;
}

void Car::engine_on()
{
    engine_running = true;
}

void Car::engine_off()
{
    engine_running = false;
}

void Car::set_throttle_pedal(float percentage)
{
    throttle_pedal = percentage;
}

void Car::set_brake_pedal(float percentage)
{
    brake_pedal = percentage;
}

void Car::set_steering_angle(float angle)
{
    steering_angle = angle;
}

float Car::get_throttle_pedal() const
{
    return throttle_pedal;
}

float Car::get_brake_pedal() const
{
    return brake_pedal;
}

float Car::get_steering_angle() const
{
    return steering_angle;
}

bool Car::is_engine_on() const
{
    return engine_running;
}

float Car::get_speed() const
{
    return speed;
}

float Car::get_acceleration() const
{
    return acceleration;
}

Position Car::get_position() const
{
    return position;
}

FTraction Car::get_traction() const
{
    return traction;
}

FDrag Car::get_drag() const
{
    return drag;
}

FRollingResistance Car::get_rolling_resistance() const
{
    return rolling_resistance;
}

EngineCharacteristics Car::get_engine_characteristics() const
{
    return engine_characteristics;
}

float Car::get_engine_force() const
{
    /*
    Fengine = Tengine * xg * xd * n / Rw
    where
    Tengine is the torque of the engine at a given rpm,
    xg is the gear ratio,
    xd is the differential ratio,
    n is transmission efficiency and
    Rw is wheel radius.


    Engine is running at 2500 rpm, looking this up on the curve gives engine torque of 448 Nm (=330 ft lbs)
Gear ratio (first gear): 2.66
Differential ratio: 3.42
Transmission efficiency: 0.7 (guess)
Wheel radius: 0.34 m (=13.4 inch)
Mass: 1500 kg (= 3300 lbs of weight) including the driver.

This gives us a potential drive force of (448*2.66*3.42*0.7/0.34 = ) 8391 N
    */

    auto engine_force = get_torque() * gear_ratio[current_gear] * differential_ratio * transmission_efficiency / wheel_radius;

    return engine_force;
}

uint32_t Car::get_engine_rpm() const
{
    return engine_rpm;
}

float Car::get_frontal_area() const
{
    return frontal_area;
}

float Car::get_aero_coefficient() const
{
    return aero_coefficient;
}

float Car::get_c_drag() const
{
    return c_drag;
}

float Car::get_c_rr() const
{
    return c_rr;
}

Vec3<float> Car::get_velocity() const
{
    return velocity;
}

float Car::get_torque() const
{
    // from 1000rpm to 6000rpm some linear interpolation of torque can be used
    if (engine_rpm < 1000)
        return 0.0f;
    if (engine_rpm > 6000)
        return engine_characteristics.get_max_torque();

    float min_rpm = 1000.0f;
    float max_rpm = 6000.0f;
    float min_torque = 0.0f;
    float max_torque = engine_characteristics.get_max_torque();

    auto torque = min_torque + (max_torque - min_torque) * (engine_rpm - min_rpm) / (max_rpm - min_rpm);

    return torque * throttle_pedal;
}

float Car::get_mass() const
{
    return mass;
}

void Car::get_gear_ratios(std::array<float, 7> &gears) const
{
    for (int i = 0; i < 7; ++i)
    {
        gears[i] = gear_ratio[i];
    }
}

float Car::get_wheel_radius() const
{
    return wheel_radius;
}

float Car::get_differential_ratio() const
{
    return differential_ratio;
}

float Car::get_transmission_efficiency() const
{
    return transmission_efficiency;
}

void Car::set_rpm(uint32_t rpm)
{
    engine_rpm = rpm;
}