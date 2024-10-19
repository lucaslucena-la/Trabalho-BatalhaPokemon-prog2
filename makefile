# Definir o compilador
CXX = g++

# Definir as flags de compilação
CXXFLAGS = -std=c++11 -Wall

# Arquivos de código fonte e cabeçalhos
SRC = main.cpp game.cpp pokemon.cpp ataque.cpp
HEADERS = game.h pokemon.h ataque.h

# Nome do executável
TARGET = pokemon_battle

# Regras
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpar os arquivos gerados
clean:
	rm -f $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

