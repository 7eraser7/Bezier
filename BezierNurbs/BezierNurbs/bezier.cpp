#include "bezier.h"

vertex middle(const vertex & p1, const vertex & p2)
{
	return vertex((p1.x + p2.x)/2, (p1.y + p2.y)/2);
}

double distMax(const vector<vertex> & points){

	if(points.size()==0) return 0;

	double distance=0;
	double interD;
	for(unsigned int i=0; i<points.size();i++)
	{
		for(unsigned int j=0; j<i; j++)
		{
			interD=sqrt(pow((points[i].x-points[j].x), 2.0) + pow((points[i].y-points[j].y), 2.0f));
			if(interD>distance) distance=interD;
		}
	}

	return distance;

}

//Routine qui prend en entrée les points de controle et un vecteur d'instant t et qui renvoie
//les points de la courbe de Bézier correspondant aux instants t
vector<vertex> deCastljau(const vector<vertex> & controlPoints, double epsilon){

	double dist=distMax(controlPoints);
	cout << dist << " ";

	if(dist < epsilon)
		return controlPoints;

	vector<vertex> outputPoints;
	vector<vector<vertex>> interPoints;
	interPoints.resize(controlPoints.size());
	

	//Initialisation
	for(unsigned int n=0; n<controlPoints.size(); n++)
	{
		interPoints[n].resize(controlPoints.size());
		interPoints[0][n]=controlPoints[n];
	}

	for(unsigned int i=1; i<controlPoints.size(); i++)
	{
		for(unsigned int j=0; j<controlPoints.size() - i; j++)
		{
			interPoints[i][j] = middle(interPoints[i-1][j], interPoints[i-1][j+1]);
		}
	}

	outputPoints.push_back(interPoints[controlPoints.size()-1][0]);

	vector<vertex> leftPoints(controlPoints.size());
	vector<vertex> rightPoints(controlPoints.size());

	for (unsigned int i=0; i<controlPoints.size(); i++)
	{
		leftPoints[i] = interPoints[i][0];
		rightPoints[i] = interPoints[controlPoints.size()-i-1][i];
	}

	vector<vertex> leftOutput = deCastljau(leftPoints, epsilon);
	vector<vertex> rightOutput = deCastljau(rightPoints, epsilon);

	outputPoints.insert(outputPoints.begin(), leftOutput.begin(), leftOutput.end());
	outputPoints.insert(outputPoints.end(), rightOutput.begin(), rightOutput.end());

	return outputPoints;
}

