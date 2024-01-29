NAME = gray_code
SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS = ${addprefix ${SRCS_DIR}, \
	main.cpp \
	gray_code.cpp}

OBJS = ${SRCS:${SRCS_DIR}%.cpp=${OBJS_DIR}%.o}
DEPS = ${OBJS:%.o=%.d}

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./includes -MMD
LFLAGS = 

${NAME}: ${OBJS_DIR} ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

${OBJS_DIR}%.o: ${SRCS_DIR}%.cpp 
	${CXX} ${CXXFLAGS} -c $< -o $@ ${IFLAGS}

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

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