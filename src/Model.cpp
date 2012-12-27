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

    glmUnitize(model);
    //glmFacetNormals(model);
    //glmVertexNormals(model, 90.0);
}

void Model::draw()
{
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
}