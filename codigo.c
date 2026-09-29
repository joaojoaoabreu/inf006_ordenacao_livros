#include <stdio.h>
#define MAX_LIVROS 20

typedef struct {
    char nome [60];
    int preco;
} livro;

void main{
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
