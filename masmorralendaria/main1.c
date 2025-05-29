#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

/* Variáveis globais do jogo */
int jogadorX = 1;       // Posição X inicial do jogador
int jogadorY = 1;       // Posição Y inicial do jogador
int temChave = 0;       // Flag para verificar se jogador pegou a chave
int tentativas = 0;     // Contador de tentativas/vidas

/* Enumeração dos estados do jogo */
enum EstadoJogo {
    MENU,     // Tela de menu principal
    CREDITO,  // Tela de créditos
    SAIR,     // Estado para sair do jogo
    VILA,     // Fase inicial (vila)
    FASE1,    // Primeira fase da masmorra
    FASE2,    // Segunda fase da masmorra
    FASE3,    // Terceira e última fase
    DERROTA,  // Tela de derrota
    VITORIA   // Tela de vitória
};

/* Protótipos das funções */
void fase1();          // Função da primeira fase
void fase2();          // Função da segunda fase
int fase3();           // Função da terceira fase (retorna 1 se vencer)

/* Função principal */
int main() {
    int estadoAtual = MENU;  // Começa no menu principal
    int i, j; // Variáveis para loops for

    // Loop principal do jogo
    while (1) {
        /* Máquina de estados do jogo */
        if (estadoAtual == MENU) {
            // Exibe o menu principal
            system("cls");
            printf("=== MENU PRINCIPAL ===\n");
            printf("1. Jogar\n");
            printf("2. Creditos\n");
            printf("3. Sair\n");
            printf("Escolha uma opcao: ");
            
            int opcao;
            scanf("%d", &opcao);

            // Processa a escolha do usuário
            switch (opcao) {
                case 1:
                    estadoAtual = VILA;  // Inicia o jogo
                    break;
                case 2:
                    estadoAtual = CREDITO;  // Mostra créditos
                    break;
                case 3:
                    estadoAtual = SAIR;  // Sai do jogo
                    break;
                default:
                    printf("Opcao invalida.\n");
                    system("pause");
            }
        }
        else if (estadoAtual == CREDITO) {
            // Tela de créditos
            system("cls");
            printf("=== CREDITOS ===\n");
            printf("Desenvolvido por: Pedro Souza, Raphael tuma, Gustavo Pinho e Joao Pedro\n");
            system("pause");
            estadoAtual = MENU;  // Volta ao menu
        }
        else if (estadoAtual == SAIR) {
            // Sai do jogo
            system("cls");
            printf("Obrigado por jogar!\n");
            break;
        }
        else if (estadoAtual == VILA) {
            /* Fase inicial - Vila */
            const int tam_vila = 10;
            // Mapa da vila (10x10)
            int vila[10][10] = {
                {'*','*','*','*','*','*','*','*','*','*'},
                {'*',' ','*','P',' ','*','P','*','@','*'},
                {'*',' ','*',' ',' ','*',' ','*',' ','*'},
                {'*',' ','*',' ',' ','*',' ','*',' ','*'},
                {'*',' ','*',' ',' ','*',' ','*',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','D',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','*','*','*'}
            };

            // Reseta posição do jogador e status da chave
            jogadorX = 1;
            jogadorY = 1;
            temChave = 0;
            int k, nx, ny; // Variáveis para loops for

            // Loop da fase vila
            while (1) {
                system("cls");
                
                // Renderiza o mapa
                for (i = 0; i < tam_vila; i++) {
                    for (j = 0; j < tam_vila; j++) {
                        if (i == jogadorX && j == jogadorY) {
                            printf("& ");  // Jogador
                        }
                        else if (temChave && i == 8 && j == 1) {
                            printf("= ");  // Porta aberta
                        }
                        else {
                            printf("%c ", vila[i][j]);  // Elementos do mapa
                        }
                    }
                    printf("\n");
                }

                // Controles
                printf("\nUse W A S D para mover, I para interagir\n");
                int comando = getch();

                // Calcula nova posição
                int novoX = jogadorX;
                int novoY = jogadorY;

                // Movimentação
                if (comando == 'w' || comando == 'W') novoX--;
                else if (comando == 's' || comando == 'S') novoX++;
                else if (comando == 'a' || comando == 'A') novoY--;
                else if (comando == 'd' || comando == 'D') novoY++;
                else if (comando == 'i' || comando == 'I') {
                    // Lógica de interação
                    int item = vila[jogadorX][jogadorY];

                    if (item == '@') {  // Pegar chave
                        temChave = 1;
                        vila[jogadorX][jogadorY] = ' ';
                        printf("Voce pegou a chave! A porta agora está aberta.\n");
                        system("pause");
                    }
                    else if (jogadorX == 8 && jogadorY == 1) {  // Porta
                        if (temChave) {
                            printf("Voce abriu a porta e entrou na masmorra!\n");
                            estadoAtual = FASE1;
                            break;
                        }
                        else {
                            printf("A porta esta trancada. Pegue a chave primeiro.\n");
                        }
                    }
                    else {
                        // Interação com NPCs
                        int px[] = {-1, 1, 0, 0};
                        int py[] = {0, 0, -1, 1};
                        int encontrouNPC = 0;
                        
                        for (k = 0; k < 4; k++) {
                            nx = jogadorX + px[k];
                            ny = jogadorY + py[k];
                            
                            if (nx >= 0 && nx < tam_vila && ny >= 0 && ny < tam_vila && vila[nx][ny] == 'P') {
                                encontrouNPC = 1;
                                if (nx == 1 && ny == 3) {
                                    printf("NPC 1: Bem-vindo! Pegue a chave e entre na masmorra para comecar.\n");
                                }
                                else if (nx == 1 && ny == 6) {
                                    printf("NPC 2: Dica: cuidado com os espinhos nas fases seguintes!\n");
                                }
                                else {
                                    printf("NPC: Ola, aventureiro.\n");
                                }
                                break;
                            }
                        }

                        if (!encontrouNPC) {
                            printf("Nada para interagir aqui.\n");
                        }
                    }
                    system("pause");
                    continue;
                }

                // Atualiza posição do jogador se o movimento for válido
                if (vila[novoX][novoY] != '*') {
                    jogadorX = novoX;
                    jogadorY = novoY;
                }
            }
        }
        else if (estadoAtual == FASE1) {
            fase1();  // Chama a primeira fase
            estadoAtual = FASE2;  // Vai para próxima fase
        }
        else if (estadoAtual == FASE2) {
            fase2();  // Chama a segunda fase
            estadoAtual = FASE3;  // Vai para próxima fase
        }
        else if (estadoAtual == FASE3) {
            if (fase3() == 1) {  // Se vencer a terceira fase
                estadoAtual = VITORIA;
            }
            else {
                estadoAtual = MENU;  // Volta ao menu se perder
            }
        }
        else if (estadoAtual == VITORIA) {
            // Tela de vitória
            system("cls");
            printf("========================================\n");
            printf("=             VITORIA!                =\n");
            printf("=                                     =\n");
            printf("=  Parabens! Voce completou todas as  =\n");
            printf("=  fases do jogo com sucesso!         =\n");
            printf("=                                     =\n");
            printf("=  Obrigado por jogar!                =\n");
            printf("========================================\n");
            system("pause");
            estadoAtual = MENU;  // Volta ao menu
        }
    }

    return 0;
}

/* Implementação da primeira fase */
void fase1() {
    const int tam = 10;
    // Mapa da fase 1 (10x10)
    int mapa[10][10] = {
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*',' ',' ',' ',' ',' ',' ',' ','@','*'},
        {'*',' ','*','*',' ',' ','*',' ',' ','*'},
        {'*',' ','*',' ',' ',' ','*',' ',' ','*'},
        {'*',' ','*',' ',' ',' ','*','*',' ','*'},
        {'*',' ','*',' ',' ',' ',' ','*',' ','*'},
        {'*',' ','*',' ',' ',' ',' ','*',' ','*'},
        {'*',' ','*',' ',' ',' ',' ','*',' ','*'},
        {'*','D',' ',' ',' ',' ',' ',' ',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*'}
    };

    int jogadorX = 1, jogadorY = 1;  // Posição inicial
    int temChave = 0;  // Flag para chave
    int i, j; // Variáveis para loops for

    // Loop da fase 1
    while (1) {
        system("cls");

        // Renderiza o mapa
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                if (i == jogadorX && j == jogadorY) {
                    printf("& ");  // Jogador
                }
                else if (temChave && i == 8 && j == 1) {
                    printf("= ");  // Porta aberta
                }
                else {
                    printf("%c ", mapa[i][j]);  // Elementos do mapa
                }
            }
            printf("\n");
        }

        // Controles
        printf("\nUse W A S D para mover, I para interagir\n");
        int comando = getch();

        // Calcula nova posição
        int novoX = jogadorX;
        int novoY = jogadorY;

        // Movimentação
        if (comando == 'w' || comando == 'W') novoX--;
        else if (comando == 's' || comando == 'S') novoX++;
        else if (comando == 'a' || comando == 'A') novoY--;
        else if (comando == 'd' || comando == 'D') novoY++;
        else if (comando == 'i' || comando == 'I') {
            // Lógica de interação
            if (mapa[jogadorX][jogadorY] == '@') {  // Pegar chave
                temChave = 1;
                mapa[jogadorX][jogadorY] = ' ';
                printf("Voce pegou a chave! A porta agora está aberta.\n");
                system("pause");
            }
            else if (jogadorX == 8 && jogadorY == 1) {  // Porta
                if (temChave) {
                    printf("Voce abriu a porta e passou para a proxima fase!\n");
                    system("pause");
                    break;
                }
                else {
                    printf("A porta esta trancada. Pegue a chave primeiro.\n");
                }
            }
            else {
                printf("Nada para interagir aqui.\n");
            }
            system("pause");
            continue;
        }

        // Atualiza posição se movimento for válido
        if (novoX >= 0 && novoX < tam && novoY >= 0 && novoY < tam && mapa[novoX][novoY] != '*') {
            jogadorX = novoX;
            jogadorY = novoY;
        }
    }
}

/* Implementação da segunda fase */
void fase2() {
    const int tam = 20;  // Tamanho do mapa (20x20)
    int mapa[20][20];    // Matriz do mapa
    int tentativas = 0;  // Contador de tentativas
    int contadorMovimentoMonstro = 0;  // Controle do monstro
    int i, j, x, y; // Variáveis para loops for

    // Loop principal da fase (reinicia se perder vida)
    while (1) {
        // Inicializa mapa vazio
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                mapa[i][j] = ' ';
            }
        }

        // Cria paredes nas bordas
        for (i = 0; i < tam; i++) {
            mapa[0][i] = '*';
            mapa[tam-1][i] = '*';
            mapa[i][0] = '*';
            mapa[i][tam-1] = '*';
        }

        // Posiciona chave e porta
        mapa[1][1] = '@';
        mapa[18][18] = 'D';

        // Cria paredes internas
        for (i = 3; i < 17; i++) {
            mapa[5][i] = '*';
            mapa[15][i] = '*';
        }

        // Gera espinhos aleatórios
        srand(time(NULL));
        int espinhosColocados = 0;
        while (espinhosColocados < 30) {
            x = 1 + rand() % (tam-2);
            y = 1 + rand() % (tam-2);

            if (mapa[x][y] == ' ' && !(x == 1 && y == 1) && !(x == 18 && y == 18)) {
                mapa[x][y] = '#';
                espinhosColocados++;
            }
        }

        // Inicializa variáveis do jogador e monstro
        int jogadorX = 1, jogadorY = 2;
        int temChave = 0;
        int monstroX = 10, monstroY = 15;
        int k; // Variável para loop for

        // Loop do jogo
        while (1) {
            system("cls");

            // Renderiza o mapa
            for (i = 0; i < tam; i++) {
                for (j = 0; j < tam; j++) {
                    if (i == jogadorX && j == jogadorY) {
                        printf("& ");  // Jogador
                    }
                    else if (i == monstroX && j == monstroY) {
                        printf("X ");  // Monstro
                    }
                    else if (temChave && mapa[i][j] == 'D') {
                        printf("= ");  // Porta aberta
                    }
                    else {
                        printf("%c ", mapa[i][j]);  // Elementos do mapa
                    }
                }
                printf("\n");
            }

            // Controles e informações
            printf("\nUse W A S D para mover, I para interagir\n");
            printf("Tentativas restantes: %d\n", 3 - tentativas);
            int comando = getch();

            // Calcula nova posição
            int novoX = jogadorX;
            int novoY = jogadorY;

            // Movimentação
            if (comando == 'w' || comando == 'W') novoX--;
            else if (comando == 's' || comando == 'S') novoX++;
            else if (comando == 'a' || comando == 'A') novoY--;
            else if (comando == 'd' || comando == 'D') novoY++;
            else if (comando == 'i' || comando == 'I') {
                // Lógica de interação
                if (mapa[jogadorX][jogadorY] == '@') {  // Pegar chave
                    temChave = 1;
                    mapa[jogadorX][jogadorY] = ' ';
                    printf("Voce pegou a chave!\n");
                }
                else if (mapa[jogadorX][jogadorY] == 'D') {  // Porta
                    if (temChave) {
                        printf("Voce abriu a porta e venceu a fase!\n");
                        system("pause");
                        return;
                    }
                    else {
                        printf("A porta esta trancada. Pegue a chave primeiro.\n");
                    }
                }
                else {
                    printf("Nada para interagir aqui.\n");
                }
                system("pause");
                continue;
            }

            // Verifica movimento válido
            if (novoX >= 0 && novoX < tam && novoY >= 0 && novoY < tam && 
                mapa[novoX][novoY] != '*' && mapa[novoX][novoY] != '#') {
                jogadorX = novoX;
                jogadorY = novoY;
            }
            else if (novoX >= 0 && novoX < tam && novoY >= 0 && novoY < tam && 
                    mapa[novoX][novoY] == '#') {
                // Pisou em espinhos
                printf("Voce pisou em espinhos! Perdeu uma vida.\n");
                tentativas++;
                system("pause");
                break;
            }

            // Movimento do monstro (a cada 2 turnos)
            contadorMovimentoMonstro++;
            if (contadorMovimentoMonstro >= 2) {
                int direcao = rand() % 4;  // Direção aleatória
                int novoMonstroX = monstroX;
                int novoMonstroY = monstroY;
                
                // Calcula nova posição do monstro
                if (direcao == 0) novoMonstroX--;
                else if (direcao == 1) novoMonstroX++;
                else if (direcao == 2) novoMonstroY--;
                else if (direcao == 3) novoMonstroY++;

                // Verifica movimento válido do monstro
                if (novoMonstroX > 0 && novoMonstroX < tam-1 && 
                    novoMonstroY > 0 && novoMonstroY < tam-1 && 
                    mapa[novoMonstroX][novoMonstroY] != '*' && 
                    mapa[novoMonstroX][novoMonstroY] != '#' && 
                    !(novoMonstroX == jogadorX && novoMonstroY == jogadorY)) {
                    monstroX = novoMonstroX;
                    monstroY = novoMonstroY;
                }
                contadorMovimentoMonstro = 0;
            }

            // Verifica se monstro pegou o jogador
            if (jogadorX == monstroX && jogadorY == monstroY) {
                printf("O monstro te pegou! Perdeu uma vida.\n");
                tentativas++;
                system("pause");
                break;
            }
        }

        // Verifica se perdeu todas as vidas
        if (tentativas >= 3) {
            printf("Voce perdeu todas as vidas! Fim de jogo.\n");
            system("pause");
            return;
        }
    }
}

/* Implementação da terceira fase (retorna 1 se vencer) */
int fase3() {
    const int tam = 40;  // Mapa grande (40x40)
    int mapa[tam][tam];  // Matriz do mapa
    int i, j; // Variáveis para loops for
    
    // Posições fixas
    int monstroXInicial = 38, monstroYInicial = 1;
    int teleX1 = 5, teleY1 = 5;   // Teleporte 1
    int teleX2 = 34, teleY2 = 34;  // Teleporte 2
    
    int tentativas = 0;  // Contador de tentativas

    // Loop principal da fase (reinicia se perder vida)
    while (1) {
        // Inicializa variáveis
        int jogadorX = 1, jogadorY = 1;
        int temChave = 0;
        int monstroX = monstroXInicial, monstroY = monstroYInicial;
        int turno = 0;

        // Limpa o mapa
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                mapa[i][j] = ' ';
            }
        }

        // Cria paredes nas bordas
        for (i = 0; i < tam; i++) {
            mapa[0][i] = '*';
            mapa[tam-1][i] = '*';
            mapa[i][0] = '*';
            mapa[i][tam-1] = '*';
        }

        // Posiciona itens importantes
        mapa[1][38] = '@';  // Chave
        mapa[38][38] = 'D'; // Porta
        mapa[teleX1][teleY1] = '<'; // Teleportes
        mapa[teleX2][teleY2] = '<';

        // Cria obstáculos e espinhos no mapa
        for (i = 5; i <= 15; i++) mapa[10][i] = '#';
        for (i = 10; i <= 30; i++) mapa[15][i] = '#';
        for (i = 5; i <= 20; i++) mapa[i][25] = '#';
        for (i = 20; i <= 35; i++) mapa[30][i] = '#';
        for (i = 10; i <= 35; i += 2) mapa[i][5] = '#';
        mapa[12][12] = '#'; mapa[13][13] = '#'; mapa[14][14] = '#';
        mapa[18][18] = '#'; mapa[22][22] = '#'; mapa[26][10] = '#';
        mapa[28][15] = '#'; mapa[33][33] = '#'; mapa[5][35] = '#';

        // Cria paredes internas
        for (i = 5; i < 20; i++) mapa[i][10] = '*';
        for (i = 25; i < 35; i++) mapa[18][i] = '*';
        for (i = 8; i < 15; i++) mapa[i][20] = '*';
        mapa[6][6] = '*'; mapa[10][30] = '*'; mapa[15][15] = '*';
        mapa[32][32] = '*'; mapa[35][5] = '*';

        // Loop do jogo
        while (1) {
            system("cls");

            // Renderiza o mapa
            for (i = 0; i < tam; i++) {
                for (j = 0; j < tam; j++) {
                    if (i == jogadorX && j == jogadorY) {
                        printf("& ");  // Jogador
                    }
                    else if (i == monstroX && j == monstroY) {
                        printf("V ");  // Monstro
                    }
                    else if (temChave && i == 38 && j == 38) {
                        printf("= ");  // Porta aberta
                    }
                    else {
                        printf("%c ", mapa[i][j]);  // Elementos do mapa
                    }
                }
                printf("\n");
            }

            // Controles e informações
            printf("\nUse W A S D para mover, I para interagir\n");
            printf("Tentativas restantes: %d\n", 3 - tentativas);
            int comando = getch();

            // Calcula nova posição
            int novoX = jogadorX;
            int novoY = jogadorY;

            // Movimentação
            if (comando == 'w' || comando == 'W') novoX--;
            else if (comando == 's' || comando == 'S') novoX++;
            else if (comando == 'a' || comando == 'A') novoY--;
            else if (comando == 'd' || comando == 'D') novoY++;
            else if (comando == 'i' || comando == 'I') {
                // Lógica de interação
                if (mapa[jogadorX][jogadorY] == '@') {  // Pegar chave
                    temChave = 1;
                    mapa[jogadorX][jogadorY] = ' ';
                    printf("Você pegou a chave! A porta agora está aberta.\n");
                    system("pause");
                }
                else if (mapa[jogadorX][jogadorY] == 'D' && temChave) {  // Porta com chave
                    printf("Parabéns! Você terminou o jogo!\n");
                    system("pause");
                    return 1;  // Retorna 1 para indicar vitória
                }
                else {
                    printf("Nada para interagir aqui.\n");
                    system("pause");
                }
                continue;
            }

            // Verifica movimento válido
            if (mapa[novoX][novoY] != '*' && mapa[novoX][novoY] != '#') {
                jogadorX = novoX;
                jogadorY = novoY;
            }
            else if (mapa[novoX][novoY] == '#') {  // Pisou em espinhos
                printf("Você pisou em espinhos! Perdeu uma vida.\n");
                tentativas++;
                system("pause");

                if (tentativas >= 3) {  // Perdeu todas as vidas
                    printf("Você perdeu todas as vidas! Fim de jogo.\n");
                    system("pause");
                    return 0;
                }
                break;
            }

            // Sistema de teleporte
            if (mapa[jogadorX][jogadorY] == '<') {
                if (jogadorX == teleX1 && jogadorY == teleY1) {
                    jogadorX = teleX2;
                    jogadorY = teleY2;
                    printf("Teleporte!\n");
                    system("pause");
                }
                else if (jogadorX == teleX2 && jogadorY == teleY2) {
                    jogadorX = teleX1;
                    jogadorY = teleY1;
                    printf("Teleporte!\n");
                    system("pause");
                }
            }

            // Movimento do monstro (a cada 2 turnos)
            turno++;
            if (turno % 2 == 0) {
                int novoMonstroX = monstroX;
                int novoMonstroY = monstroY;

                // Monstro persegue o jogador
                if (monstroX < jogadorX) novoMonstroX++;
                else if (monstroX > jogadorX) novoMonstroX--;

                if (monstroY < jogadorY) novoMonstroY++;
                else if (monstroY > jogadorY) novoMonstroY--;

                // Verifica movimento válido do monstro
                if (mapa[novoMonstroX][novoMonstroY] != '*' &&
                    mapa[novoMonstroX][novoMonstroY] != '#' &&
                    !(novoMonstroX == teleX1 && novoMonstroY == teleY1) &&
                    !(novoMonstroX == teleX2 && novoMonstroY == teleY2)) {
                    monstroX = novoMonstroX;
                    monstroY = novoMonstroY;
                }
            }

            // Verifica se monstro pegou o jogador
            if (monstroX == jogadorX && monstroY == jogadorY) {
                printf("O monstro te pegou! Perdeu uma vida.\n");
                tentativas++;
                system("pause");
                break;
            }
        }

        // Verifica se perdeu todas as vidas
        if (tentativas >= 3) {
            printf("Você perdeu todas as vidas! Fim de jogo.\n");
            system("pause");
            return 0;
        }
    }
}