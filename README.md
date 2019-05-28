# Opengl-GLSL-Sandbox-Renderer
A little sandbox renderer for learning modern Opengl and GLSL.

Bits added so far:
-Qt window
-Vertex buffers
-Index buffers
-Vertex shader
-Fragment shader
-Camera class
-Qt mouse event
-Qt key press event
-Added plane, utah teapot, ninja star and cube as primitive shapes
-Ambient lighting
-More accurate diffuse lighting
-Specular lighting

Note: I've added all the dependencies because I think it is much easier for a beginner to just clone and run it directly. Right now dependencies are built in Windows only.

Abstracted opengl into classes, made project scalable:

![](Snapshots/RefactoredCode.JPG)

Fixed diffuse light issue with rotated and translated objects:

![](Snapshots/DiffuseLighting.JPG)

Added debug normals in iconic C.G. utah teapot:

![](Snapshots/DebugNormal.JPG)

First premitive shape:

![](Snapshots/Capture.JPG)