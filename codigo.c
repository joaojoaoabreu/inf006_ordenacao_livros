#include <stdio.h>
#define MAX_LIVROS 20

typedef struct {
    char nome [60];
    int preco;
} livro;

// Ponteiro pra função que será implementado em breve pra criar função de ordenação
// genérica que puxa uma função de condição para determinar como será ordenado o objeto
// livro *lista_livro <- Nome figurativo
typedef int (*condicao)(livro, livro);

void ordenar_nome();
void ordenar_preco();

int preco_crescente(livro l1, livro l2);
int preco_decrescente(livro l1, livro l2);

int main() {
    livro lista_livros[MAX_LIVROS];
    int sair = 0;
    int opcao;
    while(!sair){
        switch(opcao) {
            
            case 1:
                sair = 1;
                break;
                
            case 2:
                ordenar_nome();
                break;
            
            case 3:
                ordenar_preco();
                break;
        }
    }
}

void ordenar_nome(){
    
}

void ordenar_preco(){
    
}


// Funções de condição que serão chamadas pela função de ordenação principal

int preco_crescente(livro l1, livro l2)
{
	if (l1.preco < l2.preco) return 1;

	return 0;
}

int preco_decrescente(livro l1, livro l2)
{
	if (l1.preco > l2.preco) return 1;

	return 0;
}

