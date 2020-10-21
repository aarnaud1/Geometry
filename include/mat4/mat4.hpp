/*
 * Copyright (C) 2020  Adrien ARNAUD
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

#ifndef __GEOMETRY_MAT4_HPP__
#define __GEOMETRY_MAT4_HPP__

#include <iostream>

#include <stdint.h>
#include <math.h>
#include <string.h>

#include "geometry.h"

#include "vec3/vec3.hpp"
#include "vec4/vec4.hpp"

#ifdef __NVCC__
#  define FUN_ATTRIBUTES __host__ __device__
#else
#  define FUN_ATTRIBUTES
#endif

namespace geometry
{
template <typename T>
struct Mat4
{};

// -----------------------------------------------------------------------------

template <>
struct Mat4<float>
{
  mat4f_t data;

  FUN_ATTRIBUTES Mat4()
  {
    for(int i = 0; i < 16; i++)
    {
      this->data.data[i] = 0.0f;
    }
  }

  FUN_ATTRIBUTES Mat4(float coeffs[16])
  {
    for(int i = 0; i < 16; i++)
    {
      this->data.data[i] = coeffs[i];
    }
  }

  FUN_ATTRIBUTES Mat4<float>(const Mat4 &cp)
  {
    for(int i = 0; i < 16; i++)
    {
      this->data.data[i] = cp.data.data[i];
    }
  }

  inline FUN_ATTRIBUTES float operator[](const size_t id)
  {
    return this->data.data[id];
  }

  inline FUN_ATTRIBUTES void transpose()
  {
    this->data = mat4f_transpose(this->data);
  }

  inline FUN_ATTRIBUTES void inverse()
  {
    this->data = mat4f_inverse(this->data);
  }

  inline FUN_ATTRIBUTES void rotate(const Vec3<float> &axis, const float theta)
  {
    mat4f_t rot = mat4f_rotation(axis.data, theta);
    this->data = mat4f_mul(rot, this->data);
  }

  // TODO : Work with a mat4 or a mat3 object
  inline FUN_ATTRIBUTES void setRotation(const float *rot)
  {
    mat4f_setRotation(&(this->data), rot);
  }

  inline FUN_ATTRIBUTES void setTranslation(const Vec3<float> &t)
  {
    mat4f_setTranslation(
        &(this->data), t.data.coords.x, t.data.coords.y, t.data.coords.z);
  }

  // TODO : return a Mat3 object
  inline FUN_ATTRIBUTES Mat4<float> getRotation()
  {
    Mat4<float> ret;
    ret.data = mat4f_getRotation(this->data);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec4<float> getTranslation()
  {
    Vec4<float> ret;
    ret.data = mat4f_getTranslation(this->data);
    return ret;
  }

  inline FUN_ATTRIBUTES Mat4<float> &operator=(const Mat4<float> &m)
  {
    for(int i = 0; i < 16; i++)
    {
      this->data.data[i] = m.data.data[i];
    }
    return *this;
  }

  inline FUN_ATTRIBUTES Mat4<float> &operator+=(const Mat4<float> &m)
  {
    this->data = mat4f_add(this->data, m.data);
    return *this;
  }

  inline FUN_ATTRIBUTES Mat4<float> &operator-=(const Mat4<float> &m)
  {
    this->data = mat4f_sub(this->data, m.data);
    return *this;
  }

  inline FUN_ATTRIBUTES Mat4<float> &operator*=(const Mat4<float> &m)
  {
    this->data = mat4f_mul(this->data, m.data);
    return *this;
  }

  inline FUN_ATTRIBUTES Mat4<float> &operator*=(const float k)
  {
    this->data = mat4f_k_mul(this->data, k);
    return *this;
  }

  inline FUN_ATTRIBUTES Mat4<float> operator+(const Mat4<float> &m)
  {
    Mat4<float> ret;
    ret.data = mat4f_add(this->data, m.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Mat4<float> operator*(const Mat4<float> &m)
  {
    Mat4<float> ret;
    ret.data = mat4f_mul(this->data, m.data);
    return ret;
  }

  inline FUN_ATTRIBUTES Mat4<float> operator*(const float k)
  {
    Mat4<float> ret;
    ret.data = mat4f_k_mul(this->data, k);
    return ret;
  }

  inline FUN_ATTRIBUTES Vec4<float> operator*(const Vec4<float> &v)
  {
    Vec4<float> ret;
    ret.data = mat4f_mul_vector(v.data, this->data);
    return ret;
  }

  // Static functions

  static inline FUN_ATTRIBUTES Mat4<float> from_quat(const Vec4<float> &quat)
  {
    Mat4<float> ret;
    ret.data = mat4f_create_from_quaternion(
        quat.data.coords.t, quat.data.coords.x, quat.data.coords.y,
        quat.data.coords.z);
    return ret;
  }

  static inline FUN_ATTRIBUTES Mat4<float>
  fromQuat(const float w, const float x, const float y, const float z)
  {
    Mat4<float> ret;
    ret.data = mat4f_create_from_quaternion(w, x, y, z);
    return ret;
  }

  static inline FUN_ATTRIBUTES Mat4<float>
  rotation(const Vec3<float> &axis, const float theta)
  {
    Mat4<float> ret;
    ret.data = mat4f_rotation(axis.data, theta);
    return ret;
  }

  static inline FUN_ATTRIBUTES Mat4<float>
  affine(const Vec3<float> &axis, const float theta, const Vec3<float> &t)
  {
    Mat4<float> ret;
    ret.data = mat4f_affine(axis.data, theta, t.data);
    return ret;
  }

  static inline FUN_ATTRIBUTES Mat4<float> perspective(
      const float fovy, const float aspect, const float near, const float far)
  {
    Mat4<float> ret;
    ret.data = mat4f_create_perspective(fovy, aspect, near, far);
    return ret;
  }

  static inline FUN_ATTRIBUTES Mat4<float> lookAt(
      const Vec3<float> &position, const Vec3<float> &direction,
      const Vec3<float> &up)
  {
    Mat4<float> ret;
    ret.data = mat4f_lookAt(position.data, direction.data, up.data);
    return ret;
  }
};

inline FUN_ATTRIBUTES Mat4<float> operator*(const float k, const Mat4<float> &m)
{
  Mat4<float> ret;
  ret.data = mat4f_k_mul(m.data, k);
  return ret;
}

inline FUN_ATTRIBUTES Mat4<float> transpose(const Mat4<float> &m)
{
  Mat4<float> ret;
  ret.data = mat4f_transpose(m.data);
  return ret;
}

inline FUN_ATTRIBUTES Mat4<float> inverse(const Mat4<float> &m)
{
  Mat4<float> ret;
  ret.data = mat4f_inverse(m.data);
  return ret;
}

// -----------------------------------------------------------------------------

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Mat4<T> &m)
{
  os << "\n";
  os << "|" << m.data.coeffs.c00 << " " << m.data.coeffs.c01 << " "
     << m.data.coeffs.c02 << " " << m.data.coeffs.c03 << "|\n";
  os << "|" << m.data.coeffs.c10 << " " << m.data.coeffs.c11 << " "
     << m.data.coeffs.c12 << " " << m.data.coeffs.c13 << "|\n";
  os << "|" << m.data.coeffs.c20 << " " << m.data.coeffs.c21 << " "
     << m.data.coeffs.c22 << " " << m.data.coeffs.c23 << "|\n";
  os << "|" << m.data.coeffs.c30 << " " << m.data.coeffs.c31 << " "
     << m.data.coeffs.c32 << " " << m.data.coeffs.c33 << "|\n";
  return os;
}

template <typename T>
inline std::istream &operator>>(std::istream &is, Mat4<T> &m)
{
  is >> m.data.coeffs.c00 >> m.data.coeffs.c01 >> m.data.coeffs.c02
      >> m.data.coeffs.c03 >> m.data.coeffs.c10 >> m.data.coeffs.c11
      >> m.data.coeffs.c12 >> m.data.coeffs.c13 >> m.data.coeffs.c20
      >> m.data.coeffs.c21 >> m.data.coeffs.c22 >> m.data.coeffs.c23
      >> m.data.coeffs.c30 >> m.data.coeffs.c31 >> m.data.coeffs.c32
      >> m.data.coeffs.c33;
  return is;
}
} // namespace geometry

#endif // __GEOMETRY_MAT4_HPP__
