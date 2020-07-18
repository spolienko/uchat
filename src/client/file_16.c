#include "client.h"



void mx_print_img(t_row *row, t_info *inf) {
    GdkPixbuf *px;

    if (mx_check_on_cmd(inf->body) == 3)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/+.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 4)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/sadness.png",
            340, 340, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 5)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/danger.png",
            270, 270, TRUE, NULL);
    if (mx_check_on_cmd(inf->body) == 6)
        px = gdk_pixbuf_new_from_file_at_scale ("src/client/img/sad_cat.png",
            390, 390, TRUE, NULL);
    mx_do_print_img(row, inf, px);
}


static char *love() {
    char *message = "___$$$$$$$$______$$$$$$$$$\n"
        "_$$$$$$$$$$$$__$$$$$$$__$$$$\n"
        "$$$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "$$$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "$$$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "_$$$$$$$$$$$$$$$$$$$$$$__$$$\n"
        "___$$$$$$$$$$$$$$$$$$$$$$$\n"
        "______$$$$$$$$$$$$$$$$$\n"
        "________$$$$$$$$$$$$$\n"
        "___________$$$$$$$\n"
        "_____________$$$\n"
        "______________$\n";

    return message;
}

void mx_print_text(t_row *row, t_info *inf) {
    if (mx_check_on_cmd(inf->body) == 1)
        row->v_body = gtk_label_new(love());
}

void mx_print_cmd(t_row *row, t_info *inf) {
    if (mx_check_on_cmd(inf->body) > 1)
        mx_print_img(row, inf);
    if (mx_check_on_cmd(inf->body) == 1)
        mx_print_text(row, inf);
}

char *mx_get_new_body_str(char *new_str) {
    int arr[2] = {0, 0};

    if (new_str[1] == '|')
        arr[1] = 1;
    else if (new_str[2] == '|')
        arr[1] = 2;
    else if (new_str[3] == '|')
        arr[1] = 3;
    else if (new_str[4] == '|')
        arr[1] = 4;
    return new_str + arr[1] + 1;
}
