/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Samuel
 *
 * Created on 12 de Maio de 2020, 21:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

typedef struct {
    int cod;
    char nome[50];
} cadastro;

int main(int argc, char** argv) {

    int tam = 0, i, opc, primeira_vez_cadastro = 1, codigo;
    cadastro *vtr_cadastro;

    while (opc != 7) {
        printf("\n---CRUD SIMPLES---\n");
        printf("Digite uma opção:\n");
        printf(" 1-Cadastrar\n 2-Listar Cadastros\n 3-Alterar Cadastro\n 4-Excluir Cadastro\n 5-Pesquisar cadastro\n 6-Gravar em arquivo\n 7-Encerrar\n ");
        printf("--->");
        scanf("%d", &opc);
        switch (opc) {

            case 1: //cadastrar
            {
                int status = 0;
                cadastro cliente;
                tam++;
                printf("\n---CADASTRO---\n");
                printf("Digite o nome:");
                scanf(" %s", &cliente.nome);

                if (primeira_vez_cadastro == 1) {
                    vtr_cadastro = (cadastro *) malloc(tam * sizeof (cadastro));
                    primeira_vez_cadastro = 0;
                    cliente.cod = 1; //
                    vtr_cadastro[tam - 1] = cliente;
                    status = 1;

                } else {
                    vtr_cadastro = (cadastro *) realloc(vtr_cadastro, tam * sizeof (cadastro));
                    cliente.cod++; //
                    vtr_cadastro[tam - 1] = cliente;
                    status = 1;

                }
                if (status == 1) {
                    printf("Cadastro efetuado com sucesso!\n");
                }
                break;
            }

            case 2: //listar
            {
                printf("\n---LISTA DE CADASTRO---\n");
                for (i = 0; i < tam; i++) {
                    printf("Código: %d\t", vtr_cadastro[i].cod);
                    printf("Nome: %s\n", vtr_cadastro[i].nome);
                }
                break;
            }

            case 3: //alterar
            {
                int alterar = tam, status = 0;
                char nome[50];
                printf("\n---ALTERAÇÂO DE CADASTRO---\n");
                printf("Informe o código do cliente:");
                printf("--->");
                scanf("%d", &codigo);

                for (i = 0; i < tam; i++) {
                    if (codigo == vtr_cadastro[i].cod) {
                        alterar--;
                        printf("Digite novamente o nome do cliente:");
                        scanf(" %s", &nome);
                        strcpy(vtr_cadastro[i].nome, nome);
                        status = 1;
                    }
                }
                if (alterar == tam) {
                    printf("Cadastro não encontrado!!!\n");
                }
                if (status == 1) {
                    printf("Alteração do cadastro efetuada com sucesso!\n");
                }
                break;
            }

            case 4:
            { //excluir
                int exclui = -1, status = 0;
                printf("Informe o código do cliente que você deseja excluir:");
                printf("--->");
                scanf("%d", &codigo);

                for (i = 0; i < tam; i++) {
                    if (codigo == vtr_cadastro[i].cod) {
                        vtr_cadastro[i] = vtr_cadastro[tam - 1];
                        tam--;
                        vtr_cadastro = (cadastro *) realloc(vtr_cadastro, tam * sizeof (cadastro));
                        exclui = 0;
                        status = 1;
                    }
                }
                if (exclui == -1) {
                    printf("Erro. Não foi possível fazer a exclusão do cadastro do cliente!\n");
                }
                if (status == 1) {
                    printf("Cadastro excluído com sucesso!\n");
                }
                break;
            }

            case 5:
            {//pesquisar
                int opc;
                printf("\n---PESQUISAR CADASTRO---\n");
                printf("Escolha uma opção:\n");
                printf("1-Pesquisa por código\n");
                printf("2-Pesquisa por nome\n");
                printf("--->");
                scanf("%d", &opc);

                switch (opc) {
                    case 1:
                    {
                        int status = 0;
                        printf("\n---PESQUISAR POR CÓDIGO---\n");
                        printf("Informe o código para pesquisar o cadastro:\n");
                        printf("--->");
                        scanf("%d", &codigo);

                        for (i = 0; i < tam; i++) {
                            if (codigo == vtr_cadastro[i].cod) {
                                printf("Código: %d\t", vtr_cadastro[i].cod);
                                printf("Nome: %s\n", vtr_cadastro[i].nome);
                                status = 1;
                            }
                        }
                        if (status == 0) {
                            printf("Não existe cliente cadastrado com esse código!\n");
                        }
                        break;
                    }
                    case 2:
                    {
                        char nome[50];
                        int status = 0;
                        printf("\n---PESQUISAR POR CÓDIGO---\n");
                        printf("Informe o nome para pesquisar o cadastro:\n");
                        printf("--->");
                        scanf(" %s", &nome);

                        for (i = 0; i < tam; i++) {
                            if (strcmp(vtr_cadastro[i].nome, nome) == 0) {
                                printf("Código: %d\t", vtr_cadastro[i].cod);
                                printf("Nome: %s\n", vtr_cadastro[i].nome);
                                status = 1;
                            }
                        }
                        if (status == 0) {
                            printf("Não existe cliente cadastrado com esse nome!\n");
                        }
                        break;
                    }
                    default:
                    {
                        printf("Opção inválida.\n");
                        break;
                    }
                }
                break;
            }

            case 6:
            {
                int opt;
                printf("Escolha uma opção:\n");
                printf(" 1-TXT\n 2-CSV\n 3-BIN\n");
                scanf("%d", &opt);
                switch (opt) {
                    case 1:
                    {
                        FILE *arquivo;
                        arquivo = fopen("arquivo.txt", "w"); //grava arquivo TXT
                        if (arquivo == NULL) {
                            printf("Falha ao escrever arquivo!\n");
                        }
                        int j, result; //a funcao fprintf serve para escrever dados formatados em um arquivo
                        for (j = 0; j < tam; j++) {
                            result = fprintf(arquivo, "Código: %d\tNome: %s\n", vtr_cadastro[j].cod, vtr_cadastro[j].nome); // grava todos os dados cadastrados em um arquivo .txt e .csv
                        }
                        if (result == EOF) {
                            printf("Erro na gravação.");
                        }
                        int fflsuh(FILE * arquivo);
                        fclose(arquivo);
                        break;
                    }
                    case 2:
                    {
                        FILE *arquivo;
                        arquivo = fopen("arquivo.csv", "w"); //grava arquivo CSV
                        if (arquivo == NULL) {
                            printf("Falha ao escrever arquivo!\n");
                        }
                        int j, result; //a funcao fprintf serve para escrever dados formatados em um arquivo
                        for (j = 0; j < tam; j++) {
                            result = fprintf(arquivo, "Code: %d\nName: %s\n\n", vtr_cadastro[j].cod, vtr_cadastro[j].nome); // grava todos os dados cadastrados em um arquivo .txt e .csv
                        }
                        if (result == EOF) {
                            printf("Erro na gravação.");
                        }
                        int fflsuh(FILE * arquivo);
                        fclose(arquivo);
                        break;
                    }
                    case 3:
                    {
                        FILE *arquivob;
                        arquivob = fopen("arquivo.bin", "wb"); //wb =write binario
                        if (arquivob == NULL) {
                            printf("Falha ao escrever arquivo!\n");
                        }
                        fwrite(vtr_cadastro, sizeof (cadastro), tam, arquivob); //grava todos os dados cadastrados em um arquivo .bin
                        int fflush(FILE * arquivob);
                        fclose(arquivob);
                        break;
                    }
                    default:
                    {
                        printf("Opção inválida.\n");
                        break;
                    }
                }
                break;
            }

            case 7: //encerrar
            {
                printf("Encerrando o programa...");
                break;
            }

            default://opcao invalida
            {
                printf("Opção inválida\n");
                break;
            }
        }
    }
    return (EXIT_SUCCESS);
}
