#include <windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

#include <stdlib.h>

    float Cx = 0.0f, Cy = 2.5f, Cz = 0.0f;
    float Lx = 0.0f, Ly = 2.5f, Lz = -20.0f;
    float angle_depanBelakang = 0.0f;
    float angle_depanBelakang2 = 0.0f;
    float angle_samping = 0.0f;
    float angle_samping2 = 0.0f;
    float angle_vertikal = 0.0f;
    float angle_vertikal2 = 0.0f;
    float silinderAngle = 0.0f;
    float silinderAngle1 = 0.0f;
    float silinderAngle2 = 0.0f;
    float silinderAngle3 = 0.0f;
    bool ori = true, silinder = false, silinder1 = false, silinder2 = false, silinder3 = false, silinder4 = false, silinder5 = false, kamera = false, kamera1 = false, kamera2 = false, kamera3 = false, kamera4 = false, kamera5 = false;

float toRadians(float angle){
    return angle * M_PI / 180;
}
class Vector{
    public:
    float x, y, z;
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
void handphone() {
float amb[] = {0.34f, 0.34f, 0.34f, 1.0f};
float diff[] = {0.41f, 0.41f, 0.41f, 1.0f};
float spec[] = {0.11f, 0.11f, 0.11f, 1.0f};
float shine = 200.0f;
glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
glPushMatrix();
glTranslated(0.3,0.3,0.3);//cube
glScaled(4,8,0.7);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(2.0,0.9,0.3);//cube
glScaled(0.7,0.7,0.7);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(2.1,2.5,0.3);//cube
glScaled(0.5,1.5,0.7);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(0.3,0.3,0.3);//cube
glScaled(4,8,0.7);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
    glTranslated(1.7,-3.6,0.3);//cube
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
    glTranslated(1,-3.6,0.3);//cube
    float BODY_LENGTH2 = 0.2f;
	float BODY_RADIUS2 = 0.2f;
	int SLICES2 = 30;
	int STACKS2 = 30;
	glRotatef(90, 90, 0, 0);
	GLUquadric *s= gluNewQuadric();
	gluCylinder(s, BODY_RADIUS2, BODY_RADIUS2, BODY_LENGTH2, SLICES2, STACKS2);
	gluDisk(s, 0.0f, BODY_RADIUS2, SLICES2, STACKS2);
	glTranslatef(0.0f, 0.0f, BODY_LENGTH2);
	gluDisk(s, 0.0f, BODY_RADIUS2, SLICES2, STACKS2);
glPopMatrix();
    
}

static void BigBox(){
float amb[]={0.0f, 0.5f, 0.0f, 1.0f};
float diff[]={0.0f, 0.5f, 0.0f, 1.0f};
float spec[]={0.0f, 0.5f, 0.0f, 1.0f};
float shine=0.0f;
glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);
glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
glBegin(GL_QUADS);
glVertex3f(-10000.0f, 0.0f, -10000.0f);
glVertex3f(10000.0f, 0.0f, -10000.0f);
glVertex3f(10000.0f, 0.0f, 10000.0f);
glVertex3f(-10000.0f, 0.0f, 10000.0f);
glEnd();
}
/* ini adalah function untuk melakukan pergerakan.
magnitude adalah besarnya gerakan sedangkan direction digunakan untuk menentukan
 arah.
gunakan -1 untuk arah berlawanan dengan vektor awal.
*/
void vectorMovement(Vector toMove, float magnitude, float direction){
    float speedX = toMove.x * magnitude * direction;
    float speedY = toMove.y * magnitude * direction;
    float speedZ= toMove.z * magnitude * direction;
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
    float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLx);
    float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLy);
    float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLz);
    Lx = Lx1+Cx;
    Ly = Ly1+Cy;
    Lz = Lz1+Cz;
}
void initGL(){
    depanBelakang.set_values(0.0f, 0.0f, -1.0f);
    samping.set_values(1.0f, 0.0f, 0.0f);
    vertikal.set_values(0.0f, 1.0f, 0.0f);
    float ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
}
void reshape(GLsizei width, GLsizei height){
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void keyControl(int k, int x, int y) {
    switch(k) {
        case GLUT_KEY_UP: //arrow up
            vectorMovement(vertikal, 2.0f, 1.0f);
        break;
        case GLUT_KEY_DOWN: //arrow down
            vectorMovement(vertikal, 2.0f, -1.0f);
        break;
        case GLUT_KEY_LEFT: //arrow left
            angle_depanBelakang += 15.0f;
            samping.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
            vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
            //cameraRotation(vertikal, angle_samping-angle_samping2);
            angle_depanBelakang2 = angle_depanBelakang;
        break;
        case GLUT_KEY_RIGHT: //arrow right
            angle_depanBelakang -= 15.0f;
            samping.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
            vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
            //cameraRotation(vertikal, angle_samping-angle_samping2);
            angle_depanBelakang2 = angle_depanBelakang;
        break;
    }
}
void keyFunction(unsigned char key, int x, int y){
/* Agar fungsi ini bekerja, pastikan CapsLock menyala,
kecuali tombol-tombol khusus seperti Spasi, dll */
    switch(key){
    case 87: // W
    vectorMovement(samping, 2.0f, 1.0f);
    break;
    case 83: // S
    vectorMovement(samping, 2.0f, -1.0f);
    break;
    case 68: // D
    vectorMovement(depanBelakang, 2.0f, 1.0f);
    break;
    case 65: // A
    vectorMovement(depanBelakang, 2.0f, -1.0f);
    break;
    case 32: // Spasi
        if (silinder){
            silinder = false;
        } else {
            silinder = true;
        }
    break;
    case 116: // t
        if (silinder1){
            silinder1 = false;
        } else {
            silinder1 = true;
        }
    break;
    case 102: // f
        if (silinder2){
            silinder2 = false;
        } else {
            silinder2 = true;
        }
    break;
    case 104: // h
        if (silinder3){
            silinder3 = false;
        } else {
            silinder3 = true;
        }
    break;
    case 103: // g
        if (silinder4){
            silinder4 = false;
        } else {
            silinder4 = true;
        }
    break;
    case 98: // g
        if (silinder5){
            silinder5 = false;
        } else {
            silinder5 = true;
        }
    break;
    case 13: // Enter
        if (kamera){
            kamera = false;
        } else {
            kamera = true;
        }
    break;
    case 84: // T
        if (kamera1){
            kamera1 = false;
        } else {
            kamera1 = true;
        }
    break;
    case 70: // F
        if (kamera2){
            kamera2 = false;
        } else {
            kamera2 = true;
        }
    break;
    case 72: // H
        if (kamera3){
            kamera3 = false;
        } else {
            kamera3 = true;
        }
    break;
    case 71: // G
        if (kamera4){
            kamera4 = false;
        } else {
            kamera4 = true;
        }
    break;
    case 66: // B
        if (kamera5){
            kamera5 = false;
        } else {
            kamera5 = true;
        }
    break;
    case 90: // Z
        angle_depanBelakang += 15.0f;
        samping.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
        vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
        //cameraRotation(vertikal, angle_samping-angle_samping2);
        angle_depanBelakang2 = angle_depanBelakang;
    break;
    case 88:
        angle_depanBelakang -= 15.0f;
        samping.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
        vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
        //cameraRotation(vertikal, angle_samping-angle_samping2);
        angle_depanBelakang2 = angle_depanBelakang;
    break;
    case 74: // J
        angle_vertikal += 5.0f;
        samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        //memutar vector sumbu z terhadap x (target, patokan)
        depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        cameraRotation(vertikal, angle_vertikal - angle_vertikal2); // lookat
        angle_vertikal2 = angle_vertikal;
    break;
    case 76: // L
        angle_vertikal -= 5.0f;
        samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        cameraRotation(vertikal, angle_vertikal - angle_vertikal2);
        angle_vertikal2 = angle_vertikal;
    break;
    case 73: // I
        angle_samping -= 5.0f;
        //vertikal.vectorRotation(samping, angle_samping - angle_samping2);
        depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
        cameraRotation(samping, angle_samping - angle_samping2);
        angle_samping2 = angle_samping;
    break;
    case 75: // K
        angle_samping += 5.0f;
        //vertikal.vectorRotation(samping, angle_samping-angle_samping2);
        depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
        cameraRotation(samping, angle_samping - angle_samping2);
        angle_samping2 = angle_samping;
    break;
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset the current matrix to the "identity"
    glLoadIdentity();
    // Move the "drawing cursor" around
    gluLookAt(Cx, Cy, Cz,
    Lx, Ly, Lz,
    vertikal.x, vertikal.y, vertikal.z);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, -15.0f);
    glRotatef(silinderAngle2, 0.0f, 0.0f, 1.0f);
    glRotatef(silinderAngle1, 0.0f, 1.0f, 0.0f);
    glRotatef(silinderAngle, 1.0f, 0.0f, 0.0f);
    handphone();
    glPopMatrix();
    glPushMatrix();
    BigBox();
    glPopMatrix();
    if (silinder){
        silinderAngle += 1.0f;
    }
    if (silinder1){
        silinderAngle -= 1.0f;
    }
    if (silinder2){
        silinderAngle1 += 1.0f;
    }
    if (silinder3){
        silinderAngle1 -= 1.0f;
    }
    if (silinder4){
        silinderAngle2 += 15.0f;
    }
    if (silinder5){
        silinderAngle2 -= 15.0f;
    }
    if (kamera){
        keyFunction('K', 0, 0);
    }
    if (kamera1){
        keyFunction('I', 0, 0);
    }
    if (kamera2){
        keyFunction('J', 0, 0);
    }
    if (kamera3){
        keyFunction('L', 0, 0);
    }
    if (kamera4){
        keyFunction('Z', 0, 0);
    }
    if (kamera5){
        keyFunction('X', 0, 0);
    }
    glFlush();
    glutSwapBuffers();
}

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Pertemuan 7");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyControl);
    glutKeyboardFunc(keyFunction);
    glutMainLoop();
    return EXIT_SUCCESS;
}

