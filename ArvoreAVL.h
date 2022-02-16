//  Arquivo ArvoreAVL.h

FILE *arqin, *arqout, *stats;

struct NO{
    char word[32];
    unsigned long int count;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL(void);
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, char* valor, unsigned long int count);
int altura_ArvAVL(ArvAVL *raiz);
unsigned long int totalNO_ArvAVL(ArvAVL *raiz);
void imprime_emOrdem_ArvAVL(ArvAVL *raiz);
void broke_text(char* file_name);
