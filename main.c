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

void creationDico (Dico dico[3000]) //la dictionnaire est un tableau de Dico de taille 3000
{
   int i ;

   for(i=0 ; i<3000 ; i++) { //pour chaque case on associe un mot aleatoire et puis sa definition
    dico[i].mot = aleamot(2,8);
    dico[i].def = def(dico[i].mot);
   }
}

//procedure de creation de la structure et fonctions de recherche et d'insertion


void accesLongcpt(Maillon *t,int L , Maillon **q , int *cpt ) {
	//donne le premier mot de longueure superieur ou egal a L dans q si il existe et NULL sinon, il donne aussi le nombre de comaparaison fait : CPT
	*q=t;
	*cpt= 1 ;
	while ( (*q)!=NULL && strlen(mot_maillon(*q))<L) {
	    (*q)=suivant(*q);
	    (*cpt)++;
	}
}
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
    for (i=0 ; i <3000 ; i++)
    {
     //on cherche l'ordre de la premiere lettre en prenant 'a' a l'ordre 0
     ordre = dico[i].mot[0] -97;
     //on insere le mot dans le structure
     insertion(dico[i].mot , &T[ordre] , i);
    }
}
void dicoStructurePlus ( Dico dico[3000] , Maillon* T2 [26][26])
{   // creation de notre structure améliorée ( c'est une structure de 2D ou nombre de ligne et nombre de colonne  correspond respectivement  à l'ordre de 1ere lettre et 2eme lettre de notre mot
    int i , ordrelig , ordrecol ;
    for (i=0 ; i < 3000 ;i++ )
    {
        ordrelig = dico[i].mot[0]-97; //ordrelig est l'ordre de la premiere lettre de notre mot
        ordrecol = dico[i].mot[1]-97; //ordrecol est l'ordre de la deuxieme lettre de notre mot
        insertion (dico[i].mot , &T2[ordrelig][ordrecol] , i ); // on insere le mot dans notre nouvelle structure selon l'ordre de ses deux premiers lettres
    }

}
void afficher(Maillon *p) {
while (p != NULL) {
    printf("%s  \n",mot_maillon(p));
    p=suivant(p);
}
}

void Recherche1D (  char MOT[8] ,  int  *i , Maillon* T[26] , int *cpt  )
{
    int ordre ;
    ordre = MOT[0] - 97 ;
    *cpt = 1 ; // cpt est le nombre de comparaisons faits jusqu'a trouver MOT
    Maillon* p = T[ordre] ; // on initialise le pointeur  p sur  la tete de liste qui contient les mots commençons par le premier lettre de MOT
    accesLongcpt(T[ordre], strlen(MOT), &p , &(*cpt)); // accés à  le premier maillon a un  mot de longueure superieur ou egal a la longueur de MOT
    while (  p!=NULL && strcmp( MOT , mot_maillon(p))!= 0 && strlen(MOT)== strlen(mot_maillon(p))  ) // on parcourt les maillon tant qu'on n'arrive pas à une maillon a un mot sa longueur est supérieur que MOT ou on n'atteind pas encore  la fin de notre liste
    {
        (*cpt)++ ;
        p=suivant(p);
    }
    if ( p == NULL || strcmp(MOT , mot_maillon(p))!= 0 ) // c'est à dire si on ne trouve pas MOT
    {
        *cpt = 0 ; // la valeur null de cpt nous informe que MOT  n'est pas disponible
    }
    else
    {
        *i = indice(p) ; // MOT est dans la maillon  pointé par p
    }
}

void Recherche2D (  char MOT[8] ,  int  *i , Maillon* T2[26][26] , int *cpt  )
{
    int ordrecol , ordrelig ;
    ordrelig = MOT[0] - 97 ;
    ordrecol = MOT[1] - 97 ;
    *cpt = 1 ;
    Maillon* p = T2[ordrelig][ordrecol] ; // on initilaise le pointeur p sur la tete de liste des mots commençants par les deux premiers lettres de MOT
    accesLongcpt(T2[ordrelig][ordrecol], strlen(MOT), &p , &(*cpt)); // // accés à  le premier maillon a un  mot de longueure superieur ou egal a la longueur de MOT
    while (  p!=NULL && strcmp( MOT , mot_maillon(p))!= 0 && strlen(MOT)== strlen(mot_maillon(p))  )
    {
        (*cpt)++ ;
        p=suivant(p);
    }
    if ( p == NULL || strcmp(MOT , mot_maillon(p))!= 0 )
    {
        *cpt = 0 ;
    }
    else
    {
        *i = indice(p) ;
    }
}
void Recherche (char MOT[8], int *i , Maillon* T [26] , Maillon* T2[26][26], int *cpt1d , int *cpt2d )
{   // cette procedure est une fusiion de  deux types de recherches précédentes
    int ind1d=0 , ind2d=0 ;
    Recherche1D(MOT, &ind1d , T , &(*cpt1d) ); // cpt1d est le nombre de comparaison faites pour trouver MOT dans la structure T ( s'il existe , sinon cpt1d =0 )
    Recherche2D(MOT,&ind2d , T2 , &(*cpt2d) ); // cpt2d est le nombre de comparaison faites pour trouver MOT dans la nouvelle structure T2 ( s'il existe , sinon cpt2d =0 )
    if (ind1d == ind2d )
    {
        *i=ind1d ;
    }
    else
    {
        printf("Erreur !! \n"); // s'il  y a  une  contradictions entre la résultat (l'indice du MOT ) sortit par les deux recherches il faut informer l'utilisateur ( primitivement il n'y a jamais )
    }
}
int optimisation ( int cpt1d , int cpt2d )
    // la sortie de cette fonction ( result ) désigne le pourcentage de réduction de nombre de comparaisons faites entre la structure initiale et notre structure améliorée
{
    int result = (cpt1d * 100) / cpt2d ;
    return result ;
}
int main()
{
    int j;
    Dico dico[3000];
    Maillon* T[26]={NULL};
    creationDico(dico);
    for (j=0 ;j<3000;j++){
    printf("%d :  %s %d \n",j ,dico[j].mot,dico[j].def);
    }
    dicoStructure(dico ,T);
    printf("ici c'est les listes \n");
    for (j=0 ; j<26 ; j++){
    printf("T[%d] \n",j);
    afficher(T[j]);
    }
    Maillon* T2 [26][26]={NULL} ;
    dicoStructurePlus(dico , T2 );
    printf(" tapez n'importe quelle touche pour afficher la structure amelioree :     ");
    getch();
    int k ;
    for (j=0 ; j <26 ; j++ )
    {
        for (k=0 ; k<26 ; k++)
        {
            printf("T[%d][%d] \n" , j , k);
            afficher (T2[j][k]);
        }
    }
    char mot[8] ;
    int indice=0 , cpt1d , cpt2d ;
    printf("donnez le mot à chercher :    ");
    scanf("%s" , mot );
    Recherche (mot , &indice , T , T2 , &cpt1d , &cpt2d);
    if ( cpt1d != 0 && cpt2d != 0) // on a dit préalablement que la valeur null de nombre de comparaison faites signifie que le mot n'existe pas
    {
    printf(" On a trouvé %s !!! , il est dans dico[%d]\n" ,mot ,  indice);
    printf("Pour trouver %s : \n on a fait %d comparaisons dans la structure initiale mais seuelement %d comparaisons dans notre nouvelle structure ! \n", mot , cpt1d , cpt2d );
    printf("La recherche est optimsee  %d%% \n", optimisation(cpt1d , cpt2d));
    }

    else
    {
        printf("%s n'existe pas dans deco[3000] !!! \n ", mot);
    }
    return 0;
}
