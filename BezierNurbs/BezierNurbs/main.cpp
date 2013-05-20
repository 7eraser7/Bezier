
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "vertex.h"

using namespace std;

void affichage(){

    glClear(GL_COLOR_BUFFER_BIT);

    // On force l'affichage du résultat
    glFlush();
}

void mouse(int button,int state,int x,int y)
{
    // Si on appuie sur le bouton de gauche
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        affichage();
    }

}

/* Evènement du clavier */
void clavier(unsigned char touche,int x,int y){
    switch (touche){
    case 'q':/* Quitter le programme */
        exit(0);
    }
}

void afficherInformations(){
    cout<<"\n\n\n\n\n";
    cout<<"Liste des commandes :"<<endl;
    cout<<"Creez des vertex avec le clique gauche"<<endl;
    cout<<"Appuyez sur 'R' pour reinitialiser"<<endl;
	cout<<"Appuyez sur 'Q' pour quitter"<<endl;
}

// Main :

int main(int argc, char **argv){

	vector<vertex> bezierControlPoints = vector<vertex>();

    afficherInformations();

    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Courbes de Bezier");

    /* Repère 2D délimitant les abscisses et les ordonnées*/
    gluOrtho2D(-250.0,250.0,-250.0,250.0);

    /* Initialisation d'OpenGL */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0);

    /* Enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutMouseFunc(mouse);

    /* Entrée dans la boucle principale de glut */
    glutMainLoop();
    return 0;
}