SRCSF =	operations.c node.c stack.c parse.c pivot.c $(addprefix ops/, push.c rev_rotate.c rotate.c swap.c)

OBJSF = $(patsubst %.c,%.o, $(SRCSF))

LIBSF = libft/libft.a gnl/libgnl.a ftprintf/libftprintf.a

ifndef $(OS)
OS := $(shell uname)
endif

$(info Compiling for OS:$(OS))

DIRSRC = src/
DIROBJ = obj/
DIRINC = include/
DIRLIB = ../

# All relative to Makefile's folder
SRCS = $(patsubst %.c,$(DIRSRC)%.c, $(SRCSF))
OBJS = $(patsubst %.c,$(DIROBJ)%.o, $(SRCSF))
LIBS = $(patsubst %.a,$(DIRLIB)%.a, $(LIBSF))
INCS = $(shell find $(DIRINC) -name "*.h")

LIB-I = $(patsubst %,-I%,$(dir $(LIBS)))
LIB-l = $(subst lib,-l,$(basename $(notdir $(LIBSF))))
LIB-L = $(patsubst %,-L$(DIRLIB)%, $(dir $(LIBSF)))

NAME = libpushswap.a
CC = cc

WFLAGS = -Wall -Werror -Wextra
OFLAGS = $(DFLAGS) $(WFLAGS) $(LIB-I) -I$(DIRINC)
CFLAGS = $(DFLAGS) $(LIB-L) $(LIB-l)

ifeq ($(DEBUG),1)
OFLAGS += -g -fsanitize=address
CFLAGS += -g -fsanitize=address
endif

# RULES
all: $(NAME)

# OBJ TO PROJECT
$(NAME): $(LIBS) $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# SOURCE TO OBJ
$(OBJS): $(DIROBJ)%.o : $(DIRSRC)%.c $(INCS)
	@mkdir -p $(dir $@)
	-$(CC) $(OFLAGS) -o $@ -c $<

# COMPILE LIBS
$(LIBS):
	@-echo "\n${GREEN}Compiling Library: ${BLUE}$@ ${NC}"
	@if [ "$(notdir $@)" = "libft.a" ]; then \
		make -s -C $(dir $@) all bonus; \
	else \
		make -s -C $(dir $@) all; \
	fi

# CLEANING
fclean: libclean clean
	-rm -f $(NAME)
	@-echo "${GREEN}DONE CLEANING!${NC}"

libclean_clean = $(dir $(shell find $(DIRLIB) -name "Makefile"))
libclean:
	@-echo "\n${GREEN}Cleaning Libraries: ${CYAN}$(basename $(libclean_clean))${NC}"
	@-$(foreach dir,$(libclean_clean),echo "\n${GREEN}Cleaning: ${CYAN} $(dir) ${NC}";make -i --no-print-directory -C $(dir) clean;)

clean:
	-rm -rf $(DIROBJ)

re: fclean all

.PHONY: all re fclean clean libclean

# COLORS
BLUE = \033[1;34m
CYAN = \033[1;36m
GREEN = \033[1;32m
NC = \033[0m
