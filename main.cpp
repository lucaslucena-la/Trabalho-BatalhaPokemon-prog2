#include <iostream>   // Inclui a biblioteca padrão de entrada e saída
#include <vector>     // Inclui a biblioteca de vetores
#include <string>     // Inclui a biblioteca de strings
#include "pokemon.h"  // Inclui o arquivo de cabeçalho para a classe Pokemon
#include "ataque.h"   // Inclui o arquivo de cabeçalho para a classe Ataque
#include "game.h"     // Inclui o arquivo de cabeçalho para as funções relacionadas ao jogo
#include "jogador.h"  // Inclui o arquivo de cabeçalho para a classe Jogador

using namespace std;  // Facilita o uso de elementos da biblioteca padrão sem precisar de "std::"

int main() {
    int opcao;  // Declara uma variável para armazenar a escolha do menu

    // Carregamento do arquivo de jogadores
    vector<Jogador> jogadores = carregarJogadores("jogadores.txt");  // Carrega a lista de jogadores de um arquivo
    Jogador jogadorAtual = selecionarJogador(jogadores);  // Seleciona o jogador atual a partir da lista carregada
    salvarJogadores(jogadores, "jogadores.txt");  // Salva a lista de jogadores após a seleção do jogador atual

    vector<string> logDeBatalha;  // Declara um vetor de strings para armazenar o log da batalha
    int dificuldade = 1;  // Inicializa a dificuldade do jogo
    cout << "A dificuldade atual é: " << dificuldade << endl;  // Exibe a dificuldade atual para o jogador

    // Loop do menu principal
    while (true) {
        exibirMenu();  // Exibe o menu de opções
        cin >> opcao;  // Captura a escolha do jogador

        if (opcao == 1) {
            // Carrega pokémons e ataques dos arquivos
            vector<Pokemon> pokemons = carregarPokemons("pokemons.txt");
            vector<Ataque> ataques = carregarAtaques("ataques.txt");

            vector<Pokemon> jogadorPokemons, cpuPokemons;  // Declara vetores para os pokémons do jogador e da CPU
            sortearPokemons(pokemons, jogadorPokemons, cpuPokemons, dificuldade);  // Sorteia pokémons para o jogador e para a CPU

            // Exibe os pokémons sorteados para o jogador
            cout << "\nSeus Pokémons sorteados:\n";
            for (size_t i = 0; i < jogadorPokemons.size(); ++i) {
                cout << i + 1 << ". " << jogadorPokemons[i].getNome()
                    << " (HP: " << jogadorPokemons[i].getHP()
                    << ", Nível: " << jogadorPokemons[i].getNivel()
                    << ", Tipo 1: " << jogadorPokemons[i].getTipo1()
                    << ", Tipo 2: " << (jogadorPokemons[i].getTipo2().empty() ? "Nenhum" : jogadorPokemons[i].getTipo2())
                    << ")\n";  // Exibe as informações dos pokémons sorteados
            }

            // Exibe os pokémons sorteados para a CPU
            cout << "\nPokémons sorteados da CPU:\n";
            for (const auto& p : cpuPokemons) {
                cout << "- " << p.getNome()
                    << " (HP: " << p.getHP()
                    << ", Nível: " << p.getNivel()
                    << ", Tipo 1: " << p.getTipo1()
                    << ", Tipo 2: " << (p.getTipo2().empty() ? "Nenhum" : p.getTipo2())
                    << ")\n";  // Exibe as informações dos pokémons da CPU
            }

            // Jogador escolhe seu Pokémon inicial
            int escolhaInicial;
            cout << "\nEscolha seu Pokémon inicial (1, 2 ou 3): ";
            cin >> escolhaInicial;
            escolhaInicial -= 1;  // Ajusta a escolha para o índice correto do vetor
            int pokemonAtual = escolhaInicial;  // Define o índice do Pokémon inicial do jogador
            Pokemon& cpuPokemon = cpuPokemons[0];  // Define o Pokémon inicial da CPU

            // Atribui ataques aos pokémons
            atribuirAtaquesAosPokemons(jogadorPokemons, ataques);
            atribuirAtaquesAosPokemons(cpuPokemons, ataques);

            // Loop da batalha
            while (true) {
                removerPokemonsDerrotados(jogadorPokemons);  // Remove pokémons derrotados do jogador
                removerPokemonsDerrotados(cpuPokemons);  // Remove pokémons derrotados da CPU

                // Verifica se o jogador perdeu
                if (jogadorPokemons.empty()) {
                    cout << "\nTodos os seus Pokémons foram derrotados! Você perdeu!" << endl;
                    logDeBatalha.push_back("Todos os seus Pokémons foram derrotados! Você perdeu!");
                    atualizarDerrotaJogador(jogadorAtual, jogadores);  // Atualiza as estatísticas de derrota do jogador
                    salvarJogadores(jogadores, "jogadores.txt");  // Salva as informações dos jogadores
                    break;  // Sai do loop da batalha
                }

                // Verifica se a CPU perdeu
                if (cpuPokemons.empty()) {
                    cout << "\nTodos os Pokémons da CPU foram derrotados! Você venceu!" << endl;
                    logDeBatalha.push_back("Todos os Pokémons da CPU foram derrotados! Você venceu!");
                    atualizarVitoriaJogador(jogadorAtual, dificuldade, jogadores);  // Atualiza as estatísticas de vitória do jogador
                    salvarJogadores(jogadores, "jogadores.txt");  // Salva as informações dos jogadores
                    break;  // Sai do loop da batalha
                }

                // Exibe o status dos pokémons
                cout << "\n----- Status dos Pokémons -----\n";
                cout << "Jogador: " << jogadorPokemons[pokemonAtual].getNome() << " - HP: " << jogadorPokemons[pokemonAtual].getHP() << endl;
                cout << "CPU: " << cpuPokemon.getNome() << " - HP: " << cpuPokemon.getHP() << endl;
                cout << "-------------------------------\n";

                // Opções de ação para o jogador
                cout << "\nEscolha uma ação:\n";
                cout << "1. Atacar\n2. Trocar Pokémon\n3. Exibir Histórico de Batalha\n";
                int acaoJogador;
                cin >> acaoJogador;

                if (acaoJogador == 1) {
                    // Jogador escolhe um ataque
                    exibirAtaques(jogadorPokemons[pokemonAtual]);
                    int escolhaAtaque;
                    cin >> escolhaAtaque;
                    escolhaAtaque -= 1;  // Ajusta a escolha para o índice correto do vetor

                    // Jogador realiza o ataque
                    Ataque ataqueJogador = jogadorPokemons[pokemonAtual].getAtaque(escolhaAtaque);
                    float eficacia = calcularEficacia(ataqueJogador.getTipo(), cpuPokemon.getTipo1());  // Calcula a eficácia do ataque
                    if (!cpuPokemon.getTipo2().empty()) {
                        eficacia *= calcularEficacia(ataqueJogador.getTipo(), cpuPokemon.getTipo2());
                    }

                    int critico = calcularCritico();  // Calcula se o ataque foi um golpe crítico
                    if (critico == 2) {
                        cout << "------------------ Foi um golpe crítico de " << jogadorPokemons[pokemonAtual].getNome() << " com o ataque " << ataqueJogador.getNome() << "------------------" << endl;
                        logDeBatalha.push_back("Foi um golpe crítico de " + jogadorPokemons[pokemonAtual].getNome() + " com o ataque " + ataqueJogador.getNome() + "!");
                    }

                    cout << endl;
                    // Verifica a eficácia do ataque
                    if (eficacia == 0.0) {
                        cout << "O ataque do jogador não é efetivo!" << endl;
                        logDeBatalha.push_back("O ataque de " + jogadorPokemons[pokemonAtual].getNome() + " não foi efetivo!");
                    } else if (eficacia == 0.5) {
                        cout << "O ataque do jogador não foi muito eficaz..." << endl;
                        logDeBatalha.push_back("O ataque de " + jogadorPokemons[pokemonAtual].getNome() + " não foi muito eficaz...");
                    } else if (eficacia == 1.0) {
                        cout << "O ataque do jogador Foi normalmente eficaz." << endl;
                        logDeBatalha.push_back("O ataque de " + jogadorPokemons[pokemonAtual].getNome() + " foi normalmente eficaz...");
                    } else if (eficacia == 2.0) {
                        cout << "O ataque do jogador Foi super eficaz!" << endl;
                        logDeBatalha.push_back("O ataque de " + jogadorPokemons[pokemonAtual].getNome() + " foi super eficaz!");
                    }
                    

                    // Calcula o dano do ataque
                    if (!calcularPrecisao(ataqueJogador.getPrecisao())) {
                        cout << endl;

                        cout << "!!!!!!!!! O ataque do jogador falhou !!!!!!!!!!" << endl;
                        logDeBatalha.push_back("O ataque de " + jogadorPokemons[pokemonAtual].getNome() + " falhou!");
                    } else {
                        int danoJogador = calcularDano(jogadorPokemons[pokemonAtual], cpuPokemon, ataqueJogador);
                        cout << jogadorPokemons[pokemonAtual].getNome() << " usou " << ataqueJogador.getNome() << " e causou " << danoJogador << " de dano!" << endl;
                        logDeBatalha.push_back(jogadorPokemons[pokemonAtual].getNome() + " usou " + ataqueJogador.getNome() + " e causou " + to_string(danoJogador) + " de dano!");
                        
                        cpuPokemon.receberDano(danoJogador);  // Aplica o dano ao Pokémon da CPU

                        cout << cpuPokemon.getNome() << " agora tem " << cpuPokemon.getHP() << " de HP!" << endl;
                        cout << endl;

                        // Se o Pokémon da CPU for derrotado, troca o Pokémon
                        
                        // Se o Pokémon da CPU for derrotado, troca o Pokémon
                        if (cpuPokemon.estaDerrotado()) {
                            cout << cpuPokemon.getNome() << " foi derrotado!" << endl;

                            try {
                                removerPokemonsDerrotados(cpuPokemons);  // Remove os pokémons derrotados da CPU
                                cpuPokemon = trocarPokemonCPU(cpuPokemons);  // Troca o Pokémon da CPU
                                cout << endl << "CPU escolheu " << cpuPokemon.getNome() << " para continuar a batalha!" << endl;
                                logDeBatalha.push_back("CPU escolheu " + cpuPokemon.getNome() + " para continuar a batalha!");

                                // Permite que o jogador escolha atacar ou trocar de Pokémon antes que a CPU ataque
                                bool turnoJogador = true;
                                while (turnoJogador) {
                                    cout << "\nEscolha sua ação:\n";
                                    cout << "1. Atacar\n2. Trocar Pokémon\n";
                                    int escolha;
                                    cin >> escolha;

                                    if (escolha == 1) {
                                        // Exibe os ataques do Pokémon do jogador e executa o ataque
                                        exibirAtaques(jogadorPokemons[pokemonAtual]);
                                        int ataqueEscolhido;
                                        cin >> ataqueEscolhido;
                                        ataqueEscolhido -= 1;  // Ajusta o índice do ataque

                                        Ataque ataqueJogador = jogadorPokemons[pokemonAtual].getAtaque(ataqueEscolhido);
                                        int danoJogador = calcularDano(jogadorPokemons[pokemonAtual], cpuPokemon, ataqueJogador);
                                        
                                        cout << jogadorPokemons[pokemonAtual].getNome() << " usou " << ataqueJogador.getNome() 
                                            << " e causou " << danoJogador << " de dano!" << endl;
                                        logDeBatalha.push_back(jogadorPokemons[pokemonAtual].getNome() + " usou " + ataqueJogador.getNome() + " e causou " + to_string(danoJogador) + " de dano!");

                                        cpuPokemon.receberDano(danoJogador);

                                        turnoJogador = false;  // Encerrar o turno do jogador para que a CPU possa atacar
                                    } else if (escolha == 2) {
                                        jogadorPokemons[pokemonAtual] = trocarPokemonJogador(jogadorPokemons, pokemonAtual);  // Passa o índice pokemonAtual por referência

                                        turnoJogador = true;  // Encerrar o turno do jogador para que a CPU possa atacar
                                    } else {
                                        cout << "Opção inválida! Tente novamente.\n";
                                    }
                                }

                            } catch (const runtime_error& e) {
                                cout << "Todos os Pokémons da CPU foram derrotados! Você venceu!" << endl;
                                atualizarVitoriaJogador(jogadorAtual, dificuldade, jogadores);  // Atualiza a vitória do jogador
                                salvarJogadores(jogadores, "jogadores.txt");  // Salva as informações dos jogadores
                                break;  // Sai do loop da batalha
                            }
                        }
                    }
                } else if (acaoJogador == 2) {
                    // Jogador troca de Pokémon
                    jogadorPokemons[pokemonAtual] = trocarPokemonJogador(jogadorPokemons, pokemonAtual);

                } else if (acaoJogador == 3) {
                    // Exibe o histórico de batalha
                    exibirHistoricoDeBatalha(logDeBatalha);

                    continue;  
                }

                // CPU ataca
                if (!cpuPokemon.estaDerrotado()) {
                int escolhaCPU = escolherAtaqueCPU(cpuPokemon, jogadorPokemons[pokemonAtual], dificuldade);  // CPU escolhe o ataque
                Ataque ataqueCPU = cpuPokemon.getAtaque(escolhaCPU);

                int criticoCPU = calcularCritico();  // Calcula se o ataque da CPU foi um golpe crítico
                if (criticoCPU == 2) {
                    cout << endl;
                    cout << "------------------ Foi um golpe crítico de " << cpuPokemon.getNome() << " com o ataque " << ataqueCPU.getNome() << " ------------------" << endl;
                    logDeBatalha.push_back("Foi um golpe crítico de " + cpuPokemon.getNome() + " com o ataque " + ataqueCPU.getNome() + "!");
                }

                float eficacia = calcularEficacia(ataqueCPU.getTipo(), jogadorPokemons[pokemonAtual].getTipo1());  // Calcula a eficácia do ataque da CPU
                if (!jogadorPokemons[pokemonAtual].getTipo2().empty()) {
                    eficacia *= calcularEficacia(ataqueCPU.getTipo(), jogadorPokemons[pokemonAtual].getTipo2());
                }

                // Verifica a eficácia do ataque da CPU
                if (eficacia == 0.0) {
                    cout << endl;
                    cout << "O ataque da CPU não é efetivo!" << endl;
                    logDeBatalha.push_back("O ataque de " + cpuPokemon.getNome() + " não foi efetivo!");
                } else if (eficacia == 0.5) {
                    cout << endl;
                    cout << "O ataque da CPU não foi muito eficaz..." << endl;
                    logDeBatalha.push_back("O ataque de " + cpuPokemon.getNome() + " não foi muito eficaz...");
                } else if (eficacia == 1.0) {
                    cout << endl;
                    cout << "O ataque da CPU foi normalmente eficaz." << endl;
                    logDeBatalha.push_back("O ataque de " + cpuPokemon.getNome() + " foi normalmente eficaz...");
                } else if (eficacia == 2.0) {
                    cout << endl;
                    cout << "------------------ O ataque da CPU foi super eficaz ------------------" << endl;
                    logDeBatalha.push_back("O ataque de " + cpuPokemon.getNome() + " foi super eficaz!");
                }

                // Calcula o dano do ataque da CPU
                if (!calcularPrecisao(ataqueCPU.getPrecisao())) {
                    cout << endl;
                    cout << "!!!!!!!! O ataque da CPU falhou !!!!!!!!" << endl;
                    logDeBatalha.push_back("O ataque de " + cpuPokemon.getNome() + " falhou!");
                } else {
                    int danoCPU = calcularDano(cpuPokemon, jogadorPokemons[pokemonAtual], ataqueCPU);
                    cout << cpuPokemon.getNome() << " usou " << ataqueCPU.getNome() << " e causou " << danoCPU << " de dano!" << endl;
                    logDeBatalha.push_back(cpuPokemon.getNome() + " usou " + ataqueCPU.getNome() + " e causou " + to_string(danoCPU) + " de dano!");

                    jogadorPokemons[pokemonAtual].receberDano(danoCPU);  // Aplica o dano ao Pokémon do jogador

                    cout << jogadorPokemons[pokemonAtual].getNome() << " agora tem " << jogadorPokemons[pokemonAtual].getHP() << " de HP!" << endl;

                    if (jogadorPokemons[pokemonAtual].estaDerrotado()) {
                        cout << jogadorPokemons[pokemonAtual].getNome() << " foi derrotado!" << endl;
                        if (!jogadorPokemons.empty()) {
                            jogadorPokemons[pokemonAtual] = jogadorPokemons[0];  // Se o Pokémon do jogador for derrotado, troca para o próximo
                        }
                    }
                }
            }

            }

        } else if (opcao == 2) {
            // Ajusta a dificuldade do jogo
            dificuldade = ajustarDificuldade();
            cout << endl;
            cout << "Dificuldade ajustada para: " << dificuldade << endl << endl;

        } else if (opcao == 3) {
            // Exibe o ranking dos jogadores
            for (const auto& jogador : jogadores) {
                cout << "\n----- Ranking do Jogador: " << jogador.getNome() << " -----" << endl;
                cout << "Vitórias (Fácil): " << jogador.getVitoriasFacil() << endl;
                cout << "Vitórias (Médio): " << jogador.getVitoriasMedio() << endl;
                cout << "Vitórias (Difícil): " << jogador.getVitoriasDificil() << endl;
                cout << "Derrotas: " << jogador.getDerrotas() << endl;
                cout << "Pontuação: " << jogador.getPontuacao() << endl;
                cout << "-----------------------------------------------" << endl;
            }

        } else if (opcao == 4) {
            // Sai do jogo
            cout << "Saindo do jogo..." << endl;
            break;

        } else {
            // Caso o jogador insira uma opção inválida
            cout << "Opção inválida! Tente novamente." << endl;
        }
    }

    return 0;  // Retorna 0, indicando que o programa terminou corretamente
}
