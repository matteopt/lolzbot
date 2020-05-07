#include "lolzbot.hpp"

int main() {
	Common::screen_x = GetSystemMetrics(SM_CXSCREEN);
	Common::screen_y = GetSystemMetrics(SM_CYSCREEN);
	Client::Init();
	getchar();
}
