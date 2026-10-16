
#pragma once

#include <array>
#include <cstdint>

#include "utils.hpp"

class EngineCharacteristics
{
public:
    // Constructor to initialize engine characteristics with maximum RPM and torque in Newton-meters (N·m)
    EngineCharacteristics(uint32_t max_rpm, float max_torque) : max_rpm(max_rpm), max_torque(max_torque) {}

    float get_max_torque() const { return max_torque; }
    uint32_t get_max_rpm() const { return max_rpm; }

private:
    uint32_t max_rpm;
    float max_torque;
};

class ICar
{
public:
    // Set position of the car
    virtual void set_position(const Position &position) = 0;

    // Engine control for the car
    virtual void engine_on() = 0;
    virtual void engine_off() = 0;

    // Control inputs for the car
    virtual void set_throttle_pedal(float percentage) = 0;
    virtual void set_brake_pedal(float percentage) = 0;
    virtual void set_steering_angle(float angle) = 0;

    // Get the current state of the car
    virtual float get_throttle_pedal() const = 0;
    virtual float get_brake_pedal() const = 0;
    virtual float get_steering_angle() const = 0;

    // Get the current engine state of the car
    virtual bool is_engine_on() const = 0;

    // Get the current speed of the car
    virtual float get_speed() const = 0;
    // Get the current acceleration of the car
    virtual float get_acceleration() const = 0;

    // Get the current position of the car
    virtual Position get_position() const = 0;

    virtual void set_rpm(uint32_t rpm) = 0;

    // Forces
    virtual FTraction get_traction() const = 0;
    virtual FDrag get_drag() const = 0;
    virtual FRollingResistance get_rolling_resistance() const = 0;

    virtual EngineCharacteristics get_engine_characteristics() const = 0;

    virtual float get_engine_force() const = 0;
    virtual uint32_t get_engine_rpm() const = 0;
    virtual float get_frontal_area() const = 0;
    virtual float get_aero_coefficient() const = 0;
    virtual float get_c_drag() const = 0;
    virtual float get_c_rr() const = 0;
    virtual Vec3<float> get_velocity() const = 0;

    virtual float get_torque() const = 0;
    virtual float get_mass() const = 0;

    virtual void get_gear_ratios(std::array<float, 7> &gears) const = 0;

    virtual float get_wheel_radius() const = 0;
    virtual float get_differential_ratio() const = 0;
    virtual float get_transmission_efficiency() const = 0;

    virtual ~ICar() {}
};

class Car : public ICar
{
public:
    Car() : position(), engine_running(false), throttle_pedal(0.0f),
            brake_pedal(0.0f), steering_angle(0.0f), speed(0.0f),
            acceleration(0.0f), traction(), drag(), rolling_resistance(),
            engine_force(0.0f), engine_rpm(0), engine_characteristics(6500, 400.0f) {}

    // Set position of the car
    void set_position(const Position &position) override;

    // Engine control for the car
    void engine_on() override;
    void engine_off() override;

    // Control inputs for the car
    void set_throttle_pedal(float percentage) override;
    void set_brake_pedal(float percentage) override;
    void set_steering_angle(float angle) override;

    // Get the current state of the car
    float get_throttle_pedal() const override;
    float get_brake_pedal() const override;
    float get_steering_angle() const override;

    // Get the current engine state of the car
    bool is_engine_on() const override;

    // Get the current speed of the car
    float get_speed() const override;
    // Get the current acceleration of the car
    float get_acceleration() const override;

    // Get the current position of the car
    Position get_position() const override;

    // Forces
    FTraction get_traction() const override;
    FDrag get_drag() const override;
    FRollingResistance get_rolling_resistance() const override;

    EngineCharacteristics get_engine_characteristics() const override;

    void set_rpm(uint32_t rpm) override;

    float get_engine_force() const override;
    uint32_t get_engine_rpm() const override;
    float get_frontal_area() const override;
    float get_aero_coefficient() const override;

    float get_c_drag() const override;
    float get_c_rr() const override;
    Vec3<float> get_velocity() const override;
    float get_torque() const override;
    float get_mass() const override;
    void get_gear_ratios(std::array<float, 7> &gears) const override;
    float get_wheel_radius() const override;
    float get_differential_ratio() const override;

    float get_transmission_efficiency() const override;

private:
    Position position;

    bool engine_running;
    float throttle_pedal;
    float brake_pedal;
    uint32_t current_gear;

    float steering_angle;
    float speed;
    float acceleration;
    FTraction traction;
    FDrag drag;
    FRollingResistance rolling_resistance;
    Vec3<float> velocity;

    float engine_force;
    uint32_t engine_rpm;

    // Engine characteristics
    EngineCharacteristics engine_characteristics;

    const float frontal_area = 2.2f;
    const float aero_coefficient = 0.30f;

    const float c_drag = 0.5f * aero_coefficient * frontal_area * AIR_DENSITY;
    const float c_rr = 30 * c_drag;                                             // Rolling resistance coefficient, typical value for car tires
    const float gear_ratio[7] = {2.66f, 1.78f, 1.30f, 1.0f, 0.74f, 0.5f, 2.9f}; // Assuming a 6-speed gearbox + reverse gear
    const float differential_ratio = 3.42;
    const uint32_t mass = 1500;
    float wheel_radius = 0.34f;
    const float transmission_efficiency = 0.7f;
};