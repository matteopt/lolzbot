#include "input.hpp"

void Input::Click(int abs_x, int abs_y, bool right_click) {
	tagINPUT input = tagINPUT();
	tagMOUSEINPUT mouse_click = tagMOUSEINPUT();

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
