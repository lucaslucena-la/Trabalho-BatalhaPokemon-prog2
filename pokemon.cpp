#include "pokemon.h"  // Inclui o arquivo de cabeçalho da classe Pokemon

// Construtor do Pokémon
// Inicializa os atributos de um Pokémon com os valores fornecidos
Pokemon::Pokemon(string nome, string tipo1, string tipo2, int hp, int nivel, int ataque, int defesa, int velocidade, int ataqueEspecial, int defesaEspecial)
    : nome(nome), tipo1(tipo1), tipo2(tipo2), hp(hp), nivel(nivel), ataque(ataque), defesa(defesa), 
      velocidade(velocidade), ataqueEspecial(ataqueEspecial), defesaEspecial(defesaEspecial), derrotado(false) {}


// Funções "getters" que retornam o valor de cada atributo do Pokémon
string Pokemon::getNome() const { 
    return nome;  // Retorna o nome do Pokémon
}

string Pokemon::getTipo1() const { 
    return tipo1;  // Retorna o primeiro tipo do Pokémon
}

string Pokemon::getTipo2() const { 
    return tipo2;  // Retorna o segundo tipo do Pokémon
}

int Pokemon::getHP() const { 
    return hp;  // Retorna o valor de HP (vida) do Pokémon
}

int Pokemon::getNivel() const { 
    return nivel;  // Retorna o nível do Pokémon
}

int Pokemon::getAtaque() const { 
    return ataque;  // Retorna o valor do ataque do Pokémon
}

int Pokemon::getDefesa() const { 
    return defesa;  // Retorna o valor da defesa do Pokémon
}

int Pokemon::getVelocidade() const { 
    return velocidade;  // Retorna a velocidade do Pokémon
}

int Pokemon::getAtaqueEspecial() const { 
    return ataqueEspecial;  // Retorna o valor de ataque especial do Pokémon
}

int Pokemon::getDefesaEspecial() const { 
    return defesaEspecial;  // Retorna o valor de defesa especial do Pokémon
}

// Função para adicionar um ataque ao Pokémon
// O Pokémon pode ter até 4 ataques, então essa função verifica se o limite foi atingido antes de adicionar
void Pokemon::adicionarAtaque(Ataque ataque) {
    if (ataques.size() < 4) {  // Se o número de ataques for menor que 4
        ataques.push_back(ataque);  // Adiciona o ataque ao vetor de ataques do Pokémon
    }
}

// Função para retornar um ataque específico por índice
// Verifica se o índice fornecido é válido e retorna o ataque correspondente
Ataque Pokemon::getAtaque(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < ataques.size()) {
        return ataques[index];  // Retorna o ataque correspondente ao índice
    }
    return Ataque();  // Se o índice for inválido, retorna um ataque vazio (padrão)
}

// Função para reduzir o HP do Pokémon quando ele recebe dano
void Pokemon::receberDano(int dano) {
    hp -= dano;  // Subtrai o valor do dano do HP atual
    if (hp < 0) {  // Garante que o HP não seja negativo
        hp = 0;
    }
}

// Função para verificar se o Pokémon foi derrotado
// O Pokémon é considerado derrotado quando seu HP é igual a 0
bool Pokemon::estaDerrotado() const {
    return hp == 0;  // Retorna true se o HP for 0, indicando que o Pokémon está derrotado
}

