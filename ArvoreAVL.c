#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAVL.h" //inclui os Prot�tipos


// =================================================

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no)
{
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

void RotacaoLL(ArvAVL *A){ // rotação simples pra esquerda
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){ // rotação simples pra direita
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){ // rotação para DIREITA e depois para ESQUERDA
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){// rotação para ESQUERDA e depois para DIREITA
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

// ===================================================



ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

unsigned long int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int insere_ArvAVL(ArvAVL *raiz, char* valor, unsigned long int count){
    int res;
    if(*raiz == NULL)
    {
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
        {
            return 0;
        }

        strcpy(novo->word, valor);
        novo->count = count;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(strcmp(valor, atual->word) < 0) // valor é menor que a atual
    { 
        if((res = insere_ArvAVL(&(atual->esq), valor, count)) == 1)
        {
            if(fatorBalanceamento_NO(atual) >= 2)
            {
                if(strcmp(valor, (*raiz)->esq->word) < 0)
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }
    else
    {
        if(strcmp(valor, atual->word) > 0)
        {
            if((res = insere_ArvAVL(&(atual->dir), valor, count)) == 1)
            {
                if(fatorBalanceamento_NO(atual) >= 2)
                {
                    if(strcmp(valor, (*raiz)->dir->word) > 0)
                    {
                        RotacaoRR(raiz);
                    }
                    else
                    {
                        RotacaoRL(raiz);
                    }
                }
            }
        }
        else
        {
            atual->count += count;
            return 0;
        }
    }
    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;
    return res;
}

void imprime_emOrdem_ArvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        imprime_emOrdem_ArvAVL(&((*raiz)->esq));
        fprintf(arqout, "%s %ld\n",(*raiz)->word, (*raiz)->count);
        imprime_emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void broke_text(char* file_name)
{
    FILE *arqin;
    FILE *arqout;
    arqin = fopen(file_name, "rt");
    if(arqin == NULL)
    {
        printf("Error: Open the %s.txt.\n", file_name);
        exit(-1);
    }
    arqout = fopen("broken_text.txt", "wt");
    if(arqout == NULL)
    {
        printf("Error: Open the broken_text.txt.\n");
        fclose(arqin);
        exit(-1);
    }

    unsigned char c;
    unsigned char ant_c = '\n';
    while(!feof(arqin))
    {
        c = fgetc(arqin);
        if (c == ' ' || c == '\n') // se for espaço ou quebra de linha, quebra linha
        {
            c = '\n';
        }
        if (c != '\n' && (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')) // se não for uma letra, ignora esse caracter
        {
            continue;
        }
        if (ant_c == '\n' && c == '\n') // se for dois \n seguidos, deleta 1
        {
            continue;
        }
        if (c >= 'A' && c <= 'Z') // se for maiuscula, vira minuscula
        {
            c += 'a' - 'A';
        }
        ant_c = c;
        fputc(c, arqout); 
    }
    fclose(arqout);
    fclose(arqin);
}
