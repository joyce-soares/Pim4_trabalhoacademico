#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define LOGIN_USER "admin"
#define LOGIN_PASSWORD "admin123"

static char user[50];
static char password[50];

void login();
void menu();
void registerPatient();
void listPatients();
void backMenu();
void limparBuffer(void);

int main()
{

    printf("\t>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("\t>>>>>| BEM-VINDO(A) |>>>>>\n");
    printf("\t>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");

    login();


return 0;
}
void login(){

    printf("Por favor, faca login para continuar: \n\nUsuario: ");
    scanf("%s", &user);
    printf("Senha: ");
    scanf("%s", &password);

    int comp1 = strncmp(user, LOGIN_USER, 5);
    int comp2 = strncmp(password, LOGIN_PASSWORD, 8);

    if((comp1 == 0) && (comp2 == 0)){
       menu();
    }else{
        printf("Erro ao efetuar login, por favor, tente novamente.");
    }
}

void menu(){
    printf("\nO que voce deseja fazer? :\n");
    printf("1 - Cadastrar Paciente\n");
    printf("2 - Listar Pacientes\n");
    printf("3 - Sair\n");

    int option;
    scanf("%d", &option);

    switch(option){
    case 1:
       registerPatient();
        break;
    case 2:
        listPatients();
        break;
    case 3:
        printf("Ate a proxima!!");
        Sleep(2);
        //exit(0);
        break;
    default:
        printf("Opcao Invalida! Tente outra opcao, por favor:");
        Sleep(2);
        menu();
        break;
    }
}

void registerPatient(){

    FILE *file;
    file = fopen("CADASTRO_PACIENTES.txt","a");

    char nome[30];
    char cpf[30];
    char telefone[30];
    int nascimento[20];
    char email[50];
    char dataDiagnostico[20];
    char comorbidade[500];



    printf("Digite nome do paciente:\n ");
    scanf("%s", nome);
    limparBuffer();
    fprintf(file,"%s", nome);

    printf("Digite CPF do paciente:\n ");
    scanf(" %s", cpf);
    fprintf(file,"%s", cpf);

    printf("Digite telefone do paciente:\n ");
    scanf(" %s", telefone);
    fprintf(file,"%s", telefone);

    printf("Digite nascimento do paciente:\n ");
    scanf(" %s", nascimento);
    fprintf(file,"%s", nascimento);

    printf("Digite email do paciente:\n ");
    scanf(" %s", email);
    fprintf(file,"%s", email);

    printf("Digite a data de diagnostico do paciente:\n ");
    scanf(" %s", dataDiagnostico);
    fprintf(file,"%s", dataDiagnostico);

    printf("Digite comorbidade do paciente:\n ");
    scanf(" %s", comorbidade);
    fprintf(file,"%s", comorbidade);

    fclose(file);

    printf("Paciente registrado. \nDeseja voltar ao menu? S/N\n");
    backMenu();
}

void listPatients(){
    printf("Pacientes listados. \nDeseja voltar ao menu? S/N\n");
    backMenu();
}

void backMenu(){
     char op;
    fflush(stdin);
    scanf("%c", &op);
    if(op == 's'){
        menu();
    }else{
        exit(0);
    }
}
//FUNCAO PARA LIM PAR BUFFER
void limparBuffer(void){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
