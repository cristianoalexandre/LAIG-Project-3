#include "Torus.h"


void aux_drawTorus(double smallrad,double bigrad,int smallsubdivs,int bigsubdivs,int tanloc);

Torus::Torus(){

}

Torus::~Torus(){
}

Torus::Torus(float iRadius, float oRadius, int slcs, int loops){

	this->innerRadius = iRadius;
	this->outerRadius = oRadius;
	this->slices = slcs;
	this->loops = loops;

}

void Torus::setInnerRadius(float irad){this->innerRadius = irad;}
void Torus::setOuterRadius(float oRad){this->outerRadius = oRad;}
void Torus::setSlices(int slcs){this->slices = slcs;}
void Torus::setLoops(int loop){this->loops = loop;}

void Torus::draw(){

	this->getTexture()->apply();
	aux_drawTorus(this->innerRadius, this->outerRadius, this->slices, this->loops, -1);

}

void aux_drawTorus(double smallrad,double bigrad,int smallsubdivs,int bigsubdivs,int tanloc)
{
    const double pi = 3.1415926535898;
    for (int i1 = 0; i1 < bigsubdivs; ++i1)
    {
        double t1a = double(i1)/bigsubdivs;
        double a1a = t1a * 2.0*pi;
        double t1b = double(i1+1)/bigsubdivs;
        double a1b = t1b * 2.0*pi;
        glBegin(GL_QUAD_STRIP);
        for (int i2 = 0; i2 <= smallsubdivs; ++i2)
        {
            double t2 = double(i2)/smallsubdivs;
            double a2 = t2 * 2.0*pi;

            double nax = cosl(a2)*cosl(a1a);
            double nay = cosl(a2)*sinl(a1a);
            double naz = sinl(a2);
            double pax = (bigrad + smallrad * cosl(a2))*cosl(a1a);
            double pay = (bigrad + smallrad * cosl(a2))*sinl(a1a);
            double paz = smallrad * sinl(a2);
            glNormal3d(nax, nay, naz);
          /*  if (tanloc != -1)
                glVertexAttrib3dARB(tanloc, -sin(a1a), cos(a1a), 0.);*/
            glTexCoord2d(t1a, t2);
            glVertex3d(pax, pay, paz);

            double nbx = cosl(a2)*cosl(a1b);
            double nby = cosl(a2)*sinl(a1b);
            double nbz = sinl(a2);
            double pbx = (bigrad + smallrad * cosl(a2))*cosl(a1b);
            double pby = (bigrad + smallrad * cosl(a2))*sinl(a1b);
            double pbz = smallrad * sinl(a2);
            glNormal3d(nbx, nby, nbz);
            /*if (tanloc != -1)
                glVertexAttrib3dARB(tanloc, -sin(a1b), cos(a1b), 0.);*/
            glTexCoord2d(t1b, t2);
            glVertex3d(pbx, pby, pbz);
        }
        glEnd();
    }
}

