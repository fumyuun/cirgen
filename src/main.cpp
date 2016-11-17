#include <gtk/gtk.h>

#include <iostream>

#include "model.h"
#include "generic_block.h"

GdkFont *font;

model_t model;


static gboolean delete_event( GtkWidget *widget, GdkEvent *event, gpointer data)
{
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

static gboolean expose_event_callback(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    model.draw(widget);

    return TRUE;
}

struct drag_info_t {
    int start_x;
    int start_y;
    int offset_x;
    int offset_y;

    bool is_dragging;
    generic_block_t *target;
} drag_info = {0};

static gboolean button_press_event_callback(GtkWidget *widget, GdkEventButton *event)
{
    generic_block_t *draw = (generic_block_t*)model.intersects(event->x, event->y);
    if (event->button == 1 && draw != NULL) {
        std::cout << "Hit" << std::endl;
        drag_info.is_dragging = true;
        drag_info.target = draw;
        drag_info.start_x = event->x;
        drag_info.start_y = event->y;
        drag_info.offset_x = draw->pos_x - event->x;
        drag_info.offset_y = draw->pos_y - event->y;

    }

    return TRUE;
}

static gboolean button_release_event_callback(GtkWidget *widget, GdkEventButton *event)
{
    std::cout << "Release" << std::endl;

    drag_info.is_dragging = false;

    return TRUE;
}

static gboolean motion_notify_event(GtkWidget *widget, GdkEventMotion *event)
{
    if (drag_info.is_dragging) {
        std::cout << "(" << (event->x - drag_info.start_x) << "," << (event->y - drag_info.start_y) << ")" << std::endl;

        drag_info.target->set_pos(event->x - drag_info.start_x, event->y - drag_info.start_y);

        gtk_widget_queue_draw_area(widget, 0, 0, 400, 400);
    }
    return TRUE;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *drawing_area;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    font = gdk_font_load("-*-helvetica-bold-r-normal--*-120-*-*-*-*-*-1");
    if (font == NULL) {
        std::cerr << "Unable to load a font" << std::endl;
        return 1;
    }
    
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    drawing_area = gtk_drawing_area_new();

    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK);

    gtk_widget_set_size_request(drawing_area, 100, 100);

    g_signal_connect(G_OBJECT(drawing_area), "expose_event", G_CALLBACK(expose_event_callback), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "button_press_event", G_CALLBACK(button_press_event_callback), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "button_release_event", G_CALLBACK(button_release_event_callback), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "motion_notify_event", G_CALLBACK(motion_notify_event), NULL);
    
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    
    gtk_widget_show(drawing_area);
    gtk_widget_show(window);

    generic_block_t henk(10, 10, "henk");

    henk.add_input("a_in");
    henk.add_input("b_in");

    henk.add_output("c_out");

    model.drawables.push_back(&henk);

    gtk_main();
    
    return 0;
}
