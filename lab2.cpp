//#include <GL/glut.h>
//#include <vector>
//#include <random>
//#include <iostream>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//using namespace std;
//
//struct Pentagon {
//    double x, y, radius;
//    double r, g, b;
//    double rotate, scaleX = 1.0, scaleY = 1.0;
//};
//
//vector<Pentagon> pentagons;
//GLuint textures[1];
//bool currentTexture = false;
//bool UnionColor = false;
//bool NotUnionColor = false;
//bool grid = false;
//int grid_size = 20;
//
//void loadTexture() {
//    glGenTextures(1, textures);
//
//    int width, height, nrChannels;
//    unsigned char *data;
//
//    for (int i = 0; i < 1; i++) {
//        glBindTexture(GL_TEXTURE_2D, textures[i]);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        data = stbi_load("/Users/maksim/CLionProjects/OpenGL/content_texture.png", &width, &height, &nrChannels, STBI_rgb_alpha);
//        if (data) {
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//            glGenerateMipmap(GL_TEXTURE_2D);
//        }
//        if (data == nullptr) {
//            cout << "Not file";
//        }
//    }
//}
//
//void drawPentagon(const Pentagon & p) {
//    glPushMatrix();
//    glTranslatef(p.x, p.y, 0.0f);
//    glRotatef(p.rotate, 0.0f, 0.0f, 1.0f);
//    glScalef(p.scaleX, p.scaleY, 1.0f);
//
//    glColor3f(p.r, p.g, p.b);
//    glBegin(GL_POLYGON);
//    for(int i = 0; i < 5; ++i) {
//        float angle = 2.0f * M_PI * i / 5;
//        glVertex2f(cos(angle) * p.radius, sin(angle) * p.radius);
//    }
//    glEnd();
//
//    glPopMatrix();
//}
//
//void drawPentagonWithTexture(const Pentagon & p, GLuint textureID) {
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glPushMatrix();
//
//    glTranslatef(p.x, p.y, 0.0f);
//    glRotatef(p.rotate, 0.0f, 0.0f, 1.0f);
//    glScalef(p.scaleX, p.scaleY, 1.0f);
//
//    glColor3f(p.r, p.g, p.b);
//    glBegin(GL_POLYGON);
//    for(int i = 0; i < 5; ++i) {
//        float angle = 2.0f * M_PI * i / 5;
//        float tx = (cos(angle) + 1.0f) * 0.5f;
//        float ty = (sin(angle) + 1.0f) * 0.5f;
//        glTexCoord2f(tx, ty);
//        glVertex2f(cos(angle) * p.radius, sin(angle) * p.radius);
//    }
//    glEnd();
//    glPopMatrix();
//
//    glDisable(GL_TEXTURE_2D);
//}
//
//void drawGrid(int width, int height, int gridSize) {
//    glPushMatrix();
//    gluOrtho2D(-500, 500, -500, 500);
//
//    glLineWidth(5.0f);
//    glColor3f(0.9f, 0.9f, 0.9f);
//
//    glBegin(GL_LINES);
//    for (int i = -width; i < width; i += gridSize) {
//        glVertex2f(i, -1000);
//        glVertex2f(i, 1000);
//    }
//    for (int j = -height; j < height; j += gridSize) {
//        glVertex2f(-1000, j);
//        glVertex2f(1000, j);
//    }
//
//    glEnd();
//    glPopMatrix();
//}
//
//
//void display() {
//    glClearColor(1.0f, 1.0f, 1.f, 0.5f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    if (grid) {
//        drawGrid(1000, 1000, grid_size);
//    }
//
//    if (currentTexture) {
//        for (int i = 0; i < pentagons.size(); i++) {
//            drawPentagonWithTexture(pentagons[i], textures[0]);
//        }
//
//    } else {
//        for (int i = 0; i < pentagons.size(); i++) {
//            drawPentagon(pentagons[i]);
//        }
//    }
//
//    glutSwapBuffers();
//}
//
//vector<double> randomColor() {
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_real_distribution<> dis(0.0, 1.0);
//
//    double randomR = dis(gen);
//    double randomG = dis(gen);
//    double randomB = dis(gen);
//    return {randomR, randomG, randomB};
//}
//
//void mouse(int button, int state, int x, int y) {
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        float normX = (double) x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0f;
//        float normY = 1.0f - (double) y / (glutGet(GLUT_WINDOW_HEIGHT) / 2);
//
//        if (pentagons.empty() || pentagons.back().radius > 0.01) {
//            Pentagon p;
//            p.x = normX;
//            p.y = normY;
//            p.radius = 0.0;
//
//            vector<double> color = randomColor();
//            p.r = color[0];
//            p.g = color[1];
//            p.b = color[2];
//
//            pentagons.push_back(p);
//        }
//        else {
//            Pentagon & p = pentagons.back();
//            p.radius = sqrt(pow(p.x - normX, 2) + pow(p.y - normY, 2));
//        }
//        glutPostRedisplay();
//    }
//}
//
//void keyboard(unsigned char key, int x, int y) {
//    const double val = 0.1;
//    const double rotateValue = 4.5;
//    const double scaleValue = 0.1;
//
//    if (pentagons.empty()) return;
//
//    Pentagon &p = pentagons.back();
//
//    switch (key) {
//        case 'r':
//            p.rotate += rotateValue;
//            break;
//        case 'a':
//            p.x += val;
//            p.y += val;
//            break;
//        case 'd':
//            p.x -= val;
//            p.y -= val;
//            break;
//        case 's':
//            p.x += val;
//            p.y -= val;
//            break;
//        case 'w':
//            p.x -= val;
//            p.y += val;
//            break;
//        case 'm':
//            p.scaleX += scaleValue;
//            p.scaleY += scaleValue;
//            break;
//        case '-':
//            p.scaleX -= scaleValue;
//            p.scaleY -= scaleValue;
//            break;
//        case 'c': {
//            vector<double> color = randomColor();
//            p.r = color[0];
//            p.g = color[1];
//            p.b = color[2];
//            break;
//        }
//        case 't':
//            currentTexture = !currentTexture;
//            break;
//        case 'g':
//            grid = !grid;
//            break;
//        case 'z':
//            grid_size += 5;
//            break;
//        case 'x':
//            grid_size -= 5;
//            break;
//    }
//
//    if (key == 'u') {
//        UnionColor = !UnionColor;
//
//        if (UnionColor) {
//            glEnable(GL_COLOR_LOGIC_OP);
//            glLogicOp(GL_AND);
//        }
//        else {
//            glDisable(GL_COLOR_LOGIC_OP);
//        }
//    }
//
//    if (key == 'n') {
//        NotUnionColor = !NotUnionColor;
//
//        if (NotUnionColor) {
//            glEnable(GL_COLOR_LOGIC_OP);
//            glLogicOp(GL_NAND);
//        }
//        else {
//            glDisable(GL_COLOR_LOGIC_OP);
//        }
//    }
//
//    glutPostRedisplay();
//}
//
//void menu(int num) {
//    switch (num) {
//        case 0:
//            grid = !grid;
//            break;
//        case 1:
//            currentTexture = !currentTexture;
//            break;
//        case 2:
//            grid_size += 5;
//            break;
//        case 3:
//            if (grid_size > 5) grid_size -= 5;
//            break;
//        case 4:
//            UnionColor = !UnionColor;
//            if (UnionColor) {
//                glEnable(GL_COLOR_LOGIC_OP);
//                glLogicOp(GL_AND);
//            } else {
//                glDisable(GL_COLOR_LOGIC_OP);
//            }
//            break;
//        case 5:
//            NotUnionColor = !NotUnionColor;
//            if (NotUnionColor) {
//                glEnable(GL_COLOR_LOGIC_OP);
//                glLogicOp(GL_NAND);
//            } else {
//                glDisable(GL_COLOR_LOGIC_OP);
//            }
//            break;
//        default:
//            break;
//    }
//    glutPostRedisplay();
//}
//
//void createMenu() {
//    glutCreateMenu(menu);
//    glutAddMenuEntry("Toggle Grid", 0);
//    glutAddMenuEntry("Toggle Texture", 1);
//    glutAddMenuEntry("Increase Grid Size", 2);
//    glutAddMenuEntry("Decrease Grid Size", 3);
//    glutAddMenuEntry("Toggle Union Color", 4);
//    glutAddMenuEntry("Toggle Not Union Color", 5);
//
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//}
//
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//
//    glutInitWindowSize(1000, 1000);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Lab2");
//
//    loadTexture();
//    glutDisplayFunc(display);
//    glutMouseFunc(mouse);
//    glutKeyboardFunc(keyboard);
//
//    createMenu();
//
//    glutMainLoop();
//    return 1;
//}