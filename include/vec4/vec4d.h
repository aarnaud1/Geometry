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

#ifndef __GEOMETRY_VEC4D_H__
#define __GEOMETRY_VEC4D_H__

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "vec3/vec3d.h"

#define VEC4D_PRINT(v)                                                         \
  fprintf(                                                                     \
      stdout, "%f %f %f %f\n", v.coords.x, v.coords.y, v.coords.z, v.coords.t)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
typedef union
{
  struct __attribute__((packed))
  {
    double x, y, z, t;
  } coords;
  double data[4];
  vec3d_t get_vec3;
} vec4d_t;
#pragma GCC diagnostic pop

#ifdef __cplusplus
extern "C" {
#endif

inline vec4d_t
vec4d_create(const double x, const double y, const double z, const double t);

inline vec4d_t vec4d_add(const vec4d_t v1, const vec4d_t v2);

inline vec4d_t vec4d_sub(const vec4d_t v1, const vec4d_t v2);

inline vec4d_t vec4d_norm(const vec4d_t v);

inline vec4d_t vec4d_mul(const vec4d_t v, const double k);

inline double vec4d_dist(const vec4d_t v1, const vec4d_t v2);

inline double vec4d_dot(const vec4d_t v1, const vec4d_t v2);

inline double vec4d_len(const vec4d_t v);

#ifdef __cplusplus
}
#endif

inline vec4d_t
vec4d_create(const double x, const double y, const double z, const double t)
{
  vec4d_t res;
  res.coords.x = x;
  res.coords.y = y;
  res.coords.z = z;
  res.coords.t = t;
  return res;
}

inline vec4d_t vec4d_add(const vec4d_t v1, const vec4d_t v2)
{
  vec4d_t res;
  res.coords.x = v1.coords.x + v2.coords.x;
  res.coords.y = v1.coords.y + v2.coords.y;
  res.coords.z = v1.coords.z + v2.coords.z;
  res.coords.t = v1.coords.t + v2.coords.t;
  return res;
}

inline vec4d_t vec4d_sub(const vec4d_t v1, const vec4d_t v2)
{
  vec4d_t res;
  res.coords.x = v1.coords.x - v2.coords.x;
  res.coords.y = v1.coords.y - v2.coords.y;
  res.coords.z = v1.coords.z - v2.coords.z;
  res.coords.t = v1.coords.t - v2.coords.t;
  return res;
}

inline vec4d_t vec4d_norm(const vec4d_t v)
{
  vec4d_t res;
  const double d = sqrtf(
      v.coords.x * v.coords.x + v.coords.y * v.coords.y
      + v.coords.z * v.coords.z + v.coords.t * v.coords.t);
  res.coords.x = v.coords.x / d;
  res.coords.y = v.coords.y / d;
  res.coords.z = v.coords.z / d;
  res.coords.t = v.coords.t / d;
  return res;
}

inline vec4d_t vec4d_mul(const vec4d_t v, const double k)
{
  vec4d_t res;
  res.coords.x = k * v.coords.x;
  res.coords.y = k * v.coords.y;
  res.coords.z = k * v.coords.z;
  res.coords.t = k * v.coords.t;
  return res;
}

inline double vec4d_dist(const vec4d_t v1, const vec4d_t v2)
{
  return sqrtf(
      powf(v2.coords.x - v1.coords.x, 2) + powf(v2.coords.y - v1.coords.y, 2)
      + powf(v2.coords.z - v1.coords.z, 2)
      + powf(v2.coords.t - v1.coords.t, 2));
}

inline double vec4d_dot(const vec4d_t v1, const vec4d_t v2)
{
  return v1.coords.x * v2.coords.x + v1.coords.y * v2.coords.y
         + v1.coords.z * v2.coords.z + v1.coords.t * v2.coords.t;
}

inline double vec4d_len(const vec4d_t v)
{
  return sqrtf(
      powf(v.coords.x, 2) + powf(v.coords.y, 2) + powf(v.coords.z, 2)
      + powf(v.coords.t, 2));
}

#endif // __GEOMETRY_VEC4D_H__
