#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define LOGIN_USER "admin"
#define LOGIN_PASSWORD "admin123"

static char user[50];
static char password[50];


typedef struct{
    char nome[50];
    char email[50];
    char cpf[20];
    char telefone[20];
    char dataNascimento[20];
    char dataDiagnostico[20];
    char comorbidade[30];
}Paciente;


void login();
void menu();
void registerPatient();
void listPatients();
void backMenu();
FILE* abreArquivo(char caminho[30], char modo);
void verificaPacienteGrupoRisco(char dataNascimento[20]);
void addOutroArquivo(int idade);

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
        login();
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
        exit(0);
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
    file = abreArquivo("pacientes_cadastrados.txt", 'a');
    if (file == NULL) {
        printf("Erro ao cadastrar.");
        exit(0);
    }else {

    Paciente paciente;

    printf("Digite nome do paciente:\n ");
    fflush(stdin);
    fgets(paciente.nome, 50, stdin);
    fprintf(file,"Nome: %s", paciente.nome);

    printf("Digite CPF do paciente:");
    fgets(paciente.cpf, 20, stdin);
    fprintf(file,"Cpf: %s\n", paciente.cpf);

    printf("Digite telefone do paciente:");
    fgets(paciente.telefone, 20, stdin);
    fprintf(file,"Telefone: %s\n", paciente.telefone);

    printf("Digite nascimento do paciente:");
    fgets(paciente.dataNascimento, 20, stdin);
    fprintf(file,"Data de nascimento: %s", paciente.dataNascimento);

    printf("Digite email do paciente:");
    fgets(paciente.email, 50, stdin);
    fprintf(file,"Email: %s\n", paciente.email);

    printf("Digite a data de diagnostico do paciente:");
    fgets(paciente.dataDiagnostico, 20, stdin);
    fprintf(file,"Data do diagnostico: %s", paciente.dataDiagnostico);

    printf("O paciente possui comorbidade?: S/N ");
     //fflush(stdin);
    char op;
    scanf("%c", &op);
    if(op == 's' || op == 'S'){
        //fflush(stdin);
        fgets(paciente.comorbidade, 30, stdin);
        fprintf(file,"Comorbidade: %s", paciente.comorbidade);
        verificaPacienteGrupoRisco(paciente.dataNascimento);
    }
    fclose(file);
    printf("Paciente registrado.\nDeseja voltar ao menu? S/N\n");
    backMenu();
    }
}

void listPatients(){

    FILE *arquivo;
    Paciente paciente;
    char conteudo[50];
    arquivo = abreArquivo("pacientes_cadastrados.txt", 'r');
    if(arquivo != NULL){
       /* while(!feof(arquivo)){
            fscanf(arquivo, "%s %s %s %s %s %s ", &paciente.nome, &paciente.cpf,  paciente.telefone, paciente.dataNascimento, paciente.dataDiagnostico, paciente.comorbidade);
            printf("Nome: %s\nCPF: %s\nTelefone: %s\nData de Nascimento: %s\nEmail: %s\nData de diagnostico: %s/\nComorbidade: %s\n\n", paciente.nome, paciente.cpf, paciente.telefone, paciente.dataNascimento, paciente.dataDiagnostico, paciente.comorbidade);
        }*/

        while(fgets(conteudo, 50, arquivo) != NULL){
            printf("%s", conteudo);
        }


    }else{
        printf("arquivo nao encontrado!!");
    }

    printf("\nDeseja voltar ao menu? S/N\n");
    backMenu();
}

void backMenu(){
     char op;
    fflush(stdin);
    scanf("%c", &op);
    if(op == 's' || op == 'S'){
        system("cls");
        menu();
    }else{
        exit(0);
    }

}

FILE* abreArquivo(char caminho[30], char modo){
    FILE *arquivo;
    switch (modo){
    case 'g' :
        arquivo = fopen(caminho, "w");
        break;
    case 'r' :
        arquivo = fopen (caminho, "r");
        break;
    case 'a' :
        arquivo = fopen (caminho, "a");
        break;
    if (arquivo == NULL){
        printf("Nao foi possivel abrir o arquivo.");
        exit(0);
    }
    return arquivo;
    }
}

void verificaPacienteGrupoRisco(char dataNascimento[20]){

    char *ano = strtok(dataNascimento, "/");
    ano = strtok(NULL, "/");
    ano = strtok(NULL, "/");
    int anoNasc = atoi(ano);

    int anoAtual;//Esta variável foi criada para receber o resultado do comando que exibe o ano atual.
    time_t data_ano;//Foi criada uma variável chamada data_ano que é do tipo time_t que é um tipo de variável que recebe valores de data e hora.
    time(&data_ano);
    struct tm *data = localtime(&data_ano);
    anoAtual = (data->tm_year+1900);

    int idade = anoAtual - anoNasc;
    if(idade > 65){
        addOutroArquivo(idade);
    }
}

void addOutroArquivo(int idade){

    FILE *file;
    file = abreArquivo("pacientes_grupo_de_risco.txt", 'a');
     if (file == NULL) {
        printf("Erro ao cadastrar.");
        exit(0);
    }else {
        char cep[10];
        printf("Este paciente e do grupo de risco, por pavor preencher as informacoes:\nCEP do paciente: ");
        fflush(stdin);
        fgets(cep, 20, stdin);
        fprintf(file,"CEP: %s", cep);
        fprintf(file,"Idade: %d", idade);
        fclose(file);
    }
}
