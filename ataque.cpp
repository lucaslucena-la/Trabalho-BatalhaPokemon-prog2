#include "ataque.h"

// Construtor padrão
Ataque::Ataque() : nome(""), categoria(""), poder(0), precisao(0.0), tipo("") {}

// Construtor personalizado
Ataque::Ataque(std::string nome, std::string categoria, int poder, float precisao, std::string tipo)
    : nome(nome), categoria(categoria), poder(poder), precisao(precisao), tipo(tipo) {}

// Getters
std::string Ataque::getNome() const { return nome; }
std::string Ataque::getCategoria() const { return categoria; }
std::string Ataque::getTipo() const { return tipo; }
int Ataque::getPoder() const { return poder; }
float Ataque::getPrecisao() const { return precisao; }
