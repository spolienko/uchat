#include "client.h"


char *mx_parsing_mes(char *m, t_s *s) {
    if (mx_is_have_editing(m))
        return mx_edit_creating(m, s);
    else if (mx_is_have_drop(m))
        return mx_drop_creating(m, s);
    else if (mx_is_have_change_pass(m))
        return mx_change_pass_creating(m, s);
    else if (mx_is_have_matyki(m, s))
        return NULL;
    else if (mx_is_have_sound(m, s))
        return NULL;
    else if (mx_is_have_visual(m, s))
        return NULL;
    else if (mx_is_have_visual(m, s))
        return NULL;
    else if (mx_is_have_clean_history(m))
        return mx_clean_history(s);
    else if (mx_is_have_privat_message(m))
        return mx_create_privat_message(m, s);
    return mx_parsing_normal_mess(m, s);
}





void mx_inf(GtkWidget *widget, t_s *s) {
    (void)widget;
    t_inf_row *inf = malloc(sizeof(t_inf_row));

    init_help(inf, s);
    g_idle_add ((int (*)(void *))mx_show_widget, s->h->v_window);
}



void mx_closeApp(GtkWidget *window, t_s *s) {   
    (void)window;
    mx_exit_chat(s);
    printf("Destroy\n");
    exit(1);
    gtk_main_quit();
}

void mx_closeApp2(GtkWidget *window, t_s *s) { 
    mx_drop_sesion(s);
    mx_closeApp(window, s);
}


char *mx_get_cmd(char *str) {
    int arr[300];
    int arrr[2] = {0, 0};

    arr[0] = 0;
    arr[1] = 0;
    while (str[arrr[1]] != '\0') {
        if (str[arrr[1]] == '|') {
            arr[arrr[0]] = arrr[1];
            arrr[0]++;
        }
        arrr[1]++;
    }
    return strndup(str + arr[0], arr[1] + 1);
}


