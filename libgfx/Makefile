# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 14:13:30 by crenaudi          #+#    #+#              #
#    Updated: 2020/05/18 15:28:54 by padelord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgfx.a
AR = ar rc
CC = clang
RL = ranlib
RM = rm -f

SDIR	=	./src
ODIR	=	./obj
IDIR	=	./includes

CFLAGS = -Wall -Wextra
CFLAGS += -Werror

ifeq ($(shell uname), Darwin)
  IDIR	+=	./includes/MacOs
  LDFLAGS = -framework OpenGl -framework AppKit
else
  IDIR	+=	./includes/Linux
  LDFLAGS = -lXext -lX11 -lbsd
endif
DEPS	=	Makefile

CFLAGS	+=	$(addprefix -I, $(IDIR))

_D1		=	maths
_S1		=	distance.c			\
			normalize.c			\
			product.c			\
			quaternion.c        \
			quaternion_cal.c	\
			raddeg.c			\
			rotation.c			\
			scale.c				\
			spherical_matrice.c

_D2		=	struct_cam
_S2		=	camera2d.c			\
			camera3d.c

_D3		=	struct_img
_S3		=	image.c				\
			sprite.c			\
			init.c				\
			apply.c				\
			scale.c				\
			close.c

_D4		=	color
_S4		=	color_hsl.c			\
			color_rgvb.c

_D5		=	trace
_S5		=	bresenham.c

_D6		=	engine
_S6		=	window.c

_SRC	=	$(addprefix $(_D1)/, $(_S1))
_SRC	+=	$(addprefix $(_D2)/, $(_S2))
_SRC	+=	$(addprefix $(_D3)/, $(_S3))
_SRC	+=	$(addprefix $(_D4)/, $(_S4))
_SRC	+=	$(addprefix $(_D5)/, $(_S5))
_SRC	+=	$(addprefix $(_D6)/, $(_S6))

SRC		=	$(addprefix $(SDIR)/,$(_SRC))

OBJ		=	$(SRC:$(SDIR)/%.c=$(ODIR)/%.o)


all: $(NAME)

$(OBJ): $(ODIR)/%.o : $(SDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(shell echo "\033[0;33m Compiling:\t$@\033[0m\r\t\t\t\t\t\t\033[0;32m [OK] \033[0m")"

$(NAME):	$(OBJ)
	@echo "\033[0;33m Compiling:\tlibgfx.a\033[0m\r\t\t\t\t\t\t\033[0;32m [OK] \033[0m"
	@$(AR) $(NAME) $(OBJ)
	@$(RL) $(NAME)
	@echo "\033[0;33m [LIBGFX]\033[0;32m[SUCCESS] \033[0m"

clean:
	@echo "Deleting objects in $(ODIR)/"
	@$(RM) $(OBJ)

fclean: clean
	@echo "Deleting $(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
