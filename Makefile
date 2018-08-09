# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/08/09 22:38:46 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS=wolf3d.h world.h texture_sys.h
SRCS=main.c collision.c render.c map.c map_token.c util.c util_math.c \
texture_sys.c
NAME=wolf3d
CFLAGS=-Wall -Wextra -Werror -Wconversion -g
LIBS=-I libft/includes -L libft/ -lft -lm
SDL2_CONFIG=SDL2/bin/sdl2-config
SDL_SRCS=SDL2-2.0.8

all: $(NAME)

# TODO: probably download the tarball
$(SDL_SRCS):
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
