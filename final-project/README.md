# Final Project - Night City Scene

A 2D OpenGL animated night city scene built with C++, FreeGLUT, and GLEW.

The scene features an FEU Tech building, animated clouds, stars, a moving jeepney, road elements, a side building, a Paresan storefront, building window toggles, and streetlight interaction.

## Features

- 2D OpenGL city scene
- FEU Tech building with toggleable windows
- Moving jeepney animation
- Animated clouds
- Stars and night sky background
- Road with dashed lane markings
- Streetlight with toggleable light beam
- Jeepney headlights
- Mouse interaction
- Modular drawing functions

## Technologies Used

- C++
- OpenGL
- FreeGLUT
- GLEW
- MSYS2 UCRT64
- MinGW g++

## How to Run

Run these commands from the repository root folder:

```powershell
g++ .\final-project\main.cpp -o .\final-project\final-project.exe -lfreeglut -lglew32 -lopengl32 -lglu32
```

```powershell
.\final-project\final-project.exe
```

## Controls

```text
Left Click   - Toggle building window lights
Right Click  - Toggle streetlight
Alt + F4     - Exit fullscreen window
```

## Sample Output

### Night City Scene

![Night City Scene](../assets/sample-output.png)

### Interactive Lighting Toggle

![Interactive Lighting Toggle](../assets/sample-output2.png)

## Notes

- Generated `.exe` files are ignored and should not be committed.
- This project uses OpenGL fixed-function rendering.
- The scene is fullscreen when launched.
- The animation uses a GLUT timer for continuous updates.

## Future Improvements

- Add texture mapping for buildings and vehicles
- Add smoother animation controls
- Add more scene objects
- Add keyboard-based exit support
- Add configurable fullscreen/windowed mode

## License

This project is for educational and portfolio purposes only. All rights are reserved.

You may view the source code, but you may not copy, modify, distribute, or use this code without permission from the author.

## Author

Created by Tim Nieto.