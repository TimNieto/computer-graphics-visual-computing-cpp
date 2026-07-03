#include <GL/glut.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>

constexpr int WINDOW_WIDTH = 900;
constexpr int WINDOW_HEIGHT = 700;

constexpr float CAMERA_MOVE_SPEED = 0.2f;
constexpr float CAMERA_LOOK_SPEED = 0.05f;
constexpr float OBJECT_ROTATION_SPEED = 5.0f;

constexpr float DIAMOND_SIZE = 2.0f;
constexpr float SPHERE_DISTANCE = 5.0f;
constexpr float SPHERE_RADIUS = 0.5f;

constexpr float MIN_PITCH = -1.4f;
constexpr float MAX_PITCH = 1.4f;

float camera_x = 0.0f;
float camera_y = 0.0f;
float camera_z = 12.0f;

float camera_yaw = 0.0f;
float camera_pitch = 0.0f;

float rotation_x = 0.0f;
float rotation_y = 0.0f;

struct Vertex {
    float x;
    float y;
    float z;
};

struct Face {
    int first;
    int second;
    int third;
};

struct Color {
    float red;
    float green;
    float blue;
    float alpha;
};

const Vertex DIAMOND_VERTICES[] = {
    {0.0f, DIAMOND_SIZE, 0.0f},
    {0.0f, -DIAMOND_SIZE, 0.0f},
    {-DIAMOND_SIZE, 0.0f, 0.0f},
    {DIAMOND_SIZE, 0.0f, 0.0f},
    {0.0f, 0.0f, DIAMOND_SIZE},
    {0.0f, 0.0f, -DIAMOND_SIZE}
};

const Face DIAMOND_FACES[] = {
    {0, 4, 3},
    {0, 3, 5},
    {0, 5, 2},
    {0, 2, 4},
    {1, 3, 4},
    {1, 5, 3},
    {1, 2, 5},
    {1, 4, 2}
};

const Color LIGHT_COLORS[] = {
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 0.0f, 1.0f}
};

const Vertex LIGHT_POSITIONS[] = {
    {SPHERE_DISTANCE, 0.0f, 0.0f},
    {-SPHERE_DISTANCE / 2.0f, 0.0f, SPHERE_DISTANCE * 0.866f},
    {-SPHERE_DISTANCE / 2.0f, 0.0f, -SPHERE_DISTANCE * 0.866f}
};

void set_material_color(const Color& color) {
    GLfloat material_color[] = {
        color.red,
        color.green,
        color.blue,
        color.alpha
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_color);
}

void set_lighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    GLfloat ambient_light[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

    for (int i = 0; i < 3; ++i) {
        GLenum light = GL_LIGHT0 + i;
        glEnable(light);

        GLfloat light_position[] = {
            LIGHT_POSITIONS[i].x,
            LIGHT_POSITIONS[i].y,
            LIGHT_POSITIONS[i].z,
            1.0f
        };

        GLfloat light_color[] = {
            LIGHT_COLORS[i].red,
            LIGHT_COLORS[i].green,
            LIGHT_COLORS[i].blue,
            LIGHT_COLORS[i].alpha
        };

        GLfloat light_direction[] = {
            -LIGHT_POSITIONS[i].x,
            -LIGHT_POSITIONS[i].y,
            -LIGHT_POSITIONS[i].z
        };

        glLightfv(light, GL_POSITION, light_position);
        glLightfv(light, GL_DIFFUSE, light_color);
        glLightfv(light, GL_SPECULAR, light_color);
        glLightfv(light, GL_SPOT_DIRECTION, light_direction);
        glLightf(light, GL_SPOT_CUTOFF, 40.0f);
        glLightf(light, GL_SPOT_EXPONENT, 15.0f);
    }
}

void set_face_normal(const Vertex& first, const Vertex& second, const Vertex& third) {
    float ux = second.x - first.x;
    float uy = second.y - first.y;
    float uz = second.z - first.z;

    float vx = third.x - first.x;
    float vy = third.y - first.y;
    float vz = third.z - first.z;

    float normal_x = (uy * vz) - (uz * vy);
    float normal_y = (uz * vx) - (ux * vz);
    float normal_z = (ux * vy) - (uy * vx);

    glNormal3f(normal_x, normal_y, normal_z);
}

void draw_diamond() {
    set_material_color({0.8f, 0.8f, 0.8f, 1.0f});
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);

    glBegin(GL_TRIANGLES);

    for (const Face& face : DIAMOND_FACES) {
        const Vertex& first = DIAMOND_VERTICES[face.first];
        const Vertex& second = DIAMOND_VERTICES[face.second];
        const Vertex& third = DIAMOND_VERTICES[face.third];

        set_face_normal(first, second, third);

        glVertex3f(first.x, first.y, first.z);
        glVertex3f(second.x, second.y, second.z);
        glVertex3f(third.x, third.y, third.z);
    }

    glEnd();
}

void draw_light_spheres() {
    for (int i = 0; i < 3; ++i) {
        glPushMatrix();
        glTranslatef(LIGHT_POSITIONS[i].x, LIGHT_POSITIONS[i].y, LIGHT_POSITIONS[i].z);

        GLfloat emission_color[] = {
            LIGHT_COLORS[i].red,
            LIGHT_COLORS[i].green,
            LIGHT_COLORS[i].blue,
            LIGHT_COLORS[i].alpha
        };

        GLfloat no_color[] = {0.0f, 0.0f, 0.0f, 1.0f};

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_color);

        glutSolidSphere(SPHERE_RADIUS, 20, 20);

        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_color);

        glPopMatrix();
    }
}

void update_camera() {
    glLoadIdentity();

    float look_x = std::sin(camera_yaw) * std::cos(camera_pitch);
    float look_y = std::sin(camera_pitch);
    float look_z = -std::cos(camera_yaw) * std::cos(camera_pitch);

    gluLookAt(
        camera_x,
        camera_y,
        camera_z,
        camera_x + look_x,
        camera_y + look_y,
        camera_z + look_z,
        0.0f,
        1.0f,
        0.0f
    );
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update_camera();

    glPushMatrix();
    glRotatef(rotation_x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation_y, 0.0f, 1.0f, 0.0f);

    set_lighting();
    draw_light_spheres();
    draw_diamond();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'w':
            camera_z -= CAMERA_MOVE_SPEED;
            break;
        case 's':
            camera_z += CAMERA_MOVE_SPEED;
            break;
        case 'a':
            camera_x -= CAMERA_MOVE_SPEED;
            break;
        case 'd':
            camera_x += CAMERA_MOVE_SPEED;
            break;
        case 'q':
            camera_y -= CAMERA_MOVE_SPEED;
            break;
        case 'e':
            camera_y += CAMERA_MOVE_SPEED;
            break;
        case 'i':
            rotation_x -= OBJECT_ROTATION_SPEED;
            break;
        case 'k':
            rotation_x += OBJECT_ROTATION_SPEED;
            break;
        case 'j':
            rotation_y -= OBJECT_ROTATION_SPEED;
            break;
        case 'l':
            rotation_y += OBJECT_ROTATION_SPEED;
            break;
        case 27:
            std::exit(0);
        default:
            break;
    }

    glutPostRedisplay();
}

void special_keyboard(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camera_yaw -= CAMERA_LOOK_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            camera_yaw += CAMERA_LOOK_SPEED;
            break;
        case GLUT_KEY_UP:
            camera_pitch += CAMERA_LOOK_SPEED;
            break;
        case GLUT_KEY_DOWN:
            camera_pitch -= CAMERA_LOOK_SPEED;
            break;
        default:
            break;
    }

    camera_pitch = std::clamp(camera_pitch, MIN_PITCH, MAX_PITCH);
    glutPostRedisplay();
}

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Graphics Lab 9 - Dynamic Lighting");

    glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);

    glutMainLoop();

    return 0;
}