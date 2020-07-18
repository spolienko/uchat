#include "client.h"



void mx_set_styles_for_mess(t_row *row, char *str, t_info *inf) {
    if (!mx_check_on_cmd(inf->body) && inf->body[0] == '|') {
        if (str[0] == 'b')
            mx_set_bold_line(row);
        if (str[0] == 'i')
            mx_set_italic_line(row);
        if (str[1] == 'r')
            mx_set_red_line(row);
        if (str[1] == 'l')
            mx_set_lime_line(row);
        if (str[1] == 'o')
            mx_set_orange_line(row);
        if (str[2] == '1')
            mx_set_h1_line(row);
        if (str[2] == '2')
            mx_set_h2_line(row);
    }
}




char *mx_parsing_cmd(char *str) {
    char *strr = mx_get_cmd(str);
    char *strrr = mx_strneww(3);
    int cn = 0;

    while(strr[cn] != '\0') {
        if (strr[cn] == 'b' || strr[cn] == 'i' ) {
            strrr[0] = strr[cn];
        }
        if (strr[cn] == 'r' || strr[cn] == 'l' || strr[cn] == 'o') {
           strrr[1] = strr[cn];
        }
        if (strr[cn] == '1' || strr[cn] == '2' ) {
            strrr[2] = strr[cn];
        }
        cn++;
    }
    return strrr;
}

void mx_set_class_for_elem(t_row *row, t_info *inf) {
    row->c_v_author = gtk_widget_get_style_context(row->v_author);
    row->c_v_time = gtk_widget_get_style_context(row->v_time);
    row->c_v_body = gtk_widget_get_style_context(row->v_body);
    char *str = mx_parsing_cmd(inf->body);
    
    mx_set_styles_for_mess(row, str, inf);
}

void mx_end_initing(t_row *row, t_info *inf, t_s *s) {
    gtk_box_pack_start(GTK_BOX(row->v_hrow), row->v_body, FALSE, FALSE, 0);
    gtk_widget_set_size_request(row->v_body, 100, 30);    
    gtk_widget_set_size_request(row->v_body, 80, 30);
    mx_print_X(row, inf, s);
    mx_print_E(row, inf, s);
    mx_set_class_for_elem(row, inf);
    (void)inf;
    (void)s;
}

void mx_do_print_img(t_row *row, t_info *inf, GdkPixbuf *px) {
    if (mx_check_on_cmd(inf->body) == 7)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/?.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 8)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/hello.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 2)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/aut.jpg",
            250, 250, TRUE, NULL);
    row->v_body = gtk_image_new_from_pixbuf(px);
}

