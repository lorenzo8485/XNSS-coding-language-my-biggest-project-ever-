#define SFML_STATIC 1
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <random>
#include <cmath>

using namespace std;

// --- GLOBAL ENGINE STATE ---
struct EngineState {
    sf::RenderWindow window;
    sf::Color currentColor = sf::Color::White;
    sf::Vector2f currentPos = { 0, 550 }; // XNSS 0,0 is bottom
    map<string, vector<float>> lists;
    map<string, float> objects;
    vector<float> temp_list;
} state;

// --- UTILITY: Randomness ---
float get_random(string listName) {
    if (state.lists.count(listName)) {
        auto& l = state.lists[listName];
        static mt19937 gen(random_device{}());
        uniform_int_distribution<> dis(0, l.size() - 1);
        return l[dis(gen)];
    }
    return 0;
}

// --- CORE INTERPRETER LOGIC ---
void runLine(string line) {
    if (line.empty() || line.substr(0, 2) == "//") return;

    // 1. Fundamentals
    if (line.find("write(\"") != string::npos) {
        size_t s = line.find("\"") + 1, e = line.rfind("\"");
        cout << line.substr(s, e - s) << endl;
    }

    // 2. Variable/Object Creation
    else if (line.find("create.object(\"") != string::npos) {
        size_t s = line.find("\"") + 1, e = line.rfind("\"");
        state.objects[line.substr(s, e - s)] = 0;
    }

    // 3. List Management
    else if (line.find("create.list[") != string::npos) {
        state.temp_list.clear();
        string vals = line.substr(line.find("[") + 1, line.find("]") - line.find("[") - 1);
        stringstream ss(vals); string item;
        while (getline(ss, item, ',')) state.temp_list.push_back(stof(item));
    }
    else if (line.find("list.name(\"") != string::npos) {
        size_t s = line.find("\"") + 1, e = line.rfind("\"");
        state.lists[line.substr(s, e - s)] = state.temp_list;
    }

    // 4. Drawing & Colors
    else if (line.find("draw.color") != string::npos) {
        int r, g, b;
        sscanf(line.c_str(), "draw.color(R:%d G:%d B:%d)", &r, &g, &b);
        state.currentColor = sf::Color(r, g, b);
    }
    else if (line.find("draw.pos") != string::npos) {
        float x, y;
        sscanf(line.c_str(), "draw.pos(x:%f y:%f)", &x, &y);
        state.currentPos = { x, 600 - y };
    }

    // 5. Shapes & Curves
    else if (line.find("draw.square") != string::npos) {
        float l = (line.find("random.choice") != string::npos) ?
            get_random(line.substr(line.find("(\"") + 2, line.find("\")") - line.find("(\"") - 2)) : 0;
        if (l == 0) sscanf(line.c_str(), "draw.square(L:%f)", &l);
        sf::RectangleShape rect({ l, l });
        rect.setPosition(state.currentPos);
        rect.setFillColor(state.currentColor);
        state.window.draw(rect);
    }
    else if (line.find("draw.line.curve") != string::npos) {
        float x_d, y_h;
        sscanf(line.c_str(), "draw.line.curve(x:%f y:%f)", &x_d, &y_h);
        sf::VertexArray curve(sf::LineStrip);
        sf::Vector2f p0 = state.currentPos, p2 = { p0.x + x_d, p0.y }, p1 = { p0.x + x_d / 2, p0.y - y_h };
        for (float t = 0; t <= 1.01; t += 0.02) {
            float px = pow(1 - t, 2) * p0.x + 2 * (1 - t) * t * p1.x + pow(t, 2) * p2.x;
            float py = pow(1 - t, 2) * p0.y + 2 * (1 - t) * t * p1.y + pow(t, 2) * p2.y;
            curve.append(sf::Vertex({ px, py }, state.currentColor));
        }
        state.window.draw(curve);
    }
}

int main() {
    state.window.create(sf::VideoMode(800, 600), "XNSS Engine 4.0");

    // Load the .xnss file
    ifstream file("script.xnss");
    if (!file.is_open()) {
        cout << "Error: Could not find script.xnss" << endl;
        return 1;
    }

    state.window.clear(sf::Color(30, 30, 30)); // Dark background

    string line;
    while (getline(file, line)) {
        runLine(line);
        if (line.find("end.work") != string::npos) break;
    }

    state.window.display();

    // Keep window open until user closes it
    while (state.window.isOpen()) {
        sf::Event event;
        while (state.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) state.window.close();
        }
    }
    return 0;
}