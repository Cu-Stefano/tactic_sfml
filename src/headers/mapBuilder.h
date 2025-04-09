#pragma once
#include "state.h"

using namespace std;

std::vector<std::vector<int>> map_generator();

void initialize_Map(state& gs);

void draw_map(state& gs);