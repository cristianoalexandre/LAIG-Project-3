#ifndef MODEL_H
#define	MODEL_H

#include <string>

#include "Object.h"
#include "glm.h"

using namespace std;

class Model : public Object
{
private:
    GLMmodel* model;
	double height;
    
public:    
    Model();
    Model(string filename);
    ~Model();
    
	double getHeight();
    void loadOBJ(string filename);
    void draw();
};

#endif	/* MODEL_H */

