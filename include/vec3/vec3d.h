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

#ifndef __GEOMETRY_VEC3D_H__
#define __GEOMETRY_VEC3D_H__

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define VEC3D_PRINT(v)                                                         \
  fprintf(stdout, "%f %f %f\n", v.coords.x, v.coords.y, v.coords.z)

typedef union
{
  struct __attribute__((packed))
  {
    double x, y, z;
  } coords;
  double data[3];
} vec3d_t;

#ifdef __cplusplus
extern "C" {
#endif

inline vec3d_t vec3d_create(const double x, const double y, const double z);

inline vec3d_t vec3d_add(const vec3d_t v1, const vec3d_t v2);

inline vec3d_t vec3d_sub(const vec3d_t v1, const vec3d_t v2);

inline vec3d_t vec3d_norm(const vec3d_t v);

inline vec3d_t vec3d_mul(const vec3d_t v, const double k);

inline vec3d_t vec3d_cross(const vec3d_t v1, const vec3d_t v2);

inline vec3d_t vec3d_reflect(const vec3d_t v, const vec3d_t n);

inline double vec3d_dist(const vec3d_t v1, const vec3d_t v2);

inline double vec3d_dot(const vec3d_t v1, const vec3d_t v2);

inline double vec3d_len(const vec3d_t v);

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

inline vec3d_t vec3d_create(const double x, const double y, const double z)
{
  vec3d_t res;
  res.coords.x = x;
  res.coords.y = y;
  res.coords.z = z;
  return res;
}

inline vec3d_t vec3d_add(const vec3d_t v1, const vec3d_t v2)
{
  vec3d_t res;
  res.coords.x = v1.coords.x + v2.coords.x;
  res.coords.y = v1.coords.y + v2.coords.y;
  res.coords.z = v1.coords.z + v2.coords.z;
  return res;
}

inline vec3d_t vec3d_sub(const vec3d_t v1, const vec3d_t v2)
{
  vec3d_t res;
  res.coords.x = v1.coords.x - v2.coords.x;
  res.coords.y = v1.coords.y - v2.coords.y;
  res.coords.z = v1.coords.z - v2.coords.z;
  return res;
}

inline vec3d_t vec3d_norm(const vec3d_t v)
{
  vec3d_t res;
  double d = (double) sqrt(
      v.coords.x * v.coords.x + v.coords.y * v.coords.y
      + v.coords.z * v.coords.z);
  res.coords.x = v.coords.x / d;
  res.coords.y = v.coords.y / d;
  res.coords.z = v.coords.z / d;
  return res;
}

inline vec3d_t vec3d_mul(const vec3d_t v, const double k)
{
  vec3d_t res;
  res.coords.x = v.coords.x * k;
  res.coords.y = v.coords.y * k;
  res.coords.z = v.coords.z * k;
  return res;
}

inline vec3d_t vec3d_cross(const vec3d_t v1, const vec3d_t v2)
{
  vec3d_t res;
  res.coords.x = v1.coords.y * v2.coords.z - v1.coords.z * v2.coords.y;
  res.coords.y = v1.coords.z * v2.coords.x - v1.coords.x * v2.coords.z;
  res.coords.z = v1.coords.x * v2.coords.y - v1.coords.y * v2.coords.x;
  return res;
}

inline vec3d_t vec3d_reflect(const vec3d_t i, const vec3d_t n)
{
  vec3d_t res;
  const vec3d_t normalized = vec3d_norm(n);
  const double tmp = 2.0f * vec3d_dot(normalized, i);
  res = vec3d_sub(i, vec3d_mul(normalized, tmp));
  return res;
}

inline double vec3d_dist(const vec3d_t v1, const vec3d_t v2)
{
  return sqrt(
      pow(v2.coords.x - v1.coords.x, 2) + powf(v2.coords.y - v1.coords.y, 2)
      + pow(v2.coords.z - v1.coords.z, 2));
}

inline double vec3d_dot(const vec3d_t v1, const vec3d_t v2)
{
  return v1.coords.x * v2.coords.x + v1.coords.y * v2.coords.y
         + v1.coords.z * v2.coords.z;
}

inline double vec3d_len(const vec3d_t v)
{
  return sqrt(
      powf(v.coords.x, 2) + powf(v.coords.y, 2) + powf(v.coords.z, 2));
}
#endif // __GEOMETRY_VEC3DF_H__
