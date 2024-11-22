#include <stdio.h>
#include <string.h>

typedef struct {
   unsigned matricula;
   char nome[32];
   float notas [4];
}Alunos;

void removeEnter(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

float calcularMedia(float notas[], int tamanho) {
    float soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += notas[i];
    }
    return soma / tamanho;
}

float calcularMediaFinal(float notas[]){
    float media;
    media = ((calcularMedia(notas, 3 ) *6)+(notas[3] *4))/10;
    return media;
}

int main() {
    char disciplina[52];
    int qtd;
    Alunos alunos[30];
    
    puts("----------------------------------------------");
    puts("                  BEM VINDO!                  ");
    puts("----------------------------------------------");
    
    while (1) {
        puts("Digite o nome da disciplina (no maximo 50 caracteres).");
        fgets(disciplina, 52, stdin);
        removeEnter(disciplina);
        
        if (strlen(disciplina) > 50) {
            int c;
            puts("Limite de caracteres ultrapassado.");
            
            while ((c = getchar()) != '\n' && c != EOF){
            }   
            
            continue;
            
        } else {
            break;
        } 
    }
    
    while (1) {
        puts("Digite a quantidade de alunos (no maximo 30 alunos).");
        scanf("%d%*c", &qtd);
        
        if (qtd > 30) {
            puts("Quantidade de alunos excedeu o limite.");
            continue;
        } else {
            break;
        }
    }

    for (int i = 0; i < qtd; i++) {
        printf("Digite a matricula do aluno %d: ", i + 1);
        scanf("%u%*c", &alunos[i].matricula );
        
        printf("Digite o nome do aluno %d (no maximo 30 caracteres): ", i + 1);
        fgets(alunos[i].nome, 32, stdin);
        
        removeEnter(alunos[i].nome);
    }

    printf("Matriculas e nomes dos alunos:\n");
    for (int i = 0; i < qtd; i++) {
        printf("Matricula: %u, Nome: %s\n", alunos[i].matricula, alunos[i].nome);
    }

for (int i = 0; i < qtd; i++) {
        printf("colocando as notas para o aluno %s\n", alunos[i].nome);
        for (int j = 0; j < 3; j++) {
            printf("Digite a nota %d do aluno %s: ", j + 1, alunos[i].nome);
            scanf("%f%*c", &alunos[i].notas[j]);
        }
        
        float media = calcularMedia(alunos[i].notas, 3);
        
        if (media >= 4 && media < 7) {
            printf("%s esta em recuperacao com media %.2f\n", alunos[i].nome, media);
            printf("Digite a nota de recuperacao do aluno %s: ", alunos[i].nome);
            scanf("%f%*c", &alunos[i].notas[3]);
        } else {
            alunos[i].notas[3] = 0; 
        }
    }

printf("Notas dos alunos:\n");
    for (int i = 0; i < qtd; i++) {
        printf("Aluno: %s\n", alunos[i].nome);
        printf("Notas: %.2f, %.2f, %.2f\n", alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2]);
        if (alunos[i].notas[3] > 0) {
            printf("Nota de recuperacao: %.2f\n", alunos[i].notas[3]);
        }
    }



printf("Disciplina: %s\n", disciplina);
puts("------------------------------------------------------------------------------------------");
printf("\tMatricula\tNome\t\tNota1\tNota2\tNota3\tRec\tMedia\t Situacao\n");
puts("------------------------------------------------------------------------------------------");
for (int i = 0; i < qtd; i++){
    
    if(calcularMedia(alunos[i].notas,3) >= 7){
        printf("\t%u\t %s\t\t %0.2f\t %0.2f\t %0.2f \t -- \t %0.2f \t Aprovado\n", alunos[i].matricula, alunos[i].nome,
        alunos[i].notas[0],alunos[i].notas[1],alunos[i].notas[2],calcularMedia(alunos[i].notas,3));

    }else if(calcularMedia(alunos[i].notas,3) < 4){
        printf("\t%u\t %s\t\t %0.2f\t %0.2f\t %0.2f \t -- \t %0.2f \t Reprovado\n", alunos[i].matricula, alunos[i].nome,
        alunos[i].notas[0],alunos[i].notas[1],alunos[i].notas[2],calcularMedia(alunos[i].notas,3));

    }else if(calcularMediaFinal(alunos[i].notas) >= 5){
        printf("\t%u\t %s\t\t %0.2f\t %0.2f\t %0.2f \t %0.2f \t %0.2f \t Aprovado\n", alunos[i].matricula, alunos[i].nome,
        alunos[i].notas[0],alunos[i].notas[1],alunos[i].notas[2],alunos[i].notas[3], calcularMediaFinal(alunos[i].notas));
        
    }else if(calcularMediaFinal(alunos[i].notas) < 5){
        printf("\t%u\t %s\t\t %0.2f\t %0.2f\t %0.2f \t %0.2f \t %0.2f \t Reprovado\n", alunos[i].matricula, alunos[i].nome,
        alunos[i].notas[0],alunos[i].notas[1],alunos[i].notas[2],alunos[i].notas[3], calcularMediaFinal(alunos[i].notas));
        
    }else{
        printf("\t%u\t %s\t\t %0.2f\t %0.2f\t %0.2f \t -- \t %0.2f \t Reprovado\n", alunos[i].matricula, alunos[i].nome,
        alunos[i].notas[0],alunos[i].notas[1],alunos[i].notas[2],calcularMedia(alunos[i].notas,3));
    }
    
}
    return 0;
}
