#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>  // Para sortear ataques aleatórios
#include <cmath>
#include <algorithm> // Para find

using namespace std;



// Função para carregar Pokémons a partir de um arquivo
vector<Pokemon> carregarPokemons(const string& nomeArquivo) {
    vector<Pokemon> pokemons;
    ifstream arquivo(nomeArquivo);
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Pokémons." << endl;
        return pokemons;
    }

    // Ignorar a primeira linha (cabeçalho)
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, tipo1, tipo2;
        int hp = 0, nivel = 0, ataque = 0, defesa = 0, velocidade = 0, ataqueEspecial = 0, defesaEspecial = 0;

        // Ler os dados do arquivo, separando por vírgulas
        getline(ss, nome, ',');
        getline(ss, tipo1, ',');
        getline(ss, tipo2, ',');  // Pode conter "Nenhum" ou estar vazio
        
        if (!(ss >> hp)) {
            cerr << "Erro ao ler o HP de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> nivel)) {
            cerr << "Erro ao ler o Nível de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> ataque)) {
            cerr << "Erro ao ler o Ataque de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> defesa)) {
            cerr << "Erro ao ler a Defesa de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> velocidade)) {
            cerr << "Erro ao ler a Velocidade de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> ataqueEspecial)) {
            cerr << "Erro ao ler o Ataque Especial de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> defesaEspecial)) {
            cerr << "Erro ao ler a Defesa Especial de " << nome << endl;
            continue;
        }

        // Criar o Pokémon e adicioná-lo ao vetor
        Pokemon pokemon(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataqueEspecial, defesaEspecial);
        pokemons.push_back(pokemon);
    }

    arquivo.close();
    return pokemons;
}

// Função para carregar Ataques a partir de um arquivo
vector<Ataque> carregarAtaques(const string& nomeArquivo) {
    vector<Ataque> ataques;
    ifstream arquivo(nomeArquivo);
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Ataques." << endl;
        return ataques;
    }

    // Ignorar a primeira linha (cabeçalho)
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, categoria, tipo;
        int poder = 0;
        float precisao = 0.0;

        getline(ss, nome, ',');
        getline(ss, categoria, ',');

        if (!(ss >> poder)) {
            cerr << "Erro ao ler o Poder de " << nome << endl;
            continue;
        }
        ss.ignore();

        if (!(ss >> precisao)) {
            cerr << "Erro ao ler a Precisão de " << nome << endl;
            continue;
        }
        ss.ignore();

        getline(ss, tipo);

        // Criar o ataque e adicioná-lo ao vetor
        Ataque ataque(nome, categoria, poder, precisao, tipo);
        ataques.push_back(ataque);
    }

    arquivo.close();
    return ataques;
}

// Função para verificar se um ataque pode ser atribuído ao Pokémon
bool podeAtribuirAtaque(const Pokemon& pokemon, const Ataque& ataque) {
    // Ataques do tipo "Normal" podem ser atribuídos a qualquer Pokémon
    if (ataque.getTipo() == "Normal") {
        return true;
    }
    // Ataque deve corresponder ao tipo do Pokémon
    return (ataque.getTipo() == pokemon.getTipo1() || ataque.getTipo() == pokemon.getTipo2());
}

// Função para atribuir ataques aleatórios a cada Pokémon
void atribuirAtaquesAosPokemons(vector<Pokemon>& pokemons, const vector<Ataque>& ataques) {
    random_device rd;  // Gera uma semente aleatória para o gerador de números pseudo-aleatórios
    mt19937 gen(rd()); // Cria o gerador Mersenne Twister inicializado com a semente gerada
    uniform_int_distribution<> dist(0, ataques.size() - 1); // Cria uma distribuição uniforme para sortear ataques (índices de 0 ao tamanho da lista de ataques)

    for (auto& pokemon : pokemons) {
        vector<Ataque> ataquesAtribuidos;  // Vetor temporário para armazenar os ataques já atribuídos a este Pokémon

        while (ataquesAtribuidos.size() < 4) {  // Cada Pokémon deve ter exatamente 4 ataques
            int indice = dist(gen);  // Sorteia um índice aleatório dentro do vetor de ataques
            const Ataque& ataque = ataques[indice];  // Seleciona o ataque com base no índice sorteado

            // Verifica se o ataque é compatível com o Pokémon (regra de tipo) e se ainda não foi atribuído
            if (podeAtribuirAtaque(pokemon, ataque)) {
                bool ataqueJaAtribuido = false;
                
                // Verifica se o ataque já foi atribuído ao Pokémon para evitar repetições
                for (const auto& a : ataquesAtribuidos) {
                    if (a.getNome() == ataque.getNome()) {  // Se já houver um ataque com o mesmo nome
                        ataqueJaAtribuido = true;
                        break;  // Para o loop, pois o ataque já foi atribuído
                    }
                }

                // Se o ataque ainda não foi atribuído, adiciona ao Pokémon
                if (!ataqueJaAtribuido) {
                    pokemon.adicionarAtaque(ataque);  // Atribui o ataque ao Pokémon
                    ataquesAtribuidos.push_back(ataque);  // Armazena o ataque para controle
                }
            }
        }
    }
}

// Função para gerar um valor crítico (1 ou 2)
int calcularCritico() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 16);
    return (dist(gen) == 1) ? 2 : 1;  // 1/16 de chance de ser crítico
}

// Função para gerar o fator aleatório entre 217 e 255
int calcularAleatorio() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(217, 255);
    return dist(gen);
}

// Função para calcular a eficácia do ataque
float calcularEficacia(const Ataque& ataque, const Pokemon& defensor) {
    // Por simplicidade, vamos assumir que a eficácia pode ser 2x, 0.5x ou 1x
    // Isso deve ser ajustado com base nos tipos do ataque e do Pokémon defensor
    // Exemplo simplificado (a lógica completa precisaria de uma tabela de tipos):
    if (ataque.getTipo() == "Agua" && defensor.getTipo1() == "Fogo") return 2.0;
    if (ataque.getTipo() == "Fogo" && defensor.getTipo1() == "Agua") return 0.5;
    return 1.0;  // Caso não seja super eficaz ou pouco eficaz
}

// Função para calcular o STAB (Same Type Attack Bonus)
float calcularSTAB(const Ataque& ataque, const Pokemon& atacante) {
    if (ataque.getTipo() == atacante.getTipo1() || ataque.getTipo() == atacante.getTipo2()) {
        return 1.5;  // STAB aplicado
    }
    return 1.0;  // Sem STAB
}

// Função para calcular o dano total de um ataque
int calcularDano(const Pokemon& atacante, const Pokemon& defensor, const Ataque& ataque) {
    int nivel = atacante.getNivel();
    int poder = ataque.getPoder();
    int ataqueStat = (ataque.getCategoria() == "Fisico") ? atacante.getAtaque() : atacante.getAtaqueEspecial();
    int defesaStat = (ataque.getCategoria() == "Fisico") ? defensor.getDefesa() : defensor.getDefesaEspecial();

    int critico = calcularCritico();
    float STAB = calcularSTAB(ataque, atacante);
    float eficacia = calcularEficacia(ataque, defensor);
    int aleatorio = calcularAleatorio();

    // Cálculo do dano
    int danoBase = (((2 * nivel * poder * ataqueStat / defesaStat) / 50) + 2);
    int danoFinal = (((danoBase * critico * STAB * eficacia * aleatorio) / 255));

    // Exibir se foi crítico
    if (critico == 2) {
        cout << "Foi um golpe crítico!" << endl;
    }

    // Exibir se foi super eficaz ou não
    if (eficacia > 1.0) {
        cout << "Foi super eficaz!" << endl;
    } else if (eficacia < 1.0) {
        cout << "Não foi muito eficaz..." << endl;
    }

    return danoFinal;
}

// Função para a CPU escolher um ataque aleatório
int escolherAtaqueCPU(const Pokemon& cpuPokemon, const Pokemon& jogadorPokemon, int dificuldade) {
    if (dificuldade == 1) {
        // Escolhe um ataque aleatório no modo fácil
        return rand() % 4;
    } else {
        // Escolhe o ataque mais eficaz no modo médio/difícil
        int melhorAtaque = 0;
        float melhorDano = 0;
        for (int i = 0; i < 4; ++i) {
            Ataque ataque = cpuPokemon.getAtaque(i);
            float danoEstimado = calcularDano(cpuPokemon, jogadorPokemon, ataque);
            if (danoEstimado > melhorDano) {
                melhorDano = danoEstimado;
                melhorAtaque = i;
            }
        }
        return melhorAtaque;
    }
}

// Função para sortear três Pokémons aleatórios para o jogador e para a CPU
void sortearPokemons(const vector<Pokemon>& todosPokemons, vector<Pokemon>& jogadorPokemons, vector<Pokemon>& cpuPokemons, int dificuldade) {
    
    // Criação de um gerador de números aleatórios
    random_device rd;
    mt19937 gen(rd());

    // Cria uma distribuição uniforme para escolher índices aleatórios dentro do intervalo de pokémons disponíveis
    uniform_int_distribution<> dist(0, todosPokemons.size() - 1);

    // Vetor para armazenar os índices dos Pokémons já sorteados (para evitar repetição)
    vector<int> indicesUsados;

    // Sorteia três Pokémons para o jogador
    while (jogadorPokemons.size() < 3) {
        // Sorteia um índice aleatório entre os Pokémons disponíveis
        int indice = dist(gen);
        // Verifica se o índice sorteado já foi usado
        if (find(indicesUsados.begin(), indicesUsados.end(), indice) == indicesUsados.end()) {
            // Se o índice ainda não foi usado, adiciona o Pokémon sorteado ao vetor do jogador
            jogadorPokemons.push_back(todosPokemons[indice]);
            // Marca o índice como usado
            indicesUsados.push_back(indice);
        }
    }

    // Inicializa as variáveis para armazenar o nível mínimo e máximo dos Pokémons do jogador
    int nivelMinimoJogador = jogadorPokemons[0].getNivel();
    int nivelMaximoJogador = jogadorPokemons[0].getNivel();

    // Loop para encontrar o Pokémon mais fraco (nível mínimo) e o mais forte (nível máximo) do jogador
    for (const auto& pokemon : jogadorPokemons) {
        if (pokemon.getNivel() < nivelMinimoJogador) {
            // Atualiza o nível mínimo se o Pokémon atual tiver um nível menor
            nivelMinimoJogador = pokemon.getNivel();
        }
        if (pokemon.getNivel() > nivelMaximoJogador) {
            // Atualiza o nível máximo se o Pokémon atual tiver um nível maior
            nivelMaximoJogador = pokemon.getNivel();
        }
    }

    // Vetor para armazenar os Pokémons elegíveis para a CPU, de acordo com a dificuldade
    vector<Pokemon> pokemonsElegiveis;

    // Loop para filtrar Pokémons da CPU com base na dificuldade
    for (size_t i = 0; i < todosPokemons.size(); ++i) {
        // Verifica se o Pokémon ainda não foi sorteado para o jogador (não está em indicesUsados)
        if (find(indicesUsados.begin(), indicesUsados.end(), i) == indicesUsados.end()) {
            // Se a dificuldade for "Fácil"
            if (dificuldade == 1) {
                // Adiciona apenas os Pokémons cujo nível seja menor ou igual ao do Pokémon mais fraco do jogador
                if (todosPokemons[i].getNivel() <= nivelMinimoJogador) {
                    pokemonsElegiveis.push_back(todosPokemons[i]);
                }
            }
            // Se a dificuldade for "Médio"
            else if (dificuldade == 2) {
                // Adiciona os Pokémons cujo nível seja menor ou igual ao do Pokémon mais forte do jogador
                if (todosPokemons[i].getNivel() <= nivelMaximoJogador) {
                    pokemonsElegiveis.push_back(todosPokemons[i]);
                }
            }
            // Se a dificuldade for "Difícil"
            else if (dificuldade == 3) {
                // Adiciona os Pokémons cujo nível seja maior ou igual ao do Pokémon mais forte do jogador
                if (todosPokemons[i].getNivel() >= nivelMaximoJogador) {
                    pokemonsElegiveis.push_back(todosPokemons[i]);
                }
            }
        }
    }

    // Sorteia três Pokémons para a CPU a partir da lista de Pokémons elegíveis
    while (cpuPokemons.size() < 3) {
        // Se a lista de Pokémons elegíveis estiver vazia, exibe uma mensagem de erro e sai
        if (pokemonsElegiveis.empty()) {
            cerr << "Erro: Não há Pokémons elegíveis suficientes para a CPU!" << endl;
            return;
        }

        // Sorteia um índice da lista de Pokémons elegíveis
        uniform_int_distribution<> distElegivel(0, pokemonsElegiveis.size() - 1);
        int indice = distElegivel(gen);
        // Adiciona o Pokémon sorteado à lista da CPU
        cpuPokemons.push_back(pokemonsElegiveis[indice]);
        // Remove o Pokémon sorteado da lista para evitar repetição
        pokemonsElegiveis.erase(pokemonsElegiveis.begin() + indice);
    }
}

/************************* FUNÇÕES DO RANKING **************************/

// Função para carregar o ranking a partir de um arquivo
// Se o arquivo não existir ou não puder ser aberto, retorna um ranking inicial com 0 vitórias, derrotas e pontuação
Ranking carregarRanking(const std::string& nomeArquivo) {
    Ranking ranking = {0, 0, 0, 0, 0};  // Inicializa o ranking com valores padrão
    std::ifstream arquivo(nomeArquivo);  // Abre o arquivo de ranking para leitura

    if (arquivo.is_open()) {
        // Carrega todas as informações de vitórias, derrotas e pontuação
        arquivo >> ranking.vitoriasFacil >> ranking.vitoriasMedio 
                >> ranking.vitoriasDificil >> ranking.derrotas >> ranking.pontuacao;
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo de ranking: " << nomeArquivo << std::endl;
    }

    return ranking;
}

// Função para salvar o ranking em um arquivo
// O ranking é salvo em formato de texto, com vitórias, derrotas e pontuação separadas por espaço
void salvarRanking(const Ranking& ranking, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);  // Abre o arquivo de ranking para escrita
    if (arquivo.is_open()) {
        // Salva todas as informações de vitórias, derrotas e pontuação no arquivo
        arquivo << ranking.vitoriasFacil << " " 
                << ranking.vitoriasMedio << " " 
                << ranking.vitoriasDificil << " " 
                << ranking.derrotas << " " 
                << ranking.pontuacao << "\n";
        arquivo.close();  // Fecha o arquivo após a gravação
        std::cout << "Ranking salvo com sucesso no arquivo: " << nomeArquivo << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo de ranking para escrita: " << nomeArquivo << std::endl;
    }
}



// Função para exibir o ranking no console
// Exibe o número de vitórias, derrotas e a pontuação acumulada pelo jogador
void exibirRanking(const Ranking& ranking) {
    std::cout << "\n----- Ranking -----\n";
    std::cout << "Vitórias (Fácil): " << ranking.vitoriasFacil << "\n";     // Vitórias no modo Fácil
    std::cout << "Vitórias (Médio): " << ranking.vitoriasMedio << "\n";     // Vitórias no modo Médio
    std::cout << "Vitórias (Difícil): " << ranking.vitoriasDificil << "\n"; // Vitórias no modo Difícil
    std::cout << "Derrotas: " << ranking.derrotas << "\n";                  // Total de derrotas
    std::cout << "Pontuação: " << ranking.pontuacao << "\n";                // Pontuação total
    std::cout << "-------------------\n";
}

// Função para atualizar o ranking após uma vitória
// A pontuação é incrementada com base na dificuldade: Fácil = 10, Médio = 20, Difícil = 30 pontos
void atualizarRanking(Ranking& ranking, int dificuldade) {
    // Atualiza a pontuação e as vitórias com base na dificuldade
    if (dificuldade == 1) {
        ranking.vitoriasFacil++;     // Incrementa vitórias no modo Fácil
        ranking.pontuacao += 10;     // Modo Fácil adiciona 10 pontos
    } else if (dificuldade == 2) {
        ranking.vitoriasMedio++;     // Incrementa vitórias no modo Médio
        ranking.pontuacao += 20;     // Modo Médio adiciona 20 pontos
    } else if (dificuldade == 3) {
        ranking.vitoriasDificil++;   // Incrementa vitórias no modo Difícil
        ranking.pontuacao += 30;     // Modo Difícil adiciona 30 pontos
    }
}


// Função para atualizar o ranking após uma derrota
// Apenas incrementa o número de derrotas, sem alterar a pontuação
void atualizarDerrota(Ranking& ranking) {
    ranking.derrotas++;  // Incrementa o número de derrotas
}

void reiniciarRanking(Ranking& ranking) {
    // Redefine todas as variáveis do ranking para zero
    ranking.vitoriasFacil = 0;
    ranking.vitoriasMedio = 0;
    ranking.vitoriasDificil = 0;
    ranking.derrotas = 0;
    ranking.pontuacao = 0;
    
    // Salva o ranking zerado no arquivo
    salvarRanking(ranking, "ranking.txt");
    
    std::cout << "Ranking reiniciado com sucesso!" << std::endl;
}
