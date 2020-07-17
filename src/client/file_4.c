#include "client.h"



char *mx_help_str(t_s *s) {
    if (!strcmp(s->h->lang, "eng"))
        return mx_help_str_eng();
    if (!strcmp(s->h->lang, "rus"))
        return mx_help_str_rus();
    return mx_help_str_eng();        
}

int mx_get_editing_id(char *m) {
    int i[2] = {0, 0};
    char sss[1000];
    int cc;

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|')
                i[1] = gg;
        }
    }
    sprintf(sss ,"%s\n", strndup(m+2, i[1] - 2));
    cc = atoi(sss);
    return cc;
}

char *mx_strneww(int size) {
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return NULL;
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

char *mx_get_new_body_e(char *m) {
    int i[2] = {0, 0};
    char *sss = mx_strneww(1000);

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            } 
        }
    }
    sprintf(sss ,"%s", strndup(m + i[1] + 1, strlen(m) - i[1] - 1));
    return sss;
}




char *mx_edit_creating(char *m, t_s *s) {
    cJSON *send = cJSON_CreateObject();
    int id_edit_mess = mx_get_editing_id(m);
    char *new_body = mx_get_new_body_e(m);
    
    cJSON_AddStringToObject(send, "kind", "edit");
    cJSON_AddStringToObject(send, "login", s->h->login);
    cJSON_AddStringToObject(send, "msg", new_body);
    cJSON_AddNumberToObject(send, "edit_id", id_edit_mess);
    return cJSON_Print(send);
}
