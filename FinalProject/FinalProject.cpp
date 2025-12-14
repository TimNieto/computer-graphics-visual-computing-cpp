
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;


float paresanScale = 1.5f;
float paresanX = -0.5f;
float paresanY = -0.5f;

float randbldgX = -0.98f;
float randbldgY = -0.5f;
float randbldgScale = 1.8f;

// -------------------- Shared globals --------------------
float nowTime = 0.0f;

bool windowsLit = false; // false = normal, true = lit

// --- Vertex arrays for TechBuild1 (copied from Lab7) ---
GLfloat TechBuild1[] = {
    // Left tall block
    -0.6f, 0.85f, 0.0f,
    -0.12f, 0.85f, 0.0f,
    -0.12f, -0.5f, 0.0f,

    -0.6f, 0.85f, 0.0f,
    -0.1f, -0.5f, 0.0f,
    -0.6f, -0.5f, 0.0f,

    // Right short block (notch wide enough for text)
    -0.55f, 0.65f, 0.0f,
     0.6f, 0.65f, 0.0f,
     0.6f, -0.5f, 0.0f,

    -0.55f,0.65f,0.0f,
     0.6f,-0.5f,0.0f,
     -0.2f,-0.5f,0.0f
};

GLfloat TechBuild1C[] = {
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

GLfloat TechBuild2[] = {
    -0.6f, -0.5f, 0.0f,
     0.6f, -0.5f, 0.0f,
     0.6f, -0.15f, 0.0f,
     -0.6f, -0.15f, 0.0f,
};

GLfloat TechBuild2C[] = {
   30 / 256.0f, 30 / 256.0f, 30 / 256.0f,
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f,
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f,
    30 / 256.0f, 30 / 256.0f, 30 / 256.0f,

};

GLfloat TechBuild3[] = {
    0.6f, -0.5f, 0.0f,
     0.45f, -0.38f, 0.0f,
     0.30f, -0.38f, 0.0f,
     0.30f, -0.5f, 0.0f,
};

GLfloat windows[] = {

    -0.55f, 0.63f, 0.0f,  -0.35f, 0.63f, 0.0f,
    -0.35f, 0.43f, 0.0f,  -0.55f, 0.43f, 0.0f,  // Window 1

    -0.33f, 0.63f, 0.0f,  -0.13f, 0.63f, 0.0f,
    -0.13f, 0.43f, 0.0f,  -0.33f, 0.43f, 0.0f,  // Window 2

    0.15f, 0.63f, 0.0f,   0.35f, 0.63f, 0.0f,
    0.35f, 0.43f, 0.0f,   0.15f, 0.43f, 0.0f,   // Window 3

    0.37f, 0.63f, 0.0f,   0.57f, 0.63f, 0.0f,
    0.57f, 0.43f, 0.0f,   0.37f, 0.43f, 0.0f,   // Window 4

    // Row 2
    -0.55f, 0.41f, 0.0f,  -0.35f, 0.41f, 0.0f,
    -0.35f, 0.21f, 0.0f,  -0.55f, 0.21f, 0.0f,  // Window 5

    -0.33f, 0.41f, 0.0f,  -0.13f, 0.41f, 0.0f,
    -0.13f, 0.21f, 0.0f,  -0.33f, 0.21f, 0.0f,  // Window 6

    0.15f, 0.41f, 0.0f,   0.35f, 0.41f, 0.0f,
    0.35f, 0.21f, 0.0f,   0.15f, 0.21f, 0.0f,   // Window 7

    0.37f, 0.41f, 0.0f,   0.57f, 0.41f, 0.0f,
    0.57f, 0.21f, 0.0f,   0.37f, 0.21f, 0.0f,   // Window 8

    // Row 3
    -0.55f, 0.19f, 0.0f,  -0.35f, 0.19f, 0.0f,
    -0.35f, -0.01f, 0.0f, -0.55f, -0.01f, 0.0f, // Window 9

    -0.33f, 0.19f, 0.0f,  -0.13f, 0.19f, 0.0f,
    -0.13f, -0.01f, 0.0f, -0.33f, -0.01f, 0.0f, // Window 10

    0.15f, 0.19f, 0.0f,   0.35f, 0.19f, 0.0f,
    0.35f, -0.01f, 0.0f,  0.15f, -0.01f, 0.0f,  // Window 11

    0.37f, 0.19f, 0.0f,   0.57f, 0.19f, 0.0f,
    0.57f, -0.01f, 0.0f,  0.37f, -0.01f, 0.0f   // Window 12
};




GLfloat planterColors[] = {
    // 12 quads × 4 vertices × RGB = 144 floats
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,

    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,
    0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f,  0.0f, 0.4f, 0.0f
};



GLfloat planters[] = {
    // Bottom row (y ~ -0.35 to -0.30)
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
     0.06f, -0.30f, 0.0f,  -0.02f, -0.30f, 0.0f,

     0.08f, -0.35f, 0.0f,   0.16f, -0.35f, 0.0f,
     0.16f, -0.30f, 0.0f,   0.08f, -0.30f, 0.0f,

     0.18f, -0.35f, 0.0f,   0.26f, -0.35f, 0.0f,
     0.26f, -0.30f, 0.0f,   0.18f, -0.30f, 0.0f,

     // Top row (y ~ -0.25 to -0.20)
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
      0.06f, -0.20f, 0.0f,  -0.02f, -0.20f, 0.0f,

      0.08f, -0.25f, 0.0f,   0.16f, -0.25f, 0.0f,
      0.16f, -0.20f, 0.0f,   0.08f, -0.20f, 0.0f,

      0.18f, -0.25f, 0.0f,   0.26f, -0.25f, 0.0f,
      0.26f, -0.20f, 0.0f,   0.18f, -0.20f, 0.0f
};


void drawText(const char* text, float x, float y, float scaleX, float scaleY, float lineWidth) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scaleX, scaleY, 1.0f); // separate X and Y scale
    glLineWidth(lineWidth);

    for (const char* c = text; *c != '\0'; c++) {
        // draw bold by drawing several offsets briefly
        for (float dx = -0.003f; dx <= 0.003f; dx += 0.003f) {
            for (float dy = -0.003f; dy <= 0.003f; dy += 0.003f) {
                glPushMatrix();
                glTranslatef(dx, dy, 0);
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
                glPopMatrix();
            }
        }
        glTranslatef(glutStrokeWidth(GLUT_STROKE_ROMAN, *c), 0, 0);
    }

    glPopMatrix();
}

void drawTechBuild1() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Draw main building
    glVertexPointer(3, GL_FLOAT, 0, TechBuild1);
    glColorPointer(3, GL_FLOAT, 0, TechBuild1C);
    glDrawArrays(GL_TRIANGLES, 0, 12);

    glVertexPointer(3, GL_FLOAT, 0, TechBuild2);
    glColorPointer(3, GL_FLOAT, 0, TechBuild2C);
    glDrawArrays(GL_QUADS, 0, 4);

    glVertexPointer(3, GL_FLOAT, 0, TechBuild3);
    glColorPointer(3, GL_FLOAT, 0, TechBuild1C);
    glDrawArrays(GL_POLYGON, 0, 4);

    // Draw planters (dark green)
    glVertexPointer(3, GL_FLOAT, 0, planters);
    glColorPointer(3, GL_FLOAT, 0, planterColors);
    glDrawArrays(GL_QUADS, 0, 64); // 8 quads × 4 vertices each = 32



    GLfloat dynamicWindowsC[16 * 4 * 3]; // 16 windows × 4 vertices × 3 colors
    for (int i = 0; i < 16 * 4; i++) {
        if (windowsLit) {
            dynamicWindowsC[i * 3 + 0] = 1.0f;   // R
            dynamicWindowsC[i * 3 + 1] = 1.0f;   // G
            dynamicWindowsC[i * 3 + 2] = 0.6f;   // B (yellowish lit color)
        }
        else {
            dynamicWindowsC[i * 3 + 0] = 0.3f;   // R
            dynamicWindowsC[i * 3 + 1] = 0.5f;   // G
            dynamicWindowsC[i * 3 + 2] = 0.8f;   // B (default)
        }
    }



    glVertexPointer(3, GL_FLOAT, 0, windows);
    glColorPointer(3, GL_FLOAT, 0, dynamicWindowsC);
    glDrawArrays(GL_QUADS, 0, 16 * 4); // 16 quads * 4 vertices

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Draw FEU TECH text
    glColor3f(50 / 256.0f, 100 / 256.0f, 50 / 256.0f);
    drawText("FEU", -0.59f, 0.73f, 0.0006f, 0.0005f, 6.0f);
    drawText("TECH", -0.325f, 0.73f, 0.0006f, 0.0005f, 6.0f);

    // --- Logo --- 
    const int segments = 50;
    float cx = -0.38f;  // centered between FEU and TECH
    float cy = 0.75f;    // slightly above baseline of text
    float radius = 0.045f;

    std::vector<GLfloat> logoVertices(segments * 3);
    std::vector<GLfloat> logoOutline(segments * 3);

    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = radius * cosf(theta) + cx;
        float y = radius * sinf(theta) + cy;

        logoVertices[i * 3 + 0] = x;
        logoVertices[i * 3 + 1] = y;
        logoVertices[i * 3 + 2] = 0.0f;

        logoOutline[i * 3 + 0] = x;
        logoOutline[i * 3 + 1] = y;
        logoOutline[i * 3 + 2] = 0.0f;
    }

    // Draw yellow filled circle
    glColor3f(1.0f, 1.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, logoVertices.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Draw green outline
    glColor3f(0.0f, 0.6f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, logoOutline.data());
    glDrawArrays(GL_LINE_LOOP, 0, segments);
    glDisableClientState(GL_VERTEX_ARRAY);

    // --- Torch inside the logo ---
    GLfloat torchVertices[] = {
        // Torch handle (quad)
        cx - 0.008f, cy - 0.015f, 0.0f,
        cx + 0.008f, cy - 0.015f, 0.0f,
        cx + 0.008f, cy + 0.01f, 0.0f,
        cx - 0.008f, cy + 0.01f, 0.0f,

        // Torch flame (triangle)
        cx, cy + 0.025f, 0.0f,
        cx - 0.01f, cy + 0.01f, 0.0f,
        cx + 0.01f, cy + 0.01f, 0.0f
    };

    GLfloat torchColors[] = {
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
    glVertexPointer(3, GL_FLOAT, 0, torchVertices);
    glColorPointer(3, GL_FLOAT, 0, torchColors);
    glDrawArrays(GL_QUADS, 0, 4);    // handle
    glDrawArrays(GL_TRIANGLES, 4, 3); // flame
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

float cloud1X = -0.5f;
float cloud2X = 0.2f;
bool lightOn = true; // streetlight toggle
float cloudSpeed = 0.005f; // cloud movement per frame (smaller)

float wrapX(float x) {
    if (x > 1.3f) return -1.3f;
    if (x < -1.3f) return 1.3f;
    return x;
}

// Draw smooth circle using vertex array
void drawCircleVA(float x, float y, float r) {
    std::vector<GLfloat> vertices;
    vertices.reserve(362);
    // Center for triangle fan
    vertices.push_back(x);
    vertices.push_back(y);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1415926f / 180.0f;
        vertices.push_back(x + cosf(angle) * r);
        vertices.push_back(y + sinf(angle) * r);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, (int)vertices.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Draw cloud using vertex array
void drawCloudVA(float x, float y) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0, 1.0, 1.0, 0.90f);
    drawCircleVA(x, y, 0.09f);
    drawCircleVA(x + 0.10f, y + 0.03f, 0.09f * 1.15f);
    drawCircleVA(x + 0.22f, y, 0.09f);
    drawCircleVA(x - 0.05f, y + 0.02f, 0.09f * 0.85f);
    drawCircleVA(x + 0.30f, y + 0.01f, 0.09f * 0.80f);

    glColor4f(1.0, 1.0, 1.0, 0.50f);
    drawCircleVA(x + 0.12f, y - 0.03f, 0.09f * 1.3f);

    glDisable(GL_BLEND);
}

// Draw stars using vertex array
void drawStarsVA() {
    static std::vector<GLfloat> starVerts;
    if (starVerts.empty()) {
        starVerts.reserve(140);
        for (int i = 0; i < 70; i++) {
            float x = (rand() % 200 - 100) / 100.0f;
            float y = (rand() % 200 - 100) / 100.0f;
            starVerts.push_back(x);
            starVerts.push_back(y);
        }
    }

    glPointSize(2.0f);
    glColor3f(1, 1, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, starVerts.data());
    glDrawArrays(GL_POINTS, 0, (int)starVerts.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Draw streetlight using vertex arrays
void drawStreetLightVA() {
    float baseX = -0.95f;
    float baseY = -0.99f;
    float poleWidth = 0.04f;
    float poleHeight = 0.8;

    // --- Darker pole ---
    GLfloat poleVerts[] = {
        baseX, baseY,
        baseX + poleWidth, baseY,
        baseX + poleWidth, baseY + poleHeight,
        baseX, baseY + poleHeight
    };
    glColor3f(0.05f, 0.05f, 0.05f);  // Dark gray / almost black
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, poleVerts);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    // --- Darker curved arm ---
    std::vector<GLfloat> armVerts;
    for (float t = 0; t <= 1.0; t += 0.05f) {
        float x = baseX + poleWidth / 2 + t * 0.25f;
        float y = baseY + poleHeight + 0.05f * sinf(t * 3.14f);
        armVerts.push_back(x);
        armVerts.push_back(y);
    }
    glLineWidth(5.0f);
    glColor3f(0.05f, 0.05f, 0.05f);  // Darker gray
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, armVerts.data());
    glDrawArrays(GL_LINE_STRIP, 0, (int)armVerts.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);

    // --- Darker lamp head (polygon) ---
    std::vector<GLfloat> lampVerts;
    float lampX = baseX + 0.25f;
    float lampY = baseY + poleHeight + 0.05f * sinf(1.0f);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.1415926f / 180.0f;
        lampVerts.push_back(lampX + cosf(angle) * 0.05f);
        lampVerts.push_back(lampY + sinf(angle) * 0.03f);
    }
    glColor3f(0.1f, 0.1f, 0.1f); // Darker gray
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lampVerts.data());
    glDrawArrays(GL_POLYGON, 0, (int)lampVerts.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);

    // --- Light beam remains semi-transparent ---
    if (lightOn) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLfloat lightVerts[] = {
            lampX, lampY - 0.01f,
            lampX - 0.08f, -1.0f,
            lampX + 0.08f, -1.0f
        };
        glColor4f(1.0f, 1.0f, 0.6f, 0.25f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, lightVerts);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_BLEND);

        // Bulb center
        glColor3f(1.0f, 1.0f, 0.8f);
        drawCircleVA(lampX, lampY, 0.02f);
    }
}

float xOffset = -1.2f; // jeepney start offscreen left
float speed = 0.003f;  // movement per timer tick

// Draw rectangle
void drawRect(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Draw circle (immediate mode used for rims; acceptable for small shapes)
void drawCircle(float cx, float cy, float radius, int segments, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Draw backward-starting large left-facing triangle inside headlight
void drawTriangleBackward(float cx, float cy, float /*circleRadius*/, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    float startX = cx - 0.0f; // relative
    glVertex2f(startX + width, cy - height / 2); // bottom right
    glVertex2f(startX + width, cy + height / 2); // top right
    glVertex2f(startX, cy);                     // left tip
    glEnd();
}

// Draw road (dark gray)
void drawRoad() {
    float roadTop = -0.5f;    // lowered from -0.1f
    float roadBottom = -.99f; // lowered from -0.4f
    float roadHeight = roadTop - roadBottom;

    // Road background (dark gray)
    drawRect(-1.0f, roadBottom, 2.0f, roadHeight, 0.2f, 0.2f, 0.2f);

    // White dashed center line
    float centerY = (roadTop + roadBottom) / 2.0f;
    float dashLength = 0.06f;
    float gap = 0.04f;
    float x = -0.95f;
    while (x < 0.95f) {
        float nextX = x + dashLength;
        if (nextX > 0.95f) nextX = 0.95f;
        drawRect(x, centerY - 0.01f, nextX - x, 0.02f, 1.0f, 1.0f, 1.0f);
        x += dashLength + gap;
    }
}

// Draw jeepney
void drawJeepney(float xOffset) {
    float jeepY = -0.65f; // below building
    float scaleX = 0.6f;   // shorter jeepney

    // Muted colors for night
    float roofR = 0.6f, roofG = 0.6f, roofB = 0.3f;     // dull yellow
    float bodyR = 0.6f, bodyG = 0.1f, bodyB = 0.1f;     // muted red
    float stepR = 0.6f, stepG = 0.1f, stepB = 0.1f;
    float noseR = 0.6f, noseG = 0.1f, noseB = 0.1f;

    // Roof
    drawRect(-0.65f * scaleX + xOffset, 0.15f + jeepY, 1.0f * scaleX, 0.1f, roofR, roofG, roofB);
    // Body
    drawRect(-0.55f * scaleX + xOffset, -0.05f + jeepY, 0.65f * scaleX, 0.2f, bodyR, bodyG, bodyB);
    // Rear step
    drawRect(0.1f * scaleX + xOffset, -0.05f + jeepY, 0.2f * scaleX, 0.15f, stepR, stepG, stepB);
    // Front nose / driver cabin
    drawRect(0.25f * scaleX + xOffset, -0.05f + jeepY, 0.4f * scaleX, 0.2f, noseR, noseG, noseB);

    // Driver's mirrors (muted gray)
    drawRect(0.2f * scaleX + xOffset, 0.05f + jeepY, 0.05f * scaleX, 0.01f, 0.4f, 0.4f, 0.4f);
    drawRect(0.15f * scaleX + xOffset, 0.04f + jeepY, 0.05f * scaleX, 0.04f, 0.5f, 0.5f, 0.5f);

    // Windows (dark blue)
    float winX = -0.45f * scaleX + xOffset;
    float winWidth = 0.12f * scaleX;
    float winHeight = 0.1f;
    for (int i = 0; i < 3; i++) {
        drawRect(winX, 0.0f + jeepY, winWidth, winHeight, 0.05f, 0.1f, 0.3f);
        winX += 0.15f * scaleX;
    }

    // Rear placard (muted yellow)
    drawRect(0.25f * scaleX + xOffset, 0.1f + jeepY, 0.03f * scaleX, 0.15f, 0.6f, 0.6f, 0.3f);

    // Wheels (dark gray)
    drawCircle(-0.25f * scaleX + xOffset, -0.05f + jeepY, 0.07f, 30, 0.1f, 0.1f, 0.1f);
    drawCircle(0.5f * scaleX + xOffset, -0.05f + jeepY, 0.07f, 30, 0.1f, 0.1f, 0.1f);
    // White rims
    drawCircle(-0.25f * scaleX + xOffset, -0.05f + jeepY, 0.03f, 20, 0.8f, 0.8f, 0.8f);
    drawCircle(0.5f * scaleX + xOffset, -0.05f + jeepY, 0.03f, 20, 0.8f, 0.8f, 0.8f);

    // Bumpers (dark gray)
    drawRect(-0.55f * scaleX + xOffset, -0.07f + jeepY, 0.05f * scaleX, 0.02f, 0.3f, 0.3f, 0.3f);
    drawRect(0.65f * scaleX + xOffset, -0.07f + jeepY, 0.05f * scaleX, 0.02f, 0.3f, 0.3f, 0.3f);

    // Headlights (slightly transparent)
    float lightR = 0.03f;
    float triangleWidth = 0.24f * scaleX;
    float triangleHeight = 0.32f;


    // Enable blending for headlights
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Headlight 1 (front, lower)
    GLfloat lightVerts1[] = {
        0.65f * scaleX + xOffset, 0.0f + jeepY,             // back/base at jeep
        0.65f * scaleX + xOffset + 0.25f, jeepY - 0.05f,   // top forward
        0.65f * scaleX + xOffset + 0.25f, jeepY + 0.05f    // bottom forward
    };
    glColor4f(1.0f, 1.0f, 0.6f, 0.2f); // 20% opacity
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lightVerts1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Headlight 2 (front, upper)
    GLfloat lightVerts2[] = {
        0.65f * scaleX + xOffset, 0.1f + jeepY,             // back/base at jeep
        0.65f * scaleX + xOffset + 0.25f, jeepY + 0.05f,   // top forward
        0.65f * scaleX + xOffset + 0.25f, jeepY + 0.15f    // bottom forward
    };
    glColor4f(1.0f, 1.0f, 0.6f, 0.2f); // 20% opacity
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lightVerts2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_BLEND);

    drawCircle(0.65f * scaleX + xOffset, 0.0f + jeepY, 0.02f, 20, 1.0f, 1.0f, 0.8f);
    drawCircle(0.65f * scaleX + xOffset, 0.1f + jeepY, 0.02f, 20, 1.0f, 1.0f, 0.8f);
}


// --- PARESAN ---
// right border
GLfloat rightBorder[] = {
    1.0f,0.0f,  1.0f,0.375f,  0.9875f,0.375f, 0.9875f,0.0f
};

// bottom border
GLfloat bottomBorder[] = {
    0.9875f,0.0f, 0.9875f,0.125f, 0.8125f,0.125f, 0.8125f,0.0f
};

// middle border top
GLfloat midBorder1[] = {
    0.9875f,0.2917f, 0.9875f,0.375f, 0.8125f,0.375f, 0.8125f,0.2917f
};

// left border
GLfloat leftBorder[] = {
    0.8125f,0.0f, 0.8125f,0.375f, 0.8f,0.375f,  0.8f,0.0f
};

// middle border upper
GLfloat midBorder2[] = {
    1.0f,0.375f, 1.0f,0.4f, 0.8f,0.4f, 0.8f,0.375f
};

// inside fill
GLfloat inside[] = {
    0.9875f,0.125f, 0.9875f,0.2917f, 0.8125f,0.2917f, 0.8125f,0.125f
};


// --- RANDBLDG ---
// bottom wall
GLfloat bottomWall[] = {
    0.19375f,0.0f, 0.19375f,0.2083f, 0.00625f,0.2083f, 0.00625f,0.0f
};

// level separation
GLfloat separation[] = {
    0.2f,0.2083f, 0.2f,0.2583f, 0.0f,0.2583f, 0.0f,0.2083f
};

// top wall
GLfloat topWall[] = {
    0.19375f,0.2583f, 0.19375f,0.4667f, 0.00625f,0.4667f, 0.00625f,0.2583f
};

// roof
GLfloat roof[] = {
    0.2f,0.4667f, 0.2f,0.5167f, 0.0f,0.5167f, 0.0f,0.4667f
};

// door
GLfloat door[] = {
    0.175f,0.0f, 0.175f,0.1667f, 0.025f,0.1667f, 0.025f,0.0f
};

// pillars
GLfloat pillar1[] = {
    0.05f,0.2583f, 0.05f,0.4667f, 0.025f,0.4667f, 0.025f,0.2583f
};

GLfloat pillar2[] = {
    0.1125f,0.2583f, 0.1125f,0.4667f, 0.0875f,0.4667f, 0.0875f,0.2583f
};

GLfloat pillar3[] = {
    0.175f,0.2583f, 0.175f,0.4667f, 0.15f,0.4667f, 0.15f,0.2583f
};

// =====================================================
//                DRAW HELPERS
// =====================================================

void drawQuad(GLfloat* verts, float r, float g, float b, bool outline) {
    glColor3f(r, g, b);
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glDrawArrays(GL_POLYGON, 0, 4);

    if (outline) {
        glColor3f(0, 0, 0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

void drawTextSmall(const char* text, float x, float y, float scale, float spacing) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, scale);
    for (const char* c = text; *c; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
        glTranslatef(spacing, 0, 0);
    }
    glPopMatrix();
}

// =====================================================
//                PARESAN DRAW (with transform)
// =====================================================

void paresan(float tx, float ty, float sc) {
    glPushMatrix();
    // We move them so their origin (0,0) becomes (tx,ty) and scale by sc.
    glTranslatef(tx, ty, 0.0f);
    glScalef(sc, sc, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    drawQuad(rightBorder, 0.25f, 0.25f, 0.25f, true);
    drawQuad(bottomBorder, 0.25f, 0.25f, 0.25f, true);
    drawQuad(midBorder1, 0.25f, 0.25f, 0.25f, true);
    drawQuad(leftBorder, 0.25f, 0.25f, 0.25f, true);
    drawQuad(midBorder2, 0.25f, 0.25f, 0.25f, true);
    drawQuad(inside, 0.5f, 0.5f, 0.5f, false);

    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.2f, 0.098f, 0.0f);
    drawTextSmall("PARESAN", 0.82f, 0.32f, 0.00028f, 2.0f);
    glPopMatrix();
}

// =====================================================
//                RAND BUILDING DRAW (with transform)
// =====================================================

void randbldg(float tx, float ty, float sc) {
    glPushMatrix();
    glTranslatef(tx, ty, 0.0f);
    glScalef(sc, sc, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    drawQuad(bottomWall, 0.25f, 0.25f, 0.25f, true);
    drawQuad(separation, 0.25f, 0.25f, 0.25f, true);
    drawQuad(topWall, 0.5f, 0.5f, 0.5f, true);
    drawQuad(roof, 0.25f, 0.25f, 0.25f, true);
    drawQuad(door, 0.5f, 0.5f, 0.5f, true);

    drawQuad(pillar1, 0.25f, 0.25f, 0.25f, true);
    drawQuad(pillar2, 0.25f, 0.25f, 0.25f, true);
    drawQuad(pillar3, 0.25f, 0.25f, 0.25f, true);

    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

// -------------------- Display, input, and animation --------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(0.02f, 0.02f, 0.08f); glVertex2f(-1, -1);
    glColor3f(0.05f, 0.05f, 0.18f); glVertex2f(-1, 1);
    glColor3f(0.02f, 0.02f, 0.08f); glVertex2f(1, 1);
    glColor3f(0.01f, 0.01f, 0.04f); glVertex2f(1, -1);
    glEnd();

    // Sky elements
    drawStarsVA();

    // Tech building (center)
    drawTechBuild1();

    // Road and moving jeepney in foreground (below building)
    drawRoad();




    //clouds
    drawCloudVA(cloud1X, 0.55f);
    drawCloudVA(cloud2X, 0.75f);

    // User-placed buildings (PARESAN and RANDBLDG)
    // We use the editable variables at the top: paresanX, paresanY, paresanScale, etc.
    paresan(paresanX, paresanY, paresanScale);
    randbldg(randbldgX, randbldgY, randbldgScale);

    drawJeepney(xOffset);

    // Streetlight on left
    drawStreetLightVA();

    glutSwapBuffers();
}

void timer(int value) {
    // update jeepney
    xOffset += speed;
    float jeepWidth = 0.9f; // approximate width
    if (xOffset > 1.0f + jeepWidth / 2)
        xOffset = -1.0f - jeepWidth / 2; // wrap around smoothly

    // clouds drift slowly to right
    cloud1X += cloudSpeed;
    cloud2X += cloudSpeed * 0.6f;
    cloud1X = wrapX(cloud1X);
    cloud2X = wrapX(cloud2X);

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 fps
}

// Arrow keys with gradual slowing (moves clouds)
void specialKeys(int key, int x, int y) {
    if (cloudSpeed < 0.001f) cloudSpeed = 0.001f; // minimum speed

    if (key == GLUT_KEY_LEFT) {
        cloud1X -= cloudSpeed * 10.0f;
        cloud2X -= cloudSpeed * 10.0f;
    }
    if (key == GLUT_KEY_RIGHT) {
        cloud1X += cloudSpeed * 10.0f;
        cloud2X += cloudSpeed * 10.0f;
    }

    cloud1X = wrapX(cloud1X);
    cloud2X = wrapX(cloud2X);

    // Reduce speed slightly each press
    cloudSpeed *= 0.95f;

    glutPostRedisplay();
}

// Right-click to toggle the light
void mouseHandler(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        lightOn = !lightOn;
        glutPostRedisplay();
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        windowsLit = !windowsLit; // toggle lights
        glutPostRedisplay();       // redraw scene
    }
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);

    // nice smoothing
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

// -------------------- Main --------------------
int main(int argc, char** argv) {
    srand((unsigned)time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("FINALPROJECT");

    // Keep full screen per your choice
    glutFullScreen();

    // Initialize GLEW (if available) - safe check
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::fprintf(stderr, "Warning: glewInit failed: %s\n", glewGetErrorString(err));
        // Not fatal; some systems work without GLEW initialization for simple GLUT usage
    }

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseHandler);

    glutMainLoop();
    return 0;
}
