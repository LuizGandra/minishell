# ===========================================================================
#  =============================== COLORS ==================================
# ===========================================================================

GREEN = \033[32;3m
RED = \033[31;3m
CYAN = \033[36;1;3;208m
WHITE = \033[37;1;4m
COLOR_LIMITER = \033[0m

# ===========================================================================
#  =============================== COMPILER ================================
# ===========================================================================

CFLAGS := -Wall -Wextra -Werror -g3
RFLAGS := -lreadline -lhistory
VALGRIND_LOG := valgrind.log

# ===========================================================================
#  =============================== LIBFT ===================================
# ===========================================================================

LIB_PATH := ./libs/libft
LIB_NAME := libft.a

# ===========================================================================
#  =============================== MINISHELL ===============================
# ===========================================================================

NAME = minishell
SRC_PATH = ./src/
HEADER_PATH = ./include/
BUILD_PATH = ./build/

LEXING_PATH = ./lexing/
UTILS_PATH = ./utils/

FILES = \
	main.c \
	$(LEXING_PATH)utils.c \
	$(LEXING_PATH)lexer.c \
	$(LEXING_PATH)validation.c \
	$(UTILS_PATH)error.c \
	$(UTILS_PATH)global.c \
	$(UTILS_PATH)get_env.c 

OBJS = $(addprefix $(BUILD_PATH), $(FILES:%.c=%.o))

# ===========================================================================
#  ================================= RULES =================================
# ===========================================================================

all: libft $(BUILD_PATH) print $(NAME)


libft:
ifeq ($(wildcard $(LIB_PATH)/$(LIB_NAME)),)
	@printf "$(CYAN)------------------- ----------------- -------------------$(COLOR_LIMITER)\n"
	@printf "$(CYAN)-------------------| COMPILING LIBFT |-------------------$(COLOR_LIMITER)\n"
	@printf "$(CYAN)------------------- ----------------- -------------------$(COLOR_LIMITER)\n"
	@make build -C $(LIB_PATH) --no-print-directory
endif

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)$(LEXING_PATH)
	@mkdir -p $(BUILD_PATH)$(UTILS_PATH)

print:
ifeq ($(wildcard $(NAME)),)
	@printf "$(GREEN) ------------------------$(COLOR_LIMITER)"
	@printf "$(GREEN)| Compiling Main Project |$(COLOR_LIMITER)"
	@printf "$(GREEN)------------------------$(COLOR_LIMITER)"
	@echo " "
endif

$(NAME): $(OBJS) $(HEADER_PATH)minishell.h
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER_PATH) -L$(LIB_PATH) -lft $(RFLAGS)
	@printf "$(CYAN)------ --------------------------------------------- ------$(COLOR_LIMITER)\n"
	@printf "$(CYAN)------| MINISHELL executable was created successfully!! |------$(COLOR_LIMITER)\n"
	@printf "$(CYAN)------ --------------------------------------------- ------$(COLOR_LIMITER)\n"
	@echo " "

$(BUILD_PATH)%.o: $(SRC_PATH)%.c
	@printf "$(GREEN)[Compiling]$(COLOR_LIMITER) $(notdir $<)...\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH)

clean:
	@printf "$(RED)[Removing Objects...]$(COLOR_LIMITER)\n"
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(BUILD_PATH)
	@rm -rf $(VALGRIND_LOG)

fclean: clean
	@printf "$(RED)[Removing $(notdir $(NAME))...]$(COLOR_LIMITER)\n"
	@rm -rf $(NAME)

re: fclean
	@make --no-print-directory

valgrind: all
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--track-fds=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	--suppressions=./readline.supp \
	./$(NAME)
	@cat $(VALGRIND_LOG)

.PHONY: all clean fclean re valgrind libft