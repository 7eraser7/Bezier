
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "vertex.h"

using namespace std;

vector<vertex> bezierControlPoints;

int windowHeight;
int windowWidth;

bool shouldShowEdges;

void drawPoint(const vertex & v){
	glBegin(GL_POINT);
	glVertex2i(v.x, v.y);
	glEnd();
}

void drawPoints(const vector<vertex> & points){
	if (points.size() < 1)
		return;

	glBegin(GL_POINTS);
	glPointSize(5.0f);
	for (unsigned int i=0; i<points.size(); i++){
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();
}

void drawSegments(const vector<vertex> & points){
	if (points.size() < 2)
		return;

	glBegin(GL_LINES);
	for (unsigned int i = 1; i<points.size(); i++){
		glVertex2i(points[i-1].x, points[i-1].y);
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();
}

void resetContext(){
	bezierControlPoints = vector<vertex>();
}

void affichage(){

    glClear(GL_COLOR_BUFFER_BIT);

	drawPoints(bezierControlPoints);

	if (shouldShowEdges)
		drawSegments(bezierControlPoints);

    // On force l'affichage du r�sultat
    glFlush();
}

void mouse(int button,int state,int x,int y)
{
    // Si on appuie sur le bouton de gauche
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
		bezierControlPoints.push_back(vertex(x, windowWidth - y));

        affichage();
    }

}

/* Ev�nement du clavier */
void clavier(unsigned char touche,int x,int y){
    switch (touche){
	case 's':
		shouldShowEdges = !shouldShowEdges;
		affichage();
		break;
	case 'r':
		resetContext();
		affichage();
		break;
    case 'q':/* Quitter le programme */
        exit(0);
    }
}

void afficherInformations(){
    cout<<"\n\n\n\n\n";
    cout<<"Liste des commandes :"<<endl;
    cout<<"Creez des vertex avec le clique gauche"<<endl;
	cout<<"Appuyez sur 'S' pour montrer/cacher les segments"<<endl;
    cout<<"Appuyez sur 'R' pour reinitialiser"<<endl;
	cout<<"Appuyez sur 'Q' pour quitter"<<endl;
}

// Main :

int main(int argc, char **argv){
	windowHeight = 800;
	windowWidth = 600;

	shouldShowEdges = false;

	bezierControlPoints = vector<vertex>();

    afficherInformations();

    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(windowHeight, windowWidth);
    glutInitWindowPosition (0, 0);
    glutCreateWindow("Courbes de Bezier");

    /* Rep�re 2D d�limitant les abscisses et les ordonn�es*/
    gluOrtho2D(0, windowHeight, 0, windowWidth);

    /* Initialisation d'OpenGL */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);

    /* Enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutMouseFunc(mouse);

    /* Entr�e dans la boucle principale de glut */
    glutMainLoop();
    return 0;
}