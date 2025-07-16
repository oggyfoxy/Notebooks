#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void shift(char *src) {
    
    srand(time(0));

    size_t i;

    int mix = (rand() % 10) + 1;
    
    printf("shift = %d\n", mix);

    while(src == NULL || *src == '\0')
        return;
    for(i = 0; src[i] != '\0'; i++)
        src[i] = src[i] + mix;
}

int main () {

    //en gros je veux que mon cypher shifte tout mon texte d'un nombre x de caracteres
    //je vais devoir analyser quelle lettre est la plus frequente, puis essayer de shift jusqu'a ce que je trouve du sens
    //ou alors je fais une fonction qui incremente le shift des que je lui dis et qui reessaye et c'est a moi d'essayer
    //ou alors je donne une base de donnees a mon algo et des qu'il repere un mot comme "the" il sait que c'est trouve

    //je vais aussi faire une fonction qui permet de shift le texte d'abord
    char texte[100];

    printf("enter your text : \n");
    scanf("%[^\n]", texte);

    printf("before shift : %s\n", texte);

    shift(texte);
    printf("after shift : %s\n", texte);
 
    return 0;

}
