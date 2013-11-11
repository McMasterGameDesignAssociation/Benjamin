#ifndef _RENDERER_METHODS
#define _RENDERER_METHODS

#include "RENDERER.h"

renderer::~renderer(void)
{
	delete[] vertices;
	delete[] colors;
	tempColors.clear();
	tempVertices.clear();
}

void renderer::clearArrays(void)
{
	delete[] vertices;
	delete[] colors;
	buildOk = true;
}

renderer::renderer(void)
{
	vertices = new int[0];
	colors = new double[0];
	tempVertices.clear();
	tempColors.clear();
	buildOk = true;
}

void renderer::buildArrays(void)
{
	if(!tempVertices.empty())
	{
		clearArrays();
		vertices = new int[tempVertices.size()*2];
		colors = new double[tempColors.size()*3];
		for(int i = 0; i < tempVertices.size(); i++)
		{
			vertices[i*2] = tempVertices.at(i)[0];
			vertices[i*2 + 1] = tempVertices.at(i)[1];
			colors[i*3] = tempColors.at(i)[0];
			colors[i*3 + 1] = tempColors.at(i)[1];
			colors[i*3 + 2] = tempColors.at(i)[2];
			//cout << "X Pos " <<  vertices[i] << endl;
		}
		buildOk = false;
	}
	else;
}

void renderer::addPoint(int point[2]) 
{
	buildOk = true;
	int* newPoint;
	newPoint = new int[2];
	newPoint[0] = point[0], newPoint[1] = point[1];
	tempVertices.push_back(newPoint);
}

void renderer::addColor(int color[3]) 
{
	buildOk = true;
	double* newColor;
	newColor = new double[2];
	newColor[0] = color[0], newColor[1] = color[1], newColor[2] = color[2];
	tempColors.push_back(newColor);
}

void renderer::addTile(int center[2], int color[3], int size)
{
	for(int i = 0; i < 6; i++) addColor(color);
	int * point;
	point = new int[2];
	point[0] = center[0] - size/2;
	point[1] = center[1] - size/2;
	addPoint(point);
	point[0] = center[0] + size/2;
	point[1] = center[1] - size/2;
	addPoint(point);
	point[0] = center[0] - size/2;
	point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] - size/2;
	point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] + size/2;
	point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] + size/2;
	point[1] = center[1] - size/2;
	addPoint(point);

}

void renderer::render(void)
{
	if(buildOk)
	{
		buildArrays();
		buildOk = false;
		cout << "built " << tempVertices.size() << endl;
	}
	else
	{
		glVertexPointer(2, GL_INT, 0, vertices);
		glColorPointer(3, GL_DOUBLE, 0, colors);
		glDrawArrays(GL_TRIANGLES, 0, tempVertices.size());
	}
}

void renderer::printPoint(int pos)
{
	if(pos < tempVertices.size()) cout << tempVertices.at(pos)[0] << " x pos" 
		<< endl << tempVertices.at(pos)[1] << " y pos" << endl;
	else cout << "no point found" << endl;
}

void renderer::worldToArray(world gameSpace, int resolution)
{
	unsigned int pos[2];
	double color[3];
	int location[2];
	for(int i = 0; i < gameSpace.getY(); i++)
	{
		pos[1] = i;
		for(int j = 0; j < gameSpace.getX(); j++)
		{
			pos[0] = j;
			int * color = new int[3];
			if(gameSpace.getTileCollision(gameSpace.checkTileMap(pos))) color[0] = 1, color[1] = 1, color[2] = 1;
			else color[0] = 1, color[1] = 0, color[2] = 0;
			location[0] = j*resolution, location[1] = i*resolution;
			addTile(location, color, resolution);

		}
	}
}

#endif