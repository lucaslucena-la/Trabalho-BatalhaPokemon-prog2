#include "pokemon.h"
#include <iostream>
using namespace std;

// Construtor da classe Pokémon
Pokemon::Pokemon(string nome, string tipo1, string tipo2, int hp, int nivel, int ataque, int defesa, int velocidade, int ataqueEspecial, int defesaEspecial)
    : nome(nome), tipo1(tipo1), tipo2(tipo2), hp(hp), nivel(nivel), ataque(ataque), defesa(defesa), velocidade(velocidade), ataqueEspecial(ataqueEspecial), defesaEspecial(defesaEspecial) {}

// Getters com modificador const
string Pokemon::getNome() const { return nome; }
string Pokemon::getTipo1() const { return tipo1; }
string Pokemon::getTipo2() const { return tipo2; }
int Pokemon::getHP() const { return hp; }
int Pokemon::getNivel() const { return nivel; }
int Pokemon::getAtaque() const { return ataque; }
int Pokemon::getDefesa() const { return defesa; }
int Pokemon::getVelocidade() const { return velocidade; }
int Pokemon::getAtaqueEspecial() const { return ataqueEspecial; }
int Pokemon::getDefesaEspecial() const { return defesaEspecial; }

// Retorna um ataque pelo índice
Ataque Pokemon::getAtaque(int indice) const {
    if (indice >= 0 && indice < ataques.size()) {
        return ataques[indice];
    }
    // Retornar um ataque padrão ou lançar uma exceção (depende da lógica desejada)
    return Ataque("Desconhecido", "Nenhum", 0, 0.0, "Nenhum");
}

// Adicionar ataques ao Pokémon
void Pokemon::adicionarAtaque(Ataque ataque) {
    if (ataques.size() < 4) {
        ataques.push_back(ataque);
    }
}

// Exibir detalhes do Pokémon
void Pokemon::exibirPokemon() const {
    cout << "Pokemon: " << nome << "\nTipo1: " << tipo1 << ", Tipo2: " << tipo2
         << "\nHP: " << hp << "\nNível: " << nivel << "\nAtaque: " << ataque << "\nDefesa: " << defesa
         << "\nVelocidade: " << velocidade << "\nAtaque Especial: " << ataqueEspecial << "\nDefesa Especial: " << defesaEspecial << endl;
}

// Reduzir HP ao receber dano
void Pokemon::receberDano(int dano) {
    hp -= dano;
    if (hp < 0) hp = 0;
}

// Verificar se o Pokémon está derrotado
bool Pokemon::estaDerrotado() const {
    return hp <= 0;
}
