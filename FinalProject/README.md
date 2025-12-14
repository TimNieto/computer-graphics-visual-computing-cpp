# OpenGL Night City Scene

This project renders a simple night-time city scene in OpenGL using **C++** and **FreeGLUT**. It features:

- **Buildings:** Main "Tech" building, user-defined `PARESAN`, and random building.
- **Dynamic windows:** Windows that can switch between lit and unlit states.
- **Street elements:** Road with dashed center lines, streetlights with glow effects.
- **Vehicles:** Moving jeepney with headlights.
- **Sky elements:** Stars and drifting clouds.
- **Logo and text:** "FEU TECH" text with a torch logo.

---

## **Features**

- Vertex array usage for optimized rendering of buildings, clouds, and street elements.
- Semi-transparent and dynamic lighting effects for headlights and streetlights.
- Modular drawing functions (`drawTechBuild1`, `paresan`, `randbldg`, etc.).
- Basic animation using position offsets for vehicles and clouds.

---

## **Dependencies**

- [GLEW](http://glew.sourceforge.net/) – OpenGL Extension Wrangler
- [FreeGLUT](http://freeglut.sourceforge.net/) – OpenGL Utility Toolkit
- Standard C++ libraries: `<cmath>`, `<vector>`, `<cstdlib>`, `<cstdio>`, `<ctime>`

---

## **Building**

1. Make sure you have **GLEW** and **FreeGLUT** installed on your system.
2. Compile the project using your preferred compiler. Example (Linux/Mac):

```bash
g++ -o NightCity main.cpp -lGL -lGLEW -lglut

g++ -o NightCity.exe main.cpp -lfreeglut -lglew32 -lopengl32 -lglu32

./NightCity      # Linux/Mac
NightCity.exe    # Windows
