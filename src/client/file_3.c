#include "client.h"


char *mx_help_str_eng() {
    char *sss = "Rules: max str len 100 chars\n"
        "Comands write only: |cmd|\n"
        "Formatin: |12| - font-size, |rol| - color, |ib| - fonts\n"
        "Stickers: |love|, |beuty|, |++++|, |sadness|, |danger|, |sad_cat|, "
        "|????|, |hello|, you can write this\n"
        "If you are admin you can kick users: |k_user|\n"
        "Change password: |p_new_pass|, password can`t be longer 30 chars\n"
        "Message editing: |e1234567890|new_mess\n"
        "On click Delete you are drop your account\n"
        "|m| on/off anti mat system\n"
        "|v| && |s| notification visual/sound off/on\n"
        "|c| clear history for admin\n"
        "|x_user| privat message\n";

    return sss;
}

char *mx_help_str_rus() {
    char *sss = "Правила: максимум 100 символов \n"
        "Команды писать только: |cmd| \n"
        "Formatin: |12| - размер шрифта, |rol| - цвет, |ib| - шрифты \n"
        "Наклейки: |love|, |beuty|, |++++|, |sadness|, |danger|, |sad_cat|, "
        "|????|, |hello|, you can write this\n"
        "Если вы являетесь администратором, "
        "вы можете кикнуть пользователей: |k_user| \n"
        "Изменить пароль: |p_new_pass|, пароль не может быть длиннее"
        "30 символов \n"
        "Редактирование сообщения: |е1234567890| new_mess \n"
        "После нажатия кнопки Удалить вы удаляете свой аккаунт \n"
        "|m| вкл/выкл анти мат системы \n"
        "|v| && |s| уведомление визуально/звук выключен/включен \n"
        "|c| очистить историю для администратора \n"
        "|x_user| приватное сообщение \n";

    return sss;
}

int mx_is_digit_for_editing(char *m, int i[2]) {
    char sss[1000];

    sprintf(sss ,"%s\n", strndup(m+2, i[1] - 2));
    for (unsigned long hh = 0; hh < strlen(sss) - 1; hh++) {
        if (!mx_isdigit(sss[hh]))
            return 0;
    }
    return 1;
}

int mx_is_have_editing(char *m) {
    int i[2] = {0, 0};

    if (m[0] == '|') {
        for (unsigned long gg = 1; gg < strlen(m); gg++) {
            if (m[gg] == '|') {
                i[1] = gg;
                break;
            }
            if (m[gg] == '\0')
                return 0;
        }
        if (m[1] == 'e') {
            return mx_is_digit_for_editing(m, i);
        }
    }
    return 0;
}
