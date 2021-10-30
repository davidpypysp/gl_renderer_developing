# [Glitter](http://polytonic.github.io/Glitter/)
![Screenshot](http://i.imgur.com/MDo2rsy.jpg)

## Summary
Glitter is a dead simple boilerplate for OpenGL, intended as a starting point for the tutorials on [learnopengl.com](http://www.learnopengl.com) and [open.gl](https://open.gl). Glitter compiles and statically links every required library, so you can jump right into doing what you probably want: how to get started with OpenGL.

## Getting Started
Glitter has a single dependency: [cmake](http://www.cmake.org/download/), which is used to generate platform-specific makefiles or project files. Start by cloning this repository, making sure to pass the `--recursive` flag to grab all the dependencies. If you forgot, then you can `git submodule update --init` instead.
gl renderer


* `src/programs` contains independent binary programs source for opengl effect/feature.
* `src/shaders` contains shader files for opengl required by programs.

See Install.md