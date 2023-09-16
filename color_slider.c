#include "pango/pango-attributes.h"
#include <gtk/gtk.h>

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color;

static color global_color = {.r = 0, .g = 0, .b = 0};

static void update_label_color(gpointer label) {
    PangoAttribute *textColor = pango_attr_foreground_new(global_color.r << 8,global_color.g << 8,global_color.b << 8);
    PangoAttrList *const Attrs = pango_attr_list_new();
    pango_attr_list_insert(Attrs, textColor);
    gtk_label_set_attributes(GTK_LABEL(label), Attrs);
    pango_attr_list_unref(Attrs);
}


static void print_value(GtkWidget *app, gpointer user_data){
    g_print("RED: %i GREEN: %i BLUE: %i\n", global_color.r, global_color.g, global_color.b);
    
}

static void update_value_scale_red(GtkWidget *app, gpointer user_data){
    global_color.r = gtk_range_get_value(GTK_RANGE(app));
    update_label_color(user_data);
}
static void update_value_scale_green(GtkWidget *app, gpointer user_data){
    global_color.g = gtk_range_get_value(GTK_RANGE(app));
    update_label_color(user_data);
}
static void update_value_scale_blue(GtkWidget *app, gpointer user_data){
    global_color.b = gtk_range_get_value(GTK_RANGE(app));
    update_label_color(user_data);
}


static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *scale_red;
    GtkWidget *scale_green;
    GtkWidget *scale_blue;

    window = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW (window), "Color scale_red");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    label = gtk_label_new("PRINT VALUE TO CONSOLE");
    update_label_color(label);

    scale_red = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    g_signal_connect (scale_red, "value_changed", G_CALLBACK (update_value_scale_red), label);
    scale_green = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    g_signal_connect (scale_green, "value_changed", G_CALLBACK (update_value_scale_green), label);
    scale_blue = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    g_signal_connect (scale_blue, "value_changed", G_CALLBACK (update_value_scale_blue), label);


    button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(button), label);
    g_signal_connect (button, "clicked", G_CALLBACK (print_value), label);



    grid = gtk_grid_new();

    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_red, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_green, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_blue, 2, 1, 1, 1);

    gtk_window_set_child(GTK_WINDOW (window), grid);

    gtk_window_present(GTK_WINDOW(window));

}


int main(void) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.backspace-phill.colorslider", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run (G_APPLICATION (app), 0, NULL);

    g_object_unref(app);

    return status;

}
