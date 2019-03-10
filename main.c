#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int random(int a,int b) //random genere un nombre aleatoire entre a inclu et b exclu
{
    int c;
    c = rand()%(b-a) + a;
    return c;
}
int alealong(int a ,int b) //generer la taille du mot aleatoirement de taille entre a et b tout les deux inclus
{
    int c;
    if (a<b) {
        c = random(a,b+1);
        return c;
    } else {
        exit(0);
    }
}
char alealettre(int a, int b)
{//generer une lettre aleatoire d'ordre entre a et b
    char c;
    if (a<b && a>=1 && b<=26) {
        c = random(a+96,b+97);
        return c;
    } else {
        exit(0);
    }
}
char* aleamot(int a, int b)
{//genere un mot aleatoirement de taille entre a et b, retourne un pointeur vers la chaine de caractere
    char *mot=NULL;
    //on alloue en memoire une chaine de caractere de taille b
    mot = malloc(b*sizeof(char));
    int i = alealong(a,b);
    for (int j=0 ; j<i ; j++){
        mot[j] = alealettre(1,26);
    }
    mot[i]='\0';
    return mot;
}
int def(char mot[8])
{ //donne la definition d'un mot
    int i , resu=0 , inter;
    //on parcourt la chaine de caractere
    for(i=0 ; mot[i]!='\0' ; i++) {
        //les caracteres miniscules en ascii commencent par 97 (a) donc on soustrait 96 pour avoir l'ordre
        inter = mot[i] - 96;
        resu += inter ;
    }
    return resu;
}
int main()
{
    char *i;
    int j;
    srand(time(NULL));
    i = aleamot(2,8);
    j = def(i);
    printf("%s %d",i,j);
    return 0;
}
