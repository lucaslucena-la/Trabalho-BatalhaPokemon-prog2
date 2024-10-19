#include "game.h"  // Inclui o cabeçalho do jogo, onde estão declaradas as funções e estruturas necessárias

using namespace std;

// Função para exibir o menu principal do jogo
void exibirMenu() {
    cout << "----- Menu -----" << endl;
    cout << "1. Iniciar Batalha" << endl;
    cout << "2. Ajustar Dificuldade" << endl;
    cout << "3. Visualizar Ranking" << endl;
    cout << "4. Reiniciar Ranking" << endl;
    cout << "5. Sair" << endl;  // Opção para sair do jogo
    cout << "Escolha uma opção: ";  // Solicita que o jogador escolha uma opção
}

// Função para ajustar a dificuldade do jogo
int ajustarDificuldade() {
    int novaDificuldade;
    // Exibe as opções de dificuldade
    cout << "\nEscolha a dificuldade:" << endl;
    cout << "1. Fácil" << endl;
    cout << "2. Médio" << endl;
    cout << "3. Difícil" << endl;
    cout << "Escolha: ";
    cin >> novaDificuldade;  // Lê a escolha do jogador

    // Verifica se a opção escolhida é válida
    if (novaDificuldade >= 1 && novaDificuldade <= 3) {
        return novaDificuldade;  // Retorna a dificuldade escolhida
    } else {
        // Se a escolha for inválida, mantém a dificuldade no modo "Fácil"
        cout << "Opção inválida! Dificuldade será mantida." << endl;
        return 1;  // Retorna a dificuldade "Fácil" por padrão
    }
}

// Função para exibir o ranking com as vitórias e derrotas do jogador
void exibirRanking(int vitorias, int derrotas) {
    cout << "\n----- Ranking -----" << endl;
    cout << "Vitórias: " << vitorias << endl;  // Exibe o número de vitórias
    cout << "Derrotas: " << derrotas << endl;  // Exibe o número de derrotas
    cout << "-------------------" << endl;
}

// Função para o jogador trocar de Pokémon durante a batalha
Pokemon& trocarPokemonJogador(vector<Pokemon>& jogadorPokemons) {
    while (true) {
        cout << "\nEscolha um Pokémon para continuar a batalha:" << endl;
        bool pokemonDisponivel = false;  // Flag para verificar se há Pokémons disponíveis

        // Exibe os Pokémons disponíveis (não derrotados)
        for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
            if (!jogadorPokemons[i].estaDerrotado()) {  // Verifica se o Pokémon não foi derrotado
                cout << i + 1 << ". " << jogadorPokemons[i].getNome() 
                     << " (HP: " << jogadorPokemons[i].getHP() << ")" << endl;
                pokemonDisponivel = true;  // Indica que há Pokémons disponíveis
            }
        }

        // Se todos os Pokémons do jogador foram derrotados, o jogo termina
        if (!pokemonDisponivel) {
            cout << "Todos os seus Pokémons foram derrotados!" << endl;
            exit(0);  // Encerra o jogo
        }

        int escolha;
        cin >> escolha;
        escolha -= 1;  // Ajusta o índice do Pokémon escolhido (baseado em 0)

        // Verifica se o Pokémon escolhido está disponível e não foi derrotado
        if (escolha >= 0 && static_cast<size_t>(escolha) < jogadorPokemons.size() && !jogadorPokemons[escolha].estaDerrotado()) {
            return jogadorPokemons[escolha];  // Retorna o Pokémon escolhido
        } else {
            // Mensagem de erro se o Pokémon escolhido estiver derrotado ou for uma escolha inválida
            cout << "Este Pokémon já foi derrotado ou a escolha é inválida! Escolha outro." << endl;
        }
    }
}

// Função para a CPU trocar de Pokémon durante a batalha
Pokemon& trocarPokemonCPU(vector<Pokemon>& cpuPokemons) {
    for (size_t i = 0; i < cpuPokemons.size(); ++i) {
        if (!cpuPokemons[i].estaDerrotado()) {
            return cpuPokemons[i];  // Retorna o primeiro Pokémon não derrotado da CPU
        }
    }
    // Caso todos os Pokémons da CPU tenham sido derrotados, lança uma exceção
    throw runtime_error("Todos os Pokémons da CPU foram derrotados!");
}

// Função para exibir o histórico de batalha
void exibirHistoricoDeBatalha(const vector<string>& log) {
    cout << "\n----- Histórico de Batalha -----\n";
    for (const auto& entrada : log) {
        cout << entrada << endl;  // Exibe cada entrada do histórico
    }
    cout << "-------------------------------\n";
}

// Função para exibir os ataques de um Pokémon
void exibirAtaques(const Pokemon& pokemon) {
    cout << "\nAtaques disponíveis:\n";
    for (int i = 0; i < 4; ++i) {
        Ataque ataque = pokemon.getAtaque(i);  // Obtém o ataque correspondente ao índice
        cout << i + 1 << ". " << ataque.getNome() << " - Tipo: " << ataque.getTipo() 
             << " (Categoria: " << ataque.getCategoria() << ")\n";  // Exibe os detalhes do ataque
    }
}

// Função para a CPU escolher um ataque aleatório
int escolherAtaqueCPU(const Pokemon& pokemon) {
    random_device rd;
    mt19937 gen(rd());  // Cria um gerador de números aleatórios
    uniform_int_distribution<> dist(0, 3);  // Define a distribuição para escolher um dos 4 ataques
    return dist(gen);  // Retorna um índice aleatório entre 0 e 3
}

// Função para verificar se todos os Pokémons de um jogador foram derrotados
bool todosDerrotados(const vector<Pokemon>& pokemons) {
    for (const auto& p : pokemons) {
        if (!p.estaDerrotado()) {
            return false;  // Retorna falso se algum Pokémon ainda estiver vivo
        }
    }
    return true;  // Retorna verdadeiro se todos os Pokémons foram derrotados
}

// Função para remover os Pokémons derrotados de uma lista
void removerPokemonsDerrotados(vector<Pokemon>& pokemons) {
    pokemons.erase(remove_if(pokemons.begin(), pokemons.end(),
        [](const Pokemon& p) { return p.estaDerrotado(); }), pokemons.end());  // Remove os Pokémons derrotados
}

// Função para carregar Pokémons a partir de um arquivo
vector<Pokemon> carregarPokemons(const string& nomeArquivo) {
    vector<Pokemon> pokemons;  // Vetor que irá armazenar os Pokémons carregados
    ifstream arquivo(nomeArquivo);  // Abre o arquivo com os dados dos Pokémons
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Pokémons." << endl;
        return pokemons;  // Retorna um vetor vazio se o arquivo não puder ser aberto
    }

    // Ignora a primeira linha (cabeçalho do arquivo)
    getline(arquivo, linha);

    // Lê o arquivo linha por linha
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, tipo1, tipo2;
        int hp = 0, nivel = 0, ataque = 0, defesa = 0, velocidade = 0, ataqueEspecial = 0, defesaEspecial = 0;

        // Extrai os dados do Pokémon da linha
        getline(ss, nome, ',');
        getline(ss, tipo1, ',');
        getline(ss, tipo2, ',');  // Tipo secundário pode estar vazio ou ser "Nenhum"
        
        ss >> hp >> nivel >> ataque >> defesa >> velocidade >> ataqueEspecial >> defesaEspecial;

        // Cria um Pokémon com os dados lidos e adiciona ao vetor
        Pokemon pokemon(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataqueEspecial, defesaEspecial);
        pokemons.push_back(pokemon);  // Adiciona o Pokémon ao vetor
    }

    arquivo.close();  // Fecha o arquivo
    return pokemons;  // Retorna o vetor de Pokémons carregados
}

// Função para carregar Ataques a partir de um arquivo
vector<Ataque> carregarAtaques(const string& nomeArquivo) {
    vector<Ataque> ataques;  // Vetor para armazenar os ataques carregados
    ifstream arquivo(nomeArquivo);
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de Ataques." << endl;
        return ataques;  // Retorna um vetor vazio se o arquivo não puder ser aberto
    }

    // Ignora a primeira linha (cabeçalho)
    getline(arquivo, linha);

    // Lê cada linha do arquivo
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, categoria, tipo;
        int poder = 0;
        float precisao = 0.0;

        // Lê os dados de cada ataque
        getline(ss, nome, ',');
        getline(ss, categoria, ',');
        ss >> poder >> precisao;  // Lê o poder e a precisão do ataque
        getline(ss, tipo, ',');

        // Cria um ataque com os dados lidos e adiciona ao vetor
        Ataque ataque(nome, categoria, poder, precisao, tipo);
        ataques.push_back(ataque);
    }

    arquivo.close();  // Fecha o arquivo
    return ataques;  // Retorna o vetor de ataques carregados
}

// Função para verificar se um ataque pode ser atribuído a um Pokémon com base em seu tipo
bool podeAtribuirAtaque(const Pokemon& pokemon, const Ataque& ataque) {
    // Ataques do tipo "Normal" podem ser atribuídos a qualquer Pokémon
    if (ataque.getTipo() == "Normal") {
        return true;
    }
    // Ataque só pode ser atribuído se for do mesmo tipo do Pokémon
    return (ataque.getTipo() == pokemon.getTipo1() || ataque.getTipo() == pokemon.getTipo2());
}

// Função para atribuir quatro ataques aleatórios a cada Pokémon
void atribuirAtaquesAosPokemons(vector<Pokemon>& pokemons, const vector<Ataque>& ataques) {
    random_device rd;  // Gerador de números aleatórios
    mt19937 gen(rd());  // Inicializa o gerador com uma semente
    uniform_int_distribution<> dist(0, ataques.size() - 1);  // Cria uma distribuição para sorteio de ataques

    for (auto& pokemon : pokemons) {
        vector<Ataque> ataquesAtribuidos;  // Armazena os ataques já atribuídos ao Pokémon

        while (ataquesAtribuidos.size() < 4) {  // Cada Pokémon deve ter 4 ataques
            int indice = dist(gen);  // Sorteia um índice
            const Ataque& ataque = ataques[indice];  // Obtém o ataque sorteado

            // Verifica se o ataque é compatível e ainda não foi atribuído
            if (podeAtribuirAtaque(pokemon, ataque)) {
                bool ataqueJaAtribuido = false;
                // Verifica se o ataque já foi atribuído
                for (const auto& a : ataquesAtribuidos) {
                    if (a.getNome() == ataque.getNome()) {
                        ataqueJaAtribuido = true;
                        break;
                    }
                }

                // Se o ataque não foi atribuído ainda, adiciona ao Pokémon
                if (!ataqueJaAtribuido) {
                    pokemon.adicionarAtaque(ataque);
                    ataquesAtribuidos.push_back(ataque);
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
    return dist(gen);  // Retorna o fator aleatório entre 217 e 255
}

// Função para calcular a eficácia do ataque
float calcularEficacia(const Ataque& ataque, const Pokemon& defensor) {
    // Por simplicidade, assume-se que a eficácia pode ser 2x, 0.5x ou 1x
    // Exemplo simplificado de lógica de tipos
    if (ataque.getTipo() == "Agua" && defensor.getTipo1() == "Fogo") return 2.0;
    if (ataque.getTipo() == "Fogo" && defensor.getTipo1() == "Agua") return 0.5;
    return 1.0;  // Caso o ataque não tenha vantagem ou desvantagem de tipo
}

// Função para calcular o STAB (Same Type Attack Bonus)
float calcularSTAB(const Ataque& ataque, const Pokemon& atacante) {
    // Se o tipo do ataque for o mesmo de algum dos tipos do Pokémon, aplica STAB
    if (ataque.getTipo() == atacante.getTipo1() || ataque.getTipo() == atacante.getTipo2()) {
        return 1.5;  // STAB (bônus de ataque)
    }
    return 1.0;  // Sem STAB
}

// Função para calcular o dano total de um ataque
int calcularDano(const Pokemon& atacante, const Pokemon& defensor, const Ataque& ataque) {
    int nivel = atacante.getNivel();  // Nível do Pokémon atacante
    int poder = ataque.getPoder();  // Poder do ataque
    int ataqueStat = (ataque.getCategoria() == "Fisico") ? atacante.getAtaque() : atacante.getAtaqueEspecial();  // Determina o atributo de ataque (físico ou especial)
    int defesaStat = (ataque.getCategoria() == "Fisico") ? defensor.getDefesa() : defensor.getDefesaEspecial();  // Determina o atributo de defesa (físico ou especial)

    int critico = calcularCritico();  // Calcula se o ataque foi um golpe crítico
    float STAB = calcularSTAB(ataque, atacante);  // Calcula o bônus STAB (se aplicável)
    float eficacia = calcularEficacia(ataque, defensor);  // Calcula a eficácia do ataque
    int aleatorio = calcularAleatorio();  // Fator aleatório no cálculo do dano

    // Cálculo do dano base
    int danoBase = (((2 * nivel * poder * ataqueStat / defesaStat) / 50) + 2);
    int danoFinal = (((danoBase * critico * STAB * eficacia * aleatorio) / 255));

    // Exibe se foi um golpe crítico
    if (critico == 2) {
        cout << "Foi um golpe crítico!" << endl;
    }

    // Exibe se foi super eficaz ou não
    if (eficacia > 1.0) {
        cout << "Foi super eficaz!" << endl;
    } else if (eficacia < 1.0) {
        cout << "Não foi muito eficaz..." << endl;
    }

    return danoFinal;  // Retorna o dano total causado
}

// Função para a CPU escolher um ataque de forma mais inteligente no modo Médio ou Difícil
int escolherAtaqueCPU(const Pokemon& cpuPokemon, const Pokemon& jogadorPokemon, int dificuldade) {
    if (dificuldade == 1) {
        // Modo fácil: escolhe um ataque aleatório
        return rand() % 4;
    } else {
        // Modo médio/difícil: escolhe o ataque mais eficaz
        int melhorAtaque = 0;
        float melhorDano = 0;
        for (int i = 0; i < 4; ++i) {
            Ataque ataque = cpuPokemon.getAtaque(i);
            float danoEstimado = calcularDano(cpuPokemon, jogadorPokemon, ataque);  // Calcula o dano esperado
            if (danoEstimado > melhorDano) {
                melhorDano = danoEstimado;
                melhorAtaque = i;  // Atualiza o melhor ataque
            }
        }
        return melhorAtaque;  // Retorna o índice do ataque mais eficaz
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
void atualizarDerrota(Ranking& ranking) {
    ranking.derrotas++;  // Incrementa o número de derrotas
}

// Função para reiniciar o ranking
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
