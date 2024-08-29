# SCOP: Mini-Project in Computer Graphics

This mini-project is an introductory exercise in using OpenGL with C++. The objective is to create a program that displays a 3D object, modeled in software like Blender, from a .obj file. The program renders the object in a rotating perspective and enables the application of textures through user input, with smooth transitions between colored and textured modes.

## Restrictions

This project has several restrictions to ensure a hands-on learning experience with low-level graphics programming:

- **Limited Libraries:** You can only use libraries such as GLFW for window management and GLEW for OpenGL extensions. No additional libraries are allowed for tasks such as 3D object loading, matrix manipulation, or shader management.
- **Manual Parsing:** You must manually parse the .obj files to render the 3D objects, without using third-party libraries for parsing.
- **Programming Languages:** The project must be written in C++, with OpenGL as the graphics API.
- **Makefile Requirement:** A standard Makefile must be used for compiling the project.


## Requirements

To run this project, you will need the following libraries installed:
```
GLFW: Version 3.3
GLEW: Any version that supports OpenGL 3.3
OpenGL: Version 3.3
C++17
```

To check your installed versions, use the following commands:

```bash
glxinfo | grep "OpenGL version"

apt list --installed | grep glfw

apt list --installed | grep glew
```
## Installation

Use the Makefile to compile the project

```bash
make
```
    
## Usage

To run the program, use the following command:
```bash
./scop <path_to_3Dobj>
```

## Commands

```
T : Switch to texture
C : Switch between grey and color shades
W,A,S,D and Mouse : Move the camera
```
## Demo
Here are some demonstrations of the program in action:
```bash
./scop ./3Dobj/42.obj
```
![42 Demo](./demo/42.gif)

```bash
./scop ./3Dobj/suzanne.obj
```
![Suzanne Demo](./demo/suzanne.gif)

```bash
./scop ./3Dobj/Porsche_911_GT2.obj
```
![Porsche Demo](./demo/porsche.gif)