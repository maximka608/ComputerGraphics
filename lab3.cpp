//#include <GL/glut.h>
//#include <vector>
//#include <json.hpp>
//#include <iostream>
//#include <fstream>
//#include <cmath>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//using namespace std;
//using json = nlohmann::json;
//
//struct Vertex {
//    double x, y, z;
//};
//
//GLfloat Vertices[][3] = {
//        {0.0, 0.0, 0.0},
//        {1.0, 0.0, 0.0},
//        {0.5, 0.0, 0.86602540378},
//        {0.0, 1.0, 0.0},
//        {1.0, 1.0, 0.0},
//        {0.5, 1.0, 0.86602540378}
//};
//
//vector<Vertex> vertices;
//vector<vector<double>> trajectory;
//GLuint textures[1];
//bool wireFrame = false, normals = false, useTexture = false, lighting = false;
//bool isOrthographic = false;
//double rotateX = 0, rotateY = 0;
//float camPosX = 0.0f, camPosY = 0.0f, camPosZ = 5.0f;
//float camRotX = 0.0f, camRotY = 0.0f;
//
//void read_data() {
//    ifstream file("/Users/maksim/CLionProjects/OpenGL/data.json");
//    json js;
//    file >> js;
//
//    file.close();
//
//    for (auto & v : js["vertices"]) {
//        Vertex vertex;
//        vertex.x = v[0];
//        vertex.y = v[1];
//        cout << vertex.x << " " << vertex.y << endl;
//
//        vertices.push_back(vertex);
//    }
//
//    for (auto & p : js["trajectory"]) {
//        trajectory.push_back({p[0], p[1], p[2]});
//        cout << p[0] << " " << p[1] << endl;
//    }
//
//}
//
//void loadTexture() {
//    glGenTextures(1, textures);
//
//    int width, height, nrChannels;
//    unsigned char * data;
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
//void init() {
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//
//    GLfloat lightPos[] = {0.0, 0.0, 2.0, 1.0};
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//
//    GLfloat matSpecular[] = {0.80f, 0.80f, 0.80f, 1.0f};
//    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
//
//    GLfloat shininess = 50.0f;
//    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
//
//    glNormal3f(0.0, 0.0, 1.0);
//}
//
//void updateProjection() {
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    if (isOrthographic) {
//        glOrtho(-2.0 * ((double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT)),
//                2.0 * ((double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT)),
//                -2.0, 2.0, -10.0, 10.0);
//    } else {
//        gluPerspective(45.0, (double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 100.0);
//    }
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//void drawTriangle(int a, int b, int c, float color[3]) {
//    glColor3fv(color);
//    glBegin(GL_TRIANGLES);
//    glVertex3fv(Vertices[a]);
//    glVertex3fv(Vertices[b]);
//    glVertex3fv(Vertices[c]);
//    glEnd();
//}
//
//void drawQuad(int a, int b, int c, int d, float color[3]) {
//    glColor3fv(color);
//    glBegin(GL_QUADS);
//    glVertex3fv(Vertices[a]);
//    glVertex3fv(Vertices[b]);
//    glVertex3fv(Vertices[c]);
//    glVertex3fv(Vertices[d]);
//    glEnd();
//}
//
//void draw(){
//    glTranslatef(0.0f, 0.0f, 0.0f);
//    glRotatef(rotateX, 1.0, 0.0, 0.0);
//    glRotatef(rotateY, 0.0, 1.0, 0.0);
//    float red[3] = {1.0, 0.0, 0.0};
//
//    float green[3] = {0.0, 1.0, 0.0};
//    float blue[3] = {0.0, 0.0, 1.0};
//    float yellow[3] = {1.0, 1.0, 0.0};
//    float magenta[3] = {1.0, 0.0, 1.0};
//
//    drawTriangle(0, 1, 2, red);
//
//    drawQuad(0, 1, 4, 3, green);
//    drawQuad(1, 2, 5, 4, blue);
//    drawQuad(2, 0, 3, 5, yellow);
//
//    drawTriangle(3, 4, 5, magenta);
//}
//
//void drawTexture(GLuint textureID) {
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glTranslatef(0.0f, 0.0f, 0.0f);
//    glRotatef(rotateX, 1.0, 0.0, 0.0);
//    glRotatef(rotateY, 0.0, 1.0, 0.0);
//
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(0.0, 0.0, 0.0);
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(1.0, 0.0, 0.0);
//    glTexCoord2f(0.5f, 1.0f);
//    glVertex3f(0.5, 0.0, sqrt(0.75));
//    glEnd();
//
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(0.0, 1.0, 0.0);
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(1.0, 1.0, 0.0);
//    glTexCoord2f(0.5f, 1.0f);
//    glVertex3f(0.5, 1.0, sqrt(0.75));
//    glEnd();
//
//    glBegin(GL_QUADS);
//
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(0.0, 0.0, 0.0);
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(1.0, 0.0, 0.0);
//    glTexCoord2f(1.0f, 1.0f);
//    glVertex3f(1.0, 1.0, 0.0);
//    glTexCoord2f(0.0f, 1.0f);
//    glVertex3f(0.0, 1.0, 0.0);
//
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(1.0, 0.0, 0.0);
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(0.5, 0.0, sqrt(0.75));
//    glTexCoord2f(1.0f, 1.0f);
//    glVertex3f(0.5, 1.0, sqrt(0.75));
//    glTexCoord2f(0.0f, 1.0f);
//    glVertex3f(1.0, 1.0, 0.0);
//
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(0.5, 0.0, sqrt(0.75));
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(0.0, 0.0, 0.0);
//    glTexCoord2f(1.0f, 1.0f);
//    glVertex3f(0.0, 1.0, 0.0);
//    glTexCoord2f(0.0f, 1.0f);
//    glVertex3f(0.5, 1.0, sqrt(0.75));
//    glEnd();
//
//    glDisable(GL_TEXTURE_2D);
//}
//
//Vertex calculateNormal(const Vertex& v0, const Vertex& v1, const Vertex& v2) {
//    Vertex vec1 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
//    Vertex vec2 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
//
//    Vertex normal;
//    normal.x = vec1.y * vec2.z - vec1.z * vec2.y;
//    normal.y = vec1.z * vec2.x - vec1.x * vec2.z;
//    normal.z = vec1.x * vec2.y - vec1.y * vec2.x;
//
//    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
//
//    if (length != 0.0f) {
//        normal.x /= length;
//        normal.y /= length;
//        normal.z /= length;
//    }
//
//    return normal;
//}
//
//void drawNormal(const Vertex& v0, const Vertex& v1, const Vertex& v2, float length) {
//    Vertex normal = calculateNormal(v0, v1, v2);
//    Vertex midpoint = {(v0.x + v1.x + v2.x) / 3, (v0.y + v1.y + v2.y) / 3, (v0.z + v1.z + v2.z) / 3};
//    Vertex endpoint = {midpoint.x + normal.x * length, midpoint.y + normal.y * length, midpoint.z + normal.z * length};
//
//    glBegin(GL_LINES);
//    glVertex3f(midpoint.x, midpoint.y + 0.1, midpoint.z);
//    glVertex3f(endpoint.x, endpoint.y, endpoint.z);
//    glEnd();
//}
//
//Vertex calculateQuadNormal(int a, int b, int c, int d) {
//    Vertex v0 = {Vertices[a][0], Vertices[a][1], Vertices[a][2]};
//    Vertex v1 = {Vertices[b][0], Vertices[b][1], Vertices[b][2]};
//    Vertex v2 = {Vertices[c][0], Vertices[c][1], Vertices[c][2]};
//    Vertex v3 = {Vertices[d][0], Vertices[d][1], Vertices[d][2]};
//
//
//    Vertex normal1 = calculateNormal(v0, v1, v2);
//    Vertex normal2 = calculateNormal(v0, v2, v3);
//
//    Vertex quadNormal;
//    quadNormal.x = (normal1.x + normal2.x) / 2;
//    quadNormal.y = (normal1.y + normal2.y) / 2;
//    quadNormal.z = (normal1.z + normal2.z) / 2;
//
//    float length = sqrt(quadNormal.x * quadNormal.x + quadNormal.y * quadNormal.y + quadNormal.z * quadNormal.z);
//    if (length != 0.0f) {
//        quadNormal.x /= length;
//        quadNormal.y /= length;
//        quadNormal.z /= length;
//    }
//
//    return quadNormal;
//}
//
//void drawQuadNormal(int a, int b, int c, int d, float length) {
//    Vertex quadNormal = calculateQuadNormal(a, b, c, d);
//    Vertex centroid = {
//            (Vertices[a][0] + Vertices[b][0] + Vertices[c][0] + Vertices[d][0]) / 4,
//            (Vertices[a][1] + Vertices[b][1] + Vertices[c][1] + Vertices[d][1]) / 4,
//            (Vertices[a][2] + Vertices[b][2] + Vertices[c][2] + Vertices[d][2]) / 4
//    };
//
//    Vertex endpoint = {
//            centroid.x + quadNormal.x * length,
//            centroid.y + quadNormal.y * length,
//            centroid.z + quadNormal.z * length
//    };
//
//
//    glBegin(GL_LINES);
//    glVertex3f(centroid.x + 0.1, centroid.y, centroid.z);
//    glVertex3f(endpoint.x, endpoint.y, endpoint.z);
//    glEnd();
//}
//
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//
//    updateProjection();
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    gluLookAt(camPosX, camPosY, camPosZ,
//              0.0, 0.0, 0.0,
//              0.0, 1.0, 0.0);
//
//    glRotatef(camRotX, 1.0, 0.0, 0.0);
//    glRotatef(camRotY, 0.0, 1.0, 0.0);
//
//    GLfloat lightPos[] = {0.0, 0.0, 2.0, 1.0};
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//    if (wireFrame) {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    }
//    else {
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    }
//
//    if (!useTexture) {
//        draw();
//    } else {
//        drawTexture(textures[0]);
//    }
//    if (normals) {
//        glColor3f(1.0f, 1.0f, 1.0f);
//        drawNormal(Vertex{Vertices[0][0], Vertices[0][1], Vertices[0][2]},
//                   Vertex{Vertices[1][0], Vertices[1][1], Vertices[1][2]},
//                   Vertex{Vertices[2][0], Vertices[2][1], Vertices[2][2]}, 0.2f);
//
//        drawNormal(Vertex{Vertices[3][0], Vertices[3][1], Vertices[3][2]},
//                   Vertex{Vertices[4][0], Vertices[4][1], Vertices[4][2]},
//                   Vertex{Vertices[5][0], Vertices[5][1], Vertices[5][2]}, 0.2f);
//
//        drawQuadNormal(0, 1, 4, 3, 0.2f);
//        drawQuadNormal(1, 2, 5, 4, 0.2f);
//        drawQuadNormal(2, 0, 3, 5, 0.2f);
//
//    }
//    if (lighting) {
//        init();
//    }
//
//    glutSwapBuffers();
//}
//
//void keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//        case 'a':
//            rotateY -= 10.0;
//            break;
//        case 'd':
//            rotateY += 10.0;
//            break;
//        case 'w':
//            rotateX -= 10.0;
//            break;
//        case 's':
//            rotateX += 10.0;
//            break;
//        case 'l':
//            lighting = !lighting;
//            break;
//        case 't':
//            useTexture = !useTexture;
//            break;
//        case 'v':
//            wireFrame = !wireFrame;
//            break;
//        case 'n':
//            normals = !normals;
//            break;
//        case 'p':
//            isOrthographic = !isOrthographic;
//            updateProjection();
//            break;
//        case 'f': camPosZ -= 0.1f; break;
//        case 'g': camPosZ += 0.1f; break;
//        case 'h': camPosX -= 0.1f; break;
//        case 'j': camPosX += 0.1f; break;
//        case 'k': camRotY -= 1.0f; break;
//    }
//
//    glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//
//    glutInitWindowSize(1000, 1000);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Lab3");
//
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//
//    read_data();
//    loadTexture();
//
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//
//    updateProjection();
//
//    glutMainLoop();
//
//    return 1;
//}