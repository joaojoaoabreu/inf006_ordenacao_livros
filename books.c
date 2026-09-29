#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 20

typedef struct {
    char nome[100];
    int preco;
} livro;


/* =========================
   ORDENAÇÃO POR NOME
   ========================= */

int ordenar_nome(livro lista_livros[], int numlivros)
{
    livro tro_K;

    if (numlivros == 0) {
        return -1;
    }

    for (int i = 0; i < numlivros - 1; i++) {

        for (int j = 0; j < numlivros - i - 1; j++) {

            if (strcmp(
                lista_livros[j].nome,
                lista_livros[j + 1].nome
            ) > 0) {

                tro_K = lista_livros[j];

                lista_livros[j] =
                    lista_livros[j + 1];

                lista_livros[j + 1] =
                    tro_K;
            }
        }
    }

    return 0;
}


/* =========================
   ORDENAÇÃO POR PREÇO
   ========================= */

int ordenar_preco_crescente(
    livro lista_livros[],
    int numlivros)
{
    livro tro_K;

    if (numlivros == 0) {
        return -1;
    }

    for (int i = 0; i < numlivros - 1; i++) {

        for (int j = 0; j < numlivros - i - 1; j++) {

            if (
                lista_livros[j].preco >
                lista_livros[j + 1].preco
            ) {

                tro_K = lista_livros[j];

                lista_livros[j] =
                    lista_livros[j + 1];

                lista_livros[j + 1] =
                    tro_K;
            }
        }
    }

    return 0;
}


/* =========================
   IMPRIMIR JSON
   ========================= */

void imprimir_json(
    livro lista_livros[],
    int numlivros)
{
    printf("[");

    for (int i = 0; i < numlivros; i++) {

        printf(
            "{\"nome\":\"%s\",\"preco\":%d}",
            lista_livros[i].nome,
            lista_livros[i].preco
        );

        if (i < numlivros - 1) {
            printf(",");
        }
    }

    printf("]\n");
}


/* =========================
   MAIN
   ========================= */

int main(int argc, char *argv[])
{
    livro lista_livros[MAX_LIVROS] = {

        {"The Hobbit", 3990},
        {"Clean Code", 8990},
        {"1984", 2990},
        {"Dune", 5990},
        {"The C Programming Language", 7990}

    };

    int numlivros = 5;


    /*
       Nenhum argumento:
       retorna lista original
    */

    if (argc == 1) {

        imprimir_json(
            lista_livros,
            numlivros
        );

        return 0;
    }


    /*
       Ordenar por nome
    */

    if (strcmp(argv[1], "nome") == 0) {

        ordenar_nome(
            lista_livros,
            numlivros
        );

        imprimir_json(
            lista_livros,
            numlivros
        );

        return 0;
    }


    /*
       Ordenar por preço
    */

    if (strcmp(argv[1], "preco") == 0) {

        ordenar_preco_crescente(
            lista_livros,
            numlivros
        );

        imprimir_json(
            lista_livros,
            numlivros
        );

        return 0;
    }


    printf("{\"erro\":\"ordenacao invalida\"}\n");

    return 1;
}