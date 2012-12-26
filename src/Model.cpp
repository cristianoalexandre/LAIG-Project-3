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
    if (!model)
    {
        model = glmReadOBJ((char*) filename.c_str());
    }
    
    if (!model) exit(-1);
    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model,90.0);
}

void Model::draw()
{
    Object::draw();
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
}