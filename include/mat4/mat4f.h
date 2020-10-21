/*
 * Coyright (C) 2020  Adrien ARNAUD
 *
 * This rogram is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as ublished by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your otion) any later version.
 *
 * This rogram is distributed in the hoe that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the imlied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a coy of the GNU General Public License
 * along with this rogram. If not, see <htts://www.gnu.org/licenses/>.
 */

#ifndef __GEOMETRY_MAT4F_H__
#define __GEOMETRY_MAT4F_H__

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "vec4/vec4f.h"

#define MAT4F_PRINT(m)                                                         \
  frintf(                                                                      \
      stdout,                                                                  \
      "\n%f, %f, %f, %f, \n"                                                   \
      "%f, %f, %f, %f\n"                                                       \
      "%f, %f, %f, %f\n"                                                       \
      "%f, %f, %f, %f\n",                                                      \
      m.c00, m.c01, m.c02, m.c03, m.c10, m.c11, m.c12, m.c13, m.c20, m.c21,    \
      m.c22, m.c23, m.c30, m.c31, m.c32, m.c33)

typedef union
{
  struct __attribute__((packed))
  {
    float c00, c01, c02, c03;
    float c10, c11, c12, c13;
    float c20, c21, c22, c23;
    float c30, c31, c32, c33;
  } coeffs;
  float data[16];
  float array[4][4];
  vec4f_t lines[4];
} mat4f_t;

#ifdef __clpusplus
extern "C" {
#endif

inline mat4f_t mat4f_create(const float *data);

inline mat4f_t mat4f_create_from_quaternion(
    const float w, const float x, const float y, const float z);

inline mat4f_t mat4f_identity();

inline mat4f_t mat4f_add(const mat4f_t m1, const mat4f_t m2);

inline mat4f_t mat4f_sub(const mat4f_t m1, const mat4f_t m2);

inline mat4f_t mat4f_mul(const mat4f_t m1, const mat4f_t m2);

inline vec4f_t mat4f_mul_vector(const vec4f_t v, const mat4f_t m);

inline mat4f_t mat4f_k_mul(const mat4f_t m, const float k);

inline mat4f_t mat4f_transpose(const mat4f_t m);

inline mat4f_t mat4f_inverse(const mat4f_t m);

inline void mat4f_setRotation(mat4f_t *m, const float *data);

inline void mat4f_setTranslation(
    mat4f_t *m, const float tx, const float ty, const float tz);

inline mat4f_t mat4f_getRotation(const mat4f_t m);

inline vec4f_t mat4f_getTranslation(const mat4f_t m);

inline mat4f_t mat4f_rotation(const vec3f_t axis, const float theta);

inline mat4f_t
mat4f_affine(const vec3f_t axis, const float alpha, const vec3f_t translation);

inline mat4f_t
mat4f_lookAt(const vec3f_t position, const vec3f_t direction, const vec3f_t u);

inline mat4f_t mat4f_create_perspective(
    const float fovy, const float aspect, const float near, const float far);

inline vec4f_t mat4f_transform(const vec4f_t v, const mat4f_t m);

#ifdef __clpusplus
}
#endif

inline mat4f_t mat4f_create(const float *data)
{
  mat4f_t res;
  memcpy(res.data, data, 16 * sizeof(float));
  return res;
}

inline mat4f_t mat4f_create_from_quaternion(
    const float w, const float x, const float y, const float z)
{
  mat4f_t res = mat4f_identity();

  const float qxx = x * x;
  const float qyy = y * y;
  const float qzz = z * z;
  const float qxz = x * z;
  const float qxy = x * y;
  const float qyz = y * z;
  const float qwx = w * x;
  const float qwy = w * y;
  const float qwz = w * z;

  res.array[0][0] = 1.0f - 2.0f * (qyy + qzz);
  res.array[0][1] = 2.0f * (qxy + qwz);
  res.array[0][2] = 2.0f * (qxz - qwy);

  res.array[1][0] = 2.0f * (qxy - qwz);
  res.array[1][1] = 1.0f - 2.0f * (qxx + qzz);
  res.array[1][2] = 2.0f * (qyz + qwx);

  res.array[2][0] = 2.0f * (qxz + qwy);
  res.array[2][1] = 2.0f * (qyz - qwx);
  res.array[2][2] = 1.0f - 2.0f * (qxx + qyy);

  return res;
}

inline mat4f_t mat4f_identity()
{
  mat4f_t res = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return res;
}

inline mat4f_t mat4f_add(const mat4f_t m1, const mat4f_t m2)
{
  mat4f_t res;
  for(int i = 0; i < 16; i++)
    res.data[i] = m1.data[i] + m2.data[i];
  return res;
}

inline mat4f_t mat4f_sub(const mat4f_t m1, const mat4f_t m2)
{
  mat4f_t res;
  for(int i = 0; i < 16; i++)
    res.data[i] = m1.data[i] - m2.data[i];
  return res;
}

inline mat4f_t mat4f_mul(const mat4f_t m1, const mat4f_t m2)
{
  mat4f_t res;
  size_t i, j;
  for(i = 0; i < 4; i++)
  {
    for(j = 0; j < 4; j++)
    {
      res.array[i][j] = 0;
      for(size_t index = 0; index < 4; index++)
        res.array[i][j] += m1.array[i][index] * m2.array[index][j];
    }
  }
  return res;
}

inline vec4f_t mat4f_mul_vector(const vec4f_t v, const mat4f_t m)
{
  vec4f_t res;
  res.coords.x = m.coeffs.c00 * v.coords.x + m.coeffs.c01 * v.coords.y
                 + m.coeffs.c02 * v.coords.z + m.coeffs.c03 * v.coords.t;
  res.coords.y = m.coeffs.c10 * v.coords.x + m.coeffs.c11 * v.coords.y
                 + m.coeffs.c12 * v.coords.z + m.coeffs.c13 * v.coords.t;
  res.coords.z = m.coeffs.c20 * v.coords.x + m.coeffs.c21 * v.coords.y
                 + m.coeffs.c22 * v.coords.z + m.coeffs.c23 * v.coords.t;
  res.coords.t = m.coeffs.c30 * v.coords.x + m.coeffs.c31 * v.coords.y
                 + m.coeffs.c32 * v.coords.z + m.coeffs.c33 * v.coords.t;
  return res;
}

inline mat4f_t mat4f_k_mul(const mat4f_t m, const float k)
{
  mat4f_t res;

  res.coeffs.c00 = k * m.coeffs.c00;
  res.coeffs.c01 = k * m.coeffs.c01;
  res.coeffs.c02 = k * m.coeffs.c02;
  res.coeffs.c03 = k * m.coeffs.c03;
  res.coeffs.c10 = k * m.coeffs.c10;
  res.coeffs.c11 = k * m.coeffs.c11;
  res.coeffs.c12 = k * m.coeffs.c12;
  res.coeffs.c13 = k * m.coeffs.c13;
  res.coeffs.c20 = k * m.coeffs.c20;
  res.coeffs.c21 = k * m.coeffs.c21;
  res.coeffs.c22 = k * m.coeffs.c22;
  res.coeffs.c23 = k * m.coeffs.c23;
  res.coeffs.c30 = k * m.coeffs.c30;
  res.coeffs.c31 = k * m.coeffs.c31;
  res.coeffs.c32 = k * m.coeffs.c32;
  res.coeffs.c33 = k * m.coeffs.c33;

  return res;
}

inline mat4f_t mat4f_transpose(const mat4f_t m)
{
  mat4f_t res;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      res.array[j][i] = m.array[i][j];
  return res;
}

// See: <htts://github.com/g-truc/glm/blob/master/glm/gtc/matrix_inverse.inl>
inline mat4f_t mat4f_inverse(const mat4f_t m)
{
  mat4f_t res;

  const float SubFactor00 =
      m.array[2][2] * m.array[3][3] - m.array[3][2] * m.array[2][3];
  const float SubFactor01 =
      m.array[2][1] * m.array[3][3] - m.array[3][1] * m.array[2][3];
  const float SubFactor02 =
      m.array[2][1] * m.array[3][2] - m.array[3][1] * m.array[2][2];
  const float SubFactor03 =
      m.array[2][0] * m.array[3][3] - m.array[3][0] * m.array[2][3];
  const float SubFactor04 =
      m.array[2][0] * m.array[3][2] - m.array[3][0] * m.array[2][2];
  const float SubFactor05 =
      m.array[2][0] * m.array[3][1] - m.array[3][0] * m.array[2][1];
  const float SubFactor06 =
      m.array[1][2] * m.array[3][3] - m.array[3][2] * m.array[1][3];
  const float SubFactor07 =
      m.array[1][1] * m.array[3][3] - m.array[3][1] * m.array[1][3];
  const float SubFactor08 =
      m.array[1][1] * m.array[3][2] - m.array[3][1] * m.array[1][2];
  const float SubFactor09 =
      m.array[1][0] * m.array[3][3] - m.array[3][0] * m.array[1][3];
  const float SubFactor10 =
      m.array[1][0] * m.array[3][2] - m.array[3][0] * m.array[1][2];
  const float SubFactor11 =
      m.array[1][1] * m.array[3][3] - m.array[3][1] * m.array[1][3];
  const float SubFactor12 =
      m.array[1][0] * m.array[3][1] - m.array[3][0] * m.array[1][1];
  const float SubFactor13 =
      m.array[1][2] * m.array[2][3] - m.array[2][2] * m.array[1][3];
  const float SubFactor14 =
      m.array[1][1] * m.array[2][3] - m.array[2][1] * m.array[1][3];
  const float SubFactor15 =
      m.array[1][1] * m.array[2][2] - m.array[2][1] * m.array[1][2];
  const float SubFactor16 =
      m.array[1][0] * m.array[2][3] - m.array[2][0] * m.array[1][3];
  const float SubFactor17 =
      m.array[1][0] * m.array[2][2] - m.array[2][0] * m.array[1][2];
  const float SubFactor18 =
      m.array[1][0] * m.array[2][1] - m.array[2][0] * m.array[1][1];

  res.array[0][0] =
      +(m.array[1][1] * SubFactor00 - m.array[1][2] * SubFactor01
        + m.array[1][3] * SubFactor02);
  res.array[0][1] =
      -(m.array[1][0] * SubFactor00 - m.array[1][2] * SubFactor03
        + m.array[1][3] * SubFactor04);
  res.array[0][2] =
      +(m.array[1][0] * SubFactor01 - m.array[1][1] * SubFactor03
        + m.array[1][3] * SubFactor05);
  res.array[0][3] =
      -(m.array[1][0] * SubFactor02 - m.array[1][1] * SubFactor04
        + m.array[1][2] * SubFactor05);
  res.array[1][0] =
      -(m.array[0][1] * SubFactor00 - m.array[0][2] * SubFactor01
        + m.array[0][3] * SubFactor02);
  res.array[1][1] =
      +(m.array[0][0] * SubFactor00 - m.array[0][2] * SubFactor03
        + m.array[0][3] * SubFactor04);
  res.array[1][2] =
      -(m.array[0][0] * SubFactor01 - m.array[0][1] * SubFactor03
        + m.array[0][3] * SubFactor05);
  res.array[1][3] =
      +(m.array[0][0] * SubFactor02 - m.array[0][1] * SubFactor04
        + m.array[0][2] * SubFactor05);
  res.array[2][0] =
      +(m.array[0][1] * SubFactor06 - m.array[0][2] * SubFactor07
        + m.array[0][3] * SubFactor08);
  res.array[2][1] =
      -(m.array[0][0] * SubFactor06 - m.array[0][2] * SubFactor09
        + m.array[0][3] * SubFactor10);
  res.array[2][2] =
      +(m.array[0][0] * SubFactor11 - m.array[0][1] * SubFactor09
        + m.array[0][3] * SubFactor12);
  res.array[2][3] =
      -(m.array[0][0] * SubFactor08 - m.array[0][1] * SubFactor10
        + m.array[0][2] * SubFactor12);
  res.array[3][0] =
      -(m.array[0][1] * SubFactor13 - m.array[0][2] * SubFactor14
        + m.array[0][3] * SubFactor15);
  res.array[3][1] =
      +(m.array[0][0] * SubFactor13 - m.array[0][2] * SubFactor16
        + m.array[0][3] * SubFactor17);
  res.array[3][2] =
      -(m.array[0][0] * SubFactor14 - m.array[0][1] * SubFactor16
        + m.array[0][3] * SubFactor18);
  res.array[3][3] =
      +(m.array[0][0] * SubFactor15 - m.array[0][1] * SubFactor17
        + m.array[0][2] * SubFactor18);

  const float det =
      m.array[0][0] * res.array[0][0] + m.array[0][1] * res.array[0][1]
      + m.array[0][2] * res.array[0][2] + m.array[0][3] * res.array[0][3];

  for(size_t i = 0; i < 16; i++)
  {
    res.data[i] /= det;
  }

  res = mat4f_transpose(res);
  return res;
}

inline void mat4f_setRotation(mat4f_t *m, const float *data)
{
  m->coeffs.c00 = data[0];
  m->coeffs.c01 = data[1];
  m->coeffs.c02 = data[2];
  m->coeffs.c10 = data[3];
  m->coeffs.c11 = data[4];
  m->coeffs.c12 = data[5];
  m->coeffs.c20 = data[6];
  m->coeffs.c21 = data[7];
  m->coeffs.c22 = data[8];
}

inline void
mat4f_setTranslation(mat4f_t *m, const float tx, const float ty, const float tz)
{
  m->coeffs.c03 = tx;
  m->coeffs.c13 = ty;
  m->coeffs.c23 = tz;
  return;
}

inline mat4f_t mat4f_getRotation(const mat4f_t m)
{
  mat4f_t res = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  res.coeffs.c00 = m.coeffs.c00;
  res.coeffs.c01 = m.coeffs.c01;
  res.coeffs.c02 = m.coeffs.c02;
  res.coeffs.c10 = m.coeffs.c10;
  res.coeffs.c11 = m.coeffs.c11;
  res.coeffs.c12 = m.coeffs.c12;
  res.coeffs.c20 = m.coeffs.c20;
  res.coeffs.c21 = m.coeffs.c21;
  res.coeffs.c22 = m.coeffs.c22;

  return res;
}

inline vec4f_t mat4f_getTranslation(const mat4f_t m)
{
  vec4f_t res =
      vec4f_create(m.coeffs.c30, m.coeffs.c31, m.coeffs.c32, m.coeffs.c33);
  return res;
}

inline mat4f_t mat4f_rotation(const vec3f_t axis, const float theta)
{
  mat4f_t res = mat4f_identity();

  const vec3f_t axis_ = vec3f_norm(axis);
  const float x = axis_.coords.x;
  const float y = axis_.coords.y;
  const float z = axis_.coords.z;
  const float c = cosf(theta);
  const float s = sin(theta);

  res.coeffs.c00 = x * x * (1.0f - c) + c;
  res.coeffs.c01 = x * y * (1.0f - c) - z * s;
  res.coeffs.c02 = x * z * (1.0f - c) + y * s;

  res.coeffs.c10 = x * y * (1.0f - c) + z * s;
  res.coeffs.c11 = y * y * (1.0f - c) + c;
  res.coeffs.c12 = y * z * (1.0f - c) - x * s;

  res.coeffs.c20 = x * z * (1.0f - c) - y * s;
  res.coeffs.c21 = y * z * (1.0f - c) + x * s;
  res.coeffs.c22 = z * z * (1.0f - c) + c;

  return res;
}

inline mat4f_t
mat4f_affine(const vec3f_t axis, const float alpha, const vec3f_t translation)
{
  mat4f_t res = mat4f_rotation(axis, alpha);

  res.coeffs.c03 = translation.coords.x;
  res.coeffs.c13 = translation.coords.y;
  res.coeffs.c23 = translation.coords.z;

  return res;
}

inline mat4f_t
mat4f_lookAt(const vec3f_t position, const vec3f_t direction, const vec3f_t u)
{
  mat4f_t res = mat4f_identity();

  const vec3f_t forward = vec3f_norm(vec3f_sub(position, direction));
  const vec3f_t right = vec3f_cross(vec3f_norm(u), forward);
  const vec3f_t u_ = vec3f_cross(forward, right);
  const vec3f_t de = vec3f_mul(position, -1.0f);

  res.coeffs.c00 = right.coords.x;
  res.coeffs.c10 = right.coords.y;
  res.coeffs.c20 = right.coords.z;

  res.coeffs.c01 = u_.coords.x;
  res.coeffs.c11 = u_.coords.y;
  res.coeffs.c21 = u_.coords.z;

  res.coeffs.c02 = forward.coords.x;
  res.coeffs.c12 = forward.coords.y;
  res.coeffs.c22 = forward.coords.z;

  res = mat4f_inverse(res);

  res.coeffs.c03 = vec3f_dot(de, right);
  res.coeffs.c13 = vec3f_dot(de, u_);
  res.coeffs.c23 = vec3f_dot(de, forward);

  return res;
}

inline mat4f_t mat4f_create_perspective(
    const float fovy, const float aspect, const float near, const float far)
{
  mat4f_t res = mat4f_identity();

  const float theta = (float) M_PI * fovy * 0.5f / 180.0f;
  const float range = far - near;
  const float invtan = 1.0f / tanf(theta);

  res.array[0][0] = invtan / aspect;
  res.array[1][1] = invtan;
  res.array[2][2] = -(near + far) / range;
  res.array[3][2] = -1;
  res.array[2][3] = -2 * near * far / range;

  return res;
}

inline vec4f_t mat4f_transform(const vec4f_t v, const mat4f_t m)
{
  return mat4f_mul_vector(v, m);
}

#endif // __GEOMETRY_MAT4F_H_
