# TrucoGame - Grupo 1

## Descrição do Projeto
Neste projeto final, você deve criar um jogo de Truco em C++ que incorpora e demonstra de forma abrangente os princípios da Programação Orientada a Objetos (OO). O jogo de Truco deve ser totalmente funcional, com suporte para dois jogadores humanos e implementar todas as regras do jogo de Truco.

## Integrantes
* Murilo de Paula Araujo;
* Caique Novaes Tsurumaki Pereira;
* Laert Espagnoli Neto;
* Vitor Luiz Bortoloti Pereira.


## Primeiros Passos
Primeiro, copie o repositório. Em seguida, entre na sua IDE favorita e faça a build do projeto. Execute pela IDE ou pelo executavel na pasta bin. 
> git clone https://github.com/murilodepa/INF1900-Projeto-Final.git


## Como jogar?
Ao executar o programa o jogador é apresentado a um popup com as opções Server e Client.

![image](https://github.com/murilodepa/INF1900-Projeto-Final/assets/37109251/14ff80bb-f5a7-4fd1-8003-7e7681123265)

A opção de Server permite o jogador definir o número de pessoas esperadas para o jogo, os demais jogadores serão bots e integraram o jogo para compor os 4 jogadores necessários.

![image](https://github.com/murilodepa/INF1900-Projeto-Final/assets/37109251/c2e459c5-68fb-49f1-9d72-cacf3c6e89a5)

Na opção de Client, é requerido o número de IP do servidor(utilizamos como base 127.0.0.1).

![image](https://github.com/murilodepa/INF1900-Projeto-Final/assets/37109251/4fd3d0ed-a429-4976-bf44-2e7ddc5f2b4d)

É possível conectar varias instnâncias do jogo em um mesmo computador connectando via loopback ou em diferentes máquinas conetadas na mesma rede utilizando o IP do host ou em redes diferentes utilizando programas auxiliares como Hamachi ou ZeroTier. Nos testes realizados conseguimos conectar e jogar com 4 jogadores em redes diferentes utilizando ZeroTier.


A distribuição de cartas aleatória inicia automaticamente após a entrada dos jogadores e formação dos times(os times são formados pela ordem de entrada de cada participante). As interações de click e botão de truco possuem regras de apresentação e sua interação é feita pelo click do mouse. Nas cartas, o botão esquerdo do mouse define a ação de jogar a carta escolhida virada para baixo enquanto que o botão direito joga a carta normalmente na mesa.

Na opção de truco, o jogador seguinte receberá um popup sobre aceitar ou não o truco. No caso de aceitar outro popup aparecerá na tela perguntando sobre aumentar o valor do truco ou não. 

![image](https://github.com/murilodepa/INF1900-Projeto-Final/assets/37109251/3e1030af-58e4-4ebf-a7a7-4e14e04a181f)

## Documentação
Os arquivos de documentação estão anexados ao projeto e encontram-se na pasta Documentos(tcp_INF1900.pdf e Requisitos_INF1900.pdf).


Quando um time atingir sozinho 11 pontos no jogo, as cartas da equipe serão reveladas e um popup aparecerá perguntando se o jogador aceita jogar a rodada.   

O time que atingir primeiro os 12 pontos ganha o jogo.
