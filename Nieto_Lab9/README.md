# NIETO Lab 9 - OpenGL Diamond & Spheres Scene

This project renders a 3D diamond at the center with three colored spheres acting as light sources in a 3D OpenGL scene using GLUT.

## Features

- Central 3D diamond with smooth shading.
- Three colored spheres (Red, Blue, Yellow) emitting light.
- Camera movement with keyboard controls.
- Real-time scene rotation.

## Controls

### Camera Movement
| Key | Action |
|-----|--------|
| W   | Move forward |
| S   | Move backward |
| A   | Move left |
| D   | Move right |
| Q   | Move down |
| E   | Move up |

### Rotation
| Key | Action |
|-----|--------|
| I   | Rotate up |
| K   | Rotate down |
| J   | Rotate left |
| L   | Rotate right |

### View Orientation
| Key           | Action |
|---------------|--------|
| Arrow Up      | Look up |
| Arrow Down    | Look down |
| Arrow Left    | Look left |
| Arrow Right   | Look right |

## Build Instructions

1. Make sure you have **OpenGL** and **GLUT** installed.
2. Compile using g++ (example):
```bash
g++ -o lab9 main.cpp -lGL -lGLU -lglut

./lab9
