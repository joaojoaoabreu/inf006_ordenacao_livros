# Trabalho de ordenação do professor Jose Dihego

## A minha ideia:

A minha ideia parte do pressuposto de utilizar menos código para realizar as coisas.
A explicação básica seria: mimetizar o funcionamento da função qsort() 
(Pesquisem sobre ela se quiserem, mas vou explicar basicamente como seria).

```
sort(lista_livros, tamanho_lista, ponteiro_funcao_condicao);
```

A função sort() recebe uma lista de livros (ordenados ou não), o tamanho da lista
e um ponteiro pra função de condição (listadas mais abaixo).

Ela realiza, atualmente, um insertion sort na lista de livros utilizando a função
de condição passada pra ela como regra para ordenar. Por exemplo: Se passar a função
ordenar_preco, (Por enquanto separada em 2 funções de ordenar crescente ou decrescente, já
cito isso também), ele irá ordenar a lista por ordem crescente de preço dos livros.


struct livro
- nome: string
- preco: int

## Funções condição.

O motivo de só ter funções ordenar... aqui é simples: Vitor sugeriu, ao invés de ordenar crescente ou 
decrescente, ordenar sempre crescente (ou sempre decrescente) e mudar somente como o usuário visualiza isso.
Eu vou explicar melhor depois, mas tem como criar uma função pra isso (E no código principal eu fiz uma macro
pra ser utilizada como o loop. Não é algo que eu necessariamente pretendo usar, só algo que eu fiz caso achem
melhor do que escrever um loop com 2 ternários no código).


A função se baseia em: Passar a lista, o início e o fim dela.
Utilizar operador ternário para alternar se o loop deve checar i < fim ou i > fim e se incrementa ou decrementa i,
dependendo se ini < fim ou não.
Se acharem mais legível dá pra fazer uma variável receber  ini < fim (1 pra verdadeiro ou 0 pra falso) e realizar
o operador ternário nessa variável.
Ex:

```
int opt = ini < fim
for (int i = ini; opt == true ? i < fim : i > fim; opt == true ? ++i : --i)
```

Se opt for verdadeiro, será utilizado i < fim e ++i. Se não, será utilizado i > fim e --i

```
ordenar_preco(livro l1, livro l2)  <- Recebe 2 livros para comparar

ordenar_nome(livro l1, livro l2)  <- Recebe 2 livros para comparar
```

As funções acimas vão literalmente só ser chamadas dentro de sort().
Dentro de sort fica assim: 

```
while (condicao(tmp, lista[j-1])) {
    lista[j] = lista[j-1];
    --j;
}
```
onde **condicao** é um ponteiro pra alguma dessas funções.

https://docs.google.com/document/d/1JlH3j47NdR65NOETjCDFXjR0HkNj7QyjqdaaZ-pyPr4/edit?tab=t.0
