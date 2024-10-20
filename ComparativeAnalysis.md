# Comparative Analysis of Technologies Used in the Project

## Introduction

This document covers the technologies used in the project and provides justifications for each choice based on a comparative analysis. R-Type is a game
project in our cursus, and we must use some technologies to respect the constraints of the project, like using the C++ language.

## Comparisons

### Language

| Criterion                             | **C**                                                                                                                | **C++**                                                                                                                                           |
| ------------------------------------- | -------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Performance**                       | - **Pros**: Very performant due to low-level access to memory and hardware.<br>- **Cons**: Requires manual optimization for best performance.         | - **Pros**: Comparable performance to C with compiler optimizations.<br>- **Cons**: Additional features like OOP can add overhead if misused.     |
| **Ease of Programming**               | - **Pros**: Simpler syntax, easier to grasp the basics.<br>- **Cons**: Lacks modern programming constructs, making complex tasks cumbersome.          | - **Pros**: Rich language features with templates and RAII.<br>- **Cons**: Increased complexity due to more features.                              |
| **Memory Management**                 | - **Pros**: Complete control over memory.<br>- **Cons**: Prone to memory errors like leaks and buffer overflows.                                         | - **Pros**: Offers automated memory management with smart pointers while retaining manual control.<br>- **Cons**: Some overhead from smart pointers.|
| **Object-Oriented Programming (OOP)** | - **Pros**: Can simulate OOP using structures.<br>- **Cons**: Does not natively support OOP constructs like inheritance.                               | - **Pros**: Fully supports OOP, making it easier to manage complex projects.<br>- **Cons**: Overusing OOP can lead to bloated code.               |
| **Modularity and Reusability**        | - **Pros**: Allows reusable code, but requires more effort.<br>- **Cons**: Limited language features for modularity compared to C++.                   | - **Pros**: Templates and namespaces support modularity.<br>- **Cons**: Some features, like templates, can be complex to use effectively.         |
| **Tools and Libraries**               | - **Pros**: Many libraries for low-level tasks.<br>- **Cons**: Few modern libraries for high-level development.                                         | - **Pros**: Rich ecosystem with libraries like Boost, SFML, etc.<br>- **Cons**: Some libraries can add build complexity.                           |
| **Safety and Reliability**            | - **Pros**: Simplicity can reduce certain errors.<br>- **Cons**: Manual memory management increases risk of bugs.                                      | - **Pros**: Features like smart pointers and type checking improve safety.<br>- **Cons**: Features like exceptions can be misused.                |
| **Development Time**                  | - **Pros**: Quick for small projects.<br>- **Cons**: Scalability and maintainability decrease with project size.                                        | - **Pros**: Advanced features help manage large projects.<br>- **Cons**: Learning curve can slow initial development.                              |
| **Portability**                       | - **Pros**: Highly portable across platforms.<br>- **Cons**: Requires more work for cross-platform consistency.                                         | - **Pros**: Inherits C's portability and adds features for cross-platform development.<br>- **Cons**: Some platform-specific features complicate builds.|

#### Chosen Language: **C++**

**Reasoning**: C++ provides a balance between performance, modularity, and safety, which is crucial for this project. The language's modern features and extensive libraries, like SFML, make it suitable for managing complex game logic while allowing low-level control when needed.

---

### Graphics Library

| Criterion                        | **SDL2**                                                                                                | **SFML**                                                                                                   |
| -------------------------------- | ------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| **Programming Language**         | - **Pros**: Written in C, with many bindings available.<br>- **Cons**: Lacks C++'s modern features, making code more verbose.                          | - **Pros**: Written in C++, aligning with the project's language.<br>- **Cons**: Requires C++ knowledge for effective use.                      |
| **Ease of Use**                  | - **Pros**: Provides low-level access.<br>- **Cons**: Requires more code to perform basic tasks.                                                | - **Pros**: High-level API is easier to understand and use.<br>- **Cons**: May abstract away needed low-level details.                           |
| **Performance**                  | - **Pros**: Great for low-level control.<br>- **Cons**: Optimization can be more challenging due to its lower-level nature.                          | - **Pros**: Optimized for multimedia applications.<br>- **Cons**: Performance tuning may require deep understanding of C++.                      |
| **Graphics**                     | - **Pros**: Allows full rendering control and OpenGL integration.<br>- **Cons**: Requires additional setup for 2D rendering.                        | - **Pros**: Built-in 2D rendering support simplifies starting quickly.<br>- **Cons**: Limited built-in support for 3D graphics.                  |
| **Audio**                        | - **Pros**: Supports audio via extensions like SDL_mixer.<br>- **Cons**: Additional setup needed for advanced audio.                               | - **Pros**: Easy-to-use built-in audio handling.<br>- **Cons**: Advanced audio manipulation may still require external libraries.                |
| **Input Handling**               | - **Pros**: Comprehensive input support.<br>- **Cons**: More manual handling of events is necessary.                                              | - **Pros**: Simple and integrated input handling.<br>- **Cons**: Limited customization compared to SDL2.                                         |
| **Cross-Platform Compatibility** | - **Pros**: Wide platform support.<br>- **Cons**: Configuration can be complex on certain platforms.                                              | - **Pros**: Compatible with major platforms.<br>- **Cons**: Platform-specific tweaks are necessary for optimal performance.                      |
| **Documentation and Community**  | - **Pros**: Large community with comprehensive documentation.<br>- **Cons**: Documentation may be less beginner-friendly.                         | - **Pros**: Clear and organized documentation with many tutorials.<br>- **Cons**: Smaller community compared to SDL2.                            |
| **License**                      | - **Pros**: Permissive license suitable for most projects.<br>- **Cons**: Some extensions have different licenses.                                  | - **Pros**: Permissive license with fewer dependencies.<br>- **Cons**: Less built-in extensibility compared to SDL2.                             |
| **Extensibility**                | - **Pros**: Easily extensible with additional modules.<br>- **Cons**: Additional dependencies increase project complexity.                         | - **Pros**: Integration with OpenGL extends capabilities.<br>- **Cons**: Requires knowledge of graphics programming for effective extensions.    |

#### Chosen Graphics Library: **SFML**

**Reasoning**: SFML's high-level API and built-in support for graphics, audio, and input make it ideal for 2D game development. It aligns well with C++, streamlining development and allowing more focus on game logic.

---

### Networking Library

| Criterion                        | **Boost.Asio**                                                                                             | **Standalone Asio**                                                                                        |
| -------------------------------- | ----------------------------------------------------------------------------------------------------------| ---------------------------------------------------------------------------------------------------------- |
| **Integration**                  | - **Pros**: Part of Boost, easy to use with other Boost libraries.<br>- **Cons**: Brings Boost's overall overhead.                                | - **Pros**: Lightweight without extra dependencies.<br>- **Cons**: Lacks Boost-specific utilities.                                             |
| **Ease of Use**                  | - **Pros**: Rich documentation.<br>- **Cons**: Can feel heavy if not using other Boost libraries.                                                | - **Pros**: Simpler and smaller, focused solely on networking.<br>- **Cons**: Fewer built-in utilities.                                        |
| **Performance**                  | - **Pros**: High performance for asynchronous networking.<br>- **Cons**: Slightly higher memory overhead due to Boost integration.                | - **Pros**: Similar performance while being more lightweight.<br>- **Cons**: May require more configuration for advanced features.              |
| **Features**                     | - **Pros**: Full-featured with many networking utilities.<br>- **Cons**: Can be overkill for simple networking tasks.                              | - **Pros**: Covers essential networking needs.<br>- **Cons**: Lacks some advanced utilities compared to Boost.                                  |
| **Community and Support**        | - **Pros**: Well-supported by Boost's community.<br>- **Cons**: Documentation can be overwhelming.                                                | - **Pros**: Active development focused on networking.<br>- **Cons**: Smaller community compared to Boost.                                       |

#### Chosen Networking Library: **Standalone Asio**

**Reasoning**: The lightweight nature of Standalone Asio fits well with the project's requirements for a networking library. It provides the essential functionality without the overhead of the entire Boost library, making it easier to integrate into the codebase.

### Architecture: Entity-Component-System (ECS) vs. Traditional Object-Oriented

| Criterion                              | **Traditional Object-Oriented Programming (OOP)**                                                              | **Entity-Component-System (ECS)**                                                                                  |
| -------------------------------------- | -------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| **Flexibility**                        | - **Pros**: Well-structured for static, hierarchical relationships.<br>- **Cons**: Difficult to modify behavior dynamically, as inheritance is rigid. | - **Pros**: Highly flexible, allowing dynamic composition of entities with various components.<br>- **Cons**: May be harder to conceptualize and set up initially. |
| **Performance**                        | - **Pros**: Generally efficient when objects and relationships are stable.<br>- **Cons**: Inheritance chains can cause overhead, especially in large systems. | - **Pros**: Often leads to better performance due to cache-friendly memory layouts and data-oriented design.<br>- **Cons**: Requires careful design of systems for optimal performance. |
| **Code Reusability**                   | - **Pros**: Encourages code reuse through inheritance and polymorphism.<br>- **Cons**: Reusability can be limited by rigid class hierarchies.          | - **Pros**: Components are modular and reusable across different entities, promoting code reuse.<br>- **Cons**: Systems need to manage interactions between components explicitly. |
| **Complexity Management**              | - **Pros**: Good for managing complexity in static, well-defined scenarios.<br>- **Cons**: Class hierarchies can become complex and difficult to maintain over time. | - **Pros**: Reduces complexity by separating data (components) from behavior (systems).<br>- **Cons**: Requires a different mindset compared to traditional OOP, which may increase initial learning curve. |
| **Scalability**                        | - **Pros**: Suitable for small to medium-sized projects.<br>- **Cons**: Large class hierarchies can be difficult to scale and maintain.               | - **Pros**: Highly scalable due to its data-oriented nature, making it ideal for games with many entities.<br>- **Cons**: May need specialized tools or frameworks for effective management. |
| **Data-Oriented Design**               | - **Pros**: Not inherently data-oriented, focusing on objects and their relationships.<br>- **Cons**: Can be less efficient when accessing large amounts of similar data. | - **Pros**: Embraces data-oriented design, which can improve memory access patterns and cache usage.<br>- **Cons**: Designing systems that operate on data in parallel can be challenging. |
| **Ease of Debugging**                  | - **Pros**: Easier to debug if you are familiar with OOP principles.<br>- **Cons**: Inheritance-based bugs can be hard to trace.                       | - **Pros**: Debugging can be more straightforward as data and behavior are decoupled.<br>- **Cons**: Requires tools that can inspect entities, components, and systems effectively. |
| **Learning Curve**                     | - **Pros**: Familiar to many developers who are experienced with OOP.<br>- **Cons**: May encourage overuse of inheritance, leading to design pitfalls.  | - **Pros**: Once understood, it provides a clean way to handle game state and behavior.<br>- **Cons**: Initially challenging to grasp, especially for developers used to OOP. |

#### Chosen Architecture: **Entity-Component-System (ECS)**

**Reasoning**: The ECS architecture was chosen for its flexibility, performance benefits, and suitability for handling large numbers of game entities. Its separation of data (components) from behavior (systems) aligns with the project's goals of creating a modular and scalable game engine. The ability to dynamically compose entities using different combinations of components makes ECS an ideal choice for game development, where objects often have varying behaviors and attributes.


## Conclusion

Based on this comparative analysis, **C++** was chosen for its rich feature set, modern memory management, and object-oriented capabilities, which are essential for building a scalable and modular game engine. The language's performance and flexibility provide the right balance for managing complex game logic and rendering requirements.

**SFML** was selected as the graphics library due to its simplicity and ease of use, offering built-in 2D rendering and multimedia support with minimal setup. This makes SFML an ideal choice for 2D game development, where rapid iteration and a user-friendly API are prioritized.

For network communication, **Asio** was chosen for its lightweight, cross-platform capabilities and efficient asynchronous I/O support, which aligns well with the project's need for high-performance networking in a real-time game environment. Asio's ability to manage asynchronous operations and handle multiple connections seamlessly supports the game's requirements for responsive and reliable network communication.

The **Entity-Component-System (ECS)** architecture was adopted for its flexibility and performance advantages. Its data-oriented design allows for efficient memory management and cache-friendly data processing, which are crucial in games with many dynamic entities. The ECS architecture also enables the composition of entities with diverse behaviors, promoting a modular approach to game development and making it easier to scale and maintain the game as it evolves.

Combining these technologies ensures a robust and efficient development process, leveraging C++'s performance, SFML's ease of use, Asio's networking capabilities, and the ECS architecture's modular design. This stack provides both flexibility and scalability while maintaining high performance, making it well-suited for the project's requirements.

---
Go to the main documentation : [Main documentation](Readme.md)