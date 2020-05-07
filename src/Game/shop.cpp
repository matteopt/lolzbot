#include "shop.hpp"

void Shop::Toggle() {
	// press P
	Input::Key(0x50);
}

void Shop::Buy(const char* const item_name) {
	printf("Buying %s...\n", item_name);
	// open the shop
	Toggle();
	Sleep(100);
	
	// enter the search bar
	uint8_t search_keys[2]{VK_CONTROL, VK_RETURN};
	Input::Keys(2, search_keys);
	Sleep(100);

	// search for the item
	size_t i = 0;
	while (item_name[i] != '\0') {
		const char c = item_name[i];
		// assume the item name is alpha-only (lower/upper-case)
		if ((c >= 65 && c <= 90) || c == 32)
			Input::Key(static_cast<uint8_t>(c));
		else if (c >= 97 && c <= 122)
			Input::Key(static_cast<uint8_t>(c - 32));
		i++;
	}
	Sleep(100);
	
	Input::Key(VK_RETURN);
	Sleep(100);

	// buy the item
	Input::Key(VK_RETURN);
	Sleep(100);

	// close the shop
	Toggle();
	printf("%s bought!\n", item_name);
}
