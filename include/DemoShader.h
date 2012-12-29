#ifndef DEMOSHADER_H
#define	DEMOSHADER_H

#include "CGFshader.h"
#include "CGFtexture.h"

class DemoShader : public CGFshader
{
public:
    DemoShader();
    virtual void bind(void);
    ~DemoShader(void);
    DemoShader(char* vert, char* frag);
    void setScale(float s);
    void setBaseTexture(char* path);
    float normScale;
    int wireframe;

protected:
    CGFtexture * baseTexture;
    CGFtexture * secTexture;

    GLint baseImageLoc;
    GLint secImageLoc;

    GLint scaleLoc;
};

#endif	/* DEMOSHADER_H */

