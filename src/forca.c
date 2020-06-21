#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

int chutesdados = 0; 
char chutes[20];
char palavrasecreta[TAMANHO_PALAVRA];

void abertura() {

  printf("**********************\n");
  printf("*   Jogo de Forca    *\n");
  printf("**********************\n \n");

}

void escolhepalavra(){
  sprintf(palavrasecreta, "MELANCIA");
  
  FILE* f;

  f = fopen("palavras.txt", "r");
  if(f == 0) {
    printf("Banco de dados de palavras não disponivel\n\n");
    exit(1);
  }

  int qtnddepalavras; 
  fscanf(f, "%d", &qtnddepalavras);

  srand(time(0)); 
  int randomico = rand() % qtnddepalavras; 

  for(int i = 0;  i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
  }

  fclose(f); 

}

void adicionapalavra() {

  char quer; 

  printf("\nVoce deseja acicionar uma nova palavra no jogo? (S/N) \n");
  scanf(" %c", &quer); 

  if(quer == 'S') {
    char novapalavra[TAMANHO_PALAVRA]; 
  
    printf("Qual a nova palavra? \n");
    scanf("%s", novapalavra);

    FILE* f;
    f = fopen("palavras.txt", "r+");
    if(f == 0) {
      printf("Desculpe, banco de dados nao disponibel \n\n"); 
      exit(1);
    }

    int qtd;
    fscanf(f, "%d", &qtd); 
    qtd++; 

    fseek(f, 0, SEEK_SET); 
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
  
  
}

void chuta () {

  char chute;  

  printf("Qual a letra? \n");
  scanf(" %c", &chute);

  chutes[(chutesdados)] = chute;

  (chutesdados)++;    

}

int jachutou(char letra) {

  int achou = 0; 

  for (int j =0; j < chutesdados; j++) {

    if(letra == chutes[j]) {
      achou = 1;
      break; 
    }
  }

  return achou; 
}

void desenhaforca() {
  
  int erros = chuteserrados();

  printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

  for(int i = 0; i < strlen(palavrasecreta); i++) {

    if(jachutou(palavrasecreta[i])) {
    
      printf("%c ", palavrasecreta[i]); 
    
    } else {
    
      printf("_ "); 
    
    }
  }

  printf("\n");

}

int acertou() {
  
  for (int i = 0; i < strlen(palavrasecreta); i++) {
    if(!jachutou(palavrasecreta[i])){
      return 0; 
    }
  }

  return 1; 
}

int chuteserrados() {
  int erros = 0; 

    for(int i= 0; i < chutesdados; i++) {
      
      int achou = 0; 
      for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(palavrasecreta[j] == chutes[i]) {
          achou = 1;
          break;  
        }
      }

      if(!achou) {
        erros++; 
      }

    }

    return erros;
}

int enforcou() {
  return chuteserrados() >= 5; 
}

int main() {
  
  abertura();
  escolhepalavra();

  do {
    
    desenhaforca();
    chuta();

    printf("Você já deu %d chutes\n", chutesdados);

  } while(!acertou() && !enforcou()); 

  if(acertou()) {

    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

  } else {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }

  adicionapalavra();
}