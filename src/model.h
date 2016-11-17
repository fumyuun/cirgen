#ifndef MODEL_H
#define MODEL_H

#include <gtk/gtk.h>

#include <list>

#include "drawable.h"

struct model_t {
    std::list<drawable_t*> drawables;

    void draw(GtkWidget *widget);

    drawable_t* intersects(unsigned int x, unsigned int y);
};

#endif /* MODEL_H */
