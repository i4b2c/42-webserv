NAME= webserv

CXX= c++
CXXFLAGS= -Wall -Werror -Wextra -std=c++98

SRCS=	main.cpp \
		server.cpp \
		utils.cpp \
		webServ.cpp \
		client.cpp

OBJS= $(SRCS:%.cpp=%.o) 

RM= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all