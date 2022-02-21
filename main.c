#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAVL.h"

int main()
{
    ArvAVL* root = cria_ArvAVL();
    unsigned long int total_words = 0;

    // read previous word_stats
    stats = fopen("word_stats.txt", "rt");
    if (stats == NULL)
    {
        printf("> There isn't previous word_stats\n");
    }
    else
    {
        printf("\n> Reading previous word statistics...\n\n");
        char* stats_word = malloc(32);
        unsigned long int* stats_count = malloc(sizeof(unsigned long int));
        while (1)
        {
            fscanf(stats, "%s %ld", stats_word, stats_count);
            if (feof(stats))
            {
                break;
            }
            total_words += (*stats_count);
            insere_ArvAVL(root, stats_word, *stats_count);
        }
        free(stats_word);
        free(stats_count);
        fclose(stats);

    }


    // read new text
    char file_name[64];
    printf("> What's the file name? ");
    fgets(file_name, 64, stdin);
    file_name[strlen(file_name) - 1] = '\0';

    broke_text(file_name);
    arqin = fopen("broken_text.txt", "rt");
    if (arqin == NULL)
    {
        printf("FAIL: open broken_text.txt\n");
        libera_ArvAVL(root);
        return 0;
    }

    printf("> Reading the new text words...\n\n");
    char* text_word = malloc(sizeof(char) * 32);
    unsigned long int* text_count = malloc(sizeof(unsigned long int));
    
    fgets(text_word, 32, arqin);
    while (!feof(arqin))
    {
        text_word[strlen(text_word) - 1] = '\0';
        *text_count = 1;
        total_words += (*text_count);
        insere_ArvAVL(root, text_word, *text_count);
        fgets(text_word, 32, arqin);
    }
    free(text_word);
    free(text_count);
    fclose(arqin);

    // delete previous stats
    stats = fopen("word_stats.txt", "wt");
    fclose(stats);

    // stats
    printf("\n>>> SUMMARY OF THE STATS <<<\n\n");
    printf("   >>> Total of words read: %ld \n", total_words);
    printf("   >>> Total of different words: %ld\n", totalNO_ArvAVL(root));
    printf("   >>> Height of the binary tree: %d\n\n", altura_ArvAVL(root));
    arqout = fopen("word_stats.txt", "at");
    imprime_emOrdem_ArvAVL(root);
    fclose(arqout);

    libera_ArvAVL(root);

    return 0;
}
