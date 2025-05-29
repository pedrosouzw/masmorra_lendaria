
# 🌄 Jogo de Aventura em Texto - Masmorra Lendária

## Desenvolvido por
- 🎮 Pedro Souza  
- 🎮 Raphael Tuma  
- 🎮 Gustavo Pinho  
- 🎮 João Pedro  

---

## 📖 História

Você é um aventureiro em busca do **tesouro perdido da Masmorra Lendária**. Sua jornada começa em uma vila misteriosa, onde os moradores contam histórias sobre os perigos que aguardam nos subterrâneos.

Para conquistar a riqueza escondida, você precisará:

- 🔹 Explorar a vila e conversar com NPCs para obter informações.  
- 🔹 Encontrar a chave que abre o portal para a masmorra.  
- 🔹 Superar três fases cheias de desafios, armadilhas e monstros.  
- 🔹 Usar estratégia para coletar itens e fugir de perigos mortais.  

> ⚠️ **Atenção:** Você só tem **3 tentativas** para completar sua missão!

---

## 🎮 Como Jogar

### 🔑 Controles

- `W`, `A`, `S`, `D` → Movimentação (Cima, Esquerda, Baixo, Direita)  
- `I` → Interagir com objetos e NPCs

### ⚔️ Mecânicas do Jogo

| Elemento       | Símbolo | Descrição                         |
|----------------|---------|-----------------------------------|
| **Jogador**    | `&`     | Você, o herói!                    |
| **Parede**     | `*`     | Bloqueia seu caminho              |
| **Chave**      | `@`     | Colete para abrir portas          |
| **Porta**      | `D`     | Trancada até pegar a chave        |
| **Porta Aberta** | `=`   | Passe para a próxima fase         |
| **Espinhos**   | `#`     | Perde uma vida se pisar           |
| **Monstro**    | `X`, `V`| Inimigos que te perseguem         |
| **Teleporte**  | `<`     | Teletransporte para outra área    |

---

## 🌍 Fases do Jogo

### 1️⃣ Vila Inicial
- Objetivo: Encontrar a chave para entrar na masmorra.  
- NPCs dão dicas sobre o que esperar.

### 2️⃣ Fase 1 - Labirinto Inicial
- Mapa pequeno (10x10).  
- Primeiros espinhos e obstáculos.

### 3️⃣ Fase 2 - Caverna dos Espinhos
- Mapa maior (20x20).  
- Monstro que se move a cada 2 turnos.  
- Espinhos aleatórios que reduzem suas vidas.

### 4️⃣ Fase 3 - Masmorra Final
- Mapa gigante (40x40).  
- Monstro inteligente que te persegue.  
- Sistema de teleportes para confundir o jogador.  
- Labirinto complexo com múltiplos caminhos.

---

## ⚙️ Como Executar

### Requisitos
- Compilador C (ex: `GCC`)  
- Terminal ou Prompt de Comando

### Passos

1. Salve o código como `jogo_masmorra.c`  
2. Compile com:
    ```bash
    gcc jogo_masmorra.c -o jogo
    ```
3. Execute:

    - **Windows**:
      ```bash
      jogo.exe
      ```

    - **Linux/Mac**:
      ```bash
      ./jogo
      ```

---

## 🏆 Vitória

Ao completar a Fase 3, você encontrará o **tesouro** e será coroado como o verdadeiro **herói da Masmorra Lendária**! 🏅

---

## 📝 Notas dos Desenvolvedores

Este jogo foi criado para aprimorar habilidades em programação C, incluindo:

- Uso de **matrizes** para construção de mapas  
- Lógica de **movimentação** e **colisão**  
- Sistemas de **interação** com NPCs e itens  
- Geração **procedural de obstáculos**

> 📌 **Dica:** Fale com todos os NPCs para obter **dicas valiosas**!

**Divirta-se e boa sorte na aventura! 🚀**
