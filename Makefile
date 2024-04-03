.PHONY: all clean fclean

#CORES
RESETAR		=		"\033[0m"
BRANCO		=		"\033[1;37m"
PRETO		=		"\033[30m"
VERMELHO	=		"\033[31m"
VERDE		=		"\033[32m"
AMARELO		=		"\033[33m"
AZUL		=		"\033[34m"
ROXO		=		"\033[35m"
CIANO		=		"\033[36m"
CINZA		=		"\033[37m"

#CORES BACKGROUND
BRANCO_BACK		=		"\033[7m"
PRETO_BACK		=		"\033[40m"
VERMELHO_BACK	=		"\033[41m"
VERDE_BACK		=		"\033[42m"
AMARELO_BACK	=		"\033[43m"
AZUL_BACK		=		"\033[44m"
ROXO_BACK		=		"\033[45m"
CIANO_BACK		=		"\033[46m"
CINZA_BACK		=		"\033[47m"

#EXECUTAVEIS
NAME = webserv
NAME_A = $(NAME).a

#DIRETORIOS
SRC_DIR = src/
OBJ_DIR = .obj/

#ARQUIVOS
SRCS =	$(SRC_DIR)server.cpp \
		$(SRC_DIR)utils.cpp \
		$(SRC_DIR)webServ.cpp \
		$(SRC_DIR)client.cpp \
		$(SRC_DIR)confFile.cpp \
		$(SRC_DIR)confServer.cpp \
		$(SRC_DIR)location.cpp



#ARQUIVOS .o
OBJS = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))


#MAIN
MAIN = $(SRC_DIR)main.cpp

#COMANDOS
CXX = c++
AR = ar rcs
RM = rm -f
MKDIR = mkdir -p

#FLAGS
CXXFLAGS = -g -Werror -Wextra -Wall -I./inc -std=c++98
OUTPUT = -o

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(MAIN) $(OBJS) $(CXXFLAGS) $(OUTPUT) $(NAME)
	@echo $(VERDE)"Criando executavel\t webserv" $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(MKDIR) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo $(AMARELO)"Compilando\t\t" $(<:src/%=%) $(BRANCO) "  [" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)


clean:
	@$(RM) $(OBJ_DIR)*.o
	@echo $(VERMELHO)"Removendo objetos\t .o" $(BRANCO) "  [" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)
	@echo $(VERMELHO)"Removendo executavel     webserv"$(BRANCO) "  [" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)

re: fclean all

git:
	git add *
	git commit -m .
	git push
