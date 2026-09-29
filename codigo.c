#include <stdio.h>
#include <string.h> // Fixed: Added for strcmp()

#define MAX_LIVROS 20
#define ORDENAR_ERRO -1
#define ORDENAR_SUCESSO -2

typedef struct {
    char nome[100];
    int preco;
} livro;

int ordenar_nome(livro lista_livros[], int *numlivros);
int ordenar_preco_crescente(
    livro lista_livros[],
    livro lista_livros_ordenados[],
    int numlivros);

int main() {
    livro lista_livros[MAX_LIVROS];
    livro lista_ordenado[MAX_LIVROS];
    int sair = 0;
    int opcao = 1;
    int numlivros = 0;

    while(!sair){
        switch(opcao) {
            case 1:
                sair = 1;
                break;

            case 2:
                // Fixed: Added required arguments to the function call
                ordenar_nome(lista_livros, &numlivros);
                break;

            case 3:
                ordenar_preco_crescente(lista_livros, lista_ordenado, numlivros);
                break;
        }
    }
    return 0;
}

int ordenar_nome(livro lista_livros[], int *numlivros){
    livro tro_K;

    if (*numlivros == 0){
        printf("Nenhum livro cadastrado");
        return ORDENAR_ERRO;
    }
    else {
        for(int icont = 0; icont < *numlivros - 1; icont++) {
            for(int jcont = 0; jcont < *numlivros - icont - 1; jcont++) {
                if(strcmp(lista_livros[jcont].nome, lista_livros[jcont+1].nome) > 0) {
                    tro_K = lista_livros[jcont];
                    lista_livros[jcont] = lista_livros[jcont+1];
                    lista_livros[jcont+1] = tro_K;
                }
            }
        }
        printf("Livros ordenados por nome com sucesso");
        return ORDENAR_SUCESSO;
    }
}

int ordenar_preco_crescente(livro lista_livros[], livro lista_livros_ordenados[], int numlivros){
    if (numlivros == 0){
        printf("Nenhum livro cadastrado");
        return ORDENAR_ERRO;
    }
    else {
        for(int i=0; i<numlivros; i++){
            lista_livros_ordenados[i]=lista_livros[i];
        }

        for(int i=0; i<numlivros-1; i++){
            for(int j=0; j<numlivros-i-1; j++) {
                if(lista_livros_ordenados[j].preco > lista_livros_ordenados[j+1].preco){
                    livro tro_K = lista_livros_ordenados[j];
                    lista_livros_ordenados[j] = lista_livros_ordenados[j+1];
                    lista_livros_ordenados[j+1] = tro_K;
                }
            }
        }
        printf("Livros ordenados por preço com sucesso");
        return ORDENAR_SUCESSO;
    }
}
