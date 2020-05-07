#include "common.hpp"

int Common::screen_x;
int Common::screen_y;

std::random_device Common::rngdev;
std::mt19937 Common::rng(rngdev());
// EVASION 100
std::uniform_int_distribution<std::mt19937::result_type> Common::dmstime(0, 500);
