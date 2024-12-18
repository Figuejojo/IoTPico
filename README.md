# IoT Pico
IoTPico is a modular, scalable, and maintainable development framework for the Raspberry Pi Pico W. It prioritizes a library-centric architecture, enabling core libraries (e.g., sensors, actuators, communication protocols) to be reused across various projects. Utilizing FreeRTOS for multitasking and robust unit testing, IoTPico aims to establish a flexible, testable foundation for diverse IoT projects.


## Available Projects
- **Sandbox Project**: Sandbox Project: Designed for rapid prototyping and testing of Minimum Viable Products (MVPs).
- **[New Project Name]** - [Project Description]

# Index
- [1 Project File Structure](#PFStruct)
- [2 Development Setup](#DevSetup)
    - [2.1 Dependencies](#Dependencies)
    - [2.2 Project Configuration](#PConfig)
    - [2.2 Unit Tests](#UTests)
- [3 Project Structure Details](#PStruct)
- [4 Adding New Projects ](#NewP)
- [5 Project Workflow](#PWork)
- [6 License](#License)

---

<a  name="PFStruct"></a>
# Project Structure
Below is an overview of the directory structure:

```
IoTPico/
├── libs/                         # Core reusable libraries
│   ├── sensors/                  # Sensor drivers (e.g., temperature, humidity)
│   ├── actuators/                # Actuator helpers (e.g., motors, servos)
│   ├── communication/            # Communication protocols (e.g., I2C, SPI, WiFi)
│   └── utilities/                # General helpers (e.g., delays, logging)
│   └── CMakeLists.txt            # Build configuration for libraries
├── tests/                        # Unit tests to validate libraries
│   ├── unity/                    # Unity testing framework (submodule)
│   ├── libs/                     # Tests for each library module
│   │   ├── test_sensors.c        # Unit tests for sensors
│   │   ├── test_actuators.c      # Unit tests for actuators
│   │   ├── test_communication.c  # Unit tests for communication
│   └── CMakeLists.txt            # Build configuration for tests
├── projects/                     # Full-scale applications integrating libraries
│   ├── Sandbox/                  # Fast prototyping and MVPs.
│   └── .                         # Add new projects using Sandbox as example.
├── FreeRTOS/                     # FreeRTOS kernel and configuration (submodule)
├── pico-sdk/                     # pico-SDK for Raspberry Pi Pico W (submodule)
├── CMakeLists.txt                # Root build configuration
└── README.md                     # Project documentation
└── .
```

<a  name="DevSetup"></a>
# Development Setup

<a  name="Dependencies"></a>
## Dependencies
@TODO

<a  name="PConfig"></a>
## Project Configuration

### Linux
1. **Clone Repository**

    Clone the git repository in your desired folder using
    ```shell
    git clone https://github.com/Figuejojo/IoTPico.git
    ```
2. **Initialize Submodules** 

    Initialize and update all submodules within the project directory by running::
    ```shell
    > cd IoTPico
    IoTPico> git submodule update --init --recursive
    ```
3. **Setup build directory**

    Create the build directory and build the project (Linux)
    ```shell
    IoTPico> mkdir build
    IoTPico> cd build
    IoTPico\build> cmake ..
    ```
4. **Build Projects**

    To build all projects, simply run:
    ```bash
    make
     ```
    To build a specific project, specify its name, for example:
     ```bash
     make SandBox
     ```

<a  name="UTests"></a>
## Unit Tests
@Todo

<a  name="PStruct"></a>
# Project Structure Details

- `libs/` - Core Libraries: 

Contains reusable libraries for sensors, actuators, communication protocols, and utilities. These modules are central to all projects.

- `tests/` - Unit Testing

Contains unit tests for `libs/` modules. It uses the Unity framework (included in the `unity/` folder).

- `project/` - Full-Scale Applications

Real-world applications combining libraries to create complete systems.

## Submodules
- **`FreeRTOS/`**: FreeRTOS kernel for multitasking.
- **`pico-sdk/`**: SDK for Pico W development.
- **`tests/unity/`**: Unit testing framework.

---

<a  name="NewP"></a>
# Adding new project
For details, see the README.md file under `projects/` directory.

---

<a  name="PWork"></a>
# Project Workflow

1. **Create a Ticket**: Open a new GitHub issue, e.g.,  
   `FEAT-1234: [SB] Add WiFi module support`.
2. **Create a Branch**: Use the naming convention:  
   `feature/FEAT-1234`.  
    **Development**: Work on the ticket and make descriptive commits. Example:  
    - Commit 1: `FEAT-10: [SB] Add LED Blink Task`
    - Commit 2: `FEAT-10: [SB] Fix LED One`
    - Commit 3: `FEAT-10: [SB] Make LED Pattern`

5. **Final Squash Commit**: Before merging, squash all commits into one using the format:  
   `[TYPE]-[ID] [AreaAbbreviation]: [Short Description] - [More Info]`.
    In more info list the most important changes and list the commits.

For more details on the workflow and naming conventions, refer to the [Project wiki](https://github.com/Figuejojo/IoTPico/wiki/Project-Git-Ticket,-Branch,-and-Commit-Naming-Conventions). 

---

<a  name="License"></a>
# License
This project is distributed under the MIT License. For more details, refer to the LICENSE file.