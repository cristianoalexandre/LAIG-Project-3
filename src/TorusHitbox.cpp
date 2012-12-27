#include "TorusHitbox.h"

#include "LineAnimation.h"
#include "PolyLineAnimation.h"

TorusHitbox::TorusHitbox()
{

    ring1 = new Ring();
    ring1->attributeCellIDs();
    ring2 = new Ring();
    ring2->attributeCellIDs();
    ring3 = new Ring();
    ring3->attributeCellIDs();
    ring4 = new Ring();
    ring4->attributeCellIDs();
    ring5 = new Ring();
    ring5->attributeCellIDs();
    ring6 = new Ring();
    ring6->attributeCellIDs();
    ring7 = new Ring();
    ring7->attributeCellIDs();
    ring8 = new Ring();
    ring8->attributeCellIDs();
}

void TorusHitbox::draw()
{

    glPushMatrix();
    glRotatef(-22.5, 0, 0, 1);
    ring1->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring2->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring3->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring4->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring5->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring6->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring7->draw();
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    ring8->draw();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

}