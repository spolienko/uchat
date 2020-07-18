#include "client.h"



void mx_edit(GtkWidget *widget, t_for_click *c) {
    char mes[500];
    sprintf(mes, "|e%d|", c->inf->id);

    gtk_entry_set_text(GTK_ENTRY(c->s->h->v_main_e), mes);
    (void)widget;
}

void mx_print_E(t_row *row, t_info *inf, t_s *s) {
    t_for_click *c = malloc(sizeof(t_for_click));

    c->row = row;
    c->inf = inf;
    c->s = s;
    if (!strcmp(inf->author, s->h->login) && row->is_sticker) {
        row->v_bt_ed = gtk_button_new_with_label("E");
        gtk_box_pack_start(GTK_BOX(row->v_hrow), 
        row->v_bt_ed, FALSE, FALSE, 0);
        row->c_v_bt_ed = gtk_widget_get_style_context(row->v_bt_ed);
        gtk_style_context_add_class(row->c_v_bt_ed, "X");
        g_signal_connect(G_OBJECT(row->v_bt_ed), "clicked",
                         G_CALLBACK(mx_edit), c);
    }
}

void mx_set_bold_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "bold");
    gtk_style_context_add_class (row->c_v_time, "bold");
    gtk_style_context_add_class (row->c_v_body, "bold");
}

void mx_set_italic_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "italic");
    gtk_style_context_add_class (row->c_v_time, "italic");
    gtk_style_context_add_class (row->c_v_body, "italic");
}


void mx_set_red_line(t_row *row) {
    gtk_style_context_add_class (row->c_v_author, "red");
    gtk_style_context_add_class (row->c_v_time, "red");
    gtk_style_context_add_class (row->c_v_body, "red");   
}
