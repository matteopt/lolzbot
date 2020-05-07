#include "input.hpp"

void Input::Click(const int abs_x, const int abs_y, const bool right_click) {
	INPUT input = INPUT();
	MOUSEINPUT mouse_click = MOUSEINPUT();

	mouse_click.dx = abs_x * (65535 / (float)Common::screen_x);
	mouse_click.dy = abs_y * (65535 / (float)Common::screen_y);
	mouse_click.dwFlags = (0x0002 << right_click * 2) | MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;

	input.mi = mouse_click;

	INPUT inputs[2];

	inputs[0] = input;
	input.mi.dwFlags = (0x0004 << right_click * 2) | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	inputs[1] = input;
	SendInput(2, inputs, sizeof(input));
}

void Input::Keys(const unsigned char n, const uint8_t* const keys) {
	INPUT* inputs = new INPUT[2 * n];

	for (unsigned short i = 0; i < 2 * n; i++) {
		INPUT input = INPUT();
		KEYBDINPUT key_press = KEYBDINPUT();
		
		key_press.wScan = MapVirtualKey(keys[i % n], MAPVK_VK_TO_VSC);
		key_press.dwFlags = KEYEVENTF_SCANCODE | (i >= n ? KEYEVENTF_KEYUP : 0);

		input.type = INPUT_KEYBOARD;
		input.ki = key_press;

		inputs[i] = input;
	}
	
	SendInput(2 * n, inputs, sizeof(INPUT));
	delete[] inputs;
}

void Input::Key(const uint8_t key) {
	uint8_t keys[1]{ key };
	Keys(1, keys);
}
