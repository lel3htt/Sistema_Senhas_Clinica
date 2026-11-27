# Sistema de Gerenciamento de Senhas de Atendimento Clínico

## 1. Objetivo

Desenvolver um sistema em linguagem C para cadastrar pacientes, gerar senhas e organizar a fila de atendimento conforme as prioridades.

## 2. Funcionalidades

- Cadastro de pacientes.
- Classificação automática.
- Geração de senhas.
- Organização das filas.
- Chamada e finalização de atendimentos.
- Consulta da próxima senha.
- Painel com as senhas e quantidades em espera.

## 3. Categorias de atendimento

**Normal (N):** pacientes sem prioridade.

Exemplos: N001, N002.

**Preferencial (P):** gestantes, lactantes, pessoas com necessidades especiais, obesidade, mulheres com 60 anos ou mais e homens com 65 anos ou mais.

Exemplos: P001, P002.

**Urgente (U):** pacientes com mais de 80 anos.

Exemplos: U001, U002.

A ordem de atendimento é: urgente, preferencial e normal. Dentro de cada categoria, vale a ordem de chegada (FIFO).

## 4. Tecnologias utilizadas

- Linguagem C.
- Visual Studio Code.
- GCC e OnlineGDB.
- GitHub.

## 5. Principais funções

| Função                 | Responsabilidade         |
| ---------------------- | ------------------------ |
| lerInteiro()           | Lê números               |
| lerNome()              | Lê o nome                |
| lerGenero()            | Lê o gênero              |
| classificarPaciente()  | Define a prioridade      |
| gerarSenha()           | Gera a senha             |
| inserirFila()          | Adiciona pacientes       |
| retirarFila()          | Remove pacientes         |
| consultarFila()        | Consulta a fila          |
| cadastrarPaciente()    | Realiza o cadastro       |
| chamarProximo()        | Chama o próximo paciente |
| finalizarAtendimento() | Finaliza o atendimento   |
| painel()               | Exibe o painel           |
| menu()                 | Controla as opções       |
| main()                 | Inicia o programa        |

## 6. Considerações finais

O projeto permite aplicar conceitos da linguagem C, como funções, structs, vetores, filas e estruturas de repetição.
