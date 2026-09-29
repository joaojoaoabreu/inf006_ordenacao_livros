#include <stdio.h>
#define MAX_LIVROS 20
#define ORDENAR_ERRO -1
#define ORDENAR_SUCESSO -2

typedef struct {
    char nome [60];
    int preco;
}livro;

int ordenar_nome(livro lista_livros[], int *numlivros);
int ordenar_preco_crescente(livro lista_livros[] livro lista_livros_ordenados[] int numlivros)

void main{
    livro lista_livros[MAX_LIVROS];
    livro lista_ordenado[MAX_LIVROS]
    int sair = 0;
    int opcao;
    int numlivros;
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

int ordenar_nome(livro lista_livros[], int *numlivros){
    int tro_K;
    if (numlivros == 0){
	printf{“Nenhum livro cadastrado”};
	return = ORDENAR_ERRO;
}
else{

    for(int icont = 0; icont < *numlivros; icont++) {
		for(int jcont = icont; jcont < *numlivros; jcont++) {
			if(strcmp(lista_livros[jcont].nome, lista_livros[jcont+1].nome) > 0) {
				tro_K = lista_livros[jcont];
				lista_livros[jcont] = lista_livros[jcont+1];
				lista_livros[jcont+1] = tro_K;
			}
		}
	}
printf{“Livros ordenados por nome com sucesso”};
    	return ORDENAR_SUCESSO;

}
}


int ordenar_preco_crescente(livro lista_livros[] livro lista_livros_ordenados[] int numlivros){
    if (numlivros == 0){
	printf{“Nenhum livro cadastrado”};
	return ORDENAR_ERRO;
}
   else{
    for(int i=0; i<numlivros; i++){
        lista_livros_ordenados[i]=lista_livros[i];
    }
        for(int i=0; i<numlivros-1; i++){
            if(lista_livros_ordenados[i].preco>lista_livros_ordenados[i+1].preco){
                int tro_K= lista_livros_ordenados[i].preco;
                lista_livros_ordenados[i].preco = lista_livros_ordenados[i+1];
                lista_livros_ordenados[i+1] = tro_K;
            }
        }
	printf{“Livros ordenados por preço com sucesso”};
    	return ORDENAR_SUCESSO;
    }
}
