#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 500

// Estrutura que guarda os dados do paciente
typedef struct {
    char nome[60];
    char genero;
    int idade;
    int gestante;
    int lactante;
    int necessidadeEspecial;
    int obeso;
    char senha[20];
    int categoria;
} Paciente;

// Estrutura de uma fila
typedef struct {
    Paciente pacientes[MAX];
    int inicio;
    int quantidade;
} Fila;

// Filas do sistema
Fila normal = {0};
Fila preferencial = {0};
Fila urgente = {0};

// Contadores independentes
int contadorN = 0;
int contadorP = 0;
int contadorU = 0;

// Paciente atualmente em atendimento
Paciente pacienteAtual;
int atendimentoAtivo = 0;

// Leitura de numero inteiro com validacao
int lerInteiro(char mensagem[], int minimo, int maximo) {
    char entrada[100];
    char extra;
    int valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro na leitura. Tente novamente.\n");
            clearerr(stdin);
            continue;
        }

        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada muito longa!\n");
            continue;
        }

        if (sscanf(entrada, " %d %c", &valor, &extra) == 1 &&
            valor >= minimo && valor <= maximo) {
            return valor;
        }

        printf("Valor invalido! Digite um numero entre %d e %d.\n",
               minimo, maximo);
    }
}

// Leitura e validacao do nome
void lerNome(char nome[]) {
    while (1) {
        printf("Nome do paciente: ");

        if (fgets(nome, 60, stdin) == NULL) {
            printf("Erro na leitura.\n");
            clearerr(stdin);
            continue;
        }

        if (strchr(nome, '\n') == NULL && !feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Nome muito longo!\n");
            continue;
        }

        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) > 0) {
            return;
        }

        printf("O nome nao pode ficar vazio.\n");
    }
}

// Leitura e validacao do genero
char lerGenero() {
    char entrada[100];

    while (1) {
        printf("Genero (M/F): ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro na leitura.\n");
            clearerr(stdin);
            continue;
        }

        char *p = entrada;

        while (isspace((unsigned char)*p)) {
            p++;
        }

        char genero = toupper((unsigned char)*p);

        if (genero == 'M' || genero == 'F') {
            p++;

            while (isspace((unsigned char)*p)) {
                p++;
            }

            if (*p == '\0') {
                return genero;
            }
        }

        printf("Genero invalido! Digite M ou F.\n");
    }
}

// Classificacao automatica do paciente
int classificarPaciente(Paciente p) {

    // Urgente tem prioridade sobre preferencial
    if (p.idade > 80) {
        return 3;
    }

    // Condicoes de atendimento preferencial
    if (p.gestante == 1 ||
        p.lactante == 1 ||
        p.necessidadeEspecial == 1 ||
        p.obeso == 1 ||
        (p.genero == 'F' && p.idade >= 60) ||
        (p.genero == 'M' && p.idade >= 65)) {
        return 2;
    }

    return 1;
}

// Geracao de senha sequencial
void gerarSenha(Paciente *p) {

    if (p->categoria == 3) {
        contadorU++;
        sprintf(p->senha, "U%03d", contadorU);
    }
    else if (p->categoria == 2) {
        contadorP++;
        sprintf(p->senha, "P%03d", contadorP);
    }
    else {
        contadorN++;
        sprintf(p->senha, "N%03d", contadorN);
    }
}

// Insercao de paciente na fila
int inserirFila(Fila *fila, Paciente p) {

    if (fila->quantidade >= MAX) {
        return 0;
    }

    int posicao = (fila->inicio + fila->quantidade) % MAX;

    fila->pacientes[posicao] = p;
    fila->quantidade++;

    return 1;
}

// Retirada do primeiro paciente da fila
int retirarFila(Fila *fila, Paciente *p) {

    if (fila->quantidade == 0) {
        return 0;
    }

    *p = fila->pacientes[fila->inicio];

    fila->inicio = (fila->inicio + 1) % MAX;
    fila->quantidade--;

    return 1;
}

// Consulta sem retirar o paciente da fila
int consultarFila(Fila fila, Paciente *p) {

    if (fila.quantidade == 0) {
        return 0;
    }

    *p = fila.pacientes[fila.inicio];

    return 1;
}

// Nome da categoria
void mostrarCategoria(int categoria) {

    if (categoria == 3) {
        printf("URGENTE");
    }
    else if (categoria == 2) {
        printf("PREFERENCIAL");
    }
    else {
        printf("NORMAL");
    }
}

// Cadastro de pacientes
void cadastrarPaciente() {

    Paciente p;

    printf("\n========== CADASTRO DE PACIENTE ==========\n");

    lerNome(p.nome);

    p.genero = lerGenero();

    p.idade = lerInteiro("Idade: ", 0, 120);

    p.gestante = 0;

    if (p.genero == 'F') {
        p.gestante = lerInteiro(
            "Gestante? (1-Sim / 0-Nao): ", 0, 1);
    }

    p.lactante = lerInteiro(
        "Lactante? (1-Sim / 0-Nao): ", 0, 1);

    p.necessidadeEspecial = lerInteiro(
        "Possui necessidade especial? (1-Sim / 0-Nao): ",
        0, 1);

    p.obeso = lerInteiro(
        "Possui condicao de obesidade? (1-Sim / 0-Nao): ",
        0, 1);

    // Classifica o paciente
    p.categoria = classificarPaciente(p);

    // Verifica se a fila tem espaco
    Fila *fila;

    if (p.categoria == 3) {
        fila = &urgente;
    }
    else if (p.categoria == 2) {
        fila = &preferencial;
    }
    else {
        fila = &normal;
    }

    if (fila->quantidade >= MAX) {
        printf("\nFila cheia! Cadastro nao realizado.\n");
        return;
    }

    gerarSenha(&p);

    inserirFila(fila, p);

    printf("\nPaciente cadastrado com sucesso!\n");
    printf("Nome: %s\n", p.nome);
    printf("Senha: %s\n", p.senha);
    printf("Categoria: ");
    mostrarCategoria(p.categoria);
    printf("\n");
}

// Identifica qual sera a proxima senha
int proximaSenha(Paciente *p) {

    if (consultarFila(urgente, p)) {
        return 1;
    }

    if (consultarFila(preferencial, p)) {
        return 1;
    }

    if (consultarFila(normal, p)) {
        return 1;
    }

    return 0;
}

// Consulta a proxima senha sem chamar
void consultarProxima() {

    Paciente p;

    printf("\n========== PROXIMA SENHA ==========\n");

    if (atendimentoAtivo) {
        printf("Existe um paciente em atendimento: %s\n",
               pacienteAtual.senha);
    }

    if (proximaSenha(&p)) {
        printf("Proxima senha: %s\n", p.senha);
        printf("Paciente: %s\n", p.nome);
        printf("Categoria: ");
        mostrarCategoria(p.categoria);
        printf("\n");
    }
    else {
        printf("Nao existem pacientes aguardando.\n");
    }
}

// Chamada do proximo paciente
void chamarProximo() {

    if (atendimentoAtivo) {
        printf("\nFinalize o atendimento atual antes de chamar outro.\n");
        return;
    }

    if (retirarFila(&urgente, &pacienteAtual)) {
        pacienteAtual.categoria = 3;
    }
    else if (retirarFila(&preferencial, &pacienteAtual)) {
        pacienteAtual.categoria = 2;
    }
    else if (retirarFila(&normal, &pacienteAtual)) {
        pacienteAtual.categoria = 1;
    }
    else {
        printf("\nNao existem pacientes aguardando atendimento.\n");
        return;
    }

    atendimentoAtivo = 1;

    printf("\n========== SENHA CHAMADA ==========\n");
    printf("Senha: %s\n", pacienteAtual.senha);
    printf("Paciente: %s\n", pacienteAtual.nome);
    printf("Categoria: ");
    mostrarCategoria(pacienteAtual.categoria);
    printf("\n");
}

// Finalizacao do atendimento
void finalizarAtendimento() {

    if (!atendimentoAtivo) {
        printf("\nNao existe atendimento em andamento.\n");
        return;
    }

    printf("\nAtendimento da senha %s finalizado.\n",
           pacienteAtual.senha);

    atendimentoAtivo = 0;
}

// Exibicao de uma fila
void exibirFila(Fila fila) {

    if (fila.quantidade == 0) {
        printf("Nenhum paciente aguardando.\n");
        return;
    }

    for (int i = 0; i < fila.quantidade; i++) {

        int posicao = (fila.inicio + i) % MAX;

        printf("%s - %s\n",
               fila.pacientes[posicao].senha,
               fila.pacientes[posicao].nome);
    }
}

// Painel de atendimento
void painel() {

    printf("\n========================================\n");
    printf("          PAINEL DE ATENDIMENTO\n");
    printf("========================================\n");

    printf("\nSENHA ATUAL: ");

    if (atendimentoAtivo) {
        printf("%s\n", pacienteAtual.senha);
        printf("PACIENTE: %s\n", pacienteAtual.nome);
        printf("CATEGORIA: ");
        mostrarCategoria(pacienteAtual.categoria);
        printf("\n");
    }
    else {
        printf("Nenhuma senha em atendimento.\n");
    }

    printf("\n--- QUANTIDADE DE PACIENTES EM ESPERA ---\n");
    printf("Urgentes: %d\n", urgente.quantidade);
    printf("Preferenciais: %d\n", preferencial.quantidade);
    printf("Normais: %d\n", normal.quantidade);

    printf("\n--- FILA URGENTE ---\n");
    exibirFila(urgente);

    printf("\n--- FILA PREFERENCIAL ---\n");
    exibirFila(preferencial);

    printf("\n--- FILA NORMAL ---\n");
    exibirFila(normal);

    Paciente p;

    printf("\n--- PROXIMA SENHA A SER CHAMADA ---\n");

    if (proximaSenha(&p)) {
        printf("%s - %s\n", p.senha, p.nome);
    }
    else {
        printf("Nenhum paciente aguardando.\n");
    }

    printf("\n========================================\n");
}

// Menu principal
void menu() {

    int opcao;

    do {
        printf("\n========== SISTEMA DA CLINICA ==========\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar proxima senha\n");
        printf("3 - Chamar proximo paciente\n");
        printf("4 - Finalizar atendimento\n");
        printf("5 - Consultar painel\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        opcao = lerInteiro("Escolha uma opcao: ", 0, 5);

        switch (opcao) {

            case 1:
                cadastrarPaciente();
                break;

            case 2:
                consultarProxima();
                break;

            case 3:
                chamarProximo();
                break;

            case 4:
                finalizarAtendimento();
                break;

            case 5:
                painel();
                break;

            case 0:
                printf("\nSistema encerrado. Obrigado!\n");
                break;
        }

    } while (opcao != 0);
}

// Funcao principal
int main() {

    printf("========================================\n");
    printf(" SISTEMA DE GERENCIAMENTO DE SENHAS\n");
    printf("========================================\n");

    menu();

    return 0;
}
