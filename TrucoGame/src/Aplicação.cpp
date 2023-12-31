#include "../include/Aplica��o.h"

namespace TrucoGame {

    Gerenciador::GerenciadorGrafico* Aplica��o::pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

    Aplica��o::Aplica��o() {
        if (pGrafico == nullptr) {
            std::cout << "ERROR::TrucoGame::Aplica��o nao foi possivel criar o GerenciadorGrafico" << std::endl;
            exit(1);
        }
        inicializa();
    }

    Aplica��o::~Aplica��o() {

    }

    void Aplica��o::inicializa() {
        // TODO Definir o estado inicial da interface
    }

    void Aplica��o::executar() {

        while (pGrafico->verificaJanelaAberta()) {

            //limpa janela
            pGrafico->limpaJanela();

            //mostra tudo na janela
            pGrafico->mostraElementos();

            //reseta o relogio
            pGrafico->resetarRelogio();
        }
    }
}