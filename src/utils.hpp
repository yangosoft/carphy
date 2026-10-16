#pragma once
#include <cmath>

const float AIR_DENSITY = 1.225f; // kg/m^3 at sea level and 15°C
const float ENGINE_LOSS = 0.3f;
const float GRAVITY = 9.81f; // m/s^2
const float PI = 3.14159265358979323846f;

template <typename T>
struct Vec3
{
    T x;
    T y;
    T z;
};

using Position = Vec3<float>;

using FTraction = Vec3<float>;
using FDrag = Vec3<float>;
using FRollingResistance = Vec3<float>;

// using FTraction = Vec3;
// using FDrag = Vec3;
// using FRollingResistance = Vec3;

template <typename T>
Vec3<T> add(const Vec3<T> &a, const Vec3<T> &b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
Vec3<T> subtract(const Vec3<T> &a, const Vec3<T> &b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
Vec3<T> scale(const Vec3<T> &v, T scalar)
{
    return {v.x * scalar, v.y * scalar, v.z * scalar};
}

template <typename T>
T magnitude(const Vec3<T> &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

template <typename T>
Vec3<T> normalize(const Vec3<T> &v)
{
    T mag = magnitude(v);
    return {v.x / mag, v.y / mag, v.z / mag};
}

template <typename T>
Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}

template <typename T>
T dot(const Vec3<T> &a, const Vec3<T> &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vec3<T> project(const Vec3<T> &a, const Vec3<T> &b)
{
    T dot_product = dot(a, b);
    T mag_b_squared = dot(b, b);
    return scale(b, dot_product / mag_b_squared);
}

template <typename T>
Vec3<T> reflect(const Vec3<T> &v, const Vec3<T> &n)
{
    T dot_product = dot(v, n);
    return subtract(v, scale(n, 2 * dot_product));
}

template <typename T>
Vec3<T> triple_product(const Vec3<T> &a, const Vec3<T> &b, const Vec3<T> &c)
{
    return cross(a, cross(b, c));
}
