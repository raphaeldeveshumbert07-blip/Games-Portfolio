#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

const char** difficult(int niv, int* nbMots) {
    // Listes de mots
    static const char* liste_mot_4[] = {
        "CODE", "BASE", "FLUX", "TEST", "PLAN",
        "NOTE", "PORT", "DATA", "LIEN", "TYPE",
        "CLEF", "RANG", "ZONE", "BYTE", "MODE"
    };

    static const char* liste_mot_5[] = {
        "TABLE", "INDEX", "CHAMP", "ANGLE", "CYCLE",
        "NORME", "CLASSE", "MODULE", "LOGIQUE", "OUTIL",
        "VALEUR", "NIVEAU", "ORDRE", "SIGNAL", "CHAMPS"
    };

    static const char* liste_mot_6[] = {
        "RESEAU", "SCRIPT", "MOTEUR", "PAQUET", "SCHEMA",
        "BUFFER", "CALCUL", "MODULE", "SYSTEM", "FICHIER",
        "LOGIQUE", "SERVEU", "VARIAL", "ANALYSE", "DOSSIER"
    };

    static const char* liste_mot_7[] = {
        "ANALYSE", "MACHINE", "ADRESSE", "STOCKAG", "TERMINAL",
        "FONCTION", "PROTOC", "LOGIQUE", "SERVEUR", "FICHIER",
        "RESEAUX", "CONTROLE", "PROCESS", "DOSSIER", "VARIABLE"
    };

    static const char* liste_mot_8[] = {
        "LOGICIEL", "INTERFACE", "STRUCTURE", "PROCESSUS", "PARAMETRE",
        "CONTROLEUR", "ALGORITHME", "TERMINAL", "UTILISAT", "PROGRAMME",
        "STOCKAGE", "RESEAUX", "VARIABLE", "FONCTION", "COMMANDE"
    };

    static const char* liste_mot_9[] = {
        "ORDINATEUR", "PROGRAMMEUR", "TRAITEMENT", "CONNEXION", "INSTRUCTION",
        "ALGORITHME", "UTILISATEU", "PARAMETRE", "INTERFACE", "DEVELOPPE",
        "PROCESUS", "STRUCTURE", "OPERATION", "APPLICATION", "COMMANDE"
    };

    const char** mots = NULL;

    switch (niv) {
        case 1:
            mots = liste_mot_4;
            *nbMots = sizeof(liste_mot_4) / sizeof(liste_mot_4[0]);
            break;
        case 2:
            mots = liste_mot_5;
            *nbMots = sizeof(liste_mot_5) / sizeof(liste_mot_5[0]);
            break;
        case 3:
            mots = liste_mot_6;
            *nbMots = sizeof(liste_mot_6) / sizeof(liste_mot_6[0]);
            break;
        case 4:
            mots = liste_mot_7;
            *nbMots = sizeof(liste_mot_7) / sizeof(liste_mot_7[0]);
            break;
        case 5:
            mots = liste_mot_8;
            *nbMots = sizeof(liste_mot_8) / sizeof(liste_mot_8[0]);
            break;
        case 6:
            mots = liste_mot_9;
            *nbMots = sizeof(liste_mot_9) / sizeof(liste_mot_9[0]);
            break;
        default:
            *nbMots = 0;
            break;
    }

    return mots;
}

void jeux(const char* motSecret) {
    printf("Le mot contient %lu lettres.\n", strlen(motSecret));
    int essaisRestants = 8;
    char lettresEssayees[50] = "";
    char motAffiche[50];

// Initialiser le mot affiché avec des '_'
    for (int i = 0; i < strlen(motSecret); i++) {
        motAffiche[i] = '_';
    }
    motAffiche[strlen(motSecret)] = '\0';

    while (essaisRestants > 0) {

        printf("\nMot : ");

        for (int i = 0; i < strlen(motSecret); i++) {
            printf("%c ", motAffiche[i]);
        }
        printf("\n");
        printf("Lettres essayées : ");
        for (int i = 0; i < strlen(lettresEssayees); i++) {
            printf("%c ", lettresEssayees[i]);
        }
        printf("\n");

        printf("Essais restants : %d\n", essaisRestants);

    // Demander une lettre
        char lettre;
        printf("Proposez une lettre (En Majuscule): ");
        scanf(" %c", &lettre);

    // Vérifier si déjà essayée
        if (strchr(lettresEssayees, lettre) != NULL) {
            printf("Vous avez déjà essayé cette lettre.\n");
            continue;
        }

    // Ajouter à la liste des lettres essayées
        int len = strlen(lettresEssayees);
        lettresEssayees[len] = lettre;
        lettresEssayees[len + 1] = '\0';

    // Vérifier si la lettre est dans le mot
        int bonneLettre = 0;
        for (int i = 0; i < strlen(motSecret); i++) {
            if (motSecret[i] == lettre) {
                motAffiche[i] = lettre;
                bonneLettre = 1;
            }
        }

        if (!bonneLettre) {
            essaisRestants--;
            printf("Raté ! La lettre '%c' n'est pas dans le mot.\n", lettre);
        } else {
            printf("Bien joué !\n");
        }

    // Vérifier si gagné
        if (strcmp(motAffiche, motSecret) == 0) {
            printf("\nBravo ! Vous avez trouvé le mot : %s\n", motSecret);
            break;
        }
    }
    if(essaisRestants == 0) {
        printf("\nVous avez perdu ! Le mot était : %s\n", motSecret);
    }
};

int main() {
    int niv;
    int choix;

    printf("1 - Jouer\n");
    printf("2 - Regles\n");
    printf("3 - Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    int nbMots = 0;

    switch (choix) {
        case 1: {
            printf("Difficulté du mot : 1, 2, 3, 4, 5 ou 6 ? : ");
            scanf("%d", &niv);
            const char** mots = difficult(niv, &nbMots);
            if (mots == NULL || nbMots == 0) {
                printf("Niveau invalide.\n");
                return 1;
            }

            srand(time(NULL));
            int index = rand() % nbMots;
            const char* motSecret = mots[index];
            jeux(motSecret);
            break;
        }

        case 2:
            printf("Voici les règles du jeu :\n");
            printf("Le but est de trouver le mot de l'ordinateur. Le mot caché est représenté par des tirets. A vous de proposez une lettre, si celle-ci se trouve dans le mot, le tirets a l'emplacement de cet lettre disparait et laisse entrevoir celle-ci. Une fois le mot trouver au complet, vous avez gagné ! Vous n'avez que 8 tentatives. Bonne chance !");
            break;

        case 3:
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide.\n");
            break;
    }

    return 0;
}


