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
    char name[50];
    char email[50];
    char cpf[20];
    char phoneNumber[20];
    char fullAddress[500];
    char cep[20];
    char birthDate[20];
    char diagnosisDate[20];
    char comorbidity[30];
}Patient;


void login();
void menu();
void registerPatient();
void listPatients();
void backMenu();
FILE* openFile(char path[30], char mode);
void checkPatientRiskGroup(int age, char cep[20]);
void addHealthSecretaryFile(int age, char cep[20]);
int calculateAge(char birthDate[20]);

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
        printf("Erro ao efetuar login, tente novamente.");
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
    file = openFile("pacientes_cadastrados.txt", 'a');
    if (file == NULL) {
        printf("Erro ao cadastrar.");
        exit(0);
    }else {

    Patient patient;
    int age;

    printf("Digite nome do paciente: ");
    fflush(stdin);
    fgets(patient.name, 50, stdin);
    fprintf(file,"Nome: %s", patient.name);

    printf("Digite CPF: ");
    fgets(patient.cpf, 20, stdin);
    fprintf(file,"CPF: %s", patient.cpf);

    printf("Digite telefone: ");
    fgets(patient.phoneNumber, 20, stdin);
    fprintf(file,"Telefone: %s", patient.phoneNumber);

    printf("Digite email do paciente: ");
    fgets(patient.email, 50, stdin);
    fprintf(file,"Email: %s", patient.email);

    printf("Digite o CEP: ");
    fgets(patient.cep, 20, stdin);
    fprintf(file,"CEP: %s", patient.cep);

    printf("Endereco completo: \nBairro, Rua, Numero, Cidade, Estado.\n");
    fgets(patient.fullAddress, 500, stdin);
    fprintf(file,"Endereco: %s", patient.fullAddress);

    printf("Digite nascimento do paciente: ");
    fgets(patient.birthDate, 20, stdin);
    fprintf(file,"Data de nascimento: %s", patient.birthDate);

    printf("Digite a data de diagnostico do paciente: ");
    fgets(patient.diagnosisDate, 20, stdin);
    fprintf(file,"Data do diagnostico: %s", patient.diagnosisDate);

    printf("O paciente possui comorbidade? S/N ");
    char op;
    scanf("%c", &op);
    if(op == 's' || op == 'S'){
        fflush(stdin);
        printf("Digite a comorbidade do paciente: ");
        fgets(patient.comorbidity, 30, stdin);
        fprintf(file,"Comorbidade: %s\n", patient.comorbidity);
        age = calculateAge(patient.birthDate);
        addHealthSecretaryFile(age, patient.cep);
    }else {
        checkPatientRiskGroup(age, patient.cep);
        fprintf(file,"Comorbidade: Nao possui comorbidade\n");
    }
    fclose(file);
    printf("Paciente registrado.\nDeseja voltar ao menu? S/N\n");
    backMenu();
    }
}

void listPatients(){

    FILE *file;
    char contents[50];
    file = openFile("pacientes_cadastrados.txt", 'r');
    if(file != NULL){

        while(fgets(contents, 50, file) != NULL){
            printf("%s", contents);
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

FILE* openFile(char path[30], char mode){
    FILE *file;
    switch (mode){
    case 'g' :
        file = fopen(path, "w");
        break;
    case 'r' :
        file = fopen (path, "r");
        break;
    case 'a' :
        file = fopen (path, "a");
        break;
    }
    if (file == NULL){
        printf("Nao foi possivel abrir o arquivo.");
        exit(0);
    }
    return file;
}

void checkPatientRiskGroup(int age, char cep[20]){

    if(age >= 65){
        addHealthSecretaryFile(age, cep);
    }
}

void addHealthSecretaryFile(int age, char cep[20]){

    FILE *file;
    file = openFile("pacientes_grupo_de_risco.txt", 'a');
     if (file == NULL) {
        printf("Erro ao cadastrar.");
        exit(0);
    }else {
        fprintf(file,"CEP: %s", cep);
        fprintf(file,"Idade: %d\n", age);
        fclose(file);
    }
}

int calculateAge(char birthDate[20]){
    char *year = strtok(birthDate, "/");
    year = strtok(NULL, "/");
    year = strtok(NULL, "/");
    int yearOfBirth = atoi(year);

    int currentYear;
    time_t date_year;
    time(&date_year);
    struct tm *date = localtime(&date_year);
    currentYear = (date->tm_year+1900);

    return currentYear - yearOfBirth;
}
