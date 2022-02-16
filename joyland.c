#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_STR 50

//      === FEITO POR BIANCA MIRTES ARAÚJO MIRANDA ===      //

void readData(int h, int w, int Mybot[], int porto[], int pos_bots[h][w], int area[h][w], char myId[MAX_STR]){
  char id[MAX_STR];
  int x=0, y=0;
  int n_bots, comp_str;

  // LÊ OS DADOS DA ÁREA DE PESCA.
  for(int i = 0; i < h; i++){   
    for(int j = 0; j < w; j++){
      scanf("%i", &area[i][j]);
      pos_bots[i][j] == 0;       // FORMA UMA MATRIZ COMPOSTA SOMENTE DE ZEROS DO MESMO TAMANHO DA ÁREA DE
      if(area[i][j] == 1){       // PESCA PARA ARMAZENAR AS POSIÇÕES DOS OUTROS BOTS.
         porto[0] = i;      
         porto[1] = j;        // GUARDA AS COORDENADAS DE UM PORTO PARA QUANDO O ESTOQUE ESTIVER CHEIO O BOT 
      }                       // IR PARA ELE E ASSIM EVITAR LEVAR MULTA POR EXCESSO DE CARGA.
    }
  }
  // LÊ OS DADOS DOS BOTS.
  scanf(" BOTS %i", &n_bots);
  for(int i=0; i < n_bots; i++){
    scanf("%s %i %i", id, &x, &y);
    comp_str = strcmp(id, myId);
    if(comp_str == 0){      // ARMAZENA AS COORDENADAS DO MEU BOT.
      Mybot[0] = x;           
      Mybot[1] = y;
    }
    else{
      pos_bots[x][y] = 3; // QUANDO NÃO FOR A POSIÇÃO DO MEU BOT DEMARCA NA MATRIZ POS_BOTS A POSIÇÃO DO BOT
    }                     // EM QUESTÃO.
  }
}

// FUNÇÃO QUE PROCURA O PORTO PARA VENDER A CARGA.
char* busca_porto(int linha, int coluna, int porto[2]){
  if(linha > porto[0]){
      return "UP";
  }
  else if(linha < porto[0]){
      return "DOWN";
  }
  else if(coluna < porto[1]){
      return "RIGHT";
  }
  else if(coluna > porto[1]){
      return "LEFT";
  }
}


char* movimenta_bot(int linha, int coluna, int carga, int altura, int largura, int area[altura][largura], int pos_bots[altura][largura], int bot_loc, int porto[2], int num_aleatorio){
  // A PRINCIPIO, VERIFICA SE HÁ UM PONTO DE PESCA DE ROBALO (PEIXE DE MAIOR LUCRO - 200R$) AO REDOR E VAI
  // ATÉ ELE.
  if(coluna - 1 >= 0 && area[linha][coluna-1] > 31 && area[linha][coluna-1] < 40 && pos_bots[linha][coluna-1] != 3){
    return "LEFT";
  }
  else if (coluna + 1 <= largura-1 && area[linha][coluna+1] > 31 && area[linha][coluna+1] < 40 && pos_bots[linha][coluna+1] != 3){
    return "RIGHT";
  }
  else if (linha - 1 >= 0 && area[linha-1][coluna] > 31 && area[linha-1][coluna] < 40 && pos_bots[linha-1][coluna] != 3){
    return "UP";
  }
  else if (linha + 1 <= altura-1 && area[linha+1][coluna] > 31 && area[linha+1][coluna] < 40 && pos_bots[linha+1][coluna] != 3){
      return "DOWN";
  }
  // EM SEGUIDA, CASO NÃO ENCONTRE UM PONTO DE PESCA DE CIOBA, VERIFICA SE HÁ UM PONTO DE PESCA DE CIOBA 
  // (SEGUNDO PEIXE DE MAIOR LUCRO - 150R$) E VAI ATÉ ELE.
  else if (coluna - 1 >= 0 && area[linha][coluna-1] > 21 && area[linha][coluna-1] < 30 && pos_bots[linha][coluna-1] != 3){
    return "LEFT";
  }
  else if (coluna + 1 <= largura-1 && area[linha][coluna+1] > 21 && area[linha][coluna+1] < 30 && pos_bots[linha][coluna+1] != 3){
    return "RIGHT";
  }
  else if (linha - 1 >= 0 && area[linha-1][coluna] > 21 && area[linha-1][coluna] < 30 && pos_bots[linha-1][coluna] != 3){
    return "UP";
  }
  else if (linha + 1 <= altura-1 && area[linha+1][coluna] > 21 && area[linha+1][coluna] < 30 && pos_bots[linha+1][coluna] != 3){
    return "DOWN";
  }
  // POR FIM, CASO NÃO HAJA NEM PONTOS DE PESCA DE ROBALO NEM DE CIOBA, VERIFICA SE HÁ DE TAINHA 
  // (PEIXE DE MENOR LUCRO - 100R$) E VAI ATÉ ELE. 
  else if (coluna - 1 >= 0 && area[linha][coluna-1] > 11 && area[linha][coluna-1] < 20 && pos_bots[linha][coluna-1] != 3){
    return "LEFT";
  }
  else if (coluna + 1 <= largura-1 && area[linha][coluna+1] > 11 && area[linha][coluna+1] < 20 && pos_bots[linha][coluna+1] != 3){
    return "RIGHT";
  }
  else if (linha - 1 >= 0 && area[linha-1][coluna] > 11 && area[linha-1][coluna] < 20 && pos_bots[linha-1][coluna] != 3){
    return "UP";
  }
  else if (linha + 1 <= altura-1 && area[linha+1][coluna] > 11 && area[linha+1][coluna] < 20 && pos_bots[linha+1][coluna] != 3){
    return "DOWN";
  }
  // CASO O BOT PESQUE TODOS OS PEIXES DE UM PONTO, DEIXANDO 1KG PARA EVITAR A MULTA, VERIFICA SE HÁ ALGUM
  // PONTO DE PESCA (TAINHA, CIOBA OU ROBALO) NAS POSIÇÕES AO REDOR E VAI ATÉ ELE.
  else if(bot_loc == 11 || bot_loc == 21 || bot_loc == 31){
    if(pos_bots[linha][coluna-1] != 3 && coluna - 1 > 0 && ((area[linha][coluna-1] > 31  && area[linha][coluna-1] < 40) || (area[linha][coluna-1] > 21 && area[linha][coluna-1] < 30) || (area[linha][coluna-1] > 11 && area[linha][coluna-1] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+1] != 3 && coluna + 1 < largura && ((area[linha][coluna+1] > 31  && area[linha][coluna+1] < 40) || (area[linha][coluna+1] > 21 && area[linha][coluna+1] < 30) || (area[linha][coluna+1] > 11 && area[linha][coluna+1] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+1][coluna] != 3 && linha + 1 < altura && ((area[linha+1][coluna] > 31  && area[linha+1][coluna] < 40) || (area[linha+1][coluna] > 21 && area[linha+1][coluna] < 30) || (area[linha+1][coluna] > 11 && area[linha+1][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-1][coluna] != 3 && linha - 1 > 0  && ((area[linha-1][coluna] > 31  && area[linha-1][coluna] < 40) || (area[linha-1][coluna] > 21 && area[linha-1][coluna] < 30) || (area[linha-1][coluna] > 11 && area[linha-1][coluna] < 20))){
      return "UP";
    }
    // CASO NÃO ENCONTRE AO REDOR, VERIFICA EM PONTOS MAIS AFASTADOS:
    // DUAS POSIÇÕES.
    else if(pos_bots[linha][coluna-2] != 3 && coluna - 1 > 0 && ((area[linha][coluna-2] > 31  && area[linha][coluna-2] < 40) || (area[linha][coluna-2] > 21 && area[linha][coluna-2] < 30) || (area[linha][coluna-2] > 11 && area[linha][coluna-2] < 20))){
        return "LEFT";
    }
    else if(pos_bots[linha][coluna+2] != 3 && coluna + 1 < largura && ((area[linha][coluna+2] > 31  && area[linha][coluna+2] < 40) || (area[linha][coluna+2] > 21 && area[linha][coluna+2] < 30) || (area[linha][coluna+2] > 11 && area[linha][coluna+2] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+2][coluna] != 3 && linha + 1 < altura && ((area[linha+2][coluna] > 31  && area[linha+2][coluna] < 40) || (area[linha+2][coluna] > 21 && area[linha+2][coluna] < 30) || (area[linha+2][coluna] > 11 && area[linha+2][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-2][coluna] != 3 && linha - 1 > 0  && ((area[linha-2][coluna] > 31  && area[linha-2][coluna] < 40) || (area[linha-2][coluna] > 21 && area[linha-2][coluna] < 30) || (area[linha-2][coluna] > 11 && area[linha-2][coluna] < 20))){
      return "UP";
    }
    // TRÊS POSIÇÕES.
    else if(pos_bots[linha][coluna-3] != 3 && coluna - 1 > 0 && ((area[linha][coluna-3] > 31  && area[linha][coluna-3] < 40) || (area[linha][coluna-3] > 21 && area[linha][coluna-2] < 30) || (area[linha][coluna-3] > 11 && area[linha][coluna-3] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+3] != 3 && coluna + 1 < largura && ((area[linha][coluna+3] > 31  && area[linha][coluna+3] < 40) || (area[linha][coluna+3] > 21 && area[linha][coluna+3] < 30) || (area[linha][coluna+3] > 11 && area[linha][coluna+3] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+3][coluna] != 3 && linha + 1 < altura && ((area[linha+3][coluna] > 31  && area[linha+3][coluna] < 40) || (area[linha+3][coluna] > 21 && area[linha+3][coluna] < 30) || (area[linha+3][coluna] > 11 && area[linha+3][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-3][coluna] != 3 && linha - 1 > 0  && ((area[linha-3][coluna] > 31  && area[linha-3][coluna] < 40) || (area[linha-3][coluna] > 21 && area[linha-3][coluna] < 30) || (area[linha-3][coluna] > 11 && area[linha-3][coluna] < 20))){
      return "UP";
    }
    // QUATRO POSIÇÕES.
    else if(pos_bots[linha][coluna-4] != 3 && coluna - 1 > 0 && ((area[linha][coluna-4] > 31  && area[linha][coluna-4] < 40) || (area[linha][coluna-4] > 21 && area[linha][coluna-4] < 30) || (area[linha][coluna-4] > 11 && area[linha][coluna-4] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+4] != 3 && coluna + 1 < largura && ((area[linha][coluna+4] > 31  && area[linha][coluna+4] < 40) || (area[linha][coluna+4] > 21 && area[linha][coluna+4] < 30) || (area[linha][coluna+4] > 11 && area[linha][coluna+4] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+4][coluna] != 3 && linha + 1 < altura && ((area[linha+4][coluna] > 31  && area[linha+4][coluna] < 40) || (area[linha+4][coluna] > 21 && area[linha+4][coluna] < 30) || (area[linha+4][coluna] > 11 && area[linha+4][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-4][coluna] != 3 && linha - 1 > 0  && ((area[linha-4][coluna] > 31  && area[linha-4][coluna] < 40) || (area[linha-4][coluna] > 21 && area[linha-4][coluna] < 30) || (area[linha-4][coluna] > 11 && area[linha-4][coluna] < 20))){
      return "UP";
    }
    // CASO NENHUMA DAS CONDIÇÕES ACIMA SEJAM ATENDIDAS O BOT IRÁ SE MOVIMENTAR PARA A PRIMEIRA DIREÇÃO QUE
    // ESTIVER DENTRO DO LIMITE DA ÁREA.
    else{
      if(coluna - 1 >= 0){
        return "LEFT";
      }
      else if(coluna + 1 <= largura-1){
        return "RIGHT";
      }
      else if(linha - 1 >= 0){
        return "UP";
      }
      else if(linha + 1 <= altura-1){
        return "DOWN";
      }
    }
  }
  // CASO O BOT ESTEJA NA POSIÇÃO EM QUE HÁ APENAS MAR, VERIFICA SE HÁ UM PONTO DE PESCA (ROBALO, CIOBA OU 
  // TAINHA) AO REDOR E VAI ATÉ ELE. 
  else if(bot_loc == 0){
    if(pos_bots[linha][coluna-1] != 3 && coluna - 1 > 0 && ((area[linha][coluna-1] > 31  && area[linha][coluna-1] < 40) || (area[linha][coluna-1] > 21 && area[linha][coluna-1] < 30) || (area[linha][coluna-1] > 11 && area[linha][coluna-1] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+1] != 3 && coluna + 1 < largura && ((area[linha][coluna+1] > 31  && area[linha][coluna+1] < 40) || (area[linha][coluna+1] > 21 && area[linha][coluna+1] < 30) || (area[linha][coluna+1] > 11 && area[linha][coluna+1] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+1][coluna] != 3 && linha + 1 < altura && ((area[linha+1][coluna] > 31  && area[linha+1][coluna] < 40) || (area[linha+1][coluna] > 21 && area[linha+1][coluna] < 30) || (area[linha+1][coluna] > 11 && area[linha+1][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-1][coluna] != 3 && linha - 1 > 0  && ((area[linha-1][coluna] > 31  && area[linha-1][coluna] < 40) || (area[linha-1][coluna] > 21 && area[linha-1][coluna] < 30) || (area[linha-1][coluna] > 11 && area[linha-1][coluna] < 20))){
      return "UP";
    }
    // CASO NÃO ENCONTRE AO REDOR, VERIFICA EM PONTOS MAIS AFASTADOS:
    // DUAS POSIÇÕES.
    else if(pos_bots[linha][coluna-2] != 3 && coluna - 1 > 0 && ((area[linha][coluna-2] > 31  && area[linha][coluna-2] < 40) || (area[linha][coluna-2] > 21 && area[linha][coluna-2] < 30) || (area[linha][coluna-2] > 11 && area[linha][coluna-2] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+2] != 3 && coluna + 1 < largura && ((area[linha][coluna+2] > 31  && area[linha][coluna+2] < 40) || (area[linha][coluna+2] > 21 && area[linha][coluna+2] < 30) || (area[linha][coluna+2] > 11 && area[linha][coluna+2] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+2][coluna] != 3 && linha + 1 < altura && ((area[linha+2][coluna] > 31  && area[linha+2][coluna] < 40) || (area[linha+2][coluna] > 21 && area[linha+2][coluna] < 30) || (area[linha+2][coluna] > 11 && area[linha+2][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-2][coluna] != 3  && linha - 1 > 0  && ((area[linha-2][coluna] > 31  && area[linha-2][coluna] < 40) || (area[linha-2][coluna] > 21 && area[linha-2][coluna] < 30) || (area[linha-2][coluna] > 11 && area[linha-2][coluna] < 20))){
      return "UP";
    }
    // TRÊS POSIÇÕES.
    else if(pos_bots[linha][coluna-3] != 3 && coluna - 1 > 0 && ((area[linha][coluna-3] > 31  && area[linha][coluna-3] < 40) || (area[linha][coluna-3] > 21 && area[linha][coluna-2] < 30) || (area[linha][coluna-3] > 11 && area[linha][coluna-3] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+3] != 3 && coluna + 1 < largura && ((area[linha][coluna+3] > 31  && area[linha][coluna+3] < 40) || (area[linha][coluna+3] > 21 && area[linha][coluna+3] < 30) || (area[linha][coluna+3] > 11 && area[linha][coluna+3] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+3][coluna] != 3 && linha + 1 < altura && ((area[linha+3][coluna] > 31  && area[linha+3][coluna] < 40) || (area[linha+3][coluna] > 21 && area[linha+3][coluna] < 30) || (area[linha+3][coluna] > 11 && area[linha+3][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-3][coluna] != 3 && linha - 1 > 0  && ((area[linha-3][coluna] > 31  && area[linha-3][coluna] < 40) || (area[linha-3][coluna] > 21 && area[linha-3][coluna] < 30) || (area[linha-3][coluna] > 11 && area[linha-3][coluna] < 20))){
      return "UP";
    }
    // QUATRO POSIÇÕES.
    else if(pos_bots[linha][coluna-4] != 3 && coluna - 1 > 0 && ((area[linha][coluna-4] > 31  && area[linha][coluna-4] < 40) || (area[linha][coluna-4] > 21 && area[linha][coluna-4] < 30) || (area[linha][coluna-4] > 11 && area[linha][coluna-4] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+4] != 3 && coluna + 1 < largura && ((area[linha][coluna+4] > 31  && area[linha][coluna+4] < 40) || (area[linha][coluna+4] > 21 && area[linha][coluna+4] < 30) || (area[linha][coluna+4] > 11 && area[linha][coluna+4] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+4][coluna] != 3 && linha + 1 < altura && ((area[linha+4][coluna] > 31  && area[linha+4][coluna] < 40) || (area[linha+4][coluna] > 21 && area[linha+4][coluna] < 30) || (area[linha+4][coluna] > 11 && area[linha+4][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-4][coluna] != 3 && linha - 1 > 0  && ((area[linha-4][coluna] > 31  && area[linha-4][coluna] < 40) || (area[linha-4][coluna] > 21 && area[linha-4][coluna] < 30) || (area[linha-4][coluna] > 11 && area[linha-4][coluna] < 20))){
      return "UP";
    }
    // CASO NENHUMA DAS CONDIÇÕES ACIMA SEJAM ATENDIDAS O BOT IRÁ SE MOVIMENTAR PARA A PRIMEIRA DIREÇÃO QUE
    // ESTIVER DENTRO DO LIMITE DA ÁREA.
    else{
      if(coluna - 1 > 0){
        return "LEFT";
      }
      else if(coluna + 1 < largura){
        return "RIGHT";
      }
      else if(linha - 1 > 0){
        return "UP";
      }
      else if(linha + 1 < altura){
        return "DOWN";
      }
    }
  }
  // CASO O BOT ESTEJA EM UM PORTO E JÁ TENHA VENDIDO SUA CARGA OU NÃO POSSUA CARGA AINDA PARA VENDER,
  // VERIFICA SE HÁ UM PONTO DE PESCA (ROBALO, CIOBA OU TAINHA) AO REDOR E VAI ATÉ ELE.
  else if(bot_loc == 1){
    if(pos_bots[linha][coluna-1] != 3 && coluna - 1 > 0 && ((area[linha][coluna-1] > 31  && area[linha][coluna-1] < 40) || (area[linha][coluna-1] > 21 && area[linha][coluna-1] < 30) || (area[linha][coluna-1] > 11 && area[linha][coluna-1] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+1] != 3 && coluna + 1 < largura && ((area[linha][coluna+1] > 31  && area[linha][coluna+1] < 40) || (area[linha][coluna+1] > 21 && area[linha][coluna+1] < 30) || (area[linha][coluna+1] > 11 && area[linha][coluna+1] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+1][coluna] != 3 && linha + 1 < altura && ((area[linha+1][coluna] > 31  && area[linha+1][coluna] < 40) || (area[linha+1][coluna] > 21 && area[linha+1][coluna] < 30) || (area[linha+1][coluna] > 11 && area[linha+1][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-1][coluna] != 3 && linha - 1 > 0  && ((area[linha-1][coluna] > 31  && area[linha-1][coluna] < 40) || (area[linha-1][coluna] > 21 && area[linha-1][coluna] < 30) || (area[linha-1][coluna] > 11 && area[linha-1][coluna] < 20))){
      return "UP";
    }
    // CASO NÃO ENCONTRE AO REDOR, VERIFICA EM PONTOS MAIS AFASTADOS:
    // DUAS POSIÇÕES.
    else if(pos_bots[linha][coluna-2] != 3 && coluna - 1 > 0 && ((area[linha][coluna-2] > 31  && area[linha][coluna-2] < 40) || (area[linha][coluna-2] > 21 && area[linha][coluna-2] < 30) || (area[linha][coluna-2] > 11 && area[linha][coluna-2] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+2] != 3 && coluna + 1 < largura && ((area[linha][coluna+2] > 31  && area[linha][coluna+2] < 40) || (area[linha][coluna+2] > 21 && area[linha][coluna+2] < 30) || (area[linha][coluna+2] > 11 && area[linha][coluna+2] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+2][coluna] != 3 && linha + 1 < altura && ((area[linha+2][coluna] > 31  && area[linha+2][coluna] < 40) || (area[linha+2][coluna] > 21 && area[linha+2][coluna] < 30) || (area[linha+2][coluna] > 11 && area[linha+2][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-2][coluna] != 3  && linha - 1 > 0  && ((area[linha-2][coluna] > 31  && area[linha-2][coluna] < 40) || (area[linha-2][coluna] > 21 && area[linha-2][coluna] < 30) || (area[linha-2][coluna] > 11 && area[linha-2][coluna] < 20))){
      return "UP";
    }
    // TRÊS POSIÇÕES.
    else if(pos_bots[linha][coluna-3] != 3 && coluna - 1 > 0 && ((area[linha][coluna-3] > 31  && area[linha][coluna-3] < 40) || (area[linha][coluna-3] > 21 && area[linha][coluna-2] < 30) || (area[linha][coluna-3] > 11 && area[linha][coluna-3] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+3] != 3 && coluna + 1 < largura && ((area[linha][coluna+3] > 31  && area[linha][coluna+3] < 40) || (area[linha][coluna+3] > 21 && area[linha][coluna+3] < 30) || (area[linha][coluna+3] > 11 && area[linha][coluna+3] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+3][coluna] != 3 && linha + 1 < altura && ((area[linha+3][coluna] > 31  && area[linha+3][coluna] < 40) || (area[linha+3][coluna] > 21 && area[linha+3][coluna] < 30) || (area[linha+3][coluna] > 11 && area[linha+3][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-3][coluna] != 3 && linha - 1 > 0  && ((area[linha-3][coluna] > 31  && area[linha-3][coluna] < 40) || (area[linha-3][coluna] > 21 && area[linha-3][coluna] < 30) || (area[linha-3][coluna] > 11 && area[linha-3][coluna] < 20))){
      return "UP";
    }
    // QUATRO POSIÇÕES.
    else if(pos_bots[linha][coluna-4] != 3 && coluna - 1 > 0 && ((area[linha][coluna-4] > 31  && area[linha][coluna-4] < 40) || (area[linha][coluna-4] > 21 && area[linha][coluna-4] < 30) || (area[linha][coluna-4] > 11 && area[linha][coluna-4] < 20))){
      return "LEFT";
    }
    else if(pos_bots[linha][coluna+4] != 3 && coluna + 1 < largura && ((area[linha][coluna+4] > 31  && area[linha][coluna+4] < 40) || (area[linha][coluna+4] > 21 && area[linha][coluna+4] < 30) || (area[linha][coluna+4] > 11 && area[linha][coluna+4] < 20))){
      return "RIGHT";
    }
    else if(pos_bots[linha+4][coluna] != 3 && linha + 1 < altura && ((area[linha+4][coluna] > 31  && area[linha+4][coluna] < 40) || (area[linha+4][coluna] > 21 && area[linha+4][coluna] < 30) || (area[linha+4][coluna] > 11 && area[linha+4][coluna] < 20))){
      return "DOWN";
    }
    else if(pos_bots[linha-4][coluna] != 3 && linha - 1 > 0  && ((area[linha-4][coluna] > 31  && area[linha-4][coluna] < 40) || (area[linha-4][coluna] > 21 && area[linha-4][coluna] < 30) || (area[linha-4][coluna] > 11 && area[linha-4][coluna] < 20))){
      return "UP";
    }
    // CASO NENHUMA DAS CONDIÇÕES ACIMA SEJAM ATENDIDAS O BOT IRÁ PARA A PRIMEIRA POSIÇÃO QUE ESTIVER
    // DENTRO DOS LIMITES DA ÁREA.
    else{
      if(coluna - 1 > 0){
        return "LEFT";
      }
      else if(coluna + 1 < largura){
        return "RIGHT";
      }
      else if(linha - 1 > 0){
        return "UP";
      }
      else if(linha + 1 < altura){
        return "DOWN";
      }
    }
  }
  // CASO NÃO NENHUMA DAS CONDIÇÕES SEJAM SATISFEITAS O BOT VAI PARA UM PONTO ALEATORIO QUE NÃO ESTEJA OCUPADO
  // POR OUTRO BOT DE ACORDO COM A VARIAVEL NUM_ALEATORIO.
  else{
    if (coluna - 1 >= 0 && num_aleatorio == 0 && pos_bots[linha][coluna-1] != 3){
      return "LEFT";
    }
    else if (coluna + 1 <= largura-1 && num_aleatorio == 1 && pos_bots[linha][coluna+1] != 3){
      return "RIGHT";
    }
    else if (linha - 1 >= 0 && num_aleatorio == 2 && pos_bots[linha-1][coluna] != 3){
      return "UP";
    }
    else if (linha + 1 <= altura-1 && num_aleatorio == 3 && pos_bots[linha+1][coluna] != 3){
      return "DOWN";
    }
  }
}


int main(){
  char line[MAX_STR]; // DADOS TEMPORÁRIOS
  char myId[MAX_STR]; // IDENTIFICADOR DO MEU BOT

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
    int h, w;

    scanf("AREA %i %i", &h, &w); // LÊ A ÁREA DE PESCA: h(ALTURA) x w(LARGURA)
    scanf(" ID %s", myId);       // LÊ O IDENTIFICADOR DO MEU BOT 

    int porto[2], pos_bots[h][w], area[h][w];
    int Mybot[2];      // ARMAZENA AS COORDENADAS DO MEU BOT
    int carga = 0;
    srand(time(NULL)); // UTILIZA A FUNÇÃO time(NULL) PARA QUE A CADA EXECUÇÃO A SEMENTE DA FUNÇÃO RAND 
                       // SEJA DIFERENTE 
    while(1){
      // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
        readData(h, w, Mybot, porto, pos_bots, area, myId);

        int linha = Mybot[0];
        int coluna = Mybot[1];
        int bot_loc = area[linha][coluna];
        int num_aleatorio = rand()%3;

        // CASO ENCONTRE UM PORTO E TENHA CARGA PARA VENDER 
        if(bot_loc == 1 && carga > 0){
            printf("SELL\n");
            carga = 0;
        }
        // CASO ENCONTRE QUALQUER PONTO DE PESCA (TAINHA, CIOBA OU ROBALO) E A CARGA AINDA NÃO TENHA ATINGIDO O LIMITE
        else if((bot_loc > 11 && bot_loc < 20 && carga < 10) || (bot_loc > 21 && bot_loc < 30 && carga < 10) || (bot_loc > 31 && bot_loc < 40 && carga < 10)){
            carga++;
            printf("FISH\n");
        }
        // CASO A CARGA CHEGUE A 10KG, PROCURA UM PORTO PARA VENDER CARGA
        else if(carga == 10){
          printf("%s\n", busca_porto(linha, coluna, porto));
        }
        // MOVIMENTAÇÃO DO BOT
        else{
          printf("%s\n", movimenta_bot(linha, coluna, carga, h, w, area, pos_bots, bot_loc, porto, num_aleatorio));
        }
        // LÊ QUAL FOI O RESULTADO DA AÇÃO (E EVENTUALMENTE ATUALIZA OS DADOS DO BOT).
        scanf("%s", line);
    }
    return 0;
}