#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_HISTORICO 500

typedef struct Aluno {
    int matricula;
    char nome[MAX_NOME];
    int idade;
    char historicoMedico[MAX_HISTORICO];
    char dataAdmissao[11];
    struct Aluno* prox;
} Aluno;

Aluno* criarAluno(int matricula, const char* nome, int idade, const char* historicoMedico, const char* dataAdmissao) {
    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    novo->matricula = matricula;
    strncpy(novo->nome, nome, MAX_NOME);
    novo->idade = idade;
    strncpy(novo->historicoMedico, historicoMedico, MAX_HISTORICO);
    strncpy(novo->dataAdmissao, dataAdmissao, 11);
    novo->prox = NULL;
    return novo;
}

void inserirAluno(Aluno** lista, int matricula, const char* nome, int idade, const char* historicoMedico, const char* dataAdmissao) {
    Aluno* novo = criarAluno(matricula, nome, idade, historicoMedico, dataAdmissao);
    novo->prox = *lista;
    *lista = novo;
}

void alterarAluno(Aluno* lista, int matricula, const char* nome, int idade, const char* historicoMedico, const char* dataAdmissao) {
    for (Aluno* temp = lista; temp; temp = temp->prox) {
        if (temp->matricula == matricula) {
            strncpy(temp->nome, nome, MAX_NOME);
            temp->idade = idade;
            strncpy(temp->historicoMedico, historicoMedico, MAX_HISTORICO);
            strncpy(temp->dataAdmissao, dataAdmissao, 11);
            printf("Aluno %d alterado com sucesso.\n", matricula);
            return;
        }
    }
    printf("Aluno %d não encontrado.\n", matricula);
}

void excluirAluno(Aluno** lista, int matricula) {
    Aluno *temp = *lista, *anterior = NULL;

    while (temp && temp->matricula != matricula) {
        anterior = temp;
        temp = temp->prox;
    }

    if (!temp) {
        printf("Aluno %d não encontrado.\n", matricula);
        return;
    }

    if (!anterior) *lista = temp->prox;
    else anterior->prox = temp->prox;

    free(temp);
    printf("Aluno %d excluído com sucesso.\n", matricula);
}

void listarAlunos(Aluno* lista) {
    if (!lista) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\nLista de Alunos:\n");
    for (Aluno* temp = lista; temp; temp = temp->prox) {
        printf("\nMatrícula: %d\n", temp->matricula);
        printf("Nome: %s\n", temp->nome);
        printf("Idade: %d\n", temp->idade);
        printf("Histórico Médico: %s\n", temp->historicoMedico);
        printf("Data de Admissão: %s\n", temp->dataAdmissao);
    }
}

void liberarLista(Aluno* lista) {
    while (lista) {
        Aluno* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main() {
    Aluno* lista = NULL;
    int opcao, matricula, idade;
    char nome[MAX_NOME], historico[MAX_HISTORICO], data[11];

    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir aluno\n2. Alterar aluno\n3. Excluir aluno\n4. Listar alunos\n5. Sair\nOpção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Matrícula: ");
                scanf("%d", &matricula);
                getchar();
                printf("Nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Idade: ");
                scanf("%d", &idade);
                getchar();
                printf("Histórico Médico: ");
                fgets(historico, MAX_HISTORICO, stdin);
                historico[strcspn(historico, "\n")] = 0;
                printf("Data de Admissão (dd/mm/aaaa): ");
                fgets(data, 11, stdin);
                data[strcspn(data, "\n")] = 0;
                inserirAluno(&lista, matricula, nome, idade, historico, data);
                break;

            case 2:
                printf("Matrícula: ");
                scanf("%d", &matricula);
                getchar();
                printf("Novo Nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Nova Idade: ");
                scanf("%d", &idade);
                getchar();
                printf("Novo Histórico Médico: ");
                fgets(historico, MAX_HISTORICO, stdin);
                historico[strcspn(historico, "\n")] = 0;
                printf("Nova Data de Admissão (dd/mm/aaaa): ");
                fgets(data, 11, stdin);
                data[strcspn(data, "\n")] = 0;
                alterarAluno(lista, matricula, nome, idade, historico, data);
                break;

            case 3:
                printf("Matrícula: ");
                scanf("%d", &matricula);
                excluirAluno(&lista, matricula);
                break;

            case 4:
                listarAlunos(lista);
                break;

            case 5:
                liberarLista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
