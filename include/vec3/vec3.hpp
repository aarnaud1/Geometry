/*
 * Copyright (C) 2020 Adrien ARNAUD
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GEOMETRY_VEC3_HPP__
#define __GEOMETRY_VEC3_HPP__

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "vec4/vec4f.h"
#include "vec4/vec4d.h"

#ifdef __NVCC__
#  define FUN_ATTRIBUTES __host__ __device__
#else
#  define FUN_ATTRIBUTES
#endif

namespace geometry
{
// -----------------------------------------------------------------------------

template <typename T>
struct Vec3
{};

// -----------------------------------------------------------------------------

template <>
struct Vec3<float>
{
  vec3f_t data;

  FUN_ATTRIBUTES Vec3() { this->data = vec3f_create(0, 0, 0); }

  FUN_ATTRIBUTES Vec3(const float x, const float y, const float z)
  {
    this->data = vec3f_create(x, y, z);
  }

  FUN_ATTRIBUTES Vec3(const Vec3<float> &cp)
  {
    data = vec3f_create(cp.data.coords.x, cp.data.coords.y, cp.data.coords.z);
  }

  inline FUN_ATTRIBUTES float operator[](const size_t id)
  {
    return this->data.data[id];
  }

  inline FUN_ATTRIBUTES float x() { return this->data.coords.x; }

  inline FUN_ATTRIBUTES float y() { return this->data.coords.y; }

  inline FUN_ATTRIBUTES float z() { return this->data.coords.z; }

  inline FUN_ATTRIBUTES Vec3 &operator=(const Vec3<float> &v0)
  {
    this->data.coords.x = v0.data.coords.x;
    this->data.coords.y = v0.data.coords.y;
    this->data.coords.z = v0.data.coords.z;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec3<float> operator+(const Vec3<float> &v0)
  {
    Vec3<float> ret;
    ret.data = vec3f_add(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<float> &operator+=(const Vec3<float> &v0)
  {
    *this = *this + v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec3<float> operator-(const Vec3<float> &v0)
  {
    Vec3<float> ret;
    ret.data = vec3f_sub(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<float> &operator-=(const Vec3<float> &v0)
  {
    *this = *this - v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec3<float> operator*(const float k)
  {
    Vec3<float> ret;
    ret.data = vec3f_mul(this->data, k);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<float> &operator*=(const float k)
  {
    *this = *this * k;
    return *this;
  }

  inline FUN_ATTRIBUTES float len() { return vec3f_len(this->data); }

  inline FUN_ATTRIBUTES float dist(const Vec3<float> &v0)
  {
    return vec3f_dist(this->data, v0.data);
  }

  inline FUN_ATTRIBUTES float dot(const Vec3<float> &v0)
  {
    return vec3f_dot(this->data, v0.data);
  }

  inline FUN_ATTRIBUTES Vec3<float>
  cross(const Vec3<float> &v0, const Vec3<float> &v1)
  {
    Vec3<float> ret;
    ret.data = vec3f_cross(v0.data, v1.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<float>
  reflect(const Vec3<float> &I, const Vec3<float> &N)
  {
    Vec3<float> ret;
    ret.data = vec3f_reflect(I.data, N.data);
    return ret;
  }
};

inline FUN_ATTRIBUTES Vec3<float>
operator*(const double k, const Vec3<float> &v0)
{
  Vec3<float> ret;
  ret.data = vec3f_mul(v0.data, k);
  return ret;
}

inline FUN_ATTRIBUTES float len(const Vec3<float> &v0)
{
  return vec3f_len(v0.data);
}

inline FUN_ATTRIBUTES float dist(const Vec3<float> &v0, const Vec3<float> &v1)
{
  return vec3f_dist(v0.data, v1.data);
}

inline FUN_ATTRIBUTES float dot(const Vec3<float> &v0, const Vec3<float> &v1)
{
  return vec3f_dot(v0.data, v1.data);
}

inline FUN_ATTRIBUTES Vec3<float>
cross(const Vec3<float> &v0, const Vec3<float> &v1)
{
  Vec3<float> ret;
  ret.data = vec3f_cross(v0.data, v1.data);
  return ret;
}

inline FUN_ATTRIBUTES Vec3<float>
reflect(const Vec3<float> &I, const Vec3<float> &N)
{
  Vec3<float> ret;
  ret.data = vec3f_cross(I.data, N.data);
  return ret;
}

// -----------------------------------------------------------------------------

template <>
struct Vec3<double>
{
  vec3d_t data;

  FUN_ATTRIBUTES Vec3() { this->data = vec3d_create(0, 0, 0); }

  FUN_ATTRIBUTES Vec3(const double x, const double y, const double z)
  {
    this->data = vec3d_create(x, y, z);
  }

  FUN_ATTRIBUTES Vec3(const Vec3<double> &cp)
  {
    this->data =
        vec3d_create(cp.data.coords.x, cp.data.coords.y, cp.data.coords.z);
  }

  inline FUN_ATTRIBUTES double operator[](const size_t id)
  {
    return this->data.data[id];
  }

  inline FUN_ATTRIBUTES float x() { return this->data.coords.x; }

  inline FUN_ATTRIBUTES float y() { return this->data.coords.y; }

  inline FUN_ATTRIBUTES float z() { return this->data.coords.z; }

  inline FUN_ATTRIBUTES Vec3<double> &operator=(const Vec3<double> &v0)
  {
    this->data.coords.x = v0.data.coords.x;
    this->data.coords.y = v0.data.coords.y;
    this->data.coords.z = v0.data.coords.z;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec3<double> operator+(const Vec3<double> &v0)
  {
    Vec3<double> ret;
    ret.data = vec3d_add(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<double> &operator+=(const Vec3<double> &v0)
  {
    *this = *this + v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec3<double> operator-(const Vec3<double> &v0)
  {
    Vec3<double> ret;
    ret.data = vec3d_sub(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<double> &operator-=(const Vec3<double> &v0)
  {
    *this = *this - v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec3<double> operator*(const double k)
  {
    Vec3<double> ret;
    ret.data = vec3d_mul(this->data, k);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<double> operator*=(const double k)
  {
    *this = *this * k;
    return *this;
  }

  inline FUN_ATTRIBUTES double len() { return vec3d_len(this->data); }

  inline FUN_ATTRIBUTES double dist(const Vec3<double> &v0)
  {
    return vec3d_dist(this->data, v0.data);
  }

  inline FUN_ATTRIBUTES double dot(const Vec3<double> &v0)
  {
    return vec3d_dot(this->data, v0.data);
  }

  inline FUN_ATTRIBUTES Vec3<double>
  cross(const Vec3<double> &v0, const Vec3<double> &v1)
  {
    Vec3<double> ret;
    ret.data = vec3d_cross(v0.data, v1.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec3<double>
  reflect(const Vec3<double> &I, const Vec3<double> &N)
  {
    Vec3<double> ret;
    ret.data = vec3d_reflect(I.data, N.data);
    return ret;
  }
};

inline FUN_ATTRIBUTES Vec3<double>
operator*(const double k, const Vec3<double> &v0)
{
  Vec3<double> ret;
  ret.data = vec3d_mul(v0.data, k);
  return ret;
}

inline FUN_ATTRIBUTES double len(const Vec3<double> &v0)
{
  return vec3d_len(v0.data);
}

inline FUN_ATTRIBUTES double
dist(const Vec3<double> &v0, const Vec3<double> &v1)
{
  return vec3d_dist(v0.data, v1.data);
}

inline FUN_ATTRIBUTES double dot(const Vec3<double> &v0, const Vec3<double> &v1)
{
  return vec3d_dot(v0.data, v1.data);
}

inline FUN_ATTRIBUTES Vec3<double>
cross(const Vec3<double> &v0, const Vec3<double> &v1)
{
  Vec3<double> ret;
  ret.data = vec3d_cross(v0.data, v1.data);
  return ret;
}

inline FUN_ATTRIBUTES Vec3<double>
reflect(const Vec3<double> &I, const Vec3<double> &N)
{
  Vec3<double> ret;
  ret.data = vec3d_cross(I.data, N.data);
  return ret;
}
// -----------------------------------------------------------------------------

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vec3<T> &v)
{
  os << "\n";
  os << "|" << v.data.coords.x << " " << v.data.coords.y << " "
     << v.data.coords.z << "|\n";
  return os;
}

template <typename T>
inline std::istream &operator>>(std::istream &is, Vec3<T> &v)
{
  is >> v.data.coords.x >> v.data.coords.y >> v.data.coords.z;
  return is;
}

} // namespace geometry
#endif // __GEOMETRY_VEC3_HPP__
