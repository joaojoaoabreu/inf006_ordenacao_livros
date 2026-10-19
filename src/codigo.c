#include <stdio.h>
#include <string.h> // Fixed: Added for strcmp()

#define MAX_LIVROS 10
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
void imprimir_json(livro lista_livros[], int size);
static inline int preco_crescente(livro l1, livro l2);
static inline int preco_decrescente(livro l1, livro l2);
static inline int nome_crescente(livro l1, livro l2);
static inline int nome_decrescente(livro l1, livro l2);
char minuscula(char letra);

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
	livro lista_livros[MAX_LIVROS] = {
		{ .nome = "The Hobbit", .preco = 5090},
		{ .nome = "Clean Code", .preco = 21080},
		{ .nome = "1984", .preco = 3090}, // Ótimo livro, tenho que acabar de ler ele ainda
		{ .nome = "Dune", .preco = 10000},
		{ .nome = "The C Programming Language", .preco = 79900},
		{ .nome = "C: A Modern Approach", .preco = 295000},
		{ .nome = "Structured Computer Organization", .preco = 59250},
		{ .nome = "Os Sete", .preco = 22050},
		{ .nome = "Adventures of Vegan Vamp", .preco = 2570},
		{ .nome = "Revolucao dos bichos", .preco = 2380}
	};

	if (argc < 2) {
		imprimir_json(lista_livros, MAX_LIVROS);
		return 0;
	}

	int opcao = argv[1][0] - '0';

	if (opcao < 4 && opcao >= 0) {
		sort(lista_livros, MAX_LIVROS, lista_condicoes[opcao]);
		imprimir_json(lista_livros, MAX_LIVROS);
		return 0;
	}

	printf("{\"erro\":\"ordenacao invalida\"}\n");
	return 1;
}

/*
 * Criar condições que se encaisem nesse molde
 *
 ***************************************************************
 **sort(lista_livros, tamanho_lista, ponteiro_funcao_condicao)**
 ***************************************************************
 */

int sort(livro *lista, int size, condicao cf)
{	// Por enquanto um insertion. A gente pode mudar pra outra coisa dps
	for (int i = 1; i < size; ++i) {
		livro tmp = lista[i];
		int j = i;
		while (j > 0 && cf(tmp, lista[j - 1])) {
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
		if (minuscula(l1.nome[i]) < minuscula(l2.nome[i]))
			return 1;
	}
	return 0;
}

static inline int nome_decrescente(livro l1, livro l2)
{
	for (int i = 0; l1.nome[i] && l2.nome[i]; ++i) {
		if (minuscula(l1.nome[i]) > minuscula(l2.nome[i]))
			return 1;
	}
	return 0;
}

void imprimir_json(livro lista_livros[], int size)
{
	printf("[");

	for (int i = 0; i < size; i++) {

		printf("{\"nome\":\"%s\",\"preco\":%d}",
				lista_livros[i].nome, lista_livros[i].preco
				);

		if (lista_livros[i].preco != 0 && lista_livros[i + 1].preco != 0) {
			printf(",");
		}
	}

	printf("]\n");
}

char minuscula(char letra){
    char min=letra;
    if(min>='A' && min<='Z') min+=32;
    return min;
}
