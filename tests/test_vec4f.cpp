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

#include <stdlib.h>
#include <stdio.h>
#include <geometry_cxx.hpp>

#include <ctime>

// -----------------------------------------------------------------------------

template <typename T>
static inline T _rand_val()
{
  return T(2) * T(rand()) / T(RAND_MAX) - T(1);
}

template <typename T>
inline geometry::Vec4<T> rand_vec()
{
  return geometry::Vec4<T>(
      _rand_val<T>(), _rand_val<T>(), _rand_val<T>(), _rand_val<T>());
}

// -----------------------------------------------------------------------------

void test_vec4f()
{
  geometry::Vec4<float> test(1, 2, 3, 4);

  if(test.x() != 1)
  {
    fprintf(stderr, "test_vec4f() : failed\n");
    return;
  }

  if(test.y() != 2)
  {
    fprintf(stderr, "test_vec4f() : failed\n");
    return;
  }

  if(test.z() != 3)
  {
    fprintf(stderr, "test_vec4f() : failed\n");
    return;
  }

  if(test.t() != 4)
  {
    fprintf(stderr, "test_vec4f() : failed\n");
    return;
  }

  fprintf(stdout, "test_vec4f() : success\n");
}

void test_vec4f_add()
{
  geometry::Vec4<float> a = rand_vec<float>();
  geometry::Vec4<float> b = rand_vec<float>();
  geometry::Vec4<float> c = a + b;

  if(c.x() != a.x() + b.x())
  {
    fprintf(stderr, "test_vec4f_add() : failed\n");
    return;
  }

  if(c.y() != a.y() + b.y())
  {
    fprintf(stderr, "test_vec4f_add() : failed\n");
    return;
  }

  if(c.z() != a.z() + b.z())
  {
    fprintf(stderr, "test_vec4f_add() : failed\n");
    return;
  }

  if(c.t() != a.t() + b.t())
  {
    fprintf(stderr, "test_vec4f_add() : failed\n");
    return;
  }

  fprintf(stdout, "test_vec4f_add() : success\n");
}

void test_vec4f_sub()
{
  geometry::Vec4<float> a = rand_vec<float>();
  geometry::Vec4<float> b = rand_vec<float>();
  geometry::Vec4<float> c = a - b;

  if(c.x() != a.x() - b.x())
  {
    fprintf(stderr, "test_vec4f_sub() : failed\n");
    return;
  }

  if(c.y() != a.y() - b.y())
  {
    fprintf(stderr, "test_vec4f_sub() : failed\n");
    return;
  }

  if(c.z() != a.z() - b.z())
  {
    fprintf(stderr, "test_vec4f_sub() : failed\n");
    return;
  }

  if(c.t() != a.t() - b.t())
  {
    fprintf(stderr, "test_vec4f_sub() : failed\n");
    return;
  }

  fprintf(stdout, "test_vec4f_sub() : success\n");
}

void test_vec4f_mul()
{
  geometry::Vec4<float> a = rand_vec<float>();
  const float k = _rand_val<float>();
  geometry::Vec4<float> c = a * k;

  if(c.x() != a.x() * k)
  {
    fprintf(stderr, "test_vec4f_mul() : failed\n");
    return;
  }

  if(c.y() != a.y() * k)
  {
    fprintf(stderr, "test_vec4f_mul() : failed\n");
    return;
  }

  if(c.z() != a.z() * k)
  {
    fprintf(stderr, "test_vec4f_mul() : failed\n");
    return;
  }

  if(c.t() != a.t() * k)
  {
    fprintf(stderr, "test_vec4f_mul() : failed\n");
    return;
  }

  fprintf(stdout, "test_vec4f_mul() : success\n");
}

int main(int argc, char** argv)
{
  test_vec4f();

  test_vec4f_add();

  test_vec4f_sub();

  test_vec4f_mul();

  return EXIT_SUCCESS;
}
