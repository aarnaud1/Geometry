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

#ifndef __GEOMETRY_VEC4_HPP__
#define __GEOMETRY_VEC4_HPP__

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
template <typename T>
struct Vec4
{};

// -----------------------------------------------------------------------------

template <>
struct Vec4<float>
{
  vec4f_t data;

  FUN_ATTRIBUTES Vec4() { this->data = vec4f_create(0, 0, 0, 0); }

  FUN_ATTRIBUTES
  Vec4(const float x, const float y, const float z, const float t)
  {
    this->data = vec4f_create(x, y, z, t);
  }

  FUN_ATTRIBUTES Vec4(const Vec4<float> &cp)
  {
    data = vec4f_create(
        cp.data.coords.x, cp.data.coords.y, cp.data.coords.z, cp.data.coords.t);
  }

  inline FUN_ATTRIBUTES float operator[](const size_t id) const
  {
    return this->data.data[id];
  }

  inline FUN_ATTRIBUTES float x() { return this->data.coords.x; }

  inline FUN_ATTRIBUTES float y() { return this->data.coords.y; }

  inline FUN_ATTRIBUTES float z() { return this->data.coords.z; }

  inline FUN_ATTRIBUTES float t() { return this->data.coords.t; }

  inline FUN_ATTRIBUTES Vec4 &operator=(const Vec4<float> &v0)
  {
    this->data.coords.x = v0.data.coords.x;
    this->data.coords.y = v0.data.coords.y;
    this->data.coords.z = v0.data.coords.z;
    this->data.coords.t = v0.data.coords.t;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<float> operator+(const Vec4<float> &v0)
  {
    Vec4<float> ret;
    ret.data = vec4f_add(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec4<float> &operator+=(const Vec4<float> &v0)
  {
    *this = *this + v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<float> operator-(const Vec4<float> &v0)
  {
    Vec4<float> ret;
    ret.data = vec4f_sub(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec4<float> &operator-=(const Vec4<float> &v0)
  {
    *this = *this - v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<float> operator*(const float k)
  {
    Vec4<float> ret;
    ret.data = vec4f_mul(this->data, k);
    return ret;
  }

  // Allow matrix - vector multiplication in the form V *= M
  template <typename U>
  inline FUN_ATTRIBUTES Vec4<float> &operator*=(const U &m)
  {
    *this = *this * m;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<float> &operator*=(const float k)
  {
    *this = *this * k;
    return *this;
  }

  inline FUN_ATTRIBUTES float len() { return vec4f_len(this->data); }

  inline FUN_ATTRIBUTES float dist(const Vec4<float> &v0)
  {
    return vec4f_dist(this->data, v0.data);
  }

  inline FUN_ATTRIBUTES float dot(const Vec4<float> &v0)
  {
    return vec4f_dot(this->data, v0.data);
  }
};

inline FUN_ATTRIBUTES Vec4<float>
operator*(const double k, const Vec4<float> &v0)
{
  Vec4<float> ret;
  ret.data = vec4f_mul(v0.data, k);
  return ret;
}

inline FUN_ATTRIBUTES float len(const Vec4<float> &v0)
{
  return vec4f_len(v0.data);
}

inline FUN_ATTRIBUTES float dist(const Vec4<float> &v0, const Vec4<float> &v1)
{
  return vec4f_dist(v0.data, v1.data);
}

inline FUN_ATTRIBUTES float dot(const Vec4<float> &v0, const Vec4<float> &v1)
{
  return vec4f_dot(v0.data, v1.data);
}

// -----------------------------------------------------------------------------

template <>
struct Vec4<double>
{
  vec4d_t data;

  FUN_ATTRIBUTES Vec4() { data = vec4d_create(0, 0, 0, 0); }

  FUN_ATTRIBUTES
  Vec4(const double x, const double y, const double z, const double t)
  {
    data = vec4d_create(x, y, z, t);
  }

  FUN_ATTRIBUTES Vec4(const Vec4<double> &cp)
  {
    data = vec4d_create(
        cp.data.coords.x, cp.data.coords.y, cp.data.coords.z, cp.data.coords.t);
  }

  inline FUN_ATTRIBUTES double operator[](const size_t id)
  {
    return this->data.data[id];
  }

  inline FUN_ATTRIBUTES double x() { return this->data.coords.x; }

  inline FUN_ATTRIBUTES double y() { return this->data.coords.y; }

  inline FUN_ATTRIBUTES double z() { return this->data.coords.z; }

  inline FUN_ATTRIBUTES double t() { return this->data.coords.t; }

  inline FUN_ATTRIBUTES Vec4 &operator=(const Vec4<double> &v0)
  {
    this->data.coords.x = v0.data.coords.x;
    this->data.coords.y = v0.data.coords.y;
    this->data.coords.z = v0.data.coords.z;
    this->data.coords.t = v0.data.coords.t;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<double> operator+(const Vec4<double> &v0)
  {
    Vec4<double> ret;
    ret.data = vec4d_add(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec4<double> &operator+=(const Vec4<double> &v0)
  {
    *this = *this + v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<double> operator-(const Vec4<double> &v0)
  {
    Vec4<double> ret;
    ret.data = vec4d_sub(this->data, v0.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec4<double> &operator-=(const Vec4<double> &v0)
  {
    *this = *this - v0;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<double> operator*(const double k)
  {
    Vec4<double> ret;
    ret.data = vec4d_mul(this->data, k);
    return ret;
  }

  template <typename U>
  inline FUN_ATTRIBUTES Vec4<double> &operator*=(const U &m)
  {
    *this = *this * m;
    return *this;
  }

  inline FUN_ATTRIBUTES Vec4<double> &operator*=(const double k)
  {
    *this = *this * k;
    return *this;
  }

  inline FUN_ATTRIBUTES double len() { return vec4d_len(this->data); }

  inline FUN_ATTRIBUTES double dist(const Vec4<double> &v0)
  {
    return vec4d_dist(this->data, v0.data);
  }

  inline FUN_ATTRIBUTES double dot(const Vec4<double> &v0)
  {
    return vec4d_dot(this->data, v0.data);
  }
};

inline FUN_ATTRIBUTES Vec4<double>
operator*(const double k, const Vec4<double> &v0)
{
  Vec4<double> ret;
  ret.data = vec4d_mul(v0.data, k);
  return ret;
}

inline FUN_ATTRIBUTES double len(const Vec4<double> &v0)
{
  return vec4d_len(v0.data);
}

inline FUN_ATTRIBUTES double
dist(const Vec4<double> &v0, const Vec4<double> &v1)
{
  return vec4d_dist(v0.data, v1.data);
}

inline FUN_ATTRIBUTES double dot(const Vec4<double> &v0, const Vec4<double> &v1)
{
  return vec4d_dot(v0.data, v1.data);
}

// -----------------------------------------------------------------------------

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vec4<T> &v)
{
  os << "\n";
  os << "|" << v.data.coords.x << " " << v.data.coords.y << " "
     << v.data.coords.z << " " << v.data.coords.t << "|\n";
  return os;
}

template <typename T>
inline std::istream &operator>>(std::istream &is, Vec4<T> &v)
{
  is >> v.data.coords.x >> v.data.coords.y >> v.data.coords.z
      >> v.data.coords.t;
  return is;
}

} // namespace geometry
#endif // __GEOMETRY_VEC4_HPP__
