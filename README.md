# Sistema de Gerenciamento de Senhas de Atendimento Clínico

## 1. Objetivo do projeto

O objetivo deste projeto é desenvolver um sistema em linguagem C para gerenciar senhas de atendimento de uma clínica médica.

O sistema permite cadastrar pacientes, classificá-los automaticamente conforme as regras de prioridade estabelecidas na atividade e organizar as filas de atendimento.

## 2. Funcionalidades

- Cadastro de pacientes.
- Identificação automática da categoria de atendimento.
- Geração de senhas sequenciais.
- Filas independentes para cada categoria.
- Consulta da próxima senha.
- Chamada automática conforme a prioridade.
- Identificação do paciente em atendimento.
- Finalização do atendimento.
- Painel textual de acompanhamento.
- Contagem de pacientes aguardando por categoria.
- Validação dos dados informados.

## 3. Categorias de atendimento

### Normal (N)

Pacientes que não apresentam condições de prioridade.

Exemplos de senhas: N001, N002, N003.

### Preferencial (P)

- Gestantes.
- Lactantes.
- Pessoas com necessidades especiais.
- Pessoas com condição de obesidade.
- Mulheres com 60 anos ou mais.
- Homens com 65 anos ou mais.

Exemplos de senhas: P001, P002, P003.

### Urgente (U)

Pacientes com idade superior a 80 anos.

Exemplos de senhas: U001, U002, U003.

A prioridade de atendimento segue a ordem:

1. Urgente.
2. Preferencial.
3. Normal.

Dentro de cada categoria, é respeitada a ordem de chegada (FIFO).

## 4. Tecnologias utilizadas

- Linguagem C.
- Visual Studio Code.
- OnlineGDB para compilação e testes.
- GitHub para armazenamento do código-fonte.

## 5. Estruturas utilizadas

O programa utiliza:

- Struct para armazenar os dados dos pacientes.
- Struct para representar as filas.
- Vetores para armazenar os pacientes.
- Variáveis inteiras para controlar as quantidades e categorias.
- Estruturas condicionais para classificação.
- Laços de repetição para controlar o menu e validar informações.

As filas utilizam organização circular para permitir o reaproveitamento das posições após os atendimentos.

## 6. Funções implementadas

| Função | Responsabilidade |
|---|---|
| lerInteiro() | Lê e valida números inteiros |
| lerNome() | Lê e valida o nome |
| lerGenero() | Lê e valida o gênero |
| classificarPaciente() | Classifica o paciente |
| gerarSenha() | Gera senhas sequenciais |
| inserirFila() | Insere pacientes na fila |
| retirarFila() | Retira pacientes da fila |
| consultarFila() | Consulta sem retirar da fila |
| mostrarCategoria() | Exibe a categoria |
| cadastrarPaciente() | Cadastra pacientes |
| proximaSenha() | Identifica a próxima senha |
| consultarProxima() | Consulta a próxima chamada |
| chamarProximo() | Realiza a chamada |
| finalizarAtendimento() | Finaliza o atendimento |
| exibirFila() | Exibe os pacientes aguardando |
| painel() | Apresenta o painel de atendimento |
| menu() | Controla as opções do sistema |
| main() | Inicia o programa |

## 7. Como executar

O código pode ser compilado utilizando um compilador C, como GCC.

### Compilação

```bash
gcc main.c -o clinica -std=c11 -Wall -Wextra
```

### Execução no Windows

```bash
clinica.exe
```

### Execução no Linux

```bash
./clinica
```

Também é possível utilizar o compilador online:

https://www.onlinegdb.com/online_c_compiler

Selecione a linguagem C, cole o conteúdo do arquivo main.c e clique em Run.

## 8. Exemplo de utilização

### Cadastro de paciente normal

```text
Nome do paciente: Joao
Genero (M/F): M
Idade: 30
Lactante? (1-Sim / 0-Nao): 0
Possui necessidade especial? (1-Sim / 0-Nao): 0
Possui condicao de obesidade? (1-Sim / 0-Nao): 0

Senha: N001
Categoria: NORMAL
```

### Cadastro de paciente preferencial

```text
Nome do paciente: Maria
Genero (M/F): F
Idade: 30
Gestante? (1-Sim / 0-Nao): 1
Lactante? (1-Sim / 0-Nao): 0
Possui necessidade especial? (1-Sim / 0-Nao): 0
Possui condicao de obesidade? (1-Sim / 0-Nao): 0

Senha: P001
Categoria: PREFERENCIAL
```

### Cadastro de paciente urgente

```text
Nome do paciente: Pedro
Genero (M/F): M
Idade: 85
Lactante? (1-Sim / 0-Nao): 0
Possui necessidade especial? (1-Sim / 0-Nao): 0
Possui condicao de obesidade? (1-Sim / 0-Nao): 0

Senha: U001
Categoria: URGENTE
```

## 9. Considerações finais

O projeto foi desenvolvido com o objetivo de aplicar os conceitos fundamentais da linguagem C, incluindo funções, estruturas, vetores, filas, decisões e repetições.

O sistema possui finalidade exclusivamente acadêmica. As classificações são regras didáticas estabelecidas no enunciado da atividade e não substituem avaliação clínica ou protocolos oficiais de classificação de risco.
