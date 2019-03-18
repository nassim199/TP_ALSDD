#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//implementation du modele de LLC de la structure du dictionnaire
//le maillon contient le mot et l'indice et l'addresse du maillon suivant
typedef struct Maillon { char* mot ; int ind ; struct Maillon *next; } Maillon;

void allouer (Maillon **nouveau)
{
 	*nouveau = (Maillon*)malloc(sizeof(Maillon));
}

void aff_adr(Maillon *p, Maillon *q)
{
	p->next = q ;
}

Maillon *suivant (Maillon *p)
{
	return p->next;
}

void aff_ind(Maillon *p , int indice)
{
	p->ind = indice ;
}

int indice (Maillon *p)
{
	return p->ind ;
}

void aff_mot (Maillon *p , char* nouveauMot)
{
    p->mot = nouveauMot;
}

char* mot_maillon (Maillon *p)
{
    return p->mot;
}

void liberer (Maillon** ancien)
{
	free(*ancien);
	*ancien=NULL;
}

//fonctions pour creer le dictionnaire

int random(int a,int b) //random genere un nombre aleatoire entre a inclu et b exclu
{
    int c;
    c = rand()%(b-a) + a;
    return c;
}
int alealong(int a ,int b) //generer la taille du mot aleatoirement de taille entre a et b tout les deux inclus
{
    int c;
    if (a<=b) {
        c = random(a,b+1);
        return c;
    } else {
        exit(0);
    }
}
char alealettre(int a, int b) //generer une lettre aleatoire d'ordre entre a et b
{
    char c;
    if (a<=b && a>=1 && b<=26) {
        c = random(a+96,b+97);
        return c;
    } else {
        exit(0);
    }
}
char* aleamot(int a, int b) //genere un mot aleatoirement de taille entre a et b, retourne un pointeur vers la chaine de caractere
{
    char *mot=NULL;
    //on genere aleatoirement un nombre entre a et b
    int i = alealong(a,b);
    //on alloue en memoire une chaine de caractere de taille i+1
    mot = malloc((i+1)*sizeof(char));

    for (int j=0 ; j<i ; j++){ //pour chaque case on genere une lettre aleatoire
        mot[j] = alealettre(1,26);
    }
    mot[i]='\0';
    return mot;
}
int def(char* mot) //donne la definition d'un mot
{
    int i , resu=0 , inter;

    //on parcourt la chaine de caractere
    for(i=0 ; mot[i]!='\0' ; i++) {
        //les caracteres miniscules en ascii commencent par 97 (a) donc on soustrait 96 pour avoir l'ordre
        inter = mot[i] - 96;
        resu += inter ;
    }

    return resu;
}
//type Dico est les mot avec sa definition
typedef struct Dico { char* mot ; int def ;} Dico;

//procedure de creation du dico

void creationDico (Dico dico[30]) //la dictionnaire est un tableau de Dico de taille 3000
{
   int i ;

   for(i=0 ; i<30 ; i++) { //pour chaque case on associe un mot aleatoire et puis sa definition
    dico[i].mot = aleamot(2,8);
    dico[i].def = def(dico[i].mot);
   }
}

//procedure de creation de la structure et fonctions de recherche et d'insertion

void accesLong(Maillon *t,int L , Maillon **p, Maillon **q) {
	//donne le premier mot de longueure superieur ou egal a L dans q si il existe et NULL sinon, p est le precedent de q
	*q=t;
	*p=NULL;
	while ( (*q)!=NULL && strlen(mot_maillon(*q))<L) {
	    (*p)=(*q);
	    (*q)=suivant(*q);
	}
}

void insertion(char* mot , Maillon **t , int i)
{//inserer un mot dans la liste par longueur
    int L = strlen(mot) ;

    Maillon *r = NULL  , *p = NULL, *q = NULL;
    accesLong(*t, L , &p , &q);
    allouer(&r);
    aff_adr(r,q);
    aff_ind(r,i); //i est l'indice
    aff_mot(r,mot);
    if (q==(*t)) {
    	*t = r;
    } else {
    	aff_adr(p,r);
    }

}
void dicoStructure (Dico dico[30], Maillon* T[26])
{//creation de la structure du dictionnaire
    int i ,ordre;
    Maillon *t;
    for (i=0 ; i <30 ; i++)
    {
     //on cherche l'ordre de la premiere lettre en prenant 'a' a l'ordre 0
     ordre = dico[i].mot[0] -97;
     //on insere le mot dans le structure
     insertion(dico[i].mot , &T[ordre] , i);
    }
}
void afficher(Maillon *p) {
while (p != NULL) {
    printf("%s  \n",mot_maillon(p));
    p=suivant(p);
}
}
int main()
{
    int j;
    Dico dico[30];
    Maillon* T[26]={NULL};
    creationDico(dico);
    for (j=0 ;j<30;j++){
    printf("%s %d \n",dico[j].mot,dico[j].def);
    }
    dicoStructure(dico ,T);
    printf("ici c'est les listes \n");
    for (j=0 ; j<26 ; j++){
    printf("T[%d] \n",j);
    afficher(T[j]);
    }
    return 0;
}
