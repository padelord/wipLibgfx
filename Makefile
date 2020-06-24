CC		=	clang
NAME	=	test/bean
N_LFT	=	libft.a
N_LGFX	=	libgfx.a
D_LFT	=	./libft
D_LGFX	=	./libgfx
LIBFT	=	$(D_LFT)/$(N_LFT)
DEPS	=	Makefile
DEPS	+=	$(LIBFT)
IDIR	=	./test/includes
IDIR	+=	./libft/includes

CFLAGS	=	-Wall -Wextra
#CFLAGS	+=	-Wextra


SDIR	=	./test/src
_SRC	=	main.c
SRC		=	$(addprefix $(SDIR)/,$(_SRC))
ODIR	=	./test/obj
OBJ		=	$(SRC:$(SDIR)/%.c=$(ODIR)/%.o)
LDIR	=	$(D_LFT)
LDIR	+=	$(D_LGFX)
LFLAGS	=	$(addprefix -L,$(LDIR))
LFLAGS	+=	-lft
LFLAGS	+=	-lm
LFLAGS	+=	$(shell sdl2-config --libs)

CFLAGS	+=	$(addprefix -I,$(IDIR))
CFLAGS	+=	$(shell sdl2-config --cflags)

all: $(NAME)

lib:
	@make -sC $(D_LFT)

libclean:
	@make -sC $(D_LFT) fclean

$(OBJ):	$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	clang -c $< -o $@ $(CFLAGS) -g3

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS) -g3

$(LIBFT):
	@make -sC $(D_LFT)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
