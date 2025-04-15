# ===========================================================================
# ================================ CONTROL ==================================
# ===========================================================================

UP = \033[A
CUT = \033[K
RESET = \033[0m
RED = \033[31;1m
GREEN = \033[32;1m
YELLOW = \033[33;3m
CYAN = \033[36;1;3;208m
WHITE = \033[37;1;4m

# ===========================================================================
# ================================= LIBFT ===================================
# ===========================================================================

LIB_NAME = Libft
LIB_SOURCES_PATH = ./src/
LIB_HEADER_PATH = ./
LIB_BIN_PATH = ./build/

LIB_SOURCES = \
	ft_abs.c \
	ft_itoa.c \
	ft_atoi.c \
	ft_atol.c \
	ft_atost.c \
	ft_bzero.c \
	ft_split.c \
	ft_atoui8.c \
	ft_checkw.c \
	ft_calloc.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_substr.c \
	ft_strlen.c \
	ft_memcpy.c \
	ft_strcmp.c \
	ft_memmove.c \
	ft_isprime.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_strncpy.c \
	ft_isprint.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_realloc.c \
	ft_recalloc.c \
	ft_striteri.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_atoi_base.c \
	ft_putendl_fd.c \
	ft_putchar_fd.c \
	ft_next_prime.c \
	ft_free_matrix.c

LIB_OBJECTS = $(addprefix $(LIB_BIN_PATH), $(LIB_SOURCES:%.c=%.o))

# ===========================================================================
# ============================ GET NEXT LINE ================================
# ===========================================================================

GNL_NAME = GNL
GNL_SOURCES_PATH = ./get_next_line/src/
GNL_HEADER_PATH = ./get_next_line/includes/
GNL_BIN_PATH = ./get_next_line/build/

GNL_SOURCES = \
	get_next_line_utils.c \
	get_next_line.c

GNL_OBJECTS = $(addprefix $(GNL_BIN_PATH), $(GNL_SOURCES:%.c=%.o))

# ===========================================================================
# ============================= FT_PRINTF ===================================
# ===========================================================================

PRINTF_NAME = Printf
PRINTF_SOURCES_PATH = ./ft_printf/src/
PRINTF_HEADER_PATH = ./ft_printf/includes/
PRINTF_BIN_PATH = ./ft_printf/build/

PRINTF_SOURCES = \
	string_functions.c \
	number_functions.c \
	ft_printf.c

PRINTF_OBJECTS = $(addprefix $(PRINTF_BIN_PATH), $(PRINTF_SOURCES:%.c=%.o))

# ===========================================================================
# ============================= FT_PRINTF_FD ================================
# ===========================================================================

PRINTF_FD_NAME = Printf_fd
PRINTF_FD_SOURCES_PATH = ./ft_printf_fd/src/
PRINTF_FD_HEADER_PATH = ./ft_printf_fd/includes/
PRINTF_FD_BIN_PATH = ./ft_printf_fd/build/

PRINTF_FD_SOURCES = \
	ft_printf_fd.c \
	utils.c

PRINTF_FD_OBJECTS = $(addprefix $(PRINTF_FD_BIN_PATH), $(PRINTF_FD_SOURCES:%.c=%.o))

# ===========================================================================
# ============================== HASH_MAP ===================================
# ===========================================================================

HM_NAME = Hash_Map
HM_SOURCES_PATH = ./hash_map/src/
HM_HEADER_PATH = ./hash_map/includes/
HM_BIN_PATH = ./hash_map/build/

HM_SOURCES = \
	ft_hash_table.c \
	ft_hash_item.c \
	ft_hash_map.c

HM_OBJECTS = $(addprefix $(HM_BIN_PATH), $(HM_SOURCES:%.c=%.o))

# ===========================================================================
# ========================== GARBAGE COLLECTOR ==============================
# ===========================================================================

GC_NAME = ft_gc
GC_SOURCES_PATH = ./ft_gc/src/
GC_HEADER_PATH = ./ft_gc/includes/
GC_BIN_PATH = ./ft_gc/build/

GC_SOURCES = \
	ft_gc.c

GC_OBJECTS = $(addprefix $(GC_BIN_PATH), $(GC_SOURCES:%.c=%.o))

# ===========================================================================
# ============================= MAIN RULES ==================================
# ===========================================================================

NAME := libft.a
CFLAGS := -Wall -Wextra -Werror

all: $(LIB_BIN_PATH) $(NAME)

$(LIB_BIN_PATH)%.o: $(LIB_SOURCES_PATH)%.c
	@printf "$(YELLOW)[Compiling]$(RESET) $(WHITE)%s...$(RESET)\n" "$(notdir $(<))"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(LIB_HEADER_PATH)
	@printf "$(UP)$(CUT)"
	@printf "$(GREEN)[Finished]$(RESET) $(WHITE)%s...$(RESET)\n" "$(notdir $(<))"
	@printf "\n"

$(NAME): $(LIB_OBJECTS)
	@printf "$(CYAN) ---------------------------------------\n$(RESET)"
	@printf "$(CYAN)|  %s  Was Compiled Successfully!! |\n$(RESET)" "$(LIB_NAME)"
	@printf "$(CYAN)---------------------------------------\n$(RESET)"
	@printf "\n"
	@ar rcs $(NAME) $?

$(LIB_BIN_PATH):
	@mkdir -p $(LIB_BIN_PATH)

get_next_line:
	@make --no-print-directory \
	LIB_NAME="$(GNL_NAME)" \
	LIB_BIN_PATH="$(GNL_BIN_PATH)" \
	LIB_SOURCES_PATH="$(GNL_SOURCES_PATH)" \
	LIB_OBJECTS="$(GNL_OBJECTS)" \
	LIB_HEADER_PATH="$(GNL_HEADER_PATH)"

ft_printf:
	@make --no-print-directory \
	LIB_NAME="$(PRINTF_NAME)" \
	LIB_BIN_PATH="$(PRINTF_BIN_PATH)" \
	LIB_SOURCES_PATH="$(PRINTF_SOURCES_PATH)" \
	LIB_OBJECTS="$(PRINTF_OBJECTS)" \
	LIB_HEADER_PATH="$(PRINTF_HEADER_PATH)"

ft_printf_fd:
	@make --no-print-directory \
	LIB_NAME="$(PRINTF_FD_NAME)" \
	LIB_BIN_PATH="$(PRINTF_FD_BIN_PATH)" \
	LIB_SOURCES_PATH="$(PRINTF_FD_SOURCES_PATH)" \
	LIB_OBJECTS="$(PRINTF_FD_OBJECTS)" \
	LIB_HEADER_PATH="$(PRINTF_FD_HEADER_PATH)"

hash_map:
	@make --no-print-directory \
	LIB_NAME="$(HM_NAME)" \
	LIB_BIN_PATH="$(HM_BIN_PATH)" \
	LIB_SOURCES_PATH="$(HM_SOURCES_PATH)" \
	LIB_OBJECTS="$(HM_OBJECTS)" \
	LIB_HEADER_PATH="$(HM_HEADER_PATH)"

gc:
	@make --no-print-directory \
	LIB_NAME="$(GC_NAME)" \
	LIB_BIN_PATH="$(GC_BIN_PATH)" \
	LIB_SOURCES_PATH="$(GC_SOURCES_PATH)" \
	LIB_OBJECTS="$(GC_OBJECTS)" \
	LIB_HEADER_PATH="$(GC_HEADER_PATH)"

clean:
	@printf "$(RED)[Removing Objects]$(RESET)\n"
	@rm -rf $(LIB_BIN_PATH)
	@rm -rf $(GNL_BIN_PATH)
	@rm -rf $(PRINTF_BIN_PATH)
	@rm -rf $(PRINTF_FD_BIN_PATH)
	@rm -rf $(HM_BIN_PATH)
	@rm -rf $(GC_BIN_PATH)

fclean: clean
	@printf "$(RED)[Removing %s]$(RESET)\n" "$(NAME)"
	@rm -f $(NAME)

re: fclean all

build:
	@make --no-print-directory
	@make get_next_line --no-print-directory
	@make ft_printf --no-print-directory
	@make ft_printf_fd --no-print-directory
	@make hash_map --no-print-directory
	@make gc --no-print-directory

.PHONY: all clean fclean re get_next_line ft_printf ft_printf_fd hash_map gc build
