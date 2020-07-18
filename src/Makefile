NAME_S = uchat_server
NAME_C = uchat

SRCD = src
INCD = inc
OBJD = obj

LMXD =	libmx
LBMX = libmx.a
LMXA:=	$(addprefix $(LMXD)/, $(LBMX))
LMXI:=	$(LMXD)/inc
LBMXD = libmx
LIBMX = libmx

INCS = inc/uchat.h
INCS2 = inc/uchat.h


SRC_SERVER = main.c \
			mx_demon.c \
			mx_worker.c \
			mx_do_event.c \
			mx_server.c \
			mx_network.c \
			mx_set_tls1.c \
			mx_set_tls2.c \
			mx_database_delete.c \
			mx_database_edit.c \
			mx_database_init.c \
			mx_do_msg.c \
			mx_do_login.c \
			mx_chat_send_history.c \
			mx_database_edit2.c \
			mx_database_pass.c \
			mx_do_message.c \
			mx_do_message2.c \
			mx_do_message3.c \

SRC_CLIENT = main_client.c \
			file_1.c \
			file_2.c \
			file_3.c \
			file_4.c \
			file_5.c \
			file_6.c \
			file_7.c \
			file_8.c \
			file_9.c \
			file_10.c \
			file_11.c \
			file_12.c \
			file_13.c \
			file_14.c \
			file_15.c \
			file_16.c \
			file_17.c \
			file_18.c \
			file_19.c \
			file_20.c \
			file_21.c \
			file_22.c \
			file_23.c \
			file_24.c \
			file_25.c \
			file_26.c \
			file_27.c \
			file_28.c \

OBJS_SERVER = $(addprefix $(OBJD)/, $(SRC_SERVER:%.c=%.o))
OBJS_CLIENT = $(addprefix $(OBJD)/, $(SRC_CLIENT:%.c=%.o))

CFLAGS = -std=c11  $(addprefix -W, all extra error pedantic) \
		 	$(addprefix -Wno, -unused-command-line-argument) \
			 -g -fsanitize=address \
		 	`pkg-config --cflags --libs gtk+-3.0`

CFLAGS2 = -std=c11 -g -fsanitize=address -Wall -Wextra -Wpedantic -Werror


LIBRESSL_A = ./libressl/tls/.libs/libtls.a \
			 ./libressl/ssl/.libs/libssl.a \
			 ./libressl/crypto/.libs/libcrypto.a

LIBRESSL_H = \
			-I ./libressl/include/tls.h \
			-I ./libressl/include/openssl \
			-I ./libressl/include/pqueue.h \
			-I ./libressl/tls \
			-I ./libressl/ssl \
			-I ./libressl/crypto

all: install

server: $(CJSON) $(NAME_S)

$(CJSON):
	@make -sC ./cjson
	@make -sC ./sqlite3

$(NAME_S): $(LMXA) $(OBJS_SERVER)
	@make -sC ./sqlite3
	@make -sC ./cjson
	@clang $(CFLAGS2) liba_sqlite3.a cjson_lib.a $(LMXA) $(LIBRESSL_H) $(LIBRESSL_A) $(OBJS_SERVER) -o $@
	@printf "\r\33[2K$@\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: src/server/%.c $(INCS)
	@clang $(CFLAGS2)  -o $@ -c $< -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K\033[37;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "


$(OBJS_SERVER): | $(OBJD)
$(OBJS_HELP): | $(OBJD)

$(OBJD):
	@mkdir -pv $@

$(LMXA):
	@make -sC ./cjson
	@make -sC ./libmx/

client: $(NAME_C)

$(NAME_C): $(LMXA) $(OBJS_CLIENT)
	@clang $(CFLAGS) cjson_lib.a $(LMXA)   $(LIBRESSL_H) $(LIBRESSL_A) $(OBJS_CLIENT)  -o $@
	@printf "\r\33[2K$@\t\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: src/client/%.c $(INCS2)
	@clang $(CFLAGS)  -o $@ -c $< -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K\033[37;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS_CLIENT): | $(OBJD)

install: server client

clean:
# 	@make -sC $(LBMXD) clean
	@rm -rf $(OBJD)
	@rm -rf cjson_lib.a
	@rm -rf liba_sqlite3.a
	@rm -rf ./cjson/cjson_lib.a
	@rm -rf uchat_server.log
	@printf "$(OBJD)\t\t   \033[31;1mdeleted\033[0m\n"
	@printf "cjson library\t   \033[31;1mdeleted\033[0m\n"
	@printf "liba_sqlite3.a\t   \033[31;1mdeleted\033[0m\n"
	@printf "uchat_server.log   \033[31;1mdeleted\033[0m\n"

uninstall: clean
# 	@make -sC $(LBMXD) uninstall
	@rm -rf $(NAME_S) $(NAME_C)
	@printf "$(NAME_S)\t   \033[31;1muninstalled\033[0m\n"
	@printf "$(NAME_C)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

