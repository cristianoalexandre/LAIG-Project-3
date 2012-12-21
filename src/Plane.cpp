#include <GL/glew.h>

#include "Plane.h"
#include "CGFappearance.h"

Plane::Plane(GLint divisions_u, GLint divisions_v)
{
    /** Sets appearance to NULL */
    this->appearance = NULL;

    /** Initialize all the arrays */

    control_points = new vec3[4];
    texture_points = new vec2[4];

    divisions = new GLint[2];

    /** Defines control points */

    control_points[1][0] = 0.5;
    control_points[1][1] = 0;
    control_points[1][2] = 0.5;

    control_points[3][0] = 0.5;
    control_points[3][1] = 0;
    control_points[3][2] = -0.5;

    control_points[0][0] = -0.5;
    control_points[0][1] = 0;
    control_points[0][2] = 0.5;

    control_points[2][0] = -0.5;
    control_points[2][1] = 0;
    control_points[2][2] = -0.5;

    /** Defines texture points */
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
}

void Plane::draw()
{
    /** Applying the appearance */
    if (appearance != NULL)
        appearance->apply();

    GLint cull_face_mode;
    glGetIntegerv(GL_CULL_FACE_MODE, &cull_face_mode);

    if (glIsEnabled(GL_CULL_FACE))
    {
        if (cull_face_mode == GL_FRONT)
            glCullFace(GL_BACK);
        else if (cull_face_mode == GL_BACK)
            glCullFace(GL_FRONT);
        else
            glCullFace(GL_FRONT_AND_BACK);
    }

    /** Declaration of vertex and texture evaluators */
    glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &control_points[0][0]);
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

void Plane::setTexture(CGFappearance * appearance)
{
    this->appearance = appearance;
}

Plane::~Plane()
{
    delete control_points;
    delete texture_points;
    delete divisions;
}