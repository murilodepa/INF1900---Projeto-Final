#pragma once

//Gerenciador
#include "Gerenciador/Camera.h"
#include "Gerenciador/GerenciadorGrafico.h"

namespace TrucoGame {

    class Aplica��o {
    private:
        static Gerenciador::GerenciadorGrafico* pGrafico;

        void inicializa();
    public:
        Aplica��o();
        ~Aplica��o();
        void executar();
    };
}