#pragma once

//Gerenciador
#include "Gerenciador/Camera.h"
#include "Gerenciador/GerenciadorGrafico.h"

namespace TrucoGame {

    class Aplicação {
    private:
        static Gerenciador::GerenciadorGrafico* pGrafico;

        void inicializa();
    public:
        Aplicação();
        ~Aplicação();
        void executar();
    };
}