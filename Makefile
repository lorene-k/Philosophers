# ------------  COLORS  ----------------------------------------------------- #
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
DEFAULT			=	\033[0m

# ------------  PROJECT  ---------------------------------------------------- #
NAME			=	philo

# ------------  DIRECTORIES  ------------------------------------------------ #
SRC_DIR			=	src/
OBJ_DIR			=	objs/

# ------------  SOURCES  ---------------------------------------------------- #
SRC_FLS			=	main.c \
					check.c \
					init_structs.c \
					actions.c \
					init_threads.c \
					monitor.c \
					utils.c \
					error.c

# ------------  FILEPATHS  -------------------------------------------------- #
SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FLS))
OBJS			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SRCS))

# ------------  FLAGS  ------------------------------------------------------ #
CFLAGS			=	-Wall -Wextra -Werror -g -pthread

MAKE_FLAGS		=	-s -C
RM_FLAGS		=	-rf

INCLUDES		=	-I/$(SRC_DIR)

# ------------  COMMANDS  --------------------------------------------------- #
CC				=	cc
MK				=	make all
MFC				=	make fclean
MC				=	make clean
RM				=	rm $(RM_FLAGS)

# ------------  RULES  ------------------------------------------------------ #
all:				$(NAME)

$(NAME):			$(OBJS)
					@$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS)
					@echo "$(GREEN)Compiled $(NAME)$(DEFAULT)"

$(OBJ_DIR)%.o: 		$(SRC_DIR)%.c | $(OBJ_DIR)
					@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)

clean:	
					@$(RM) $(OBJ_DIR) $(B_OBJ_DIR)

fclean:				clean 
					@$(RM) $(NAME)

re:					fclean all

.PHONY: 			all clean fclean re