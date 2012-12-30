#include "Model.h"

Model::Model()
{
	model = NULL;
}

Model::Model(string filename)
{
	this->loadOBJ(filename);
}

Model::~Model()
{
	delete model;
}

void Model::loadOBJ(string filename)
{
	model = (GLMmodel*) malloc(sizeof (GLMmodel));
	model = glmReadOBJ((char*) filename.c_str());

	GLfloat dimensions[3];
	glmUnitize(model);
	glmDimensions(model, dimensions);

	this->height = (double) dimensions[2];
	//glmFacetNormals(model);
	//glmVertexNormals(model, 90.0);
}

void Model::draw()
{
	glPushMatrix();
		glScalef(4,4,4);
		glTranslated(0,this->height,0);
		glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}