CC		=	clang
NAME	=	test/bean
N_LFT	=	libft.a
N_LGFX	=	libgfx.a
D_LFT	=	./libft
D_LGFX	=	./libgfx
LIBGFX	=	$(D_LGFX)/$(N_LGFX)
LIBFT	=	$(D_LFT)/$(N_LFT)
DEPS	=	Makefile
DEPS	+=	$(LIBFT)
DEPS	+=	$(LIBGFX)
IDIR	=	./test/includes
IDIR	+=	./libft/includes
IDIR	+=	./libgfx/includes

CFLAGS	=	-Wall -Wextra
#CFLAGS	+=	-Wextra

ifeq ($(shell uname), Darwin)
IDIR	+=	$(D_LGFX)/includes/MacOs
LFLAGS = -framework OpenGl -framework AppKit
else
LFLAGS	+= -lXext -lX11 -lbsd
IDIR	+=	$(D_LGFX)/includes/Linux
endif

SDIR	=	./test/src
_SRC	=	main.c
SRC		=	$(addprefix $(SDIR)/,$(_SRC))
ODIR	=	./test/obj
OBJ		=	$(SRC:$(SDIR)/%.c=$(ODIR)/%.o)
LDIR	=	$(D_LFT)
LDIR	+=	$(D_LGFX)
LFLAGS	+=	$(addprefix -L,$(LDIR))
LFLAGS	+=	-lgfx
LFLAGS	+=	-lft
LFLAGS	+=	-lm
LFLAGS	+=	-lmlx

CFLAGS	+=	$(addprefix -I,$(IDIR))

all: $(NAME)

lib:
	@make -sC $(D_LGFX)
	@make -sC $(D_LFT)

libclean:
	@make -sC $(D_LFT) fclean
	@make -sC $(D_LGFX) fclean

$(OBJ):	$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	clang -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

$(LIBGFX):
	@make -sC $(D_LGFX)

$(LIBFT):
	@make -sC $(D_LFT)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
