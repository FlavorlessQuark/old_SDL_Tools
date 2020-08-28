NAME = #Program-name
FLAGS = #Compile flags -Wall -Wextra -Werror

FILENAMES = main update display_init buttons
INCL = -I incl/
LIB = -L ~/.brew/lib -l SDL2 -l sdl2_image

SRCS = $(addprefix([path], $(addsuffix [extension], $(FILENAMES)))
OBJS = $(addprefix([path], $(addsuffix [extension], $(FILENAMES)))

all : $(NAME)

objs/%.o : srcs/%.c
	@/bin/mkdir -p objs
	gcc $(FLAGS) -c $(INCL) $< -o $@

$(NAME): $(OBJS)
	gcc $(FLAGS) $(INCL) $(LIB) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -rf $(NAME)

update : clean
	git add .
	git commit -m "$(MSG)"
	git push origin master

re : fclean all

.PHONY : $(NAME) clean fclean update re
