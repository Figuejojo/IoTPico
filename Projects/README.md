# How to add a new Project
Follow these steps to add and configure a new project within the `IoTPico` repository.

---

## Steps to Add a New Project

1. **Create a New Project Folder**  
   - Copy the `Sandbox/` folder located in `projects/` and rename it to your new project name (e.g., `NewProject`).

2. **Edit the New Project CMakeLists.txt**  
   - Open the `CMakeLists.txt` inside your new project folder (`Projects/NewProject/CMakeLists.txt`).
   - Replace all instances of `SandBox` with your new project name (`NewProject`).

3. **Register the Project in Root CMake**  
   - Open the root `CMakeLists.txt` file located at the repository root.  
   - Add a new `add_subdirectory()` entry for your project:
     ```cmake
     add_subdirectory(projects/NewProject)
     ```

4. **Update CMake**  
   - Navigate to the `build/` directory (or create it if it doesn’t exist):
     ```bash
     mkdir -p build && cd build
     ```
   - Run the following command to regenerate the build system:
     ```bash
     cmake ..
     ```

5. **Build the New Project**  
   - To build all projects, simply run:
     ```bash
     make
     ```
   - To build only your new project, specify its name:
     ```bash
     make NewProject
     ```
   - For example:
     ```bash
     make SandBox
     ```

---

## Notes

- **Project Naming**: Ensure your project name is unique and follows the repository's naming conventions. (Do not use spaces!)
- **Dependencies**: If your project has additional dependencies, add them to the `target_link_libraries()` section in its `CMakeLists.txt`.
- **CMake Visibility**: Only projects listed in the root `CMakeLists.txt` using `add_subdirectory()` will be built.
