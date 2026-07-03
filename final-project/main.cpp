#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

constexpr int WINDOW_WIDTH = 1200;
constexpr int WINDOW_HEIGHT = 600;
constexpr int TIMER_INTERVAL_MS = 16;

constexpr float PI = 3.1415926f;
constexpr int WINDOW_COUNT = 12;

float paresan_x = -0.5f;
float paresan_y = -0.5f;
float paresan_scale = 1.5f;

float side_building_x = -0.98f;
float side_building_y = -0.5f;
float side_building_scale = 1.8f;

float cloud_1_x = -0.5f;
float cloud_2_x = 0.2f;
float cloud_speed = 0.005f;

float jeepney_x = -1.2f;
float jeepney_speed = 0.003f;

bool streetlight_on = true;
bool windows_lit = false;

GLfloat tech_building_main[] = {
    -0.6f, 0.85f, 0.0f,
    -0.12f, 0.85f, 0.0f,
    -0.12f, -0.5f, 0.0f,

    -0.6f, 0.85f, 0.0f,
    -0.1f, -0.5f, 0.0f,
    -0.6f, -0.5f, 0.0f,

    -0.55f, 0.65f, 0.0f,
    0.6f, 0.65f, 0.0f,
    0.6f, -0.5f, 0.0f,

    -0.55f, 0.65f, 0.0f,
    0.6f, -0.5f, 0.0f,
    -0.2f, -0.5f, 0.0f
};

GLfloat tech_building_main_colors[] = {
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f,
    200 / 256.0f, 180 / 256.0f, 120 / 256.0f
};

GLfloat tech_building_base[] = {
    -0.6f, -0.5f, 0.0f,
    0.6f, -0.5f, 0.0f,
    0.6f, -0.15f, 0.0f,
    -0.6f, -0.15f, 0.0f
};

GLfloat tech_building_base_colors[] = {
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f,
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f,
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f,
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f
};

GLfloat tech_building_side[] = {
    0.6f, -0.5f, 0.0f,
    0.45f, -0.38f, 0.0f,
    0.30f, -0.38f, 0.0f,
    0.30f, -0.5f, 0.0f
};

GLfloat building_windows[] = {
    -0.55f, 0.63f, 0.0f,  -0.35f, 0.63f, 0.0f,
    -0.35f, 0.43f, 0.0f,  -0.55f, 0.43f, 0.0f,

    -0.33f, 0.63f, 0.0f,  -0.13f, 0.63f, 0.0f,
    -0.13f, 0.43f, 0.0f,  -0.33f, 0.43f, 0.0f,

    0.15f, 0.63f, 0.0f,   0.35f, 0.63f, 0.0f,
    0.35f, 0.43f, 0.0f,   0.15f, 0.43f, 0.0f,

    0.37f, 0.63f, 0.0f,   0.57f, 0.63f, 0.0f,
    0.57f, 0.43f, 0.0f,   0.37f, 0.43f, 0.0f,

    -0.55f, 0.41f, 0.0f,  -0.35f, 0.41f, 0.0f,
    -0.35f, 0.21f, 0.0f,  -0.55f, 0.21f, 0.0f,

    -0.33f, 0.41f, 0.0f,  -0.13f, 0.41f, 0.0f,
    -0.13f, 0.21f, 0.0f,  -0.33f, 0.21f, 0.0f,

    0.15f, 0.41f, 0.0f,   0.35f, 0.41f, 0.0f,
    0.35f, 0.21f, 0.0f,   0.15f, 0.21f, 0.0f,

    0.37f, 0.41f, 0.0f,   0.57f, 0.41f, 0.0f,
    0.57f, 0.21f, 0.0f,   0.37f, 0.21f, 0.0f,

    -0.55f, 0.19f, 0.0f,  -0.35f, 0.19f, 0.0f,
    -0.35f, -0.01f, 0.0f, -0.55f, -0.01f, 0.0f,

    -0.33f, 0.19f, 0.0f,  -0.13f, 0.19f, 0.0f,
    -0.13f, -0.01f, 0.0f, -0.33f, -0.01f, 0.0f,

    0.15f, 0.19f, 0.0f,   0.35f, 0.19f, 0.0f,
    0.35f, -0.01f, 0.0f,  0.15f, -0.01f, 0.0f,

    0.37f, 0.19f, 0.0f,   0.57f, 0.19f, 0.0f,
    0.57f, -0.01f, 0.0f,  0.37f, -0.01f, 0.0f
};

GLfloat planters[] = {
    -0.52f, -0.35f, 0.0f,  -0.44f, -0.35f, 0.0f,
    -0.44f, -0.30f, 0.0f,  -0.52f, -0.30f, 0.0f,

    -0.42f, -0.35f, 0.0f,  -0.34f, -0.35f, 0.0f,
    -0.34f, -0.30f, 0.0f,  -0.42f, -0.30f, 0.0f,

    -0.32f, -0.35f, 0.0f,  -0.24f, -0.35f, 0.0f,
    -0.24f, -0.30f, 0.0f,  -0.32f, -0.30f, 0.0f,

    -0.22f, -0.35f, 0.0f,  -0.14f, -0.35f, 0.0f,
    -0.14f, -0.30f, 0.0f,  -0.22f, -0.30f, 0.0f,

    -0.12f, -0.35f, 0.0f,  -0.04f, -0.35f, 0.0f,
    -0.04f, -0.30f, 0.0f,  -0.12f, -0.30f, 0.0f,

    -0.02f, -0.35f, 0.0f,   0.06f, -0.35f, 0.0f,
    0.06f, -0.30f, 0.0f,   -0.02f, -0.30f, 0.0f,

    0.08f, -0.35f, 0.0f,    0.16f, -0.35f, 0.0f,
    0.16f, -0.30f, 0.0f,    0.08f, -0.30f, 0.0f,

    0.18f, -0.35f, 0.0f,    0.26f, -0.35f, 0.0f,
    0.26f, -0.30f, 0.0f,    0.18f, -0.30f, 0.0f,

    -0.52f, -0.25f, 0.0f,  -0.44f, -0.25f, 0.0f,
    -0.44f, -0.20f, 0.0f,  -0.52f, -0.20f, 0.0f,

    -0.42f, -0.25f, 0.0f,  -0.34f, -0.25f, 0.0f,
    -0.34f, -0.20f, 0.0f,  -0.42f, -0.20f, 0.0f,

    -0.32f, -0.25f, 0.0f,  -0.24f, -0.25f, 0.0f,
    -0.24f, -0.20f, 0.0f,  -0.32f, -0.20f, 0.0f,

    -0.22f, -0.25f, 0.0f,  -0.14f, -0.25f, 0.0f,
    -0.14f, -0.20f, 0.0f,  -0.22f, -0.20f, 0.0f,

    -0.12f, -0.25f, 0.0f,  -0.04f, -0.25f, 0.0f,
    -0.04f, -0.20f, 0.0f,  -0.12f, -0.20f, 0.0f,

    -0.02f, -0.25f, 0.0f,   0.06f, -0.25f, 0.0f,
    0.06f, -0.20f, 0.0f,   -0.02f, -0.20f, 0.0f,

    0.08f, -0.25f, 0.0f,    0.16f, -0.25f, 0.0f,
    0.16f, -0.20f, 0.0f,    0.08f, -0.20f, 0.0f,

    0.18f, -0.25f, 0.0f,    0.26f, -0.25f, 0.0f,
    0.26f, -0.20f, 0.0f,    0.18f, -0.20f, 0.0f
};

GLfloat paresan_right_border[] = {
    1.0f, 0.0f, 1.0f, 0.375f, 0.9875f, 0.375f, 0.9875f, 0.0f
};

GLfloat paresan_bottom_border[] = {
    0.9875f, 0.0f, 0.9875f, 0.125f, 0.8125f, 0.125f, 0.8125f, 0.0f
};

GLfloat paresan_middle_border_1[] = {
    0.9875f, 0.2917f, 0.9875f, 0.375f, 0.8125f, 0.375f, 0.8125f, 0.2917f
};

GLfloat paresan_left_border[] = {
    0.8125f, 0.0f, 0.8125f, 0.375f, 0.8f, 0.375f, 0.8f, 0.0f
};

GLfloat paresan_middle_border_2[] = {
    1.0f, 0.375f, 1.0f, 0.4f, 0.8f, 0.4f, 0.8f, 0.375f
};

GLfloat paresan_inside[] = {
    0.9875f, 0.125f, 0.9875f, 0.2917f, 0.8125f, 0.2917f, 0.8125f, 0.125f
};

GLfloat side_building_bottom_wall[] = {
    0.19375f, 0.0f, 0.19375f, 0.2083f, 0.00625f, 0.2083f, 0.00625f, 0.0f
};

GLfloat side_building_separator[] = {
    0.2f, 0.2083f, 0.2f, 0.2583f, 0.0f, 0.2583f, 0.0f, 0.2083f
};

GLfloat side_building_top_wall[] = {
    0.19375f, 0.2583f, 0.19375f, 0.4667f, 0.00625f, 0.4667f, 0.00625f, 0.2583f
};

GLfloat side_building_roof[] = {
    0.2f, 0.4667f, 0.2f, 0.5167f, 0.0f, 0.5167f, 0.0f, 0.4667f
};

GLfloat side_building_door[] = {
    0.175f, 0.0f, 0.175f, 0.1667f, 0.025f, 0.1667f, 0.025f, 0.0f
};

GLfloat side_building_pillar_1[] = {
    0.05f, 0.2583f, 0.05f, 0.4667f, 0.025f, 0.4667f, 0.025f, 0.2583f
};

GLfloat side_building_pillar_2[] = {
    0.1125f, 0.2583f, 0.1125f, 0.4667f, 0.0875f, 0.4667f, 0.0875f, 0.2583f
};

GLfloat side_building_pillar_3[] = {
    0.175f, 0.2583f, 0.175f, 0.4667f, 0.15f, 0.4667f, 0.15f, 0.2583f
};

void draw_rectangle(float x, float y, float width, float height, float red, float green, float blue) {
    glColor3f(red, green, blue);

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void draw_circle(float center_x, float center_y, float radius, int segments, float red, float green, float blue) {
    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center_x, center_y);

    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * PI * i / segments;
        float x = radius * std::cos(theta);
        float y = radius * std::sin(theta);

        glVertex2f(center_x + x, center_y + y);
    }

    glEnd();
}

void draw_circle_vertex_array(float center_x, float center_y, float radius) {
    std::vector<GLfloat> vertices;
    vertices.reserve(724);

    vertices.push_back(center_x);
    vertices.push_back(center_y);

    for (int i = 0; i <= 360; i++) {
        float angle = i * PI / 180.0f;

        vertices.push_back(center_x + std::cos(angle) * radius);
        vertices.push_back(center_y + std::sin(angle) * radius);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<int>(vertices.size() / 2));
    glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_text(const char* text, float x, float y, float scale_x, float scale_y, float line_width) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale_x, scale_y, 1.0f);
    glLineWidth(line_width);

    for (const char* character = text; *character != '\0'; character++) {
        for (float dx = -0.003f; dx <= 0.003f; dx += 0.003f) {
            for (float dy = -0.003f; dy <= 0.003f; dy += 0.003f) {
                glPushMatrix();
                glTranslatef(dx, dy, 0.0f);
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *character);
                glPopMatrix();
            }
        }

        glTranslatef(glutStrokeWidth(GLUT_STROKE_ROMAN, *character), 0.0f, 0.0f);
    }

    glPopMatrix();
}

void draw_text_small(const char* text, float x, float y, float scale, float spacing) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, scale);

    for (const char* character = text; *character != '\0'; character++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *character);
        glTranslatef(spacing, 0.0f, 0.0f);
    }

    glPopMatrix();
}

void draw_quad(const GLfloat* vertices, float red, float green, float blue, bool outline) {
    glColor3f(red, green, blue);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_POLYGON, 0, 4);

    if (outline) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

void draw_feu_tech_logo(float center_x, float center_y) {
    constexpr int segments = 50;
    constexpr float radius = 0.045f;

    std::vector<GLfloat> logo_vertices;
    logo_vertices.reserve((segments + 2) * 3);

    logo_vertices.push_back(center_x);
    logo_vertices.push_back(center_y);
    logo_vertices.push_back(0.0f);

    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * PI * i / segments;

        logo_vertices.push_back(radius * std::cos(theta) + center_x);
        logo_vertices.push_back(radius * std::sin(theta) + center_y);
        logo_vertices.push_back(0.0f);
    }

    glColor3f(1.0f, 1.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, logo_vertices.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<int>(logo_vertices.size() / 3));
    glDisableClientState(GL_VERTEX_ARRAY);

    std::vector<GLfloat> logo_outline;
    logo_outline.reserve(segments * 3);

    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * i / segments;

        logo_outline.push_back(radius * std::cos(theta) + center_x);
        logo_outline.push_back(radius * std::sin(theta) + center_y);
        logo_outline.push_back(0.0f);
    }

    glColor3f(0.0f, 0.6f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, logo_outline.data());
    glDrawArrays(GL_LINE_LOOP, 0, static_cast<int>(logo_outline.size() / 3));
    glDisableClientState(GL_VERTEX_ARRAY);

    GLfloat torch_vertices[] = {
        center_x - 0.008f, center_y - 0.015f, 0.0f,
        center_x + 0.008f, center_y - 0.015f, 0.0f,
        center_x + 0.008f, center_y + 0.01f, 0.0f,
        center_x - 0.008f, center_y + 0.01f, 0.0f,

        center_x, center_y + 0.025f, 0.0f,
        center_x - 0.01f, center_y + 0.01f, 0.0f,
        center_x + 0.01f, center_y + 0.01f, 0.0f
    };

    GLfloat torch_colors[] = {
        50 / 256.0f, 100 / 256.0f, 50 / 256.0f,
        50 / 256.0f, 100 / 256.0f, 50 / 256.0f,
        50 / 256.0f, 100 / 256.0f, 50 / 256.0f,
        50 / 256.0f, 100 / 256.0f, 50 / 256.0f,

        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, torch_vertices);
    glColorPointer(3, GL_FLOAT, 0, torch_colors);

    glDrawArrays(GL_QUADS, 0, 4);
    glDrawArrays(GL_TRIANGLES, 4, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void draw_feu_tech_building() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, tech_building_main);
    glColorPointer(3, GL_FLOAT, 0, tech_building_main_colors);
    glDrawArrays(GL_TRIANGLES, 0, 12);

    glVertexPointer(3, GL_FLOAT, 0, tech_building_base);
    glColorPointer(3, GL_FLOAT, 0, tech_building_base_colors);
    glDrawArrays(GL_QUADS, 0, 4);

    glVertexPointer(3, GL_FLOAT, 0, tech_building_side);
    glColorPointer(3, GL_FLOAT, 0, tech_building_main_colors);
    glDrawArrays(GL_POLYGON, 0, 4);

    glDisableClientState(GL_COLOR_ARRAY);

    glColor3f(0.0f, 0.4f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, planters);
    glDrawArrays(GL_QUADS, 0, 64);

    GLfloat window_colors[WINDOW_COUNT * 4 * 3];

    for (int i = 0; i < WINDOW_COUNT * 4; i++) {
        if (windows_lit) {
            window_colors[i * 3 + 0] = 1.0f;
            window_colors[i * 3 + 1] = 1.0f;
            window_colors[i * 3 + 2] = 0.6f;
        } else {
            window_colors[i * 3 + 0] = 0.3f;
            window_colors[i * 3 + 1] = 0.5f;
            window_colors[i * 3 + 2] = 0.8f;
        }
    }

    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, building_windows);
    glColorPointer(3, GL_FLOAT, 0, window_colors);
    glDrawArrays(GL_QUADS, 0, WINDOW_COUNT * 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glColor3f(50 / 256.0f, 100 / 256.0f, 50 / 256.0f);
    draw_text("FEU", -0.59f, 0.73f, 0.0006f, 0.0005f, 6.0f);
    draw_text("TECH", -0.325f, 0.73f, 0.0006f, 0.0005f, 6.0f);

    draw_feu_tech_logo(-0.38f, 0.75f);
}

float wrap_x(float x) {
    if (x > 1.3f) {
        return -1.3f;
    }

    if (x < -1.3f) {
        return 1.3f;
    }

    return x;
}

void draw_cloud(float x, float y) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0f, 1.0f, 1.0f, 0.90f);
    draw_circle_vertex_array(x, y, 0.09f);
    draw_circle_vertex_array(x + 0.10f, y + 0.03f, 0.09f * 1.15f);
    draw_circle_vertex_array(x + 0.22f, y, 0.09f);
    draw_circle_vertex_array(x - 0.05f, y + 0.02f, 0.09f * 0.85f);
    draw_circle_vertex_array(x + 0.30f, y + 0.01f, 0.09f * 0.80f);

    glColor4f(1.0f, 1.0f, 1.0f, 0.50f);
    draw_circle_vertex_array(x + 0.12f, y - 0.03f, 0.09f * 1.3f);

    glDisable(GL_BLEND);
}

void draw_stars() {
    static std::vector<GLfloat> star_vertices;

    if (star_vertices.empty()) {
        star_vertices.reserve(140);

        for (int i = 0; i < 70; i++) {
            float x = (std::rand() % 200 - 100) / 100.0f;
            float y = (std::rand() % 200 - 100) / 100.0f;

            star_vertices.push_back(x);
            star_vertices.push_back(y);
        }
    }

    glPointSize(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, star_vertices.data());
    glDrawArrays(GL_POINTS, 0, static_cast<int>(star_vertices.size() / 2));
    glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_streetlight() {
    float base_x = -0.95f;
    float base_y = -0.99f;
    float pole_width = 0.04f;
    float pole_height = 0.8f;

    GLfloat pole_vertices[] = {
        base_x, base_y,
        base_x + pole_width, base_y,
        base_x + pole_width, base_y + pole_height,
        base_x, base_y + pole_height
    };

    glColor3f(0.05f, 0.05f, 0.05f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, pole_vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    std::vector<GLfloat> arm_vertices;

    for (float t = 0.0f; t <= 1.0f; t += 0.05f) {
        float x = base_x + pole_width / 2.0f + t * 0.25f;
        float y = base_y + pole_height + 0.05f * std::sin(t * PI);

        arm_vertices.push_back(x);
        arm_vertices.push_back(y);
    }

    glLineWidth(5.0f);
    glColor3f(0.05f, 0.05f, 0.05f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, arm_vertices.data());
    glDrawArrays(GL_LINE_STRIP, 0, static_cast<int>(arm_vertices.size() / 2));
    glDisableClientState(GL_VERTEX_ARRAY);

    float lamp_x = base_x + 0.25f;
    float lamp_y = base_y + pole_height + 0.05f * std::sin(1.0f);

    std::vector<GLfloat> lamp_vertices;

    for (int i = 0; i < 360; i += 10) {
        float angle = i * PI / 180.0f;

        lamp_vertices.push_back(lamp_x + std::cos(angle) * 0.05f);
        lamp_vertices.push_back(lamp_y + std::sin(angle) * 0.03f);
    }

    glColor3f(0.1f, 0.1f, 0.1f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lamp_vertices.data());
    glDrawArrays(GL_POLYGON, 0, static_cast<int>(lamp_vertices.size() / 2));
    glDisableClientState(GL_VERTEX_ARRAY);

    if (streetlight_on) {
        GLfloat light_vertices[] = {
            lamp_x, lamp_y - 0.01f,
            lamp_x - 0.08f, -1.0f,
            lamp_x + 0.08f, -1.0f
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1.0f, 1.0f, 0.6f, 0.25f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, light_vertices);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_VERTEX_ARRAY);

        glDisable(GL_BLEND);

        glColor3f(1.0f, 1.0f, 0.8f);
        draw_circle_vertex_array(lamp_x, lamp_y, 0.02f);
    }
}

void draw_road() {
    float road_top = -0.5f;
    float road_bottom = -0.99f;
    float road_height = road_top - road_bottom;

    draw_rectangle(-1.0f, road_bottom, 2.0f, road_height, 0.2f, 0.2f, 0.2f);

    float center_y = (road_top + road_bottom) / 2.0f;
    float dash_length = 0.06f;
    float gap = 0.04f;
    float x = -0.95f;

    while (x < 0.95f) {
        float next_x = x + dash_length;

        if (next_x > 0.95f) {
            next_x = 0.95f;
        }

        draw_rectangle(x, center_y - 0.01f, next_x - x, 0.02f, 1.0f, 1.0f, 1.0f);
        x += dash_length + gap;
    }
}

void draw_jeepney(float x_offset) {
    float jeep_y = -0.65f;
    float scale_x = 0.6f;

    draw_rectangle(-0.65f * scale_x + x_offset, 0.15f + jeep_y, 1.0f * scale_x, 0.1f, 0.6f, 0.6f, 0.3f);
    draw_rectangle(-0.55f * scale_x + x_offset, -0.05f + jeep_y, 0.65f * scale_x, 0.2f, 0.6f, 0.1f, 0.1f);
    draw_rectangle(0.1f * scale_x + x_offset, -0.05f + jeep_y, 0.2f * scale_x, 0.15f, 0.6f, 0.1f, 0.1f);
    draw_rectangle(0.25f * scale_x + x_offset, -0.05f + jeep_y, 0.4f * scale_x, 0.2f, 0.6f, 0.1f, 0.1f);

    draw_rectangle(0.2f * scale_x + x_offset, 0.05f + jeep_y, 0.05f * scale_x, 0.01f, 0.4f, 0.4f, 0.4f);
    draw_rectangle(0.15f * scale_x + x_offset, 0.04f + jeep_y, 0.05f * scale_x, 0.04f, 0.5f, 0.5f, 0.5f);

    float window_x = -0.45f * scale_x + x_offset;
    float window_width = 0.12f * scale_x;

    for (int i = 0; i < 3; i++) {
        draw_rectangle(window_x, jeep_y, window_width, 0.1f, 0.05f, 0.1f, 0.3f);
        window_x += 0.15f * scale_x;
    }

    draw_rectangle(0.25f * scale_x + x_offset, 0.1f + jeep_y, 0.03f * scale_x, 0.15f, 0.6f, 0.6f, 0.3f);

    draw_circle(-0.25f * scale_x + x_offset, -0.05f + jeep_y, 0.07f, 30, 0.1f, 0.1f, 0.1f);
    draw_circle(0.5f * scale_x + x_offset, -0.05f + jeep_y, 0.07f, 30, 0.1f, 0.1f, 0.1f);
    draw_circle(-0.25f * scale_x + x_offset, -0.05f + jeep_y, 0.03f, 20, 0.8f, 0.8f, 0.8f);
    draw_circle(0.5f * scale_x + x_offset, -0.05f + jeep_y, 0.03f, 20, 0.8f, 0.8f, 0.8f);

    draw_rectangle(-0.55f * scale_x + x_offset, -0.07f + jeep_y, 0.05f * scale_x, 0.02f, 0.3f, 0.3f, 0.3f);
    draw_rectangle(0.65f * scale_x + x_offset, -0.07f + jeep_y, 0.05f * scale_x, 0.02f, 0.3f, 0.3f, 0.3f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat lower_headlight[] = {
        0.65f * scale_x + x_offset, 0.0f + jeep_y,
        0.65f * scale_x + x_offset + 0.25f, jeep_y - 0.05f,
        0.65f * scale_x + x_offset + 0.25f, jeep_y + 0.05f
    };

    glColor4f(1.0f, 1.0f, 0.6f, 0.2f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lower_headlight);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    GLfloat upper_headlight[] = {
        0.65f * scale_x + x_offset, 0.1f + jeep_y,
        0.65f * scale_x + x_offset + 0.25f, jeep_y + 0.05f,
        0.65f * scale_x + x_offset + 0.25f, jeep_y + 0.15f
    };

    glColor4f(1.0f, 1.0f, 0.6f, 0.2f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, upper_headlight);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_BLEND);

    draw_circle(0.65f * scale_x + x_offset, 0.0f + jeep_y, 0.02f, 20, 1.0f, 1.0f, 0.8f);
    draw_circle(0.65f * scale_x + x_offset, 0.1f + jeep_y, 0.02f, 20, 1.0f, 1.0f, 0.8f);
}

void draw_paresan(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    draw_quad(paresan_right_border, 0.25f, 0.25f, 0.25f, true);
    draw_quad(paresan_bottom_border, 0.25f, 0.25f, 0.25f, true);
    draw_quad(paresan_middle_border_1, 0.25f, 0.25f, 0.25f, true);
    draw_quad(paresan_left_border, 0.25f, 0.25f, 0.25f, true);
    draw_quad(paresan_middle_border_2, 0.25f, 0.25f, 0.25f, true);
    draw_quad(paresan_inside, 0.5f, 0.5f, 0.5f, false);

    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.2f, 0.098f, 0.0f);
    draw_text_small("PARESAN", 0.82f, 0.32f, 0.00028f, 2.0f);

    glPopMatrix();
}

void draw_side_building(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    draw_quad(side_building_bottom_wall, 0.25f, 0.25f, 0.25f, true);
    draw_quad(side_building_separator, 0.25f, 0.25f, 0.25f, true);
    draw_quad(side_building_top_wall, 0.5f, 0.5f, 0.5f, true);
    draw_quad(side_building_roof, 0.25f, 0.25f, 0.25f, true);
    draw_quad(side_building_door, 0.5f, 0.5f, 0.5f, true);
    draw_quad(side_building_pillar_1, 0.25f, 0.25f, 0.25f, true);
    draw_quad(side_building_pillar_2, 0.25f, 0.25f, 0.25f, true);
    draw_quad(side_building_pillar_3, 0.25f, 0.25f, 0.25f, true);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(0.02f, 0.02f, 0.08f);
    glVertex2f(-1.0f, -1.0f);

    glColor3f(0.05f, 0.05f, 0.18f);
    glVertex2f(-1.0f, 1.0f);

    glColor3f(0.02f, 0.02f, 0.08f);
    glVertex2f(1.0f, 1.0f);

    glColor3f(0.01f, 0.01f, 0.04f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    draw_stars();
    draw_feu_tech_building();
    draw_road();

    draw_cloud(cloud_1_x, 0.55f);
    draw_cloud(cloud_2_x, 0.75f);

    draw_paresan(paresan_x, paresan_y, paresan_scale);
    draw_side_building(side_building_x, side_building_y, side_building_scale);

    draw_jeepney(jeepney_x);
    draw_streetlight();

    glutSwapBuffers();
}

void timer(int) {
    jeepney_x += jeepney_speed;

    float jeepney_width = 0.9f;

    if (jeepney_x > 1.0f + jeepney_width / 2.0f) {
        jeepney_x = -1.0f - jeepney_width / 2.0f;
    }

    cloud_1_x += cloud_speed;
    cloud_2_x += cloud_speed * 0.6f;

    cloud_1_x = wrap_x(cloud_1_x);
    cloud_2_x = wrap_x(cloud_2_x);

    glutPostRedisplay();
    glutTimerFunc(TIMER_INTERVAL_MS, timer, 0);
}

void special_keys(int key, int, int) {
    if (cloud_speed < 0.001f) {
        cloud_speed = 0.001f;
    }

    if (key == GLUT_KEY_LEFT) {
        cloud_1_x -= cloud_speed * 10.0f;
        cloud_2_x -= cloud_speed * 10.0f;
    }

    if (key == GLUT_KEY_RIGHT) {
        cloud_1_x += cloud_speed * 10.0f;
        cloud_2_x += cloud_speed * 10.0f;
    }

    cloud_1_x = wrap_x(cloud_1_x);
    cloud_2_x = wrap_x(cloud_2_x);
    cloud_speed *= 0.95f;

    glutPostRedisplay();
}

void mouse_handler(int button, int state, int, int) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        streetlight_on = !streetlight_on;
        glutPostRedisplay();
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        windows_lit = !windows_lit;
        glutPostRedisplay();
    }
}

void initialize_graphics() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Computer Graphics Final Project - Night City Scene");
    glutFullScreen();

    GLenum error = glewInit();

    if (error != GLEW_OK) {
        std::fprintf(stderr, "Warning: glewInit failed: %s\n", glewGetErrorString(error));
    }

    initialize_graphics();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(special_keys);
    glutMouseFunc(mouse_handler);

    glutMainLoop();

    return 0;
}