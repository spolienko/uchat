#include "client.h"



void mx_set_lime_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "lime");
    gtk_style_context_add_class (row->c_v_time, "lime");
    gtk_style_context_add_class (row->c_v_body, "lime"); 
}

void mx_set_orange_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "orange");
    gtk_style_context_add_class (row->c_v_time, "orange");
    gtk_style_context_add_class (row->c_v_body, "orange"); 
}

void mx_set_h1_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "h1");
    gtk_style_context_add_class (row->c_v_time, "h1");
    gtk_style_context_add_class (row->c_v_body, "h1");
}

void mx_set_h2_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "h2");
    gtk_style_context_add_class (row->c_v_time, "h2");
    gtk_style_context_add_class (row->c_v_body, "h2");
}
