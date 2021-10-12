#include <stdio.h>
#include <stdlib.h>


int main()
{
    char email[50];
    char nome[30];
    char senha[30];
    char confirmacao;


    printf("Voce tem já tem conta? S/N:");
    scanf("%s", &confirmacao);
    //scanf("%s", &senha);
    if(confirmacao == 'S'){

    }else{
        printf("Cadastre-se:\nEntre com seu nome: ");
        scanf("%s", &nome);
        printf("Entre com seu email: ");
        scanf("%s", &email);
        printf("Entre com sua senha: ");
        scanf("%s", &senha);
    }


}
