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

static inline int preco_crescente(livro l1, livro l2);
static inline int preco_decrescente(livro l1, livro l2);

int ordenar_nome(livro *lista_livros, int *numlivros);
int ordenar_preco_crescente(livro *lista_livros, livro *lista_livros_ordenados, int numlivros);

// Pequena abstração pra ficar mais bonitinho :shushing-face:
// Foi só um exemplo pra mostrar pra Vitor, mas dá pra implementar tbm assim.
// Explicando: Cria um for loop genérico que usa as variáveis **ini** e **fim** para iterar.
// Se na função que chamar existirem variáveis com esses nomes, a macro utilizará elas (Como no caso
// da função abaixo).
#define lista_dupla_via for (int i = ini; ini < fim ? i < fim : i > fim; ini < fim ? ++i : --i)

// Um teste pra saber se é possível fazer uma única função que
// lista crescente ou decrescente mesmo só com 2 parâmetros
int fds(int ini, int fim)
{
	lista_dupla_via {}
	return 1;
}

int main()
{
	livro lista_livros[MAX_LIVROS];
	livro lista_ordenado[MAX_LIVROS];
	int sair = 0;
	int opcao = 1;
	int numlivros = 0;

	while (!sair) {
		switch (opcao) {
		case 1:
			sair = 1;
			break;

		case 2:
			ordenar_nome(lista_livros, &numlivros);
			break;

		case 3:
			ordenar_preco_crescente(lista_livros, lista_ordenado, numlivros);
			break;
		}
	}
	return 0;
}

/* A ideia aqui é acabar com essas funções e utilizar a função de ordenação
 * genérica de livros (sort) que chama funções de condição para determinar
 * de que forma tudo será ordenado.
 *
 ***************************************************************
 **sort(lista_livros, tamanho_lista, ponteiro_funcao_condicao)**
 ***************************************************************
 *
 * Pensando em adicionar as funções de condição em um vetor e usar macros
 * para se referir a elas. Inclusive, seria bom de fato fazer a UI em C.
 *
 */
// int ordenar_nome(livro lista_livros[], int *numlivros){
//     livro tro_K;
//
//     if (*numlivros == 0){
//         printf("Nenhum livro cadastrado");
//         return ORDENAR_ERRO;
//     }
//     else {
//         for(int icont = 0; icont < *numlivros - 1; icont++) {
//             for(int jcont = 0; jcont < *numlivros - icont - 1; jcont++) {
//                 if(strcmp(lista_livros[jcont].nome, lista_livros[jcont+1].nome) > 0) {
//                     tro_K = lista_livros[jcont];
//                     lista_livros[jcont] = lista_livros[jcont+1];
//                     lista_livros[jcont+1] = tro_K;
//                 }
//             }
//         }
//         printf("Livros ordenados por nome com sucesso");
//         return ORDENAR_SUCESSO;
//     }
// }
//
// int ordenar_preco_crescente(livro lista_livros[], livro lista_livros_ordenados[], int numlivros){
//     if (numlivros == 0){
//         printf("Nenhum livro cadastrado");
//         return ORDENAR_ERRO;
//     }
//     else {
//         for(int i=0; i<numlivros; i++){
//             lista_livros_ordenados[i]=lista_livros[i];
//         }
//
//         for(int i=0; i<numlivros-1; i++){
//             for(int j=0; j<numlivros-i-1; j++) {
//                 if(lista_livros_ordenados[j].preco > lista_livros_ordenados[j+1].preco){
//                     livro tro_K = lista_livros_ordenados[j];
//                     lista_livros_ordenados[j] = lista_livros_ordenados[j+1];
//                     lista_livros_ordenados[j+1] = tro_K;
//                 }
//             }
//         }
//         printf("Livros ordenados por preço com sucesso");
//         return ORDENAR_SUCESSO;
//     }
// }

// Funções de condição que serão chamadas pela função de ordenação principal

int sort(livro *lista, int t,
	 condicao cf) // Por enquanto um insertion. A gente pode mudar pra outra coisa dps
{
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
