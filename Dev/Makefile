NAME = test
STATIC_LIB = libSDLX.a
SHARED_LIB = libSDLX.so

DEBUG_FLAGS= -fsanitize=address
FLAGS = 
INCLUDES = -I includes/ -I includes/includes_SDL2/

LIB_DIR = libs/
MACH_0 = $(LIB_DIR)libSDL2.dylib $(LIB_DIR)libSDL2_ttf.dylib $(LIB_DIR)libSDL2_image.dylib
LINUX = $(LIB_DIR)libSDL2-2.0.so $(LIB_DIR)libSDL2_ttf-2.0.so $(LIB_DIR)libSDL2_image-2.0.so

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
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) main.c $(LINUX)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) -fPIC $(INCLUDES) -c $< -o $@

archive: $(BIN_DIR) $(OBJS)
	ar -rc $(STATIC_LIB) $(addsuffix .o, $(addprefix bin/SDLX/, $(SDLX_NAMES)))
	ranlib $(STATIC_LIB)

shared:  $(BIN_DIR) $(OBJS)
	gcc -shared -o $(SHARED_LIB) $(addsuffix .o, $(addprefix bin/SDLX/, $(SDLX_NAMES)))

run: re clean
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all