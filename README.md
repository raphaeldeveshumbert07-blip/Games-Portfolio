# Jeu de Remplissage de Couleur (Flood Fill Game)

Un mini-jeu développé en Python avec Pygame, basé sur le principe du Flood Fill. Le joueur doit remplir toute la grille avec une seule couleur en un nombre limité de clics.

## Fonctionnement
- Une grille de couleurs aléatoires est générée.
- Le joueur clique sur une case pour changer la couleur du coin supérieur gauche.
- Le changement se propage récursivement aux cases adjacentes de même couleur.
- L'objectif est d'uniformiser toute la grille avant d'épuiser les clics disponibles.

## Fonctionnalités
- Génération aléatoire d'une grille colorée
- Algorithme de flood fill récursif
- 3 niveaux de difficulté : Easy, Medium, Hard
- Affichage du nombre de clics restants
- Détection automatique de victoire ou défaite

## Installation
1. Installer Pygame : pip install pygame
2. Cloner le projet : git clone <url>
3. Lancer le script : python main.py

## Structure du projet
main.py et 
README.txt

## Licence
Projet libre d'utilisation.
