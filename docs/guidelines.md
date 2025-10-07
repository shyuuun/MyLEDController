# Coding Guidelines

To maintain a consistent codebase, please follow these guidelines.

## Naming Conventions

-   Use `camelCase` for variables and functions (e.g., `myVariable`, `doSomething()`).
-   Use `PascalCase` for classes and structs (e.g., `MyClass`).
-   Use `UPPER_SNAKE_CASE` for constants and macros (e.g., `const int MAX_LEDS = 60;`).
-   Header files should have a `.h` extension. Source files should have a `.cpp` extension.

## Formatting

-   **Indentation**: Use 2 spaces for indentation, not tabs.
-   **Braces**: Use the K&R style, where opening braces for functions are on the same line.

    ```cpp
    // Good
    void myFunction() {
      if (condition) {
        // ...
      }
    }

    // Bad
    void myFunction()
    {
      if(condition){
        //...
      }
    }
    ```

-   **Spacing**: Use a single space around operators (`=`, `+`, `-`, `*`, `/`, `==`, etc.).

## Comments

-   Use comments to explain _why_ you are doing something, not _what_ you are doing. The code should be self-explanatory about what it does.
-   For functions, consider using Doxygen-style comments to document parameters and return values.

### Documentation Placement

-   **Header Files (`.h`):** Place documentation for public functions, classes, and variables in the header file, directly above their declaration. This describes _how to use_ the interface.

    ```cpp
    // File: led/LED.h
    /**
     * @brief Sets the color of a specific LED.
     * @param index The index of the LED to change.
     * @param color The new color for the LED.
     */
    void setLedColor(int index, CRGB color);
    ```

-   **Source Files (`.cpp`):** Place comments inside function bodies in the source file to explain complex algorithms or implementation details (the _why_ and _how_ of the internal logic).

    ```cpp
    // File: led/LED.cpp
    void setLedColor(int index, CRGB color)
    {
        // This check is necessary to prevent buffer overflows.
        if (index >= 0 && index < NUM_LEDS)
        {
            leds[index] = color;
        }
    }
    ```

## Commit Messages

-   Use the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification.
-   Examples:
    -   `feat: Add rainbow effect`
    -   `fix: Correct off-by-one error in loop`
    -   `docs: Update README with setup instructions`
    -   `style: Format code according to guidelines`
    -   `refactor: Improve performance of web server responses`
