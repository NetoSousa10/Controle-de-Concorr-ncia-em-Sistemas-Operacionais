# Controle de Concorrência em Sistemas Operacionais

Este projeto implementa um sistema de controle de concorrência utilizando o **Algoritmo Token-Ring** para garantir a exclusão mútua e o **Algoritmo do Valentão** para eleição de coordenador.

## Introdução

Nos sistemas operacionais modernos, vários processos podem ser executados simultaneamente, acessando recursos compartilhados. Para evitar problemas como condições de corrida, deadlocks e inanição, é essencial implementar mecanismos que garantam a exclusão mútua e a coordenação entre processos.

### Conceitos

- **Concorrência:** Execução simultânea de múltiplos processos que podem acessar recursos compartilhados.
- **Exclusão Mútua:** Garantia de que apenas um processo pode acessar um recurso compartilhado por vez.
- **Seções Críticas:** Partes do código onde os processos acessam recursos compartilhados.

## Algoritmos Implementados

### Algoritmo Token-Ring

Garante a exclusão mútua ao permitir que apenas o processo que possui o token acesse a seção crítica. O token circula entre os processos de forma ordenada.

### Algoritmo do Valentão

Utilizado para eleger um novo coordenador caso o atual falhe. O processo com o maior ID se torna o novo coordenador.

## Estrutura do Código

O código é dividido nas seguintes partes:

- **Variáveis Globais:** Definem o número de processos, o token e o coordenador.
- **Função `secao_critica`:** Simula a operação na seção crítica.
- **Função `processo`:** Controla o comportamento de cada processo, incluindo a exclusão mútua e a eleição de coordenador.
- **Função `main`:** Cria as threads dos processos e aguarda a finalização das mesmas.
