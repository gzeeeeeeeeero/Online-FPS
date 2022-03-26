#pragma once

#include <vector>
#include "config.hh"
#include "vector.hh"

using std::vector;

vec<float> player = {10, 3};
vec<float> dir    = { 1, 0};
vec<float> cam    = { 0, 1};
vec< int > map    = {int(player.x),
                     int(player.y)};
vector<float> kols;
vector<vec<float>> rays;
