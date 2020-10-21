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

#ifndef __GEOMETRY_VEC4F_H__
#define __GEOMETRY_VEC4F_H__

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "vec3/vec3f.h"

#define VEC4F_PRINT(v)                                                         \
  fprintf(                                                                     \
      stdout, "%f %f %f %f\n", v.coords.x, v.coords.y, v.coords.z, v.coords.t)

typedef union
{
  struct __attribute__((packed))
  {
    float x, y, z, t;
  } coords;
  float data[4];
  vec3f_t get_vec3;
} vec4f_t;

#ifdef __cplusplus
extern "C" {
#endif

inline vec4f_t
vec4f_create(const float x, const float y, const float z, const float t);

inline vec4f_t vec4f_add(const vec4f_t v1, const vec4f_t v2);

inline vec4f_t vec4f_sub(const vec4f_t v1, const vec4f_t v2);

inline vec4f_t vec4f_norm(const vec4f_t v);

inline vec4f_t vec4f_mul(const vec4f_t v, const float k);

inline float vec4f_dist(const vec4f_t v1, const vec4f_t v2);

inline float vec4f_dot(const vec4f_t v1, const vec4f_t v2);

inline float vec4f_len(const vec4f_t v);

#ifdef __cplusplus
}
#endif

inline vec4f_t
vec4f_create(const float x, const float y, const float z, const float t)
{
  vec4f_t res;
  res.coords.x = x;
  res.coords.y = y;
  res.coords.z = z;
  res.coords.t = t;
  return res;
}

inline vec4f_t vec4f_add(const vec4f_t v1, const vec4f_t v2)
{
  vec4f_t res;
  res.coords.x = v1.coords.x + v2.coords.x;
  res.coords.y = v1.coords.y + v2.coords.y;
  res.coords.z = v1.coords.z + v2.coords.z;
  res.coords.t = v1.coords.t + v2.coords.t;
  return res;
}

inline vec4f_t vec4f_sub(const vec4f_t v1, const vec4f_t v2)
{
  vec4f_t res;
  res.coords.x = v1.coords.x - v2.coords.x;
  res.coords.y = v1.coords.y - v2.coords.y;
  res.coords.z = v1.coords.z - v2.coords.z;
  res.coords.t = v1.coords.t - v2.coords.t;
  return res;
}

inline vec4f_t vec4f_norm(const vec4f_t v)
{
  vec4f_t res;
  const float d = sqrtf(
      v.coords.x * v.coords.x + v.coords.y * v.coords.y
      + v.coords.z * v.coords.z + v.coords.t * v.coords.t);
  res.coords.x = v.coords.x / d;
  res.coords.y = v.coords.y / d;
  res.coords.z = v.coords.z / d;
  res.coords.t = v.coords.t / d;
  return res;
}

inline vec4f_t vec4f_mul(const vec4f_t v, const float k)
{
  vec4f_t res;
  res.coords.x = k * v.coords.x;
  res.coords.y = k * v.coords.y;
  res.coords.z = k * v.coords.z;
  res.coords.t = k * v.coords.t;
  return res;
}

inline float vec4f_dist(const vec4f_t v1, const vec4f_t v2)
{
  return sqrtf(
      powf(v2.coords.x - v1.coords.x, 2) + powf(v2.coords.y - v1.coords.y, 2)
      + powf(v2.coords.z - v1.coords.z, 2)
      + powf(v2.coords.t - v1.coords.t, 2));
}

inline float vec4f_dot(const vec4f_t v1, const vec4f_t v2)
{
  return v1.coords.x * v2.coords.x + v1.coords.y * v2.coords.y
         + v1.coords.z * v2.coords.z + v1.coords.t * v2.coords.t;
}

inline float vec4f_len(const vec4f_t v)
{
  return sqrtf(
      powf(v.coords.x, 2) + powf(v.coords.y, 2) + powf(v.coords.z, 2)
      + powf(v.coords.t, 2));
}

#endif // __GEOMETRY_VEC4F_H__
