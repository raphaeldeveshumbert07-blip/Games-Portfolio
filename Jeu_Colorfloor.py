import pygame
import random
import sys

# Constantes
TAILLE_CASE = 40
COULEURS = [(240, 226, 195), (220, 236, 233), (242, 234, 224), (246, 199, 179), (195, 222, 221), (130, 178, 192)]
TAILLE_POLICE = TAILLE_CASE//2

def generer_grille(largeur, hauteur):
    """
    Génère une grille de couleurs aléatoires.

    Args:
        largeur (int): La largeur de la grille en nombre de cases.
        hauteur (int): La hauteur de la grille en nombre de cases.

    Returns:
        list: Une liste de listes représentant la grille de couleurs.
    """
    grille = [[random.choice(COULEURS) for _ in range(hauteur)] for _ in range(largeur)]
    return grille

def dessiner_grille(grille, affichage):
    """
    Dessine la grille sur l'affichage.

    Args:
        grille (list): Une liste de listes représentant la grille de couleurs.
        affichage (pygame.Surface): La surface sur laquelle dessiner la grille.
    """
    for x, ligne in enumerate(grille):
        for y, couleur in enumerate(ligne):
            pygame.draw.rect(affichage, couleur, (x * TAILLE_CASE, y * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE))

def remplir_case(grille, x, y, ancienne_couleur, nouvelle_couleur):
    """
    Remplit une case et ses voisins avec une nouvelle couleur récursivement.

    Args:
        grille (list): Une liste de listes représentant la grille de couleurs.
        x (int): La coordonnée x de la case à remplir.
        y (int): La coordonnée y de la case à remplir.
        ancienne_couleur: La couleur de la case à remplir.
        nouvelle_couleur: La nouvelle couleur à appliquer à la case et ses voisins.
    """
    if x < 0 or x >= len(grille) or y < 0 or y >= len(grille[0]) or grille[x][y] != ancienne_couleur:
        return None

    grille[x][y] = nouvelle_couleur
    #Appelle récursivement chacun des voisins pour savoir si ils sont de la même couleurs que notre case de départ et ainsi s'y accrocher
    remplir_case(grille, x + 1, y, ancienne_couleur, nouvelle_couleur)
    remplir_case(grille, x - 1, y, ancienne_couleur, nouvelle_couleur)
    remplir_case(grille, x, y + 1, ancienne_couleur, nouvelle_couleur)
    remplir_case(grille, x, y - 1, ancienne_couleur, nouvelle_couleur)

def grille_complete(grille):
    """
    Vérifie si l'utilisateur a complété entierement la grille d'une seule couleurs.
    
    Args:
        grille (list): Une liste de listes représentant la grille de couleurs.
    """
    couleur_ref = grille[0][0]
    for ligne in grille:
        for case in ligne:
            if case != couleur_ref:
                return False
    return True

def main():
    """
    Fonction principale du jeu.
    """
    pygame.init()
    affichage = pygame.display.set_mode((LARGEUR_FENETRE, HAUTEUR_FENETRE))
    pygame.display.set_caption("Jeu de remplissage de couleur")
    horloge = pygame.time.Clock()

    grille = generer_grille(LARGEUR_FENETRE // TAILLE_CASE, HAUTEUR_FENETRE // TAILLE_CASE)

    nb_clics = clic_max  # Initialise le compteur de clics de souris
    police = pygame.font.Font(None, TAILLE_POLICE) # Sélectionne la font par défaut
    text = police.render(str(nb_clics), 1, (0,0,0)) #Couleur du décompte


    while True:
        affichage.fill((255, 255, 255))  # Remplit l'écran avec une couleur blanche
        dessiner_grille(grille, affichage)  # Dessine la grille sur l'affichage
        affichage.blit(text, (LARGEUR_FENETRE - TAILLE_CASE//2, HAUTEUR_FENETRE - TAILLE_POLICE))
        pygame.display.flip()  # Met à jour l'affichage

        for event in pygame.event.get():
            if event.type == pygame.QUIT: #Ferme proprement le jeu si l'utilisateur ferme la fenêtre pygame
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                case_x, case_y = x // TAILLE_CASE, y // TAILLE_CASE  # Calcule les coordonnées de la case cliquée
                ancienne_couleur = grille[0][0]
                nouvelle_couleur = grille[case_x][case_y]
                if ancienne_couleur != nouvelle_couleur:
                    remplir_case(grille, 0, 0, ancienne_couleur, nouvelle_couleur)  # Remplit la case et ses voisins avec une nouvelle couleur
                    nb_clics -= 1  # Incrémente le compteur de clics de souris
        if nb_clics >= 0 :
            text = police.render(str(nb_clics), 1, (0,0,0))
        else :
            text = police.render(str(nb_clics), 1, (220,0,0))

        if grille_complete(grille):
            if nb_clics < 0 :
                print("Dommage tu as perdu, tu as fais", -nb_clics + clic_max ,"clics soit plus de", clic_max,"clics ... Recommence !")
            else :
                print("Bravo ! Vous avez rempli toute la grille en", clic_max - nb_clics, "clics.")
            pygame.quit()
            sys.exit()

        horloge.tick(30)  # Limite le nombre de boucles par seconde


if __name__ == "__main__": #Execution
    while True:
        print("Quelle difficulté voulez-vous ?")
        print("1 - Easy")
        print("2 - Medium")
        print("3 - Hard")
        niv = input("1, 2 ou 3 : ")
        if niv in ("1", "2", "3"):
            niv = int(niv)
            break
        else :
            print("Erreur : tapez seulement 1, 2 ou 3.\n")
    if niv == 1 : 
        LARGEUR_FENETRE = 200 
        HAUTEUR_FENETRE = 200 
        clic_max = 10
    elif niv == 2 : 
        LARGEUR_FENETRE = 400 
        HAUTEUR_FENETRE = 400 
        clic_max = 20
    else : 
        LARGEUR_FENETRE = 800 
        HAUTEUR_FENETRE = 800
        clic_max = 35
    main() 


    