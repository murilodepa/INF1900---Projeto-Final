#include "../include/Aplicação.h"

namespace TrucoGame {

    Gerenciador::GerenciadorGrafico* Aplicação::pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

    Aplicação::Aplicação() {
        if (pGrafico == nullptr) {
            std::cout << "ERROR::TrucoGame::Aplicação nao foi possivel criar o GerenciadorGrafico" << std::endl;
            exit(1);
        }
        inicializa();
    }

    Aplicação::~Aplicação() {

    }

    void Aplicação::inicializa() {
        // TODO Definir o estado inicial da interface
    }

    void Aplicação::executar() {

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