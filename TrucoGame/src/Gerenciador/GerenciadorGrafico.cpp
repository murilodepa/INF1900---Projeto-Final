#include "../../include//Gerenciador/GerenciadorGrafico.h"

namespace TrucoGame {

    namespace Gerenciador {

        GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;
        float GerenciadorGrafico::tempo = 0.0f;

        GerenciadorGrafico::GerenciadorGrafico() :
            window(new sf::RenderWindow(sf::VideoMode(TELA_X, TELA_Y), "TrucoGame")),
            camera(sf::Vector2f(TELA_X, TELA_Y)), relogio()
        {
            if (window == nullptr) {
                std::cout << "ERROR::TrucoGame::Gerenciador::GerenciadorGrafico nao foi possivel criar uma janela grafica" << std::endl;
                exit(1);
            }
            window->setFramerateLimit(0);
        }

        GerenciadorGrafico::~GerenciadorGrafico() {
            if (window) {
                delete(window);
                window = nullptr;
            }
        }

        GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico() {
            /**
             * @ return GerenciadorGrafico*
             *
             * Padr�o de Projeto Singleton: garante que eu tenha apenas uma inst�ncia no meu projeto como um todo, isto �,
             * n�o � poss�vel criar dois objetos diferentes deste tipo.
             */

            if (pGrafico == nullptr) {
                pGrafico = new GerenciadorGrafico();
            }
            return pGrafico;
        }

        sf::RenderWindow* GerenciadorGrafico::getWindow() {
            return window;
        }

        sf::Texture GerenciadorGrafico::carregarTextura(const char* caminhoTextura) {
            sf::Texture textura;
            if (!textura.loadFromFile(caminhoTextura)) {
                std::cout << "ERRO::TrucoGame::Gerenciador::GerenciadorGrafico::nao foi possivel encontrar o caminho da textura - " << caminhoTextura << std::endl;
                exit(1);
            }
            return textura;
        }

        sf::Font GerenciadorGrafico::carregarFonte(const char* caminhoFonte) {
            sf::Font fonte;
            if (!fonte.loadFromFile(caminhoFonte)) {
                throw("ERROR::TrucoGame::Gerenciador::GerenciadorGrafico::nao foi possivel encontrar o caminho da fonte");
            }
            return fonte;
        }

        void GerenciadorGrafico::limpaJanela() {
            window->clear();
        }

        void GerenciadorGrafico::resetarRelogio() {
            tempo = relogio.getElapsedTime().asSeconds();
            relogio.restart();
        }

        const float GerenciadorGrafico::getTempo() const {
            return tempo;
        }

        void GerenciadorGrafico::desenhaElemento(sf::RectangleShape corpo) {
            window->draw(corpo);
        }

        void GerenciadorGrafico::desenhaElemento(sf::Text texto) {
            window->draw(texto);
        }

        void GerenciadorGrafico::mostraElementos() {
            window->display();
        }

        void GerenciadorGrafico::fecharJanela() {
            if (window->isOpen()) {
                window->close();
            }
        }

        const bool GerenciadorGrafico::verificaJanelaAberta() {
            return window->isOpen();
        }

        void GerenciadorGrafico::atualizarCamera(const sf::Vector2f pos) {
            camera.atualizar(pos);
            window->setView(camera.getCamera());
        }

        void GerenciadorGrafico::atualizarCamera(const sf::Vector2f pos, sf::Vector2f tam) {
            camera.atualizar(pos, tam);
            window->setView(camera.getCamera());
        }

        const sf::View GerenciadorGrafico::getCamera() {
            return camera.getCamera();
        }

        void GerenciadorGrafico::resetarJanela() {
            camera.resetar(sf::Vector2f(TELA_X / 2.0f, TELA_Y / 2.0f));
            window->setView(camera.getCamera());
        }

        const sf::Vector2f GerenciadorGrafico::getTamJanela() const {
            return (sf::Vector2f)window->getSize();
        }

        void GerenciadorGrafico::setLimiteCamera(const sf::IntRect limiteCamera) {
            camera.setLimiteCamera(limiteCamera);
        }

        void GerenciadorGrafico::setLimiteObjeto(const sf::IntRect objeto) {
            camera.setLimiteObjeto(objeto);
        }
    }
}