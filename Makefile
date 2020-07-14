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
			demon.c \
			worker.c \
			event.c \
			server.c \
			network.c \
			set_tls1.c \
			set_tls2.c \
			mx_database_delete.c \
			mx_database_edit.c \
			mx_database_init.c \
			mx_do_msg.c \
			mx_do_login.c \
			mx_chat_send_history.c \
			mx_drop.c \
             
SRC_CLIENT = new_main_client.c

OBJS_SERVER = $(addprefix $(OBJD)/, $(SRC_SERVER:%.c=%.o))
OBJS_CLIENT = $(addprefix $(OBJD)/, $(SRC_CLIENT:%.c=%.o))

CFLAGS = -std=c11  $(addprefix -W, all extra error pedantic) \
		 	$(addprefix -Wno, -unused-command-line-argument -pedantic) \
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

$(NAME_S): $(LMXA) $(OBJS_SERVER)
	@make -sC ./cjson
	@clang $(CFLAGS2) -lsqlite3 cjson_lib.a $(LMXA) $(LIBRESSL_H) $(LIBRESSL_A) $(OBJS_SERVER) -o $@
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
	@rm -rf ./cjson/cjson_lib.a
	@rm -rf uchat_server.log
	@printf "$(OBJD)\t\t   \033[31;1mdeleted\033[0m\n"
	@printf "cjson library\t   \033[31;1mdeleted\033[0m\n"
	@printf "uchat_server.log   \033[31;1mdeleted\033[0m\n"

uninstall: clean
# 	@make -sC $(LBMXD) uninstall
	@rm -rf $(NAME_S) $(NAME_C)
	@printf "$(NAME_S)\t   \033[31;1muninstalled\033[0m\n"
	@printf "$(NAME_C)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

