# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbily <fbily@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 18:02:09 by fbily             #+#    #+#              #
#    Updated: 2024/08/23 14:59:38 by fbily            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = c++
CXXFLAGS = -Wall -Wextra -Werror -MMD -g3

NAME = scop

SRCS_DIR	=	srcs/
SRCS_NAME	=	main.cpp \
				shaders.cpp \
				vec3.cpp \
				vec4.cpp \
				mat4.cpp \
				
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_NAME))

OBJS_DIR	=	objs/
OBJ = ${SRCS_NAME:.cpp=.o}
OBJS		= $(addprefix $(OBJS_DIR), $(OBJ))

INC = -I./includes/
DEPS		=	$(addprefix $(OBJS_DIR), $(SRCS_NAME:.cpp=.d))

LIBS = -lGL -lglfw -lGLEW

RM = rm -rf

GREEN = "\033[92m"
CYAN = "\033[96m"
BOLD = "\033[1m"
NC = "\033[0m"

all : ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CXXFLAGS} ${OBJS} -o ${NAME} ${LIBS}
	@echo ${CYAN}${BOLD}Compilation ${NC}[${GREEN}OK${NC}]

${OBJS_DIR}%.o: ${SRCS_DIR}%.cpp
	@mkdir -p $(OBJS_DIR)
	@${CC} ${CXXFLAGS} ${INC} -o $@ -c $<

clean :
	@${RM} ${OBJS_DIR}
	@echo ${CYAN}${BOLD}Objects cleaned${NC}

fclean : clean
	@${RM} ${NAME}
	@echo ${CYAN}${BOLD}Cleanning ${NC}[${GREEN}OK${NC}]

re : fclean all

-include ${DEPS}

.PHONY: all clean fclean