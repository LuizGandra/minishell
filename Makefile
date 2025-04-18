# ===========================================================================
#  =============================== CONTROL =================================
# ===========================================================================

UP = \033[A
CUT = \033[K
RESET = \033[0m
RED = \033[31;3m
GREEN = \033[32;3m
YELLOW = \033[33;3m
WHITE = \033[37;1;4m
CYAN = \033[36;1;3;208m

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

BUILTINS_PATH = ./builtins/
EXPANDER_PATH = ./expander/
SIGNALS_PATH = ./signals/
LEXING_PATH = ./lexing/
UTILS_PATH = ./utils/
EXEC_PATH = ./exec/
PARSER_PATH = ./parser/

FILES = \
	main.c \
	$(BUILTINS_PATH)echo.c \
	$(BUILTINS_PATH)pwd.c \
	$(BUILTINS_PATH)exit.c \
	$(LEXING_PATH)utils.c \
	$(LEXING_PATH)lexer.c \
	$(LEXING_PATH)state.c \
	$(LEXING_PATH)validation.c \
	$(LEXING_PATH)validation_utils.c \
	$(EXEC_PATH)run.c \
	$(EXEC_PATH)exec.c \
	$(EXEC_PATH)file.c \
	$(EXEC_PATH)path.c \
	$(EXEC_PATH)macros.c \
	$(EXEC_PATH)builtin.c \
	$(EXEC_PATH)fd_list.c \
	$(EXEC_PATH)pid_list.c \
	$(EXEC_PATH)run_utils.c \
	$(EXEC_PATH)exec_utils.c \
	$(EXPANDER_PATH)var.c \
	$(EXPANDER_PATH)expander.c \
	$(EXPANDER_PATH)wildcard.c \
	$(EXPANDER_PATH)wildcard_utils.c \
	$(UTILS_PATH)env.c \
	$(UTILS_PATH)global.c \
	$(UTILS_PATH)get_pid.c \
	$(UTILS_PATH)cleanner.c \
	$(UTILS_PATH)ft_readline.c \
	$(SIGNALS_PATH)handlers.c \
	$(PARSER_PATH)here_doc.c \
	$(PARSER_PATH)parser_utils.c \
	$(PARSER_PATH)parser.c \
	$(PARSER_PATH)print.c \
	$(PARSER_PATH)token_utils.c \

OBJS = $(addprefix $(BUILD_PATH), $(FILES:%.c=%.o))

# ===========================================================================
#  ================================= RULES =================================
# ===========================================================================

all: libft $(BUILD_PATH) print $(NAME)


libft:
ifeq ($(wildcard $(LIB_PATH)/$(LIB_NAME)),)
	@printf "$(CYAN)------------------- ----------------- -------------------$(RESET)\n"
	@printf "$(CYAN)-------------------| COMPILING LIBFT |-------------------$(RESET)\n"
	@printf "$(CYAN)------------------- ----------------- -------------------$(RESET)\n"
	@make build -C $(LIB_PATH) --no-print-directory
endif

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)$(BUILTINS_PATH)
	@mkdir -p $(BUILD_PATH)$(EXPANDER_PATH)
	@mkdir -p $(BUILD_PATH)$(SIGNALS_PATH)
	@mkdir -p $(BUILD_PATH)$(LEXING_PATH)
	@mkdir -p $(BUILD_PATH)$(UTILS_PATH)
	@mkdir -p $(BUILD_PATH)$(EXEC_PATH)
	@mkdir -p $(BUILD_PATH)$(PARSER_PATH)

print:
ifeq ($(wildcard $(NAME)),)
	@printf "$(GREEN) ------------------------$(RESET)"
	@printf "$(GREEN)| Compiling Main Project |$(RESET)"
	@printf "$(GREEN)------------------------$(RESET)"
	@echo " "
endif

$(NAME): $(OBJS) $(HEADER_PATH)minishell.h
	@printf "$(YELLOW)[Building]$(RESET) $(NAME)...\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER_PATH) -L$(LIB_PATH) -lft $(RFLAGS)
	@printf "$(UP)$(CUT)"
	@printf "$(GREEN)[Builded]$(RESET) $(NAME)...\n"
	@printf "$(CYAN)------ --------------------------------------------- ------$(RESET)\n"
	@printf "$(CYAN)------| MINISHELL executable was created successfully!! |------$(RESET)\n"
	@printf "$(CYAN)------ --------------------------------------------- ------$(RESET)\n"
	@echo " "

$(BUILD_PATH)%.o: $(SRC_PATH)%.c
	@printf "$(YELLOW)[Compiling]$(RESET) $(notdir $<)...\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH)
	@printf "$(UP)$(CUT)"
	@printf "$(GREEN)[Compiled]$(RESET) $(notdir $<)...\n"


clean:
	@printf "$(RED)[Removing Objects...]$(RESET)\n"
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(BUILD_PATH)
	@rm -rf $(VALGRIND_LOG)

fclean: clean
	@printf "$(RED)[Removing $(notdir $(NAME))...]$(RESET)\n"
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
