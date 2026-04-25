NAME			:= 2048
BUILD_DIR		:= .build
SRC_DIR			:= srcs
INCLUDE_DIR		:= includes
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
CPPFLAGS		:= -MMD -MP -I $(INCLUDE_DIR) 
CFLAGS_DEBUG	:= -Wall -Wextra -MMD -I $(INCLUDE_DIR) -g3 -D DEBUG=1
P_LIBFT			:=	libft
LIBFT			:= $(P_LIBFT)/libft.a

SRCS			:= 		\
	main.c				\
	debug.c				\
	board.c				\
	logic_game.c		\
	fill_grid_numbers.c \
	display.c
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)
RM				:= rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lncurses

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(P_LIBFT) -c -o $@ $<

force:

$(LIBFT) : force
	@$(MAKE) -C $(P_LIBFT)

clean:
	@$(MAKE) -C $(P_LIBFT) clean
	$(RM) $(BUILD_DIR)

fclean: clean
	@$(MAKE) -C $(P_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

debug:
	$(MAKE) re CFLAGS="-Wall -Wextra -g3 -D DEBUG=1"

-include $(DEPS)

.PHONY: all clean fclean re
