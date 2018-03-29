#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @author Vinicius
 * @version 1.0
 */

/** Criação da assinatura da estrutura. */
typedef struct _Endereco Endereco;
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

/**
 * Função principal do projeto que abre um arquivo e divide em varios outros arquivos de acordo com a sigla do estado.
 * @param argc quantidade de parametros passados para a função principal
 * @param argv valores dos parametros passados para a função principal
 * @return retorno da função principal é do tipo inteiro e retorna 0 caso seja executada com sucesso e 1 para erro.
 */
int main(int argc, char**argv) {
    /** Inicialização de variáveis. */
    Endereco endereco;
    FILE *file;
    FILE *saida;
    int qt=0;
    char ufAtual[3] = {0,0,0};

    /** Verificação de uso correto dos parametros passados para a função. */
    if(argc != 1) {
        printf("Uso: %s \n\n", argv[0]);
        return 1;
    }

    /** Abertura do arquivo do arquivo cep_ordenado.dat. */
    file = fopen("cep_ordenado.dat","r");

    /** Lendo uma linha do arquivo cep_ordenado.dat e armazenando na estrutura endereco. */
    qt = fread(&endereco,sizeof(Endereco),1,file);

    /** Loop para ler todas as linhas do arquivo cep_ordenado.dat e separa este arquivo em diversos outros de acordo com a sigla do estado. */
    while(qt > 0) {
        stpncpy(ufAtual,endereco.sigla,2);
        if (saida = fopen(ufAtual, "r")) {
            fclose(saida);
            saida = fopen(ufAtual, "a+");
            fwrite(&endereco, sizeof(Endereco),1, saida);
            fclose(saida);
        }else {
            saida = fopen(ufAtual, "w");
            fwrite(&endereco, sizeof(Endereco),1, saida);
            fclose(saida);
        }
        qt = fread(&endereco,sizeof(Endereco),1,file);
    }
    /** Fechamento do aquivo cep_ordenado.dat */
    fclose(file);
    return 0;
}