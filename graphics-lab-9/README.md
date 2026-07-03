# Graphics Lab 9 - Dynamic Lighting

A 3D OpenGL lighting demo built with C++ and GLUT/FreeGLUT.

The project renders a faceted diamond with three colored light spheres. The user can move the camera, rotate the view, and rotate the diamond-light setup.

## Features

- 3D faceted diamond model
- Red, blue, and yellow light spheres
- Dynamic OpenGL lighting
- Camera movement controls
- View rotation controls
- Object rotation controls
- Keyboard interaction
- Depth testing
- Basic material and lighting setup

## Technologies Used

- C++
- OpenGL
- GLUT / FreeGLUT
- MSYS2 UCRT64
- MinGW g++

## How to Run

Run these commands from the repository root folder:

```powershell
g++ .\graphics-lab-9\main.cpp -o .\graphics-lab-9\graphics-lab-9.exe -lfreeglut -lopengl32 -lglu32
```

```powershell
.\graphics-lab-9\graphics-lab-9.exe
```

## Controls

```text
W / A / S / D    - Move camera
Q / E            - Move camera down/up
Arrow Keys       - Rotate camera view
I / J / K / L    - Rotate diamond and light setup
Esc              - Close window
```

## Sample Output

### Final Project - Night City Scene

![Rotated Diamond Lighting View](../assets/sample-output3.png)

### Final Project - Interactive Lighting Toggle

![Dynamic Lighting Demo](../assets/sample-output4.png)

## Notes

- Generated `.exe` files are ignored and should not be committed.
- This project uses OpenGL fixed-function lighting.
- The colored spheres represent the light sources in the scene.
- The diamond is faceted, so each face reacts to light based on its normal and angle.

## Future Improvements

- Add more lighting modes
- Add reset controls for camera and rotation
- Add smoother camera movement
- Add optional wireframe mode
- Add configurable light positions

## License

This project is for educational and portfolio purposes only. All rights are reserved.

You may view the source code, but you may not copy, modify, distribute, or use this code without permission from the author.

## Author

Created by Tim Nieto.
