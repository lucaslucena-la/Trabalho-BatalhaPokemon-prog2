#include "pokemon.h"
#include <iostream>

// Construtor do Pokémon
Pokemon::Pokemon(std::string nome, std::string tipo1, std::string tipo2, int hp, int nivel, int ataque, int defesa, int velocidade, int ataqueEspecial, int defesaEspecial)
    : nome(nome), tipo1(tipo1), tipo2(tipo2), hp(hp), nivel(nivel), ataque(ataque), defesa(defesa), 
      velocidade(velocidade), ataqueEspecial(ataqueEspecial), defesaEspecial(defesaEspecial), derrotado(false) {}

// Getters
std::string Pokemon::getNome() const { return nome; }
std::string Pokemon::getTipo1() const { return tipo1; }
std::string Pokemon::getTipo2() const { return tipo2; }
int Pokemon::getHP() const { return hp; }
int Pokemon::getNivel() const { return nivel; }
int Pokemon::getAtaque() const { return ataque; }
int Pokemon::getDefesa() const { return defesa; }
int Pokemon::getVelocidade() const { return velocidade; }
int Pokemon::getAtaqueEspecial() const { return ataqueEspecial; }
int Pokemon::getDefesaEspecial() const { return defesaEspecial; }

// Adicionar ataque ao Pokémon
void Pokemon::adicionarAtaque(Ataque ataque) {
    if (ataques.size() < 4) {  // Limitar a 4 ataques
        ataques.push_back(ataque);
    }
}

// Retornar um ataque por índice
Ataque Pokemon::getAtaque(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < ataques.size()) {
        return ataques[index];
    }
    return Ataque(); // Retorna um ataque vazio, caso o índice esteja fora dos limites
}

// Reduzir HP após receber dano
void Pokemon::receberDano(int dano) {
    hp -= dano;
    if (hp < 0) {
        hp = 0;  // Garante que o HP não fique negativo
    }
}

// Verifica se o Pokémon está derrotado
bool Pokemon::estaDerrotado() const {
    return hp == 0;  // Considera o Pokémon derrotado se o HP for zero
}

// Exibir os detalhes do Pokémon (para debugging ou exibição durante a batalha)
void Pokemon::exibirPokemon() const {
    std::cout << "Nome: " << nome << "\n"
              << "Tipo: " << tipo1 << " / " << tipo2 << "\n"
              << "HP: " << hp << "\n"
              << "Nível: " << nivel << "\n"
              << "Ataque: " << ataque << "\n"
              << "Defesa: " << defesa << "\n"
              << "Velocidade: " << velocidade << "\n"
              << "Ataque Especial: " << ataqueEspecial << "\n"
              << "Defesa Especial: " << defesaEspecial << "\n";
}
