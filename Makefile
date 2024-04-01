NAME= webserv

CXX= c++
CXXFLAGS= -Wall -Werror -Wextra -std=c++98 -I./inc

SRCS=	src/main.cpp \
		src/server.cpp \
		src/utils.cpp \
		src/webServ.cpp \
		src/client.cpp \
		src/confFile.cpp \
		src/confServer.cpp \
		src/location.cpp

OBJS= $(SRCS:%.cpp=%.o) 

RM= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(HEADER) $(CXXFLAGS) $(OBJS) -o $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
