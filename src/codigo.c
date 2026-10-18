#include <stdio.h>
#include <string.h> // Fixed: Added for strcmp()

#define MAX_LIVROS 20
#define ORDENAR_ERRO -1
#define ORDENAR_SUCESSO -2

typedef struct {
	char nome[100];
	int preco;
} livro;

// Ponteiro pra função que será implementado em breve pra criar função de ordenação
// genérica que puxa uma função de condição para determinar como será ordenado o objeto
typedef int (*condicao)(livro, livro);

int sort(livro *lista, int t, condicao cf);
static inline int preco_crescente(livro l1, livro l2);
static inline int preco_decrescente(livro l1, livro l2);

static inline int nome_crescente(livro l1, livro l2);
static inline int nome_decrescente(livro l1, livro l2);

condicao lista_condicoes[4] = {
	preco_crescente,
	preco_decrescente,
	nome_crescente,
	nome_decrescente
};

// Ordenar preço em ordem crescente 	-> 0
// Ordenar preço em ordem decrescente 	-> 1
// Ordenar nome em ordem crescente		-> 2
// Ordenar nome em ordem decrescente 	-> 3

int main(int argc, char **argv)
{
	livro lista_livros[MAX_LIVROS];

	if (argc != 2)
		return 1;

	int opcao = argv[1][0] - '0';

	if (opcao > 4 || opcao < 0)
		return 1;

	sort(lista_livros, MAX_LIVROS, lista_condicoes[opcao]);

	return 0;
}

/*
 * Criar condições que se encaisem nesse molde
 *
 ***************************************************************
 **sort(lista_livros, tamanho_lista, ponteiro_funcao_condicao)**
 ***************************************************************
 */

int sort(livro *lista, int t, condicao cf) 
{	// Por enquanto um insertion. A gente pode mudar pra outra coisa dps
	for (int i = 1; i < t; ++i) {
		livro tmp = lista[i];
		int j = i;
		while (cf(tmp, lista[j - 1])) {
			lista[j] = lista[j - 1];
			--j;
		}
		lista[j] = tmp;
	}

	return 1;
}

static inline int preco_crescente(livro l1, livro l2)
{
	if (l1.preco < l2.preco)
		return 1;

	return 0;
}

static inline int preco_decrescente(livro l1, livro l2)
{
	if (l1.preco > l2.preco)
		return 1;

	return 0;
}

static inline int nome_crescente(livro l1, livro l2)
{
	for (int i = 0; l1.nome[i] && l2.nome[i]; ++i) {
		if (l1.nome[i] == -61 || l2.nome[i] == -61)
			continue;
		if (l1.nome[i] == ' ' || l2.nome[i] == ' ')
			continue;
		if (l1.nome[i] < l2.nome[i])
			return 1;
	}
	return 0;
}

static inline int nome_decrescente(livro l1, livro l2)
{
	for (int i = 0; l1.nome[i] && l2.nome[i]; ++i) {
		if (l1.nome[i] == -61 || l2.nome[i] == -61)
			continue;
		if (l1.nome[i] == ' ' || l2.nome[i] == ' ')
			continue;
		if (l1.nome[i] > l2.nome[i])
			return 1;
	}
	return 0;
}
