NAME = cnf
SRCS_DIR = srcs/
OBJS_DIR = objs/
AST_DIR = Ast/

SRCS = ${addprefix ${SRCS_DIR}, \
	main.cpp \
	Node.cpp \
	negation_normal_form.cpp \
	conjunctive_normal_form.cpp \
	}

SRCS += ${addprefix ${SRCS_DIR}${AST_DIR}, \
	Ast.cpp \
	Ast_print.cpp \
	Ast_evaluation.cpp \
	Ast_truth_table.cpp \
	Ast_negative_normal_form.cpp \
	}

OBJS = ${SRCS:${SRCS_DIR}%.cpp=${OBJS_DIR}%.o}
DEPS = ${OBJS:%.o=%.d}

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./includes -MMD
LFLAGS = 

${NAME}: ${OBJS_DIR} ${OBJS_DIR}${AST_DIR} ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

${OBJS_DIR}%.o: ${SRCS_DIR}%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ ${IFLAGS}

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

${OBJS_DIR}${AST_DIR}:
	mkdir -p ${OBJS_DIR}${AST_DIR}

.PHONY: all
all: ${NAME}

.PHONY: clean
clean:
	rm -rf ${OBJS_DIR}

.PHONY: fclean
fclean: clean
	rm -rf ${NAME}

.PHONY: re
re: fclean
	make -C .

-include ${DEPS}