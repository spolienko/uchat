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
             
SRC_CLIENT = main_client.c

OBJS_SERVER = $(addprefix $(OBJD)/, $(SRC_SERVER:%.c=%.o))
OBJS_CLIENT = $(addprefix $(OBJD)/, $(SRC_CLIENT:%.c=%.o))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic 

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
	@make -sC ./cjson/

$(NAME_S): $(LMXA) $(OBJS_SERVER)

	@clang $(CFLAGS) -lsqlite3 $(LMXA) $(LIBRESSL_H) $(LIBRESSL_A) $(OBJS_SERVER) -o $@
	@printf "\r\33[2K$@\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: src/server/%.c $(INCS)
	@clang $(CFLAGS)  -o $@ -c $< -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K\033[37;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "


$(OBJS_SERVER): | $(OBJD)
$(OBJS_HELP): | $(OBJD)

$(OBJD):
	@mkdir -pv $@

$(LMXA):
	@make -sC ./libmx/

client: $(NAME_C)

$(NAME_C): $(LMXA) $(OBJS_CLIENT)
	@clang $(CFLAGS)  $(LMXA)   $(LIBRESSL_H) $(LIBRESSL_A) $(OBJS_CLIENT)  -o $@
	@printf "\r\33[2K$@\t\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: src/client/%.c $(INCS)
	@clang $(CFLAGS)  -o $@ -c $< -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K\033[37;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS_CLIENT): | $(OBJD)

install: server client

clean:
# 	@make -sC $(LBMXD) clean
	@rm -rf $(OBJD)
	@rm -rf cjson_lib.a
	@printf "$(OBJD)\t\t   \033[31;1mdeleted\033[0m\n"
	@printf "cjson library\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
# 	@make -sC $(LBMXD) uninstall
	@rm -rf $(NAME_S) $(NAME_C)
	@printf "$(NAME_S)\t   \033[31;1muninstalled\033[0m\n"
	@printf "$(NAME_C)\t\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

