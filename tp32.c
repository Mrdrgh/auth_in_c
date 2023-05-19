#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

typedef enum identifiant{CNI,CNE,APOGEE}identifiant;
typedef enum type_utilisateur{ETUDIANT,ADMINISTRATEUR}type_utilisateur;
typedef union login1{
    char CNI[10];
    char CNE[10];
    int APOGEE;
}login1;
typedef struct utilisateur{
    identifiant id;
    type_utilisateur type;
    login1 login2;
    char nom[20];
    char prenom[20];
    char datedenaissance[20];
    char password[20];
    struct utilisateur *suivant;
    
}utilisateur;

typedef struct livre{
    char titre[50];
    char auteur[50];
    int ISBN;
    struct livre *suivant;
}livre;

void remplire_livres(livre *E){
    printf("----------remplissage de livre-----------\n");
    printf("donner le titre du livre : ");
    scanf("%s",E->titre);
    printf("donner le nom de l'auteur : ");
    scanf("%s",E->auteur);
    printf("donner le ISBN du livre : ");
    scanf("%d",&E->ISBN);
}
livre* chargerlivre_de_fichier(){
    livre *book,*head;
    book=malloc(sizeof(livre));
    head=book;
    FILE *fp;
    fp=fopen("tp31-file.txt","r");
    if(fp==NULL){
        fprintf(stderr,"erreur 404 , path not found");
        exit(1);
    }
    while(fscanf(fp,"%s %s %d\n",book->auteur,book->titre,&book->ISBN)==3){
        book->suivant=malloc(sizeof(livre));
        book=book->suivant;
    }
    book->suivant=NULL;
    fclose(fp);
    return head;
}
livre* ajouter_dans_liste_livres(livre *liste){
    livre *nouv_element;
    nouv_element=malloc(sizeof(livre));
    remplire_livres(nouv_element);
    nouv_element->suivant=liste;
    FILE *fp;
    fp=fopen("tp31-file.txt","a+");
    fprintf(fp,"\n%s %s %d",nouv_element->auteur,nouv_element->titre,nouv_element->ISBN);
    fclose(fp);
    return nouv_element;
}
void initialiser_liste_livres(livre *L){
    L=malloc(sizeof(livre));
    L->suivant=NULL;
}
void afficher_liste_livres(livre *L){
   livre *courant;
   courant=malloc(sizeof(livre));
   courant=L;
   printf("affichage des livres : \n");
   while(courant->suivant!=NULL){
        printf("l'auteur : %s\n",courant->auteur);
        printf("le titre : %s\n",courant->titre);
        printf("le ISBN : %d\n",courant->ISBN);
        printf("-------------------\n");
        courant=courant->suivant;
   }
}

void init(utilisateur *liste){
    liste=NULL;
}

utilisateur* charger_liste_util_de_fichier() {
    FILE* fp = fopen("tp31-binary-user-file.dat", "rb");
    if (fp == NULL) {
        fprintf(stderr, "file not found");
        return NULL;
    }

    utilisateur* tete = NULL;
    utilisateur* u = NULL;
    utilisateur* dernier = NULL;

    while (1) {
        u = malloc(sizeof(utilisateur));
        if (u == NULL) {
            fprintf(stderr, "memory allocation failed");
             // free the memory allocated for the list so far
            return NULL;
        }
        if (fread(u, sizeof(utilisateur), 1, fp) != 1) {
            free(u);
            break;
        }
        if (tete == NULL) {
            tete = u;
        } else {
            dernier->suivant = u;
        }
        dernier = u;
    }

    // Reverse the list
    // utilisateur* prec = NULL;
    // u = tete;
    // while (u != NULL) {
    //     utilisateur* suiv = u->suivant;
    //     u->suivant = prec;
    //     prec = u;
    //     u = suiv;
    // }

    fclose(fp);
    return tete;
}
// utilisateur* charger_liste_util_de_fichier(){
//     FILE *fp;
//     fp=fopen("tp31-binary-user-file.dat","rb+");
//     if(fp==NULL){
//         fprintf(stderr,"file not found");
//     }
//     utilisateur *u=NULL,*tete=NULL;
//     u=malloc(sizeof(utilisateur));
//     tete=u;
//     while(fread(u,sizeof(utilisateur),1,fp)==1){
//         u->suivant=malloc(sizeof(utilisateur));
//         u=u->suivant;
//     }
//     // utilisateur* prec = NULL;
//     // u = tete;
//     // while (u != NULL) {
//     //     utilisateur* suiv = u->suivant;
//     //     u->suivant = prec;
//     //     prec = u;
//     //     u = suiv;
//     // }

//     // fclose(fp);
//     // return prec;
//     // fclose(fp);
//     // return tete;
// }

// utilisateur* charger_liste_util_de_fichier() {
//     FILE* fp = fopen("tp31-binary-user-file.dat", "rb");
//     if (fp == NULL) {
//         fprintf(stderr, "file not found");
//         return NULL;
//     }

//     utilisateur* tete = NULL;
//     utilisateur* u = NULL;

//     while (1) {
//         u = malloc(sizeof(utilisateur));
//         if (u == NULL) {
//             fprintf(stderr, "memory allocation failed");
//             return NULL;
//         }
//         if (fread(u, sizeof(utilisateur), 1, fp) != 1) {
//             free(u);
//             break;
//         }
//         u->suivant = tete;
//         tete = u;
//     }

//     fclose(fp);
//     return tete;
// }

void enregistrer_liste_util_dans_fichier(utilisateur *liste){
    utilisateur *courant;
    FILE *fp;
    fp=fopen("tp31-binary-user-file.dat","ab+");
    courant=liste;
    while(courant!=NULL){
        fwrite(courant,sizeof(utilisateur),1,fp);
        courant=courant->suivant;
    }
    fclose(fp);
}
void enregistrer_liste_util_dans_fichier_w_mode(utilisateur *liste){
    utilisateur *courant;
    FILE *fp;
    fp=fopen("tp31-binary-user-file.dat","wb");
    courant=liste;
    while(courant!=NULL){
        fwrite(courant,sizeof(utilisateur),1,fp);
        courant=courant->suivant;
    }
    fclose(fp);
}

void remplire_struct_util(utilisateur *u){
    printf("donner le type d'utilisateur : \n1-ADMIN\n2-ETUDIANT\n--->");
    int i;
    scanf("%d",&i);
    u->id=CNI;
    if(i==1){
        u->type=ADMINISTRATEUR;
    }
    if(i==2){
        u->type=ETUDIANT;
    }
    printf("donner le nom : ");
    scanf("%s",u->nom);
    printf("donner le prenom : ");
    scanf("%s",u->prenom);
    printf("donner la date de naissance (DD/MM/YYYY) : ");
    scanf("%s",u->datedenaissance);
    printf("donner le CNI : ");
    scanf("%s",u->login2.CNI);
    printf("donner le password : ");
    scanf("%s",u->password);
}

utilisateur* remplire_dans_liste_utilisateur(utilisateur *liste){
    utilisateur *nouv_element;
    nouv_element=malloc(sizeof(utilisateur));
    remplire_struct_util(nouv_element);
    nouv_element->suivant=liste;
    return nouv_element;
}

void afficher_liste_util(utilisateur *liste){
    utilisateur *courant;
    courant=liste;
    printf("affichage de la liste : \n ");
    while(courant!=NULL){
        printf("nom : %s\nprenom : %s\ndate de naissance : %s\ncni : %s\npassword : %s"
        ,courant->nom
        ,courant->prenom
        ,courant->datedenaissance
        ,courant->login2.CNI
        ,courant->password);
        if(courant->type==ADMINISTRATEUR){
            printf("\ntype : admin\n---------------\n");
        }
        if(courant->type==ETUDIANT){
            printf("\ntype : etudiant\n---------------\n");
        }
        courant=courant->suivant;
    }
}
utilisateur* delete_users_from_head_of_file(utilisateur *L){
    utilisateur *courant=L;
    L=courant->suivant;
    free(courant);
    return L;
}
utilisateur* delete_users_by_name_from_file(utilisateur *L,char *nom,char *prenom){
    utilisateur *courant,*temp;
    courant=L;
    int i=0;
    while(courant!=NULL){
        temp=courant;
        if(strcmp(courant->nom,nom)==0&&strcmp(courant->prenom,prenom)==0){goto found;i++;
            break;
        }
        
        courant=courant->suivant;
    }
    printf(" \nnom et prenom non trouves\n ");
    sleep(1.5);
    system("cls");
    return L;
    found : 
    if(i==1){L=temp->suivant;return L;}
    temp->suivant=courant->suivant;
    free(courant);
    return L;
}
int login(utilisateur *liste,livre *m){
    liste=malloc(sizeof(utilisateur));
    liste=charger_liste_util_de_fichier();
    int choix;
    char nom[20],prenom[20];
    // printf("donner le type d'utilisateur : \n1-ADMIN\n2-ETUDIANT");
    utilisateur *templiste;
    templiste=malloc(sizeof(utilisateur));
    templiste=NULL;
    int type;
    char localpassword[20],localCNI[20];
    utilisateur *courant;
    notfound :
    courant=liste;
    printf("donner le CNI : ");
    scanf("%s",localCNI);
    printf("donner le password : ");
    // scanf("%s",localpassword);
    char c;int l=0;
    while((c=_getch())!=13){
        localpassword[l]=c;
        l++;
        printf("-");
    }
    localpassword[l]='\0';
    while(courant!=NULL){
        if(strcmp(courant->login2.CNI,localCNI)==0&&strcmp(courant->password,localpassword)==0){if(courant->type==ADMINISTRATEUR){type=1;}if(courant->type==ETUDIANT){type=2;}goto found;}
        courant=courant->suivant;
    }
    printf("\nutilisateur non trouve , donner un valide CNI et PW : \n");
    sleep(1);
    system("cls");
    goto notfound;
    found :
    if(type==1){
        printf("\nCONNECTE ...");
        sleep(1);
        system("cls");
        
        while(choix!=6){
            printf("----------------MENU ADMIN : Mr %s %s ---------------\n",courant->nom,courant->prenom);
            printf("1-ajouter un livre \n2-ajouter un user \n3-affcher la liste des utilisateurs\n4-afficher liste de livres\n5-supprimer le dernier utilisatuer \n6-deconnexion\n--->");
        scanf("%d",&choix);
        if(choix==1){
            m=ajouter_dans_liste_livres(m);
                printf("livre ajoutee ! \n");
                sleep(2.5);
            system("cls");
        }
        if(choix==2){
            liste=remplire_dans_liste_utilisateur(liste);
            enregistrer_liste_util_dans_fichier_w_mode(liste);
            printf("utilisateur ajoute ");
            system("pause");
            system("cls");
        }
        if(choix==3){
            afficher_liste_util(liste); 
            system("pause");
            system("cls");
        }
        if(choix==4){
            afficher_liste_livres(m);
            system("pause");
            system("cls");
        }
        if(choix==5){
            liste=delete_users_from_head_of_file(liste);
            enregistrer_liste_util_dans_fichier_w_mode(liste);
            printf("dernier utilisateur supprime ");
            sleep(1);
            system("cls");
        }
        // if(choix==6){
        //     printf("donner le nom et le prenom de l'utilisateur a supprimer : ");
        //     scanf("%s",nom);scanf("%s",prenom);
        //     liste=delete_users_by_name_from_file(liste,nom,prenom);
        //     enregistrer_liste_util_dans_fichier_w_mode(liste);
        // }
        
        }
    }
    if(type==2){
        printf("\nCONNECTE ...");
        sleep(1);
        system("cls");
        
        while(choix!=3){
            printf("----------------MENU ETUDIANT : Mr %s %s-----------------\n",courant->nom,courant->prenom);
            printf("1-afficher liste livres\n2-afficher informations \n3-deconnexion\n---->");
        scanf("%d",&choix);
            if(choix==1){
            afficher_liste_livres(m); 
            system("pause");
            system("cls");
        }
        if(choix==2){
            printf("nom : %s\nprenom : %s\ndate de naissance : %s\ncni : %s\npassword : %s\n"
        ,courant->nom
        ,courant->prenom
        ,courant->datedenaissance
        ,courant->login2.CNI
        ,courant->password);
        system("pause");
        system("cls");
        }
        }
    }
}






int main(int argc, char const *argv[])
{
    utilisateur* liste;
    
    livre *livre;
    livre=chargerlivre_de_fichier();
    // strcpy(liste->datedenaissance,"24/7/2003");
    // strcpy(liste->login2.CNI,"FC65138");
    // strcpy(liste->password,"password");
    // strcpy(liste->nom,"darghal");strcpy(liste->prenom,"mohammed");
    // liste->id=CNI;
    // liste->type=ADMINISTRATEUR;
    // liste->suivant=NULL;
    // enregistrer_liste_util_dans_fichier(liste);
    int n,n1=0;
    while(n1!=2){
        printf("1-login\n2-sortir\n---->");
        scanf("%d",&n1);
    if(n1==1){
        login(liste,livre);
        printf("DECONNEXION ...");
        sleep(1);
        system("cls");   
    }
    if(n1==3){
        afficher_liste_util(liste);
        system("pause");
        system("cls");
    }
    
    }
    // enregistrer_liste_util_dans_fichier(liste);
    return 0;
}
