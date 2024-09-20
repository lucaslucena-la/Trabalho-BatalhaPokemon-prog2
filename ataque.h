#ifndef ATAQUE_H
#define ATAQUE_H

#include <string>

class Ataque {
private:
    std::string nome;
    std::string categoria;  // Físico ou Especial
    int poder;
    float precisao;
    std::string tipo;

public:
    // Construtor
    Ataque(std::string nome, std::string categoria, int poder, float precisao, std::string tipo);

    // Getters
    std::string getNome() const;
    std::string getCategoria() const;
    int getPoder() const;
    float getPrecisao() const;
    std::string getTipo() const;
};

#endif // ATAQUE_H
