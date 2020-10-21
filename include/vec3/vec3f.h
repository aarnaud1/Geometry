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

#ifndef __GEOMETRY_VEC3F_H__
#define __GEOMETRY_VEC3F_H__

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define VEC3F_PRINT(v)                                                         \
  fprintf(stdout, "%f %f %f\n", v.x, v.coords.y, v.coords.z)

typedef union
{
  struct __attribute__((packed))
  {
    float x, y, z;
  } coords;
  float data[3];
} vec3f_t;

#ifdef __cplusplus
extern "C" {
#endif

inline vec3f_t vec3f_create(const float x, const float y, const float z);

inline vec3f_t vec3f_add(const vec3f_t v1, const vec3f_t v2);

inline vec3f_t vec3f_sub(const vec3f_t v1, const vec3f_t v2);

inline vec3f_t vec3f_norm(const vec3f_t v);

inline vec3f_t vec3f_mul(const vec3f_t v, const float k);

inline vec3f_t vec3f_cross(const vec3f_t v1, const vec3f_t v2);

inline vec3f_t vec3f_reflect(const vec3f_t v, const vec3f_t n);

inline float vec3f_dist(const vec3f_t v1, const vec3f_t v2);

inline float vec3f_dot(const vec3f_t v1, const vec3f_t v2);

inline float vec3f_len(const vec3f_t v);

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

inline vec3f_t vec3f_create(const float x, const float y, const float z)
{
  vec3f_t res;
  res.coords.x = x;
  res.coords.y = y;
  res.coords.z = z;
  return res;
}

inline vec3f_t vec3f_add(const vec3f_t v1, const vec3f_t v2)
{
  vec3f_t res;
  res.coords.x = v1.coords.x + v2.coords.x;
  res.coords.y = v1.coords.y + v2.coords.y;
  res.coords.z = v1.coords.z + v2.coords.z;
  return res;
}

inline vec3f_t vec3f_sub(const vec3f_t v1, const vec3f_t v2)
{
  vec3f_t res;
  res.coords.x = v1.coords.x - v2.coords.x;
  res.coords.y = v1.coords.y - v2.coords.y;
  res.coords.z = v1.coords.z - v2.coords.z;
  return res;
}

inline vec3f_t vec3f_norm(const vec3f_t v)
{
  vec3f_t res;
  float d = (float) sqrt(
      v.coords.x * v.coords.x + v.coords.y * v.coords.y
      + v.coords.z * v.coords.z);
  res.coords.x = v.coords.x / d;
  res.coords.y = v.coords.y / d;
  res.coords.z = v.coords.z / d;
  return res;
}

inline vec3f_t vec3f_mul(const vec3f_t v, const float k)
{
  vec3f_t res;
  res.coords.x = v.coords.x * k;
  res.coords.y = v.coords.y * k;
  res.coords.z = v.coords.z * k;
  return res;
}

inline vec3f_t vec3f_cross(const vec3f_t v1, const vec3f_t v2)
{
  vec3f_t res;
  res.coords.x = v1.coords.y * v2.coords.z - v1.coords.z * v2.coords.y;
  res.coords.y = v1.coords.z * v2.coords.x - v1.coords.x * v2.coords.z;
  res.coords.z = v1.coords.x * v2.coords.y - v1.coords.y * v2.coords.x;
  return res;
}

inline vec3f_t vec3f_reflect(const vec3f_t i, const vec3f_t n)
{
  vec3f_t res;
  const vec3f_t normalized = vec3f_norm(n);
  const float tmp = 2.0f * vec3f_dot(normalized, i);
  res = vec3f_sub(i, vec3f_mul(normalized, tmp));
  return res;
}

inline float vec3f_dist(const vec3f_t v1, const vec3f_t v2)
{
  return sqrtf(
      powf(v2.coords.x - v1.coords.x, 2) + powf(v2.coords.y - v1.coords.y, 2)
      + powf(v2.coords.z - v1.coords.z, 2));
}

inline float vec3f_dot(const vec3f_t v1, const vec3f_t v2)
{
  return v1.coords.x * v2.coords.x + v1.coords.y * v2.coords.y
         + v1.coords.z * v2.coords.z;
}

inline float vec3f_len(const vec3f_t v)
{
  return sqrtf(powf(v.coords.x, 2) + powf(v.coords.y, 2) + powf(v.coords.z, 2));
}

#endif // __GEOMETRY_VEC3F_H__
