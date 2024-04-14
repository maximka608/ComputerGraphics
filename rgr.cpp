#include <iostream>
#include <vector>
#include <json.hpp>
#include <fstream>
#include <cmath>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;
using json = nlohmann::json;

struct Vertex {
    double x, y, z;

    Vertex() : x(0), y(0), z(0) {}

    Vertex(double x, double y, double z) : x(x), y(y), z(z) {}

    Vertex operator + (const Vertex & other) const {
        return Vertex(x + other.x, y + other.y, z + other.z);
    }

    Vertex operator - (const Vertex & other) const {
        return Vertex(x - other.x, y - other.y, z - other.z);
    }

    Vertex normalize() const {
        double norm = sqrt(x * x + y * y + z * z);
        return Vertex(x / norm, y / norm, z / norm);
    }

    Vertex operator * (double scale) const {
        return Vertex(x * scale, y * scale, z * scale);
    }

    double dot(const Vertex& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

struct Sphere {
    Vertex center;
    double radius;
    Vertex color;
    double reflection;
    bool isActive;

    Sphere(const Vertex &center, double radius, const Vertex &color, double reflection, bool isActive = true)
            : center(center), radius(radius), color(color), reflection(reflection), isActive(isActive) {}

};

struct Light {
    Vertex position;
    Vertex intensity;

    Light(const Vertex& position, const Vertex& intensity) : position(position), intensity(intensity) {}
};

struct Camera {
    Vertex position;
    Vertex direction;
    double fov;

    Camera(const Vertex& position, const Vertex& direction, float fov) : position(position), direction(direction.normalize()), fov(fov) {}
};

vector<Sphere> spheres;

void read_data() {
    ifstream file("/Users/maksim/CLionProjects/OpenGL/data.json");
    json js;
    file >> js;
    file.close();

    spheres.clear();

    for (const auto& sphereJson : js["spheres"]) {
        Vertex center(sphereJson["center"][0], sphereJson["center"][1], sphereJson["center"][2]);
        double radius = sphereJson["radius"];
        Vertex color(1, 1, 1);

        if (sphereJson.contains("color")) {
            color = Vertex(sphereJson["color"][0], sphereJson["color"][1], sphereJson["color"][2]);
        }

        spheres.push_back(Sphere(center, radius, color, 0.8, 1));
    }
}

bool rayIntersect(const Vertex orig, const Vertex dir, Sphere sphere, double & t0) {
    Vertex L = sphere.center - orig;
    double tca = L.dot(dir);
    double d2 = L.dot(L) - tca * tca;
    double r2 = sphere.radius * sphere.radius;

    if (d2 > r2) return false;

    double thc = sqrt(r2 - d2);
    t0 = tca - thc;
    double t1 = tca + thc;
    if (t0 < 0) t0 = t1;

    if (t0 < 0) return false;
    return true;
}

Vertex reflect(const Vertex &I, const Vertex &N) {
    return I - N * 2.0 * (I.dot(N));
}

Vertex castRay(const Vertex& orig, const Vertex& dir, const vector<Sphere>& spheres, const Light& light, const Camera & camera, int depth = 0) {
    if (depth > 3) {
        return Vertex(0, 0, 0);
    }

    double minDist = numeric_limits<double>::max();
    Vertex color(0, 0, 0);
    bool inShadow = false;

    for (const auto& sphere : spheres) {
        if (!sphere.isActive) continue;
        double sphereDist = 0;
        if (rayIntersect(orig, dir, sphere, sphereDist)) {
            if (sphereDist < minDist) {
                minDist = sphereDist;
                Vertex hitPoint = orig + dir * sphereDist;
                Vertex normal = (hitPoint - sphere.center).normalize();
                Vertex toLight = (light.position - hitPoint).normalize();

                double lightDistance = (light.position - hitPoint).dot(toLight);
                for (const auto& shadowSphere : spheres) {
                    if (!shadowSphere.isActive) continue;
                    double shadowDist;
                    if (rayIntersect(hitPoint + normal * 0.01, toLight, shadowSphere, shadowDist) && shadowDist < lightDistance) {
                        inShadow = true;
                        break;
                    }
                }

                if (!inShadow) {
                    Vertex ambient = sphere.color * 0.1;
                    double diff = max(0.0, toLight.dot(normal));
                    Vertex diffuse = sphere.color * diff * 0.5;

                    Vertex reflectedDir = reflect(dir, normal).normalize();
                    Vertex reflectedColor = castRay(hitPoint + normal * 0.0001, reflectedDir, spheres, light, camera, depth + 1);

                    color = ambient + diffuse + reflectedColor * sphere.reflection;
                } else {
                    color = sphere.color * 0.1;
                }
            }
        }
    }

    return color;
}


vector<Vertex> render(const vector<Sphere>& spheres, const Light& light, const Camera& camera) {
    const int width = 800;
    const int height = 600;
    vector<Vertex> framebuffer(width * height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double x = (2 * (i + 0.5) / (double) width - 1) * tan(camera.fov / 2.) * width / (double) height;
            double y = -(2 * (j + 0.5) / (double) height - 1) * tan(camera.fov / 2.);
            Vertex dir = Vertex(x, y, -1).normalize();
            framebuffer[i + j * width] = castRay(Vertex(0, 0, 0), dir, spheres, light, camera);
        }
    }

    return framebuffer;
}

int main() {
    read_data();
    spheres[0].isActive = false;
    Camera camera(Vertex(10, 10, 10), Vertex(0, -0.1, 1), M_PI / 4);
    Light light(Vertex(0, 0, 0), Vertex(1, 1, 1));
    vector<Vertex> framebuffer = render(spheres, light, camera);
    int width = 800;
    int height = 600;
    int channels = 3;
    unsigned char *data = new unsigned char[width * height * channels];

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            int index = j * width + i;
            Vertex& color = framebuffer[index];
            int dataIndex = index * 3;
            data[dataIndex] = (unsigned char)(max(0.0, min(1.0, color.x)) * 255);
            data[dataIndex + 1] = (unsigned char)(max(0.0, min(1.0, color.y)) * 255);
            data[dataIndex + 2] = (unsigned char)(max(0.0, min(1.0, color.z)) * 255);
        }
    }

    if (stbi_write_png("/Users/maksim/CLionProjects/OpenGL/image.png", width, height, channels, data, width * channels)) {
        cout << "image";
    }

    delete[] data;
    return 0;
}