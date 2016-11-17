#include "generic_block.h"

extern GdkFont *font;

// this should be calculated too
const int INPUTS_OUTPUTS_PADDING_X = 16;

generic_block_t::generic_block_t(unsigned int pos_x_, unsigned int pos_y_, std::string name_)
    : pos_x(pos_x_), pos_y(pos_y_), name(name_)
{
    recalculate_dimensions();
}

void generic_block_t::recalculate_dimensions() {
    std::list<std::string>::iterator it;

    height = (std::max(inputs.size(), outputs.size()) + 2) * (font->ascent + font->descent);
    
    name_width = gdk_text_width(font, name.c_str(), name.length());

    inputs_width = 0;
    for (it = inputs.begin(); it != inputs.end(); ++it) {
        int w = gdk_text_width(font, it->c_str(), it->length());
        if (w > inputs_width) {
            inputs_width = w;
        }
    }
    outputs_width = 0;
    for (it = outputs.begin(); it != outputs.end(); ++it) {
        int w = gdk_text_width(font, it->c_str(), it->length());
        if (w > outputs_width) {
            outputs_width = w;
        }
    }

    width = std::max(name_width, inputs_width + outputs_width + INPUTS_OUTPUTS_PADDING_X);
}

void generic_block_t::draw(GtkWidget *widget) {
    std::list<std::string>::iterator it;
    int y_offset;

    gdk_draw_rectangle(widget->window, widget->style->fg_gc[gtk_widget_get_state (widget)],
        TRUE, pos_x, pos_y, width, height);

    gdk_draw_text(widget->window, font, widget->style->black_gc,
        pos_x, pos_y + font->ascent, name.c_str(), name.length());

    y_offset = 3;
    for (it = inputs.begin(); it != inputs.end(); ++it) {
        gdk_draw_text(widget->window, font, widget->style->black_gc,
            pos_x, pos_y + y_offset * font->ascent, it->c_str(), it->length());
        y_offset++;
    }

    y_offset = 3;
    for (it = outputs.begin(); it != outputs.end(); ++it) {
        gdk_draw_text(widget->window, font, widget->style->black_gc,
            pos_x + INPUTS_OUTPUTS_PADDING_X + inputs_width, pos_y + y_offset * font->ascent, it->c_str(), it->length());
        y_offset++;
    }
}

bool generic_block_t::intersects(unsigned int x, unsigned int y) {
    return x >= pos_x && x < pos_x + width && y >= pos_y && y < pos_y + height;
}


void generic_block_t::set_name(std::string name_) {
    name = name;

    recalculate_dimensions();
}

void generic_block_t::set_pos(unsigned int x_, unsigned int y_) {
    pos_x = x_;
    pos_y = y_;

    recalculate_dimensions();
}

void generic_block_t::add_input(std::string input) {
    inputs.push_back(input);

    recalculate_dimensions();
}

void generic_block_t::add_output(std::string output) {
    outputs.push_back(output);

    recalculate_dimensions();
}

void generic_block_t::remove_input(unsigned int n) {
    std::list<std::string>::iterator it;
    int i;

    for (i = 0, it = inputs.begin(); it != inputs.end(); ++i, ++it) {
        if (i == n) {
            inputs.erase(it);

            recalculate_dimensions();

            break;
        }
    }
}

void generic_block_t::remove_output(unsigned int n) {
    std::list<std::string>::iterator it;
    int i;

    for (i = 0, it = outputs.begin(); it != outputs.end(); ++i, ++it) {
        if (i == n) {
            outputs.erase(it);

            recalculate_dimensions();

            break;
        }
    }
}
