# Comparative Analysis of Technologies Used in the Project

## Introduction

This document covers all the technologies used in the project and provides justifications for the various choices made.

## Comparisons

### Language

| Criterion                             | **C**                                                                                                                                                  | **C++**                                                                                                                                                                      |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Performance**                       | - **Very performant**: Low-level, full control over memory and hardware.<br>- **Low overhead**: No additional features that could slow down execution. | - **High performance**: Comparable to C, thanks to compiler optimizations.<br>- **Minimal overhead**: Some features (like OOP) can introduce slight overhead if misused.     |
| **Ease of Programming**               | - **Simplicity**: Minimalistic language with clear syntax.<br>- **Fewer features**: Fewer concepts to master.                                          | - **Rich language**: Supports object-oriented programming, templates, RAII for memory management.<br>- **Increased complexity**: More concepts to learn and manage.          |
| **Memory Management**                 | - **Manual**: Full control but prone to errors (leaks, overflows).                                                                                     | - **Automated**: RAII, smart pointers (like `std::unique_ptr` and `std::shared_ptr`) enable safe memory management.<br>- **Flexible**: Can manage memory manually if needed. |
| **Object-Oriented Programming (OOP)** | - **Not supported**: Requires conventions and structures to simulate OOP.                                                                              | - **Fully supported**: Classes, inheritance, polymorphism, encapsulation.<br>- **Increased productivity**: Eases the management of complexity in large projects.             |
| **Modularity and Reusability**        | - **Limited**: Fewer structures to organize code modularly.<br>- **Reusable code**: Possible, but requires more effort.                                | - **High**: Templates, namespaces, and classes facilitate creating modular, reusable code.<br>- **Rich standard libraries**: STL, Boost, etc.                                |
| **Tools and Libraries**               | - **Fewer modern tools**: Though many libraries exist, they are often less geared towards modern development practices.                                | - **Rich ecosystem**: Wide range of modern libraries, frameworks, and development tools.<br>- **Easy integration with SFML, SDL, etc.**                                      |
| **Safety and Reliability**            | - **Error-prone**: Lacks advanced type checking, no automatic exception handling.                                                                      | - **Safer**: Compile-time type checks, exception handling, modern features to avoid common errors.<br>- **Supports modern safety concepts**.                                 |
| **Development Time**                  | - **Quick for small projects**: The simplicity of the language allows rapid development of simple programs.                                            | - **Potentially longer**: Language complexity can increase development time, but advanced features improve productivity for large-scale projects.                            |
| **Portability**                       | - **Highly portable**: C is a standardized language and widely supported across platforms.                                                             | - **Highly portable**: C++ inherits C's portability and offers additional features that facilitate cross-platform development.                                               |

#### Chosen Language: **C++**

For its automated memory management, rich ecosystem of features and native supported OOP.

---

### Graphics Library

| Criterion                        | **SDL2**                                                                                            | **SFML**                                                                                                 |
| -------------------------------- | --------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| **Programming Language**         | - Written in C.<br>- Bindings available for several languages (C++, Python, etc.).                  | - Written in C++.<br>- Bindings available for other languages like Python, C#, etc.                      |
| **Ease of Use**                  | - Low-level API, requires more code for simple operations.                                          | - High-level API, easy to understand and use.<br>- Requires less code for basic operations.              |
| **Performance**                  | - High performance.<br>- Excellent event and video handling.                                        | - High performance, optimized for multimedia applications.<br>- Simplified memory and object management. |
| **Graphics**                     | - Requires OpenGL for advanced graphics.<br>- Only handles basic 2D rendering.                      | - Built-in 2D rendering.<br>- Easy-to-use for simple graphics and animations.                            |
| **Window Management**            | - Supports multiple graphical backends (OpenGL, Vulkan, Direct3D).                                  | - Based on OpenGL for graphical rendering.                                                               |
| **Audio**                        | - Requires an extension (SDL_mixer) for advanced audio management.                                  | - Built-in basic audio handling (playback, music, sound effects).                                        |
| **Input Handling**               | - Full support for keyboard, mouse, game controllers, etc.                                          | - Built-in handling for keyboard, mouse, and game controllers.                                           |
| **Textures and Sprites**         | - Requires a bit more effort to manipulate textures and sprites.                                    | - Simplified manipulation of sprites and textures.                                                       |
| **Cross-Platform Compatibility** | - Very broad compatibility (Windows, macOS, Linux, Android, iOS, etc.).                             | - Compatibility with Windows, macOS, Linux, Android, and iOS.                                            |
| **Documentation and Community**  | - Complete documentation, but sometimes technical.<br>- Large community with many resources online. | - Clear and well-organized documentation.<br>- Active community, particularly helpful for beginners.     |
| **License**                      | - zlib License (very permissive).                                                                   | - zlib/libpng License (very permissive).                                                                 |
| **Ease of Installation**         | - More complex configuration (dependencies for sound, etc.).                                        | - Simple and lightweight installation, all-in-one.                                                       |
| **Extensibility**                | - Highly extensible via multiple additional modules (SDL_image, SDL_mixer, SDL_net, etc.).          | - Fewer external dependencies, but can be extended with OpenGL or third-party libraries.                 |
| **Ecosystem**                    | - Large ecosystem, many open-source projects.                                                       | - More limited than SDL, but plenty of examples and available projects.                                  |

#### Chosen Graphics Library: **SFML**

For its ease of use and built-in 2D rendering.

---

## Conclusion

Based on this comparative analysis, **C++** was chosen for its rich feature set, modern memory management, and object-oriented support, which are crucial for creating a scalable and modular game engine. **SFML** was selected as the graphics library for its simplicity and ease of use, making it ideal for 2D game development with minimal setup and code overhead. This combination ensures both flexibility and performance while maintaining an intuitive development process.