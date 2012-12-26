#include "Patch.h"

Patch::Patch()
{

}

Patch::Patch(int order_u, int order_v, int divisions_u, int divisions_v, GLfloat control_points[][3], int lin, int col)
{
    /** Sets appearance to NULL */
   // this->appearance = NULL;
	setTexture(NULL);
    /** Allocates memory for all the arrays */
    int size_of_array_u = 0;
    int size_of_array_v = 0;

    this->order_u = order_u;
    this->order_v = order_v;

    switch (this->order_u)
    {
    case 1:
        size_of_array_u = 2;
        break;
    case 2:
        size_of_array_u = 3;
        break;
    case 3:
        size_of_array_u = 4;
        break;
    default:
        cerr << "Invalid order_u in patch creation!";
        exit(-1);
    }

    switch (this->order_v)
    {
    case 1:
        size_of_array_v = 2;
        break;
    case 2:
        size_of_array_v = 3;
        break;
    case 3:
        size_of_array_v = 4;
        break;
    default:
        cerr << "Invalid order_v in patch creation!";
        exit(-1);
    }

    int total_array_size = size_of_array_u * size_of_array_v;

    if (lin != total_array_size && col != 3)
    {
        cerr << "Invalid control_points for patch!";
        exit(-1);
    }

    this->control_points = new vec3[total_array_size];
    texture_points = new vec2[4];
    divisions = new int[2];

    /** Defines the control points */
    for (int i = 0; i < lin; i++)
    {
        for (int k = 0; k < col; k++)
        {
            this->control_points[i][k] = control_points[i][k];
        }
    }

    /** Defines the texture points */
    texture_points[1][0] = 0;
    texture_points[1][1] = 0;

    texture_points[0][0] = 0;
    texture_points[0][1] = 1;

    texture_points[3][0] = 1;
    texture_points[3][1] = 0;

    texture_points[2][0] = 1;
    texture_points[2][1] = 1;

    /** Defines number of divisions */
    divisions[0] = divisions_u;
    divisions[1] = divisions_v;

    /** Calculates strive */
    this->stride_u = 3;
    this->stride_v = (order_v + 1)*3;
}

void Patch::draw()
{
    /** Applies the appearance */
	if (getTexture() != NULL)
		getTexture()->apply();

    GLint cull_face_mode;
    glGetIntegerv(GL_CULL_FACE_MODE, &cull_face_mode);

    if (glIsEnabled(GL_CULL_FACE))
        if (cull_face_mode == GL_FRONT)
            glCullFace(GL_BACK);
        else if (cull_face_mode == GL_BACK)
            glCullFace(GL_FRONT);
        else
            glCullFace(GL_FRONT_AND_BACK);

    /** Declarates of vertex and texture evaluators */
    glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, stride_u, order_u + 1, 0.0, 1.0, stride_v, order_v + 1, &control_points[0][0]);
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texture_points[0][0]);

    /** Enables automatic calculation of normals */
    glEnable(GL_MAP2_NORMAL);
    glEnable(GL_AUTO_NORMAL);

    /** Enables the vertex and texture evaluators */
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_TEXTURE_COORD_2);

    /** Defines the number of divisions of the grid */
    glMapGrid2f(divisions[0], 0.0, 1.0, divisions[1], 0.0, 1.0);

    /** Draw the whole thing */
    glEvalMesh2(GL_FILL, 0, divisions[0], 0, divisions[1]);

    if (glIsEnabled(GL_CULL_FACE))
        glCullFace(cull_face_mode);
}

Patch::~Patch()
{
    delete control_points;
    delete texture_points;
    delete divisions;
}