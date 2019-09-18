# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/08/28 13:23:10 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER_FILES=wolf3d.h texture_sys.h model.h view.h controller.h
SRC_FILES=main.c texture_sys.c texture_sys_util.c util.c util_math.c \
model.c model_collision.c model_map.c model_map_token.c model_player.c \
model_update.c \
view.c view_raycast.c view_render.c view_ui.c view_sprites.c view_util.c \
controller.c
HEADERS=$(HEADER_FILES:%=includes/%)
SRCS=$(SRC_FILES:%=srcs/%)
NAME=wolf3d
CFLAGS=-Wall -Wextra -Werror -Wconversion -g
LIBS=-I libft/includes -L libft/ -lft -I ./includes -lm
SDL2_CONFIG=SDL2/bin/sdl2-config
SDL_SRCS=SDL2-2.0.8

all: $(NAME)

$(SDL_SRCS):
	curl -L https://www.libsdl.org/release/SDL2-2.0.8.tar.gz -o SDL2-2.0.8.tar.gz
	tar -xvzf $(SDL_SRCS).tar.gz

$(SDL2_CONFIG): $(SDL_SRCS)
	cd $(SDL_SRCS);\
	mkdir -p build;\
	cd build;\
	../configure --prefix=$(CURDIR)/SDL2;\
	make -j6; make install

$(NAME): $(SDL2_CONFIG) $(SRCS) $(HEADERS)
	make -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME) $(LIBS) $(shell ./$(SDL2_CONFIG) --cflags --libs)

clean:
	@echo "No objects to clean"

fclean: clean
	rm -f $(NAME)

re: fclean all
