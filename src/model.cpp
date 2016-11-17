#include "model.h"

void model_t::draw(GtkWidget *widget) {
    std::list<drawable_t*>::iterator it;

    for (it = drawables.begin(); it != drawables.end(); ++it) {
        (*it)->draw(widget);
    }
}

drawable_t* model_t::intersects(unsigned int x, unsigned int y) {
    std::list<drawable_t*>::reverse_iterator it;

    for (it = drawables.rbegin(); it != drawables.rend(); ++it) {
        if ((*it)->intersects(x, y)) {
            return *it;
        }
    }
    return NULL;
}
