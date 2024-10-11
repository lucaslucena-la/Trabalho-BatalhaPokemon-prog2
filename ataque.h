#ifndef ATAQUE_H
#define ATAQUE_H

#include <string>

class Ataque {
private:
    std::string nome;
    std::string categoria;
    int poder;
    float precisao;
    std::string tipo;

public:
    // Construtor padrão
    Ataque();

    // Construtor personalizado (sem qualificação "Ataque::")
    Ataque(std::string nome, std::string categoria, int poder, float precisao, std::string tipo);

    // Getters e outros métodos...
    std::string getNome() const;
    std::string getCategoria() const;
    std::string getTipo() const;
    int getPoder() const;
    float getPrecisao() const;
};

#endif // ATAQUE_H
