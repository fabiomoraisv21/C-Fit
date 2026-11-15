# C-Fit

Sistema de academia feito em C para o trabalho de Algoritmos e Estrutura de Dados 1.
Roda no terminal e controla alunos, aparelhos, historico de treinos, aulas coletivas e ranking.

Equipe Amigos da ES:
- Fábio Morais Vieira (202600687)
- Maria Eduarda de Oliveira Gualberto (202604078)
- Maria Clara de Andrade e Silva (202600694)
- Lucas Hipólito Batista Carvalho (202604076)
- Tiago Henrique Silva Fabrini (202604085)

## Como compilar

Com make:

    make
    ./cfit

Ou direto com o gcc:

    gcc src/*.c -o cfit
    ./cfit

No Windows, se o `src/*.c` não funcionar, é só colocar todos os arquivos `.c` no comando.

Para testar mais rápido, use a opção 9 do menu, que já coloca 5 alunos de exemplo.

## Estruturas usadas

**Lista encadeada (alunos.c)**
Guarda os alunos cadastrados. Dá para cadastrar, listar, buscar, editar e remover.
Também registra entrada e saída da academia, e cada entrada conta na frequência.

**Fila (fila.c, usada em aparelhos.c e aulas.c)**
- Aparelhos: se o aparelho está ocupado, o aluno entra na fila. Quando ele é liberado,
  o primeiro da fila assume. Se o aluno sai da academia, ele sai da fila e libera o
  aparelho que estava usando.
- Aulas: os primeiros inscritos até completar as vagas fazem a aula, o resto fica
  esperando a próxima turma.

**Pilha (pilha.c, usada em historico.c)**
Cada aluno tem uma pilha com os exercícios que fez. O último registrado fica no topo,
e dá para desfazer o último caso tenha sido lançado errado.

**Lista ordenada (ranking.c)**
Monta o ranking por frequência ou por treinos, colocando cada aluno já na posição certa.
Se empatar, fica em ordem alfabética.
