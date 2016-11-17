#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <gtk/gtk.h>

struct drawable_t {
    virtual void draw(GtkWidget *widget);
    virtual bool intersects(unsigned int x, unsigned int y);
};

#endif /* DRAWABLE_H */
