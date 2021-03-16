NAME = test
STATIC_LIB = libSDLX.a

DEBUG_FLAGS= -fsanitize=address
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/ -I includes/includes_SDL2/

LIB_DIR = libs/
LIBRARIES = $(LIB_DIR)libSDL2.dylib $(LIB_DIR)libSDL2_ttf.dylib $(LIB_DIR)libSDL2_image.dylib

SDLX_DIR = SDLX/
INPUT_DIR = input/
SRCS_DIR = srcs/

BIN_DIR = bin/

SRCS_NAMES =								\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))	\
	main 				\

SDLX_NAMES = 			\
	SDLX_anim			\
	SDLX_init			\
	SDLX_input			\
	SDLX_render			\
	SDLX				\

C_FILES =				\
	$(SRCS_NAMES) 		\

SRCS = $(addsuffix .c, $(C_FILES))
OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): archive
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) main.c $(LIBRARIES) -L -l $(STATIC_LIB)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

archive: $(BIN_DIR) $(OBJS)
	ar -rc $(STATIC_LIB) $(addsuffix .o, $(addprefix bin/SDLX/, $(SDLX_NAMES)))  
	ranlib $(STATIC_LIB)

run: re clean
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all