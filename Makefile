CFLAGS = -Wall -Wextra -Werror

BIN = libft_test

ALL_FUNCS = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
            ft_toupper ft_tolower ft_strlen ft_memset ft_bzero \
            ft_memcpy ft_memmove ft_memcmp ft_memchr ft_strncmp \
            ft_atoi ft_strdup ft_calloc ft_strchr ft_strrchr \
            ft_strlcpy ft_strlcat ft_strnstr ft_substr ft_strjoin \
            ft_strtrim ft_itoa ft_strmapi ft_striteri ft_split \
            ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
            ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
            ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

ifndef SRC
 ifneq (,$(wildcard .srcpath))
  SRC := $(shell cat .srcpath)
 endif
endif

help:
	@printf "\033[0;36m"
	@printf "/* *************************************************************************** */\n"
	@printf "/*                                                                             */\n"
	@printf "/*                                                         :::      ::::::::   */\n"
	@printf "/*                                                         :+:      :+:    :+: */\n"
	@printf "/*   libft tests                                       +:+ +:+         +:+     */\n"
	@printf "/*                                                    +#+  +:+       +#+       */\n"
	@printf "/*                                                 +#+#+#+#+#+   +#+           */\n"
	@printf "/*                                                       #+#    #+#            */\n"
	@printf "/*                                                      ###   ########.fr      */\n"
	@printf "/*                                                                             */\n"
	@printf "/* *************************************************************************** */\n"
	@printf "\033[0m\n"
	@printf "  make setup SRC=~/libft/src/                        save source path\n"
	@printf "\n"
	@printf "  make test                                          run all tests\n"
	@printf "\n"
	@printf "  make test-ft_strlen                                test a single function\n"
	@printf "\n"
	@printf "  make clean                                         clean object files\n"
	@printf "\n"

setup:
ifndef SRC
	@echo "Usage: make setup SRC=~/libft/src/"
else
	@echo "$(SRC)" > .srcpath
	@echo "SRC set to $(SRC)"
endif

ifndef SRC
all test clean:
	@$(MAKE) --no-print-directory help
test-%:
	@$(MAKE) --no-print-directory help
else
SRCS = $(wildcard $(SRC)/ft_*.c)
OBJS = $(SRCS:.c=.o)

avail.h:
	@for f in $(ALL_FUNCS); do \
		deps=""; \
		case $$f in \
			ft_calloc)       deps="ft_bzero" ;; \
			ft_isalnum)      deps="ft_isalpha ft_isdigit" ;; \
			ft_putstr_fd)    deps="ft_strlen" ;; \
			ft_putendl_fd)   deps="ft_putchar_fd ft_putstr_fd ft_strlen" ;; \
			ft_strdup)       deps="ft_memcpy ft_strlen" ;; \
			ft_strjoin)      deps="ft_strlen" ;; \
			ft_strlcpy)      deps="ft_memcpy ft_strlen" ;; \
			ft_strmapi)      deps="ft_strlen" ;; \
			ft_strtrim)      deps="ft_memcpy ft_strlen" ;; \
			ft_substr)       deps="ft_strlen" ;; \
			ft_lstadd_front) deps="ft_lstnew" ;; \
			ft_lstsize)      deps="ft_lstnew" ;; \
			ft_lstlast)      deps="ft_lstnew" ;; \
			ft_lstadd_back)  deps="ft_lstnew ft_lstlast" ;; \
			ft_lstdelone)    deps="ft_lstnew" ;; \
			ft_lstclear)     deps="ft_lstnew" ;; \
			ft_lstiter)      deps="ft_lstnew" ;; \
			ft_lstmap)       deps="ft_lstnew ft_lstclear ft_lstsize" ;; \
		esac; \
		avail=1; \
		if [ ! -f "$(SRC)/$$f.c" ]; then avail=0; fi; \
		for d in $$deps; do \
			if [ ! -f "$(SRC)/$$d.c" ]; then avail=0; fi; \
		done; \
		echo "#define AVAIL_$$f $$avail"; \
	done > $@

all: $(BIN)

$(BIN): libft_test.c libft_stubs.c avail.h $(OBJS)
	$(CC) $(CFLAGS) -Wl,--wrap=malloc,--wrap=free -o $@ libft_test.c libft_stubs.c $(OBJS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	./$(BIN)

test-%: all
	./$(BIN) $*

clean:
	rm -f $(OBJS) $(BIN) avail.h
endif

.PHONY: help setup all test test-% clean avail.h
