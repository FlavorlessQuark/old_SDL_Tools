NAME = test
STATIC_NAME = libSDLX.a
DYNAMIC_NAME = libSDLX.so

DEBUG_FLAGS= -fsanitize=address
FLAGS = 
INCLUDES = -I includes/ -I includes/includes_SDL2/
LIBS = -l SDL2 -l SDL2_image -l SDL2_ttf -lm
LIB_DIR = libs/

SDLX_DIR = SDLX/
INPUT_DIR = input/
SRCS_DIR = srcs/

BIN_DIR = bin/

SRCS_NAMES =								\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))	\
	main 				\

SDLX_NAMES = 			\
	SDLX_anim			\
	SDLX_collision		\
	SDLX_input			\
	SDLX_LevelManager	\
	SDLX_render			\
	SDLX_UI				\
	SDLX_utils			\
	SDLX				\

C_FILES =				\
	$(SRCS_NAMES) 		\

SRCS = $(addsuffix .c, $(C_FILES))
OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

dynamic:
	gcc -fPIC $(FLAGS) $(INCLUDES) $(SRCS) $(LIBS) -shared -o $(DYNAMIC_NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) -fPIC $(INCLUDES) -c $< -o $@

static: $(BIN_DIR) $(OBJS)
	ar -rc $(STATIC_NAME) $(addsuffix .o, $(addprefix bin/SDLX/, $(SDLX_NAMES)))
	ranlib $(STATIC_NAME)

run: re clean
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all