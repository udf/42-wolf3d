# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/08/03 17:31:05 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=main.c
NAME=wolf3d
CFLAGS=-Wall -Wextra -Werror -Wconversion -O3
LIBS=-I libft/includes -L libft/ -lft -lm
SDL2_CONFIG=SDL2/bin/sdl2-config
SDL_SRCS=SDL2-2.0.8

# TODO: probably download the tarball
$(SDL_SRCS):
	tar -xvzf $(SDL_SRCS).tar.gz

$(SDL2_CONFIG): $(SDL_SRCS)
	cd $(SDL_SRCS);\
	mkdir -p build;\
	cd build;\
	../configure --prefix=$(CURDIR)/SDL2;\
	make -j6; make install

all: $(NAME)

$(NAME): $(SDL2_CONFIG) $(SRCS)
	make -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME) $(LIBS) $(shell ./$(SDL2_CONFIG) --cflags --libs)

clean:
	@echo "No objects to clean"

fclean: clean
	rm -f $(NAME)

re: fclean all
