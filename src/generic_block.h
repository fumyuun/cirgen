#ifndef GENERIC_BLOCK_H
#define GENERIC_BLOCK_H

#include <gtk/gtk.h>

#include <string>
#include <list>

#include "drawable.h"

class generic_block_t : public drawable_t {
private:

    std::string name;
    std::list<std::string> inputs;
    std::list<std::string> outputs;

    // calculated values
    unsigned int height;
    unsigned int width;

    unsigned int name_width;
    unsigned int inputs_width;
    unsigned int outputs_width;

    void recalculate_dimensions();

public:

    unsigned int pos_x;
    unsigned int pos_y;

    generic_block_t(unsigned int pos_x_, unsigned int pos_y_, std::string name_ = "NO_NAME");

    void draw(GtkWidget *widget);
    bool intersects(unsigned int x, unsigned int y);

    void set_name(std::string name_);
    void set_pos(unsigned int x_, unsigned int y_);

    void add_input(std::string input);
    void add_output(std::string output);

    void remove_input(unsigned int n);
    void remove_output(unsigned int n);
};

#endif /* GENERIC_BLOCK_H */
