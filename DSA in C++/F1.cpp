
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;

const int W = 100;
const int H = 35;
const double PI = 3.141592653589793;

struct Point {
    double x, y, z;
};

struct Edge {
    int a, b;
};

vector<Point> points;
vector<Edge> edges;

void addPoint(double x, double y, double z) {
    points.push_back({x, y, z});
}

void addEdge(int a, int b) {
    edges.push_back({a, b});
}

void addBox(double x1, double x2,
            double y1, double y2,
            double z1, double z2) {
    int start = (int)points.size();

    addPoint(x1, y1, z1);
    addPoint(x2, y1, z1);
    addPoint(x2, y2, z1);
    addPoint(x1, y2, z1);

    addPoint(x1, y1, z2);
    addPoint(x2, y1, z2);
    addPoint(x2, y2, z2);
    addPoint(x1, y2, z2);

    int e[][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    for (auto &edge : e)
        addEdge(start + edge[0], start + edge[1]);
}

void addWheel(double x, double z) {
    int segments = 16;
    int start = (int)points.size();
    double radius = 0.48;
    double centerY = 0.5;

    for (int i = 0; i < segments; i++) {
        double a = 2.0 * PI * i / segments;
        addPoint(
            x,
            centerY + radius * cos(a),
            z + radius * sin(a)
        );
    }

    for (int i = 0; i < segments; i++)
        addEdge(start + i, start + (i + 1) % segments);
}

void buildCar() {
    // Main chassis
    addBox(-2.1, 2.1, 0.55, 0.85, -0.35, 0.35);

    // Front nose
    addBox(2.1, 3.1, 0.48, 0.65, -0.18, 0.18);

    // Cockpit
    addBox(-0.7, 0.45, 0.85, 1.15, -0.28, 0.28);

    // Rear engine cover
    addBox(-1.8, -0.7, 0.85, 1.15, -0.3, 0.3);

    // Front and rear wings
    addBox(2.8, 3.4, 0.38, 0.48, -0.9, 0.9);
    addBox(-2.5, -2.0, 0.9, 1.0, -1.0, 1.0);

    // Four wheels: front and rear, left and right
    addWheel(2.0, -0.78);
    addWheel(2.0,  0.78);
    addWheel(-1.65, -0.78);
    addWheel(-1.65,  0.78);

    // Halo support
    addBox(-0.25, 0.05, 1.12, 1.5, -0.04, 0.04);
}

struct ScreenPoint {
    int x, y;
    double depth;
};

ScreenPoint project(Point p, double angle) {
    // Rotate the car around its vertical axis
    double rx = p.x * cos(angle) - p.z * sin(angle);
    double rz = p.x * sin(angle) + p.z * cos(angle);

    // Tilt the viewing angle to see the car's top
    double cameraY = p.y * cos(0.30) - rz * sin(0.30);
    double depth = p.y * sin(0.30) + rz * cos(0.30);

    double perspective = 1.0 / (1.0 + depth * 0.045);

    return {
        (int)(W / 2 + rx * 9.0 * perspective),
        (int)(H / 2 - cameraY * 7.0 * perspective),
        depth
    };
}

void drawLine(vector<string>& screen,
              ScreenPoint a, ScreenPoint b,
              char ch) {
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int steps = max(dx, dy);

    if (steps == 0) {
        if (a.x >= 0 && a.x < W && a.y >= 0 && a.y < H)
            screen[a.y][a.x] = ch;
        return;
    }

    for (int i = 0; i <= steps; i++) {
        double t = (double)i / steps;
        int x = (int)(a.x + (b.x - a.x) * t);
        int y = (int)(a.y + (b.y - a.y) * t);

        if (x >= 0 && x < W && y >= 0 && y < H)
            screen[y][x] = ch;
    }
}

int main() {
    buildCar();

    cout << "\033[2J\033[?25l";

    double angle = 0.0;

    for (int frame = 0; ; frame++) {
        vector<string> screen(H, string(W, ' '));

        vector<ScreenPoint> projected;

        for (auto p : points)
            projected.push_back(project(p, angle));

        for (auto e : edges) {
            drawLine(screen,
                     projected[e.a],
                     projected[e.b],
                     '#');
        }

        string title = " F1 // 3D ROTATION ";
        screen[1].replace(35, title.size(), title);

        string info = " ANGLE: " +
            to_string((int)(angle * 180.0 / PI) % 360) +
            " DEG ";
        screen[H - 2].replace(35, info.size(), info);

        cout << "\033[H";

        for (const auto& row : screen)
            cout << row << '\n';

        cout.flush();

        angle += 0.045;

        this_thread::sleep_for(
            chrono::milliseconds(45)
        );
    }

    cout << "\033[?25h";
    return 0;
}
