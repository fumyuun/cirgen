#include "drawable.h"
#include <iostream>

void drawable_t::draw(GtkWidget *widget) {
    std::cerr << "Virtual draw called!" << std::endl;
}

bool drawable_t::intersects(unsigned int x, unsigned int y) {
	std::cerr << "Virtual intersects called!" << std::endl;

	return false;
}
