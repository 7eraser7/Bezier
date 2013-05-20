
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "vertex.h"
#include "bezier.h"

using namespace std;

vector<vertex> controlPoints;
vector<vertex> bezierPoints;

vertex * selectedControlPoint;

int windowHeight;
int windowWidth;

double maxDistance;

bool shouldShowEdges;
bool shouldShowPoints;

bool shouldShowBezierCurve;

bool hasSelectedVertex;

void drawPoint(const vertex & v){
	glBegin(GL_POINT);
	glVertex2i(v.x, v.y);
	glEnd();
}

void drawPoints(const vector<vertex> & points, float r, float g, float b){
	if (points.size() < 1)
		return;

	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glPointSize(100.0f);
	for (unsigned int i=0; i<points.size(); i++){
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();
}

void drawSegments(const vector<vertex> & points, float r, float g, float b){
	if (points.size() < 2)
		return;

	glBegin(GL_LINES);
	glColor3f(r, g, b);
	for (unsigned int i = 1; i<points.size(); i++){
		glVertex2i(points[i-1].x, points[i-1].y);
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();
}

void resetContext(){
	shouldShowPoints = true;
	shouldShowEdges = false;
	shouldShowBezierCurve = false;

	controlPoints = vector<vertex>();
}

vertex * getSelectedControlPoint(int x, int y){
	int xMin = x - 5;
	int xMax = x + 5;
	int yMin = y - 5;
	int yMax = y + 5;

	for (unsigned int i=0; i<controlPoints.size(); i++){
		vertex & v = controlPoints[i];
		if (v.x < xMax && v.x > xMin && v.y < yMax && v.y > yMin)
			return &v;
	}

	return NULL;
}

void affichage(){

	glClear(GL_COLOR_BUFFER_BIT);

	if (shouldShowPoints)
		drawPoints(controlPoints, 1.0f, 0.0f, 0.0f);

	if (shouldShowEdges)
		drawSegments(controlPoints, 0.0f, 1.0f, 0.0f);

	if (shouldShowBezierCurve){
		bezierPoints = deCastljau(controlPoints, maxDistance);
		drawSegments(bezierPoints, 0.0f, 0.0f, 1.0f);
	}

	// On force l'affichage du résultat
	glFlush();
}

void mouse(int button,int state,int x,int y)
{
	// Si on appuie sur le bouton gauche
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		controlPoints.push_back(vertex(x, windowWidth - y));

		affichage();
	}

	// Si on appuie sur le bouton droit
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (selectedControlPoint == NULL)
			selectedControlPoint = getSelectedControlPoint(x, windowWidth - y);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		if (selectedControlPoint != NULL){
			selectedControlPoint->x = x;
			selectedControlPoint->y = windowWidth - y;
			affichage();
		}
		selectedControlPoint = NULL;
	}
}

/* Evènement du clavier */
void clavier(unsigned char touche,int x,int y){
	vector<vertex> bezierPoints;
	switch (touche){
	case 's':
		shouldShowEdges = !shouldShowEdges;
		affichage();
		break;
	case 'p':
		shouldShowPoints = !shouldShowPoints;
		affichage();
		break;
	case 'b':
		shouldShowBezierCurve = !shouldShowBezierCurve;
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
	cout<<"Appuyez sur 'P' pour montrer/cacher les points"<<endl;
	cout<<"Appuyez sur 'R' pour reinitialiser"<<endl;
	cout<<"Appuyez sur 'Q' pour quitter"<<endl;
}

// Main :

int main(int argc, char **argv){
	windowHeight = 800;
	windowWidth = 600;

	maxDistance = 100;

	selectedControlPoint = NULL;

	hasSelectedVertex = false;

	shouldShowEdges = false;
	shouldShowPoints = true;
	shouldShowBezierCurve = false;

	controlPoints = vector<vertex>();

	afficherInformations();

	/* Initialisation de glut et creation de la fenetre */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(windowHeight, windowWidth);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Courbes de Bezier");

	/* Repère 2D délimitant les abscisses et les ordonnées*/
	gluOrtho2D(0, windowHeight, 0, windowWidth);

	/* Initialisation d'OpenGL */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(2.0f);

	/* Enregistrement des fonctions de rappel */
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	glutMouseFunc(mouse);

	/* Entrée dans la boucle principale de glut */
	glutMainLoop();
	return 0;
}