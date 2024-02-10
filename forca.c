#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

//varaiaveis globais
char palavrasecreta[TAMANHO_DA_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura(){
    printf("****************************\n");
    printf("*      Jogo da Forca       *\n");
    printf("****************************\n\n");
}

void chuta(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        
            if(chutes[j] == letra){
                    achou = 1;
                    break;
            }
        }
        return achou;
}

void desenhaforca(){
    int erros = chuteserrados();

    printf("  _______            \n");
    printf(" |/      |           \n");
    printf(" |      %c%c%c       \n", (erros >= 1 ? '(' : ' ') , (erros >= 1 ? '_' : ' '), (erros>=1 ? ')' : ' ')); 
    printf(" |      %c%c%c       \n", (erros >=3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros>=3 ? '/' : ' ')); 
    printf(" |       %c          \n", (erros >=2 ? '|' : ' '));
    printf(" |      %c           \n", (erros >=4 ? '/' : ' '));
    printf(" |                   \n");
    printf("_|___                \n");
    printf("\n\n");

    for(int i =0; i < strlen(palavrasecreta);i++){

            //aqui estava o codigo
            int achou =  jachutou(palavrasecreta[i]); 
            if(achou){
                printf("%c",palavrasecreta[i]);
            } else{
                printf("_");
            }
        }
        printf("\n");
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta);i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

void escolhepalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f==0){
        printf("DESCULPE, BANCO DE DADOS NAO DISPONIVEL\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta);

    }

    fclose(f);
}

void adicionapalavra(){
    char quer;
    printf("VOCE DESEJA ADICIONAR UMA NOVA PALAVRA AO JOGO? (S/N)\n");
    scanf(" %c", &quer);

    if(quer=='S'){
        char novapalavra[TAMANHO_DA_PALAVRA];
        printf("Qual a nova palavra?");
        scanf("%s",novapalavra);

        FILE* f = fopen("palavras.txt", "r+");
        if(f==0){
        printf("DESCULPE, BANCO DE DADOS NAO DISPONIVEL\n\n");
        exit(1);
    }

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }

}

int chuteserrados(){
    int erros = 0; 
    
    for(int i =0; i < chutesdados; i++){
        int existe = 0;
        
        for(int j = 0; j < strlen(palavrasecreta); j++){
            
            if(chutes[i] == palavrasecreta[j]){

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }

    return erros;
}
int enforcou(){

    return chuteserrados() >= 5;
}
int main(){
    
    escolhepalavra();
    abertura();

    do{
        desenhaforca();
        chuta();


    }while(!acertou() && !enforcou());

    if(acertou()){
        printf("\nPARABENS, VOCE GANHOU!\n\n");

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

    }else{
        printf("\nPUXA, VOCE FOI ENFORCADO!\n");
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