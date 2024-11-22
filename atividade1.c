#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned matricula;
    char nome[32];
    float notas[3];
} Alunos;

void removeEnter(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0'; 
    }
}

float calcularMedia(float notas[], int tamanho) {
    float soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += notas[i];
    }
    return soma / tamanho;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void salvarAlunos(Alunos alunos[], int alunos_totais, int alunos_cadastrados, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "a+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    for (int i = alunos_cadastrados; i < alunos_totais; i++) {
        fprintf(arquivo, "%u,%s,%.2f,%.2f,%.2f\n", alunos[i].matricula, alunos[i].nome,
            alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2]);
    }

    fclose(arquivo);
}

void carregarAlunos(Alunos alunos[], int *qtd, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado, inicializando sem dados anteriores.\n", nome_arquivo);
        return;
    }

    printf("Arquivo aberto com sucesso. Carregando alunos...\n");

    while (*qtd < 30) {
        // Tente ler uma linha do arquivo
        int resultado = fscanf(arquivo, "%u,%[^,],%f,%f,%f", 
            &alunos[*qtd].matricula, alunos[*qtd].nome,
            &alunos[*qtd].notas[0], &alunos[*qtd].notas[1], &alunos[*qtd].notas[2]);
        
        // Verifica se a leitura foi bem-sucedida
        if (resultado == 5) {
            printf("Lido: %u %s %.2f %.2f %.2f\n", 
                alunos[*qtd].matricula, alunos[*qtd].nome,
                alunos[*qtd].notas[0], alunos[*qtd].notas[1], alunos[*qtd].notas[2]);
            printf("--------------------\n");
            (*qtd)++;
        } else {
            // Se não leu 5 itens, interrompa a leitura
            break;
        }
    }
    fclose(arquivo);
}

int main() {
    int quantidade_alunos = 0;
    int novos_alunos = 0;
    Alunos alunos[30];

    puts("----------------------------------------------");
    puts("                  BEM VINDO!                  ");
    puts("----------------------------------------------");

    carregarAlunos(alunos, &quantidade_alunos, "alunos.txt");

    if (quantidade_alunos == 0) {
        printf("Nenhum aluno encontrado no arquivo.\n");
    } else {
        printf("Alunos carregados: %d\n", quantidade_alunos);
    }

    printf("Digite a quantidade de alunos que voce quer adicionar (no maximo 30): ");
    scanf("%d", &novos_alunos);
    limparBufferEntrada();

    int total_alunos = quantidade_alunos + novos_alunos;

    if (total_alunos > 30) {
        printf("Quantidade de alunos excedeu o limite.\n");
        return 1;
    }

    for (int i = quantidade_alunos; i < total_alunos; i++) {
        printf("Digite a matricula do aluno %d: ", i + 1);
        scanf("%u", &alunos[i].matricula);
        limparBufferEntrada();

        printf("Digite o nome do aluno %d (no maximo 30 caracteres): ", i + 1);
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        removeEnter(alunos[i].nome);

        printf("Digite as notas do aluno %d (separadas por espaco): ", i + 1);
        scanf("%f %f %f", &alunos[i].notas[0], &alunos[i].notas[1], &alunos[i].notas[2]);
        limparBufferEntrada();
        printf("--------------------\n");
    }

    salvarAlunos(alunos, total_alunos, quantidade_alunos, "alunos.txt");
    
    printf("--------------------\n");
    printf("Lista de Alunos:\n");
    printf("--------------------\n");
    for (int i = 0; i < total_alunos; i++) {
        printf("Matricula: %u, Nome: %s, Notas: %.2f, %.2f, %.2f\n",
            alunos[i].matricula, alunos[i].nome, alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2]);
        printf("--------------------\n");
    }

    return 0;
}