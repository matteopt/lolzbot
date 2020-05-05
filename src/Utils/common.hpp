#pragma once

namespace Common {
	
	int screen_x;
	int screen_y;

	std::random_device rngdev;
	std::mt19937 rng(rngdev());
	std::uniform_int_distribution<std::mt19937::result_type> dmstime(0, 500);
}
