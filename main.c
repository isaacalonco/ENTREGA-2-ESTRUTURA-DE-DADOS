#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct Curso { char nome[50]; int semestre; };

struct Contato { char telefone[20]; char email[50]; };

struct Endereco { char cidade[50];  char estado[3]; int numero; };

struct Notas { double n1; double n2; };

struct Aluno { int id; char nome[40]; float altura; struct Notas notas; struct Endereco endereco; struct Curso curso; struct Contato contato; };

void voltar(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void lerAlunos(struct Aluno aluno[], int *n) {
    for (int i = 0; i < *n; i++) {

        printf("\n----Aluno %d----\n", i + 1);

        aluno[i].id = i + 1;

        printf("Nome: ");
        scanf(" %39[^\n]", aluno[i].nome);

        printf("Altura: ");
        scanf("%f", &aluno[i].altura);

        printf("Nota 1: ");
        scanf("%lf", &aluno[i].notas.n1);

        printf("Nota 2: ");
        scanf("%lf", &aluno[i].notas.n2);

        printf("Cidade: ");
        scanf(" %49[^\n]", aluno[i].endereco.cidade);

        printf("Estado (sigla): ");
        scanf(" %2s", aluno[i].endereco.estado);

        printf("Numero da casa: ");
        scanf("%d", &aluno[i].endereco.numero);

        printf("Curso: ");
        scanf(" %49[^\n]", aluno[i].curso.nome);

        printf("Semestre: ");
        scanf("%d", &aluno[i].curso.semestre);

        printf("Email: ");
        scanf(" %49[^\n]", aluno[i].contato.email);

        printf("Telefone: ");
        scanf(" %19[^\n]", aluno[i].contato.telefone);
    }
}

void exibirAluno(struct Aluno *a) {

    double media = (a->notas.n1 + a->notas.n2) / 2;

    printf("\n----Dados do Aluno----\n");
    printf("ID: %d\n", a->id);
    printf("Nome: %s\n", a->nome);
    printf("Altura: %.2f m\n", a->altura);
    printf("Nota 1: %.2f | Nota 2: %.2f | Media: %.2f\n", a->notas.n1, a->notas.n2, media);
    printf("Cidade: %s - %s | Numero: %d\n", a->endereco.cidade, a->endereco.estado, a->endereco.numero);
    printf("Curso: %s (Semestre %d)\n", a->curso.nome, a->curso.semestre);
    printf("Email: %s | Telefone: %s\n", a->contato.email, a->contato.telefone);
}

void listarPorEstado(struct Aluno aluno[], int *n) {
    char uf[3];
    int encontrado = 0;

    printf("\nDigite a sigla do estado: ");
    scanf("%2s", uf);

    for (int i = 0; i < *n; i++) {

        if (strcmp(uf, aluno[i].endereco.estado) == 0) {
            encontrado = 1;
            exibirAluno(&aluno[i]);
        }
    }

    if (!encontrado)
        printf("\nNenhum aluno encontrado para o estado '%s'.\n", uf);

    voltar();
}

// ele funciona comparando dois elementos vizinhos por vez e trocando
// de lugar quando estão na ordem errada. Ele vai repetindo até que tudo esteja arrumado.
// Ele é menos eficiente que o Insertion Sort porque sempre percorre todos
// os pares, mesmo quando já poderia parar.

// troca quando o da esquerda tem média menor que o da direita
void bubbleMaiorNota(struct Aluno a[], int *n) {
    struct Aluno aux;

    for (int i = 0; i < *n - 1; i++) {
        // A cada rodada, os últimos 'i' já estão no lugar certo,
        for (int j = 0; j < *n - i - 1; j++) {

            double m1 = (a[j].notas.n1 + a[j].notas.n2) / 2;
            double m2 = (a[j+1].notas.n1 + a[j+1].notas.n2) / 2;

            // Se o da esquerda tirou menos, ele troca com o da direita
            if (m1 < m2) {
                aux    = a[j];
                a[j]   = a[j+1];
                a[j+1] = aux;
            }
        }
    }

    printf("\n--- Ordenado por MAIOR nota ---\n");
    for (int i = 0; i < *n; i++)
        exibirAluno(&a[i]);

    voltar();
}

// troca quando o da esquerda tem média maior que o da direita
void bubbleMenorNota(struct Aluno a[], int *n) {
    struct Aluno aux;

    for (int i = 0; i < *n - 1; i++) {
        for (int j = 0; j < *n - i - 1; j++) {

            double m1 = (a[j].notas.n1 + a[j].notas.n2) / 2;
            double m2 = (a[j+1].notas.n1 + a[j+1].notas.n2) / 2;

            // Se o da esquerda tirou mais, ele troca com o da direita
            if (m1 > m2) {
                aux    = a[j];
                a[j]   = a[j+1];
                a[j+1] = aux;
            }
        }
    }

    printf("\n--- Ordenado por MENOR nota ---\n");
    for (int i = 0; i < *n; i++)
        exibirAluno(&a[i]);

    voltar();
}

// Ordena pelo número da casa, do menor para o maior
void bubbleNumero(struct Aluno a[], int *n) {
    struct Aluno aux;

    for (int i = 0; i < *n - 1; i++) {
        for (int j = 0; j < *n - i - 1; j++) {

            // Se o número da casa da esquerda for maior, troca os dois de lugar
            if (a[j].endereco.numero > a[j+1].endereco.numero) {
                aux    = a[j];
                a[j]   = a[j+1];
                a[j+1] = aux;
            }
        }
    }

    printf("\n--- Ordenado por NUMERO DA CASA ---\n");
    for (int i = 0; i < *n; i++)
        exibirAluno(&a[i]);

    voltar();
}

// O Insertion Sort é como organizar cartas na mão: você pega uma carta nova
// e vai encaixando ela no lugar certo entre as que já estão organizadas.
// Ele é melhor que o Bubble Sort porque para de comparar
// assim que encontra o lugar certo, sem continuar varrendo à toa.

// Ordena os alunos em ordem alfabética pelo nome
void insertNome(struct Aluno a[], int *n) {
    struct Aluno chave; // guarda o aluno que vai ser reposicionado
    int j;

    // O primeiro aluno já está "organizado" sozinho, então começa do segundo
    for (int i = 1; i < *n; i++) {

        chave = a[i];
        j = i - 1;

        // Empurra pra direita todos os alunos cujo nome vem depois do da chave,
        while (j >= 0 && strcmp(a[j].nome, chave.nome) > 0) {
            a[j+1] = a[j];
            j--;
        }

        // Coloca o aluno na posição correta
        a[j+1] = chave;
    }

    printf("\n--- Insert Sort (Nome) ---\n");
    for (int i = 0; i < *n; i++)
        exibirAluno(&a[i]);

    voltar();
}

void insertMedia(struct Aluno a[], int *n) {
    struct Aluno chave;
    int j;

    for (int i = 1; i < *n; i++) {

        chave = a[i];
        j = i - 1;

        // Calcula a média da chave uma só vez aqui fora,
        // assim não recalcula a mesma coisa toda iteração do while
        double mChave = (chave.notas.n1 + chave.notas.n2) / 2;

        // Empurra pra direita quem tem média maior
        while (j >= 0) {
            double mAtual = (a[j].notas.n1 + a[j].notas.n2) / 2;

            if (mAtual > mChave) {
                a[j+1] = a[j];
                j--;
            } else break;
        }

        a[j+1] = chave;
    }

    printf("\n--- Insert Sort (Media) ---\n");
    for (int i = 0; i < *n; i++)
        exibirAluno(&a[i]);

    voltar();
}

// Ordena pelo número da casa, do menor para o maior
void insertNumero(struct Aluno a[], int *n) {
    struct Aluno chave;
    int j;

    for (int i = 1; i < *n; i++) {

        chave = a[i];
        j = i - 1;

        // Empurra pra direita quem tem número de casa maior
        while (j >= 0 && a[j].endereco.numero > chave.endereco.numero) {
            a[j+1] = a[j];
            j--;
        }

        a[j+1] = chave;
    }

    printf("\n--- Insert Sort (Numero da Casa) ---\n");
    for (int i = 0; i < *n; i++)
        exibirAluno(&a[i]);

    voltar();
}


// Funções recursivas são aquelas que se chamam de volta, resolvendo
// uma versão menor do problema a cada chamada, até chegar num ponto
// simples o suficiente pra resolver direto — esse ponto é o "caso base".

// A cada chamada, olha pro aluno na posição 'i' e passa pro próximo.
// Devolve um ponteiro pro aluno encontrado, ou NULL se não existir.
struct Aluno* buscarPorId(struct Aluno a[], int i, int n, int id) {

    // Caso base: chegou no fim sem encontrar ninguém
    if (i >= n) return NULL;

    // Se o aluno aqui tem o ID que a gente procura, retorna ele
    if (a[i].id == id) return &a[i];

    // Senão, passa pra frente: tenta com o próximo aluno (i+1)
    // O problema vai ficando menor porque i cresce até chegar em n
    return buscarPorId(a, i + 1, n, id);
}

// Lista todos os alunos de forma recursiva.
// Mostra o aluno atual e chama a si mesmo pro próximo.
void listarRec(struct Aluno a[], int i, int n) {

    // Caso base: chegou no fim da lista, hora de parar
    if (i >= n) return;

    // Mostra quem está na posição atual
    exibirAluno(&a[i]);

    // Chama de novo pra mostrar o próximo
    listarRec(a, i + 1, n);
}

// Calcula a soma de todas as médias de forma recursiva.
// Retorna a SOMA total (a divisão pra tirar a média geral fica em subMenuRec).
double calcMediaRecursiva(struct Aluno aluno[], int n) {

    if (n == 0) return 0;

    // Pega a média do último aluno e soma com o resultado do restante.
    return ((aluno[n-1].notas.n1 + aluno[n-1].notas.n2) / 2)
           + calcMediaRecursiva(aluno, n - 1);
}

void subMenuBubble(struct Aluno aluno[], int *n) {
    int opc;

    system("cls");

    while (1) {

        printf("\n--- MENU BUBBLE SORT ---\n");
        printf("1 - Listar por maiores notas\n");
        printf("2 - Listar por menores notas\n");
        printf("3 - Ordenar pelo menor numero da casa\n");
        printf("4 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opc);

        switch (opc) {
            case 1: bubbleMaiorNota(aluno, n); break;
            case 2: bubbleMenorNota(aluno, n); break;
            case 3: bubbleNumero(aluno, n);    break;
            case 4: return;
            default: printf("\nOpcao invalida!\n"); voltar();
        }
    }
}

void subMenuInsert(struct Aluno aluno[], int *n) {
    int opc;

    system("cls");

    while (1) {

        printf("\n--- MENU INSERT SORT ---\n");
        printf("1 - Ordenar por nome\n");
        printf("2 - Ordenar por media das notas\n");
        printf("3 - Ordenar por numero da casa\n");
        printf("4 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opc);

        switch(opc) {
            case 1: insertNome(aluno, n);   break;
            case 2: insertMedia(aluno, n);  break;
            case 3: insertNumero(aluno, n); break;
            case 4: return;
            default: printf("\nOpcao invalida!\n"); voltar();
        }
    }
}

void subMenuRec(struct Aluno aluno[], int *n) {
    int opc;

    system("cls");

    while (1) {

        printf("\n--- MENU RECURSIVIDADE ---\n");
        printf("1 - Buscar estudante por ID\n");
        printf("2 - Exibir estudantes recursivamente\n");
        printf("3 - Calcular media geral da turma\n");
        printf("4 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opc);

        switch(opc) {

            case 1: {
                int id;
                printf("\nDigite o ID do aluno: ");
                scanf("%d", &id);

                struct Aluno *encontrado = buscarPorId(aluno, 0, *n, id);

                if (encontrado != NULL) exibirAluno(encontrado);
                else
                    printf("\nAluno com ID %d nao encontrado.\n", id);
                voltar();
                break;
            }
            case 2: system("cls"); listarRec(aluno, 0, *n);
                voltar();
                break;
            case 3:
                system("cls");
                if (*n > 0)
                    printf("\nMedia geral da turma: %.2lf\n", calcMediaRecursiva(aluno, *n) / (*n));
                else
                    printf("\nNenhum aluno cadastrado.\n");
                voltar();
                break;
            case 4: return;
            default: printf("\nOpcao invalida!\n"); voltar();
        }
    }
}


int main() {

    struct Aluno aluno[4];
    int n = 4;
    int opc;
    int cadastrado = 0;

    while (1) {

        system("cls");

        printf("\n=========== MENU ===========\n");
        printf("0 - Cadastrar estudantes\n");
        printf("1 - Listar estudantes por estado\n");
        printf("2 - Menu Bubble Sort\n");
        printf("3 - Menu Insert Sort\n");
        printf("4 - Menu Recursividade\n");
        printf("5 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &opc);

        if (opc != 0 && opc != 5 && !cadastrado) {
            printf("\nSem estudantes cadastrados (opcao 0)!\n");
            voltar();
            continue;
        }

        switch (opc) {

            case 0: lerAlunos(aluno, &n); cadastrado = 1; break;
            case 1: listarPorEstado(aluno, &n); break;
            case 2: subMenuBubble(aluno, &n);   break;
            case 3: subMenuInsert(aluno, &n);   break;
            case 4: subMenuRec(aluno, &n);      break;
            case 5: return 0;
            default: printf("\nOpcao invalida!\n"); voltar();

        }
    }
}