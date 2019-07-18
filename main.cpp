#ifdef __APPLE__
#else
#endif

#include <stdlib.h>
#include "windows.h"
#include "GL/glut.h"
#include "stdio.h"
#include "math.h"
#define checkImageWidth 64
#define checkImageHeight 64

#include <iostream>
using namespace std;

    float R_Z=0.0f, R_X=0.0f, R_Y=0.0f;
    float T_Z=-16.0f, T_X=0.0f, T_Y=0.0f;
    float view_rotx = 0.0f, view_roty = 0.0f;
    int oldMouseX, oldMouseY;

    float Cx = 1, Cy = 1.10, Cz = 0.5;
    float Lx = 1, Ly = 1, Lz = 0;
    float Tx = 0, Ty = 1, Tz = 0;

    float sudut_x = 0.0f, sudut_y = 0.0f, sudut_z = 0.0f;
    float sudut_x2 = 0.0f, sudut_y2 = 0.0f, sudut_z2 = 0.0f;

    float angle_depanBelakang = 0.0f;
    float angle_depanBelakang2 = 0.0f;
    float angle_samping = 0.0f;
    float angle_samping2 = 0.0f;
    float angle_vertikal = 0.0f;
    float angle_vertikal2 = 0.0f;

    float linear[] = {0.0f, 0.0f, -1.0f};
    float lateral[] = {-1.0f, 0.0f, 0.0f};
    float vertical[] = {0.0f, 1.0f, 0.0f};

    float col1=0.0;
    float col2=0.0;
    float col3=0.0;

    float toRadians(float angle){
        return angle * M_PI / 180;
    }

    class Vector{
        public: float x, y, z;

        void set_values (float startX, float startY, float startZ){
            x = startX;
            y = startY;
            z = startZ;
        }

        void vectorRotation(Vector refs, float angle){
            Vector temp = refs;
            float magnitude = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
            temp.x = temp.x / magnitude;
            temp.y = temp.y / magnitude;
            temp.z = temp.z / magnitude;
            float dot_product = (x * temp.x)+(y * temp.y)+(z * temp.z);
            float cross_product_x = (y * temp.z) - (temp.z * z);
            float cross_product_y = -((x * temp.z) - (z * temp.x));
            float cross_product_z = (x * temp.y) - (y * temp.x);
            float last_factor_rodrigues = 1.0f - cos(toRadians(fmod(angle, 360.0f)));
            x = (x * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_x * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * x);
            y = (y * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_y * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * y);
            z = (z * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_z * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * z);
        }
    };
    Vector depanBelakang, samping, vertikal;

    void initGL(){
        depanBelakang.set_values(0.0f, 0.0f, -1.0f);
        samping.set_values(1.0f, 0.0f, 0.0f);
        vertikal.set_values(0.0f, 0.0f, 0.0f);
        float ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float position[] = {1.0f, 1.0f, 1.0f, 0.0f};
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glShadeModel(GL_SMOOTH);
    }
    void tabung(float r, float t) {
        float BODY_LENGTH = t;
        float BODY_RADIUS = r;
        int SLICES = 72;
        int STACKS = 72;
        GLUquadric *q = gluNewQuadric();
        gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
        glTranslatef(0.0f, 0.0f, BODY_LENGTH);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);

    }
    void wiCas(float r, float t) {
        float amb[] = {0.0f, 0.0f, 1.0f, 1.0f };
        float diff[] = {0.0f, 1.0f, 1.0f, 0.5f };
        float spec[] = {1.0f, 0.0f, 1.0f, 0.5f };
        float shine = 0.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        float BODY_LENGTH = t;
        float BODY_RADIUS = r;
        int SLICES = 72;
        int STACKS = 72;
        GLUquadric *q = gluNewQuadric();
        gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
        glTranslatef(0.0f, 0.0f, BODY_LENGTH);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);

    }
    void sudut() {
        float BODY_LENGTH = 0.7f;
        float BODY_RADIUS = 0.3f;
        int SLICES = 30;
        int STACKS = 30;
        glRotatef(180, 180, 0, 0);
        GLUquadric *q= gluNewQuadric();
        gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
        glTranslatef(0.0f, 0.0f, BODY_LENGTH);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
    }
void slotsim(){
        float amb[] = {0.0f, 0.0f, 1.0f, 1.0f };
        float diff[] = {0.0f, 1.0f, 1.0f, 0.5f };
        float spec[] = {1.0f, 0.0f, 1.0f, 0.5f };
        float shine = 0.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

        glPushMatrix();
        glTranslated(-5,4.9,0);
        glScaled(0.1,1.8,0.1);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-3.9,5.5,0);
        glScaled(2.1,0.1,0.1);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-2.8,5.1,0);
        glScaled(0.1,0.9,0.1);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();

        glTranslated(-3,4.5,0);
        glRotatef(-45, 0, 0, 5);
        glScaled(0.1,0.6,0.1);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-4.1,4.3,0);
        glScaled(1.8,0.1,0.1);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-4,4.9,0);
        glScaled(0.1,1.2,0.1);
        glutSolidCube(1.0);
        glPopMatrix();


        float amb1[] = {0.0f, 0.0f, 0.0f, 0.5f };
        float diff1[] = {0.0f, 0.0f, 0.0f, 0.5f };
        float spec1[] = {0.0f, 0.0f, 0.0f, 0.5f };
        float shine1 = 1.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec1);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine1);
        glPushMatrix();
        glTranslated(-5.1,4.9,0);
        glScaled(0.1,2,0.2);
        glutSolidCube(1.0);
        glPopMatrix();

    }
    void layar(float col1, float col2, float col3){

        float amb[] = {col1 - 0.2f, col2 - 0.2f, col3 - 0.2f, 0.5f };
        float diff[] = {col1 - 0.1f, col2 - 0.1f, col3 - 0.1f, 0.5f };
        float spec[] = {col1, col2, col3, 0.5f };
        float shine = 1.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

        glPushMatrix();
        glTranslated(0.0,0.0,0.0);
        glScaled(4.3,8.2,0.1);
        glutSolidCube(1.0);
        glPopMatrix();
    }
 void kamera(){

        glPushMatrix();
        glTranslated(1.2,5,0);
        glScaled(0.7,1.4,0.2);
        glutSolidCube(1.0);
        glPopMatrix();
        float amb[] = {0.0f, 0.0f, 1.0f, 1.0f };
        float diff[] = {0.0f, 1.0f, 1.0f, 0.5f };
        float spec[] = {1.0f, 0.0f, 1.0f, 0.5f };
        float shine = 0.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        glPushMatrix();
            glTranslated(1.2,5.3,0.1);
            float BODY_LENGTH9 = 0.1f;
            float BODY_RADIUS9 = 0.3f;
            int SLICES9 = 30;
            int STACKS9 = 30;
            glRotatef(0, 60, 60, 60);
            GLUquadric *a= gluNewQuadric();
            gluCylinder(a, BODY_RADIUS9, BODY_RADIUS9, BODY_LENGTH9, SLICES9, STACKS9);
            gluDisk(a, 0.0f, BODY_RADIUS9, SLICES9, STACKS9);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH9);
            gluDisk(a, 0.0f, BODY_RADIUS9, SLICES9, STACKS9);
        glPopMatrix();

        glPushMatrix();
            glTranslated(1.2,5.3,0.1);
            float BODY_LENGTHX = 0.12f;
            float BODY_RADIUSX = 0.15f;
            int SLICESX = 30;
            int STACKSX = 30;
            glRotatef(0, 60, 60, 60);
            GLUquadric *X= gluNewQuadric();
            gluCylinder(X, BODY_RADIUSX, BODY_RADIUSX, BODY_LENGTHX, SLICESX, STACKSX);
            gluDisk(X, 0.0f, BODY_RADIUSX, SLICESX, STACKSX);
            glTranslatef(0.0f, 0.0f, BODY_LENGTHX);
            gluDisk(X, 0.0f, BODY_RADIUSX, SLICESX, STACKSX);
        glPopMatrix();


    }
    void rangkahp(){
        glPushMatrix();
        glTranslated(0.0,0.0,0.4);
        //layar(0.1f,0.0f,0.0f);
        glPopMatrix();

        float amb[] = {0.1f, 0.1f, 0.1f, 0.5f };
        float diff[] = {0.2f, 0.2f, 0.2f, 0.5f };
        float spec[] = {0.3f, 0.3f, 0.3f, 0.5f };
        float shine = 0.5f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

        glPushMatrix();
        glTranslated(0.0,0.0,0.0);
        glScaled(4,8,0.7);
        glutSolidCube(1.0);
        glPopMatrix();

        /** SUDUT **/
        glPushMatrix();
        glTranslated(-2.0,4.0,0.35);
        sudut();
        glPopMatrix();

        glPushMatrix();
        glTranslated(2.0,4.0,0.35);
        sudut();
        glPopMatrix();

        glPushMatrix();
        glTranslated(2.0,-4.0,0.35);
        sudut();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-2.0,-4.0,0.35);
        sudut();
        glPopMatrix();

        /** TAMBAHAN TEPI **/
        glPushMatrix();
        glTranslated(-2.0,0.0,0.0);//samping
        glScaled(0.6,8.0,0.7);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(2.0,0.0,0.0);
        glScaled(0.6,8.0,0.7);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();//atas
        glTranslated(0.0,4.0,0.0);
        glScaled(4.0,0.6,0.7);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();//BAWAH
        glTranslated(0.0,-4.0,0.0);
        glScaled(4.0,0.6,0.7);
        glutSolidCube(1.0);
        glPopMatrix();


    }

    void handphone() {

        glPushMatrix();
        glTranslated(0.3,0.3,0.3);
        rangkahp();
        glPopMatrix();

        glPushMatrix();
        glTranslated(3.13,-3.1,0.3);
        slotsim();
        glPopMatrix();



        glPushMatrix();
        glTranslated(-2.05,0.6,0.3);
        glRotatef(90, 0, 1, 0);
        tabung(0.1,0.1);
        glPopMatrix();

        float amb[] = {0.0f, 0.0f, 1.0f, 1.0f };
        float diff[] = {0.0f, 1.0f, 1.0f, 0.5f };
        float spec[] = {1.0f, 0.0f, 1.0f, 0.5f };
        float shine = 0.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

        //TOMBOL POWER
        glPushMatrix();
        glTranslated(2.3,0.9,0.3);
        glScaled(0.7,0.7,0.2);
        glutSolidCube(1.0);
        glPopMatrix();

        //TOMBOL VOLUME
        glPushMatrix();
        glTranslated(2.4,2.5,0.3);//cube
        glScaled(0.5,1.5,0.2);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.3,0.3,0.3);//cube
        glScaled(4,8,0.7);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslated(1.7,-3.82,0.3);//cube
            float BODY_LENGTH = 0.2f;
            float BODY_RADIUS = 0.2f;
            int SLICES = 30;
            int STACKS = 30;
            glRotatef(90, 90, 0, 0);
            GLUquadric *q= gluNewQuadric();
            gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
            gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH);
            gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
        glPopMatrix();

        glPushMatrix();
            glTranslated(1,-3.82,0.3);//cube
            float BODY_LENGTH2 = 0.2f;
            float BODY_RADIUS2 = 0.1f;
            int SLICES2 = 30;
            int STACKS2 = 30;
            glRotatef(90, 90, 0, 0);
            GLUquadric *s= gluNewQuadric();
            gluCylinder(s, BODY_RADIUS2, BODY_RADIUS2, BODY_LENGTH2, SLICES2, STACKS2);
            gluDisk(s, 0.0f, BODY_RADIUS2, SLICES2, STACKS2);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH2);
            gluDisk(s, 0.0f, BODY_RADIUS2, SLICES2, STACKS2);
        glPopMatrix();

        //USB
        glPushMatrix();
        glTranslated(0.3,-3.67,0.3);
        glScaled(0.7,0.7,0.2);
        glutSolidCube(1.0);
        glPopMatrix();

            glPushMatrix();
            glTranslated(-0.4,-3.92,0.3);//cube
            float BODY_LENGTH3 = 0.1f;
            float BODY_RADIUS3 = 0.1f;
            int SLICES3 = 30;
            int STACKS3 = 30;
            glRotatef(90, 90, 0, 0);
            GLUquadric *r= gluNewQuadric();
            gluCylinder(r, BODY_RADIUS3, BODY_RADIUS3, BODY_LENGTH3, SLICES3, STACKS3);
            gluDisk(r, 0.0f, BODY_RADIUS3, SLICES3, STACKS3);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH3);
            gluDisk(r, 0.0f, BODY_RADIUS3, SLICES3, STACKS3);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-0.7,-3.92,0.3);//cube
            float BODY_LENGTH4 = 0.1f;
            float BODY_RADIUS4 = 0.1f;
            int SLICES4 = 30;
            int STACKS4 = 30;
            glRotatef(90, 90, 0, 0);
            GLUquadric *t= gluNewQuadric();
            gluCylinder(t, BODY_RADIUS4, BODY_RADIUS4, BODY_LENGTH4, SLICES4, STACKS4);
            gluDisk(t, 0.0f, BODY_RADIUS4, SLICES4, STACKS4);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH4);
            gluDisk(t, 0.0f, BODY_RADIUS4, SLICES4, STACKS4);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-1.0,-3.92,0.3);//cube
            float BODY_LENGTH5 = 0.1f;
            float BODY_RADIUS5 = 0.1f;
            int SLICES5 = 30;
            int STACKS5 = 30;
            glRotatef(90, 90, 0, 0);
            GLUquadric *u= gluNewQuadric();
            gluCylinder(u, BODY_RADIUS5, BODY_RADIUS5, BODY_LENGTH5, SLICES5, STACKS5);
            gluDisk(u, 0.0f, BODY_RADIUS5, SLICES5, STACKS5);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH5);
            gluDisk(u, 0.0f, BODY_RADIUS5, SLICES5, STACKS5);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-1.3,-3.92,0.3);//cube
            float BODY_LENGTH6 = 0.1f;
            float BODY_RADIUS6 = 0.1f;
            int SLICES6 = 30;
            int STACKS6 = 30;
            glRotatef(90, 90, 0, 0);
            GLUquadric *v= gluNewQuadric();
            gluCylinder(v, BODY_RADIUS6, BODY_RADIUS6, BODY_LENGTH6, SLICES6, STACKS6);
            gluDisk(v, 0.0f, BODY_RADIUS6, SLICES6, STACKS6);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH6);
            gluDisk(v, 0.0f, BODY_RADIUS6, SLICES6, STACKS6);
        glPopMatrix();

        //kamera
            glPushMatrix();
            glTranslated(0.3,3.0,-0.15);//cube
            float BODY_LENGTH7 = 0.4f;
            float BODY_RADIUS7 = 0.4f;
            int SLICES7 = 30;
            int STACKS7 = 30;
            glRotatef(0, 20, 30, 30);
            GLUquadric *y= gluNewQuadric();
            gluCylinder(y, BODY_RADIUS7, BODY_RADIUS7, BODY_LENGTH7, SLICES7, STACKS7);
            gluDisk(y, 0.0f, BODY_RADIUS7, SLICES7, STACKS7);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH7);
            gluDisk(y, 0.0f, BODY_RADIUS7, SLICES7, STACKS7);
        glPopMatrix();

        //fingerprint
        glPushMatrix();
            glTranslated(0.3,1.5,-0.15);//cube
            float BODY_LENGTH8 = 0.4f;
            float BODY_RADIUS8 = 0.4f;
            int SLICES8 = 30;
            int STACKS8 = 30;
            glRotatef(0, 60, 60, 60);
            GLUquadric *z= gluNewQuadric();
            gluCylinder(z, BODY_RADIUS8, BODY_RADIUS8, BODY_LENGTH8, SLICES8, STACKS8);
            gluDisk(z, 0.0f, BODY_RADIUS8, SLICES8, STACKS8);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH8);
            gluDisk(z, 0.0f, BODY_RADIUS8, SLICES8, STACKS8);
        glPopMatrix();

        float amb2[] = {0.0f, 0.0f, 0.0f, 0.5f };
        float diff2[] = {0.0f, 0.0f, 0.0f, 0.5f };
        float spec2[] = {0.0f, 0.0f, 0.0f, 0.5f };
        float shine2 = 0.5f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec2);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine2);
        glPushMatrix();
            glTranslated(0.3,3.0,-0.2);//cube
            float BODY_LENGTH9 = 0.12f;
            float BODY_RADIUS9 = 0.15f;
            int SLICES9 = 30;
            int STACKS9 = 30;
            glRotatef(0, 60, 60, 60);
            GLUquadric *a= gluNewQuadric();
            gluCylinder(a, BODY_RADIUS9, BODY_RADIUS9, BODY_LENGTH9, SLICES9, STACKS9);
            gluDisk(a, 0.0f, BODY_RADIUS9, SLICES9, STACKS9);
            glTranslatef(0.0f, 0.0f, BODY_LENGTH9);
            gluDisk(a, 0.0f, BODY_RADIUS9, SLICES9, STACKS9);
        glPopMatrix();

    }

    float bodyHp = 0;
    float slots = -1.0;
    float popcam = -1.0;
    boolean wicarg = false;
    float wcas = -10.0;
    float arah1 = 0.01;
    float arah2 = 0.01;
    boolean hidupkan = false;
    boolean pcon = false;
    boolean scon = false;
    float putar1 = 0.2;
    float putar2 = 0.2;
    float putar3 = 0.2;

    void vectorMovement(float toMove[], float magnitude, float direction){
        float speedX = toMove[0]*magnitude*direction;
        float speedY = toMove[1]*magnitude*direction;
        float speedZ = toMove[2]*magnitude*direction;
        Cx += speedX;
        Cy += speedY;
        Cz += speedZ;
        Lx += speedX;
        Ly += speedY;
        Lz += speedZ;
    }

    void cameraRotation(Vector refer, double angle){
        float M = sqrt(pow(refer.x, 2) + pow(refer.y, 2) + pow(refer.z, 2));
        float Up_x1 = refer.x / M;
        float Up_y1 = refer.y / M;
        float Up_z1 = refer.z / M;
        float VLx = Lx - Cx;
        float VLy = Ly - Cy;
        float VLz = Lz - Cz;
        float dot_product = (VLx * Up_x1) + (VLy * Up_y1) + (VLz * Up_z1);
        float cross_product_x = (Up_y1 * VLz) - (VLy * Up_z1);
        float cross_product_y = -((Up_x1 * VLz) - (Up_z1 * VLx));
        float cross_product_z = (Up_x1 * VLy) - (Up_y1 * VLx);
        float last_factor_rodrigues = 1.0f - cos(toRadians(angle));
        float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLx);
        float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLy);
        float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLz);

        Lx = Lx1+Cx;
        Ly = Ly1+Cy;
        Lz = Lz1+Cz;
    }

    void display()
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.8, 0.8, 0.7, 1.0);
        glLoadIdentity();

            gluLookAt(Cx, Cy, Cz,
                    Lx, Ly, Lz,
                    Tx, Ty, Tz);

        glTranslatef(-T_X, T_Y, T_Z);
        glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
        glRotatef(view_roty, 0.0f, 0.0f, 1.0f);

        glRotatef(R_X, 1.0f, 0.0f, 0.0f);
        glRotatef(R_Y, 0.0f, 1.0f, 0.0f);
        glRotatef(R_Z, 0.0f, 0.0f, 1.0f);

        glPushMatrix();
        glTranslatef(bodyHp, 0.0f, -0.75f);
        glRotatef(-90, 0.0f, -1.0f, 0.0f);
        handphone();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.3,popcam,-1.2);
        glRotatef(-90, 0.0f, -1.0f, 0.0f);
        kamera();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.3f,-3.1f,slots);
        glRotatef(-90, 0.0f, -1.0f, 0.0f);
        slotsim();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.65,0.3,-1.05);
        glRotatef(-90, 0.0f, -1.0f, 0.0f);
        layar(col1,col2,col3);
        glPopMatrix();

        glPushMatrix();
        glTranslated(wcas,0.3,-1.05);
        glRotatef(-90, 0.0f, -1.0f, 0.0f);
        wiCas(3.0,1.0);
        glPopMatrix();

        /**batas batas **/
        if(wicarg == true){
            wcas = wcas + 0.5;
        }else{
            wcas = wcas - 0.5;
        }


        if(scon == false){
            slots = slots + 0.05;
        }else{
            slots = slots - 0.05;
        }

        if(pcon == true){
            popcam = popcam + 0.05;
        }else{
            popcam = popcam - 0.05;
        }

        if(slots > -1.0){
            slots = -1.0;
            hidupkan = false;
            if(wcas > -1.0){
                wcas = -1.0;
                hidupkan = true;
            }
        }else if(slots < -3.8){
            slots = -3.8;
            if(wcas > -1.0){
                wcas = -1.0;
                hidupkan = true;
            }
            //hidupkan = true;
        }


        if(popcam < -1.0){
            popcam = -1.0;
        }else if(popcam > 0.0){
            popcam = 0.0;
        }

        if(hidupkan == true){
            col1 = col1 + 0.002;
            col2 = col2 + 0.003;
            col3 = col3 + 0.004;
        }else{
            col1 = col1 - 0.007;
            col2 = col2 - 0.008;
            col3 = col3 - 0.009;

            pcon = false;
        }
        if(col1 > 1.0){
            col1 = 1.0;
            col2 = 1.0;
            col3 = 1.0;

        }else if(col3 < 0.0){
            col1 = 0.0;
            col2 = 0.0;
            col3 = 0.0;
            pcon = false;
        }


        glFlush();
        glutSwapBuffers();
    }

    void timer(int value)
    {
        glutPostRedisplay();
        glutTimerFunc(15, timer, 0);
    }

    void reshape(GLsizei width, GLsizei height)
    {
    if (height == 0) height = 1;
        GLfloat aspect = (GLfloat)width / (GLfloat)height;
        glViewport(30, 6, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, aspect, 1.0f, 20.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void mouseControl(int button, int state, int x, int y){
        oldMouseX = x;
        oldMouseY = y;
    }

    void mouseMotion(int x, int y){
        int getX = x;
        int getY = y;
        float thetaY = 360.0f*(getX - oldMouseX)/640;
        float thetaX = 360.0f*(getY - oldMouseY)/360;
        oldMouseX = getX;
        oldMouseY = getY;
        view_rotx += thetaX;
        view_roty += thetaY;
    }

        void keyFunction(unsigned char key, int x, int y){
        switch(key){
            case 79: // Rotasi sumbu Z+ dengan tombol O
                    R_Z = R_Z + 15.0f;
                break;
            case 85: // Rotasi sumbu Z- dengan tombol U
                    R_Z = R_Z - 15.0f;
                break;
            case 73: // Rotasi sumbu Y+ dengan tombol I
                    R_Y = R_Y + 15.0f;
                break;
            case 75: // Rotasi sumbu Y- dengan tombol K
                    R_Y = R_Y - 15.0f;
                break;
            case 76: // Rotasi sumbu X+ dengan tombol L
                    R_X = R_X + 15.0f;
                break;
            case 74: // Rotasi sumbu X- dengan tombol J
                    R_X = R_X - 15.0f;
                break;
            case 13: // hidupkan layar
                    R_X = R_X - 15.0f;
                break;




            case 87: // Translasi sumbu Y+ dengan tombol W
                    T_Y = T_Y + 0.5f;
                break;
            case 83: // Translasi sumbu Y- dengan tombol S
                    T_Y = T_Y - 0.5f;
                break;
            case 68: // Translasi sumbu X- dengan tombol D
                    T_X = T_X - 0.5f;
                break;
            case 65: // Translasi sumbu X+ dengan tombol A
                    T_X = T_X + 0.5f;
                break;

            case 32: // space (reset)
                    R_Z=0.0f, R_X=0.0f, R_Y=0.0f;
                    T_Z=-16.0f, T_X=0.0f, T_Y=0.0f;

                    view_rotx = 0.0f, view_roty = 0.0f;

                    Cx = 1, Cy = 1.10, Cz = 0.5;
                    Lx = 1, Ly = 1, Lz = 0;
                    Tx = 0, Ty = 1, Tz = 0;

                break;
            case 48: // Translasi sumbu X+ dengan tombol A
                    T_X = T_X + 0.5f;
                break;
            case 90: // Zoom in dengan tombol Z
                    T_Z = T_Z + 0.5f;
                break;
            case 88: // zoom out dengan tombol X
                    T_Z = T_Z - 0.5f;
                break;
            case 86: // pop slot sim dengan tombol V
                    //slots = slots + 0.2f;
                    scon = true;
                break;
            case 66: // back slot sim dengan tombol B
                    //slots = slots - 0.2f;
                    scon = false;
                break;
            case 77: // pop CAMERA dengan tombol M
                    pcon = true;
                break;
            case 78: // back CAMERA dengan tombol N
                    pcon = false;
                break;
            case 127: // turn on phone SPACE
                    hidupkan = true;
                break;
            case 27: // TRUNOFF ESC
                    hidupkan = false;
                break;
            case 84: // wireless cas T
                    wicarg = true;
                break;
            case 89: // wireless cas OFF y
                    wicarg = false;
                break;
            }
        }


    int main(int argc, char **argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(700, 560);
        glutInitWindowPosition(50, 50);
        glutCreateWindow("Demo Display Smartphone");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyFunction);
        initGL();
        glutMouseFunc(mouseControl);
        glutMotionFunc(mouseMotion);
        glutTimerFunc(0, timer, 0);
        glutMainLoop();
        return 0;
    }
