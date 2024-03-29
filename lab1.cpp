#include <GL/glut.h>
#include <vector>
#include <random>
using namespace std;

struct Point {
    double x;
    double y;
    double r, g, b;
};

//vector<vector<Point>> groups;
//vector<double> color;

//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    for (int i = 0; i < groups.size(); i++) {
//        if (i < groups.size() - 1) {
//            glLineWidth(2.0f);
//        } else {
//            glLineWidth(5.0f);
//        }
//        glBegin(GL_LINES);
//        for (int j = 0; j < groups[i].size(); j++) {
//            glColor3f(groups[i][j].r, groups[i][j].g, groups[i][j].b);
//            glVertex2d(groups[i][j].x, groups[i][j].y);
//        }
//        glEnd();
//    }
//
//    glutSwapBuffers();
//}

//void setColor(vector<double> randoms) {
//    int index = groups.size()-1;
//    for (int i = 0; i < groups[index].size(); i++) {
//        groups[index][i].r = randoms[0];
//        groups[index][i].g = randoms[1];
//        groups[index][i].b = randoms[2];
//    }
//}

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

//void mouse(int button, int state, int x, int y) {
//    Point p;
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        if (groups.empty()) {
//            groups.push_back(vector<Point>());
//            color = randomColor();
//        }
//        double fx = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2) - 1.0;
//        double fy = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / (glutGet(GLUT_WINDOW_HEIGHT) / 2) - 1.0;
//        p.x = fx;
//        p.y = fy;
//
//        groups.back().push_back(p);
//        setColor(color);
//
//        glutPostRedisplay();
//    }
//}

//void menu(int item) {
//    switch (item) {
//        case 1:
//            groups.push_back(vector<Point>());
//            break;
//        case 2:
//            color = randomColor();
//            break;
//        case 3:
//            groups.pop_back();
//            groups.push_back(vector<Point>());
//            break;
//        case 4:
//            if (groups.back().size() > 0) {
//                groups.back().pop_back();
//                groups.back().pop_back();
//            }
//            break;
//    }
//
//    glutPostRedisplay();
//}
//
//void createMenu() {
//    glutCreateMenu(menu);
//    glutAddMenuEntry("Create new group", 1);
//    glutAddMenuEntry("Set new color", 2);
//    glutAddMenuEntry("Delete group", 3);
//    glutAddMenuEntry("Delete last primitive", 4);
//
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//}
//
//
//void keyboard(unsigned char key, int x, int y) {
//    if (key == ' ') {
//        groups.push_back(vector<Point>());
//        color = randomColor();
//        glutPostRedisplay();
//    }
//    else if (key == 'c') {
//        color = randomColor();
//    }
//    else if (key == 'd') {
//        groups.pop_back();
//        groups.push_back(vector<Point>());
//    }
//    else if (key == 'p') {
//        groups.back().pop_back();
//        groups.back().pop_back();
//    }
//}
