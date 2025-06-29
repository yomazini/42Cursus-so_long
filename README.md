# So_Long: Complete 2D Game Development Guide
## Minimalist Pixel Art Game with MiniLibX


![42 School Badge](https://img.shields.io/badge/42-School-blue)
![Norminette](https://img.shields.io/badge/Norminette-passing-success)
![Score](https://img.shields.io/badge/Score-100%2F100-brightgreen)

## 📺 Gameplay Demo

### Video Showcase
[![Watch the video on Vimeo](img/gameplay-thumbnail)](https://vimeo.com/1065327226)
[Watch the video on Vimeo](https://player.vimeo.com/video/1065327226)

### Live Gameplay
![So_Long Minimalist 2D Pixel Art Gameplay](img/So_LongMinimalist2DPixelArtGameplay.gif)

---

## 🎯 Project Overview

So_Long is a minimalist 2D pixel art game developed as part of the 42 curriculum using MiniLibX. Players navigate through creative maps, collect items, and reach the exit in this retro-inspired adventure.

### Core Features
- **Minimalist Pixel Art**: Simple yet vibrant design evoking retro gaming nostalgia
- **Smooth Gameplay**: Intuitive movement and collision detection
- **Creative Levels**: Unique map layouts that challenge the player
- **42 Standards**: Developed following 42 school project guidelines

---

## 🏗️ System Architecture

### macOS Graphics Stack Integration

```mermaid
%%{init: {'theme': 'base', 'themeVariables': {'primaryColor': '#4CAF50', 'primaryTextColor': '#ffffff', 'primaryBorderColor': '#388E3C', 'lineColor': '#666666'}}}%%
flowchart TD
    subgraph "macOS Graphics Stack"
        Q[Quartz - 2D Graphics Engine] --> QC[Quartz Compositor]
        AK[AppKit Framework] --> WS[WindowServer]
        OGL[OpenGL API] --> GPU[Graphics Processing Unit]
        WS --> QC
        QC --> Display[Screen Display]
        GPU --> FB[Framebuffer]
        FB --> QC
    end
    
    subgraph "MiniLibX Abstraction Layer"
        MLX[MiniLibX Library] --> AK
        MLX --> OGL
        MLX --> Q
    end
    
    subgraph "So_Long Application"
        SL[so_long main] --> MLX
        MP[Map Processing] --> SL
        GR[Graphics Rendering] --> MLX
        EH[Event Handling] --> MLX
    end
    
    style MLX fill:#9C27B0,stroke:#7B1FA2,color:#fff
    style SL fill:#FF5722,stroke:#D84315,color:#fff
    style Q fill:#2196F3,stroke:#1976D2,color:#fff
```

---

## 🔧 Core Technologies Deep Dive

### 1. macOS Graphics System Components

#### A. Quartz: The Foundation
- **Core 2D Graphics Engine**: Handles pixels, shapes, text, and images
- **Transparency & Effects**: Supports gradients, transparency, and visual effects
- **Quartz Compositor**: Combines visual elements from various sources into final display
- **Low-Level Nature**: Developers typically don't interact directly due to complexity

#### B. AppKit: macOS GUI Framework
- **macOS-Specific**: Part of the Cocoa framework, unique to macOS
- **Key Components**:
  - **Windows & Views**: NSWindow (application windows), NSView (rendering/events)
  - **Event Handling**: Mouse clicks, key presses, gestures
  - **Drawing & Graphics**: NSGraphicsContext, NSBezierPath, NSImage
  - **UI Controls**: NSButton, NSSlider, NSTableView
  - **Document Management**: NSDocument structure
  - **Menus & Toolbars**: NSMenu, NSToolbar classes
  - **Animations**: NSAnimation for basic effects
  - **Accessibility**: Built-in compliance
  - **Drag & Drop**: Native support
  - **File Integration**: File system interaction

#### C. OpenGL: Hardware-Accelerated Graphics
- **Cross-Platform API**: Works across different operating systems
- **GPU Acceleration**: Leverages graphics hardware for performance
- **2D & 3D Capabilities**: Comprehensive graphics rendering
- **Why Use with MiniLibX**:
  - **Performance**: AppKit drawing isn't optimized for high-performance graphics
  - **Advanced Features**: 3D rendering, shaders, lighting, shadows, textures
  - **Real-Time Rendering**: Suitable for animations and interactive graphics

#### D. WindowServer: Window Management
- **System Process**: Manages windowing, graphical output, user interaction
- **Key Functions**:
  - Window layout and visibility management
  - Intermediary between applications and graphics hardware
  - Input event routing (clicks, keystrokes)
  - Resource allocation for windows

#### E. GPU: Graphics Processing Unit
- **Specialized Hardware**: Designed for graphics acceleration
- **Core Responsibilities**:
  - Rendering graphics (shapes, textures, 3D objects)
  - Parallel calculations for rendering and shaders
  - Memory management (textures, frame buffers)
- **OpenGL Integration**: Direct communication for efficient rendering

### 2. MiniLibX: Simplified Graphics Library

#### Purpose & Design
- **Educational Focus**: Designed for 42 School projects
- **Abstraction Layer**: Hides complexity of Quartz, AppKit, and OpenGL
- **Simple Interface**: Easy-to-use functions for graphics programming

#### MiniLibX Workflow on macOS

##### Starting the Program (`mlx_init()`)
**Internal Actions:**
- Initializes internal data structures for windows, events, rendering
- Sets up OpenGL context (GPU workspace)
- Establishes AppKit communication
- Reserves WindowServer resources

**Connection Flow:**
1. MiniLibX → AppKit connection request
2. AppKit → WindowServer resource reservation
3. OpenGL context preparation

**Return Value**: MiniLibX instance pointer (success) or NULL (failure)

##### Creating Windows (`mlx_new_window()`)
**Process:**
1. MiniLibX forwards request to AppKit (size, title)
2. AppKit communicates with WindowServer
3. WindowServer allocates resources, makes window visible
4. Quartz Compositor handles layering and display

##### Graphics Rendering (`mlx_pixel_put()` example)
**Rendering Pipeline:**
1. MiniLibX converts to OpenGL instructions
2. OpenGL sends commands to GPU
3. GPU writes to framebuffer
4. Quartz Compositor reads framebuffer
5. Final composition and display

##### Event Handling (`mlx_key_hook()`, `mlx_loop()`)
**Event Flow:**
1. `mlx_key_hook()` sets callback function
2. `mlx_loop()` starts event listening
3. WindowServer detects input → AppKit → MiniLibX
4. Callback function execution

---

## 🎮 Program Flow Architecture

```mermaid
%%{init: {'theme': 'forest'}}%%
flowchart TD
    A[Main Program] --> B{Argument Check}
    B -->|argc == 2| C[Validate File Extension .ber]
    B -->|argc != 2| Z[Error: Invalid arguments]
    
    C -->|Valid| D[Initialize Game Structure]
    C -->|Invalid| Y[Error: Invalid extension]
    
    D --> E[Map Parsing & Validation]
    
    E --> F[Read Map File]
    F --> G[Check Map Structure]
    G --> H{Rectangular?}
    H -->|Yes| I[Check Borders]
    H -->|No| X[Error: Map shape]
    
    I --> J{Proper Walls?}
    J -->|Yes| K[Check Elements]
    J -->|No| X
    
    K --> L{Valid Elements?\n 1P, 1E, C≥1}
    L -->|Yes| M[Flood Fill Check]
    L -->|No| X
    
    M --> N{Valid Path?}
    N -->|Yes| O[Graphics Initialization]
    N -->|No| X
    
    O --> P[MLX Init]
    P --> Q[Load Textures]
    Q --> R[Create Window]
    
    R --> S[Game Loop]
    S --> T[Handle Input]
    T --> U[WASD Movement]
    T --> V[ESC Exit]
    
    U --> W[Update Position]
    W --> S
    
    V --> AA[Cleanup Resources]
    X --> AA
    Y --> AA
    Z --> AA
    
    AA[Cleanup Process] --> BB[Free Map Memory]
    BB --> CC[Close File Descriptors]
    CC --> DD[Destroy MLX Resources]
    
    style A fill:#4CAF50,stroke:#388E3C
    style E fill:#2196F3,stroke:#1976D2
    style O fill:#9C27B0,stroke:#7B1FA2
    style S fill:#FF9800,stroke:#F57C00
    style X fill:#F44336,stroke:#D32F2F
    style AA fill:#607D8B,stroke:#455A64
```

---

## 🗂️ Data Structure Design

```mermaid
%%{init: {'theme': 'base'}}%%
classDiagram
    class t_game {
        -int fd
        -int line_count
        -char* raw_map
        -char** map_grid
        -t_map_data props
        -void* mlx
        -void* win
        -size_t window_width
        -size_t window_height
        -int img_width
        -int img_height
        -void* textures[5]
        -size_t move_count
    }
    
    class t_map_data {
        -int width
        -int height
        -size_t player_pos_x
        -size_t player_pos_y
        -size_t collectible_count
        -size_t exit_count
        -size_t player_count
    }
    
    class MiniLibX_Functions {
        +mlx_init()
        +mlx_new_window()
        +mlx_xpm_file_to_image()
        +mlx_put_image_to_window()
        +mlx_hook()
        +mlx_loop()
    }
    
    class Texture_Mapping {
        +textures[0] Wall
        +textures[1] Floor
        +textures[2] Player
        +textures[3] Collectible
        +textures[4] Exit
    }
    
    t_game --> t_map_data : contains
    t_game --> MiniLibX_Functions : uses
    t_game --> Texture_Mapping : manages
```

---

## 📋 Complete Implementation Details

### Key MiniLibX Functions

#### Initialization Functions
- **`mlx_init()`**: Establishes connection with graphical server
  - Returns: MiniLibX instance pointer or NULL on failure
  - Sets up OpenGL context and AppKit communication

#### Window Management
- **`mlx_new_window(mlx_ptr, width, height, title)`**: Creates new window
  - Returns: Window pointer or NULL on failure
- **`mlx_clear_window(mlx_ptr, win_ptr)`**: Clears window content
- **`mlx_destroy_window(mlx_ptr, win_ptr)`**: Closes and frees window resources

#### Drawing Functions
- **`mlx_pixel_put(mlx_ptr, win_ptr, x, y, color)`**: Draws single pixel
  - Color format: 0xRRGGBB or 0xAARRGGBB
  - Performance: Slow for many pixels, use images instead

#### Image Management
- **`mlx_xpm_file_to_image(mlx_ptr, filename, &width, &height)`**: Loads XPM image
- **`mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, x, y)`**: Displays image
- **`mlx_new_image(mlx_ptr, width, height)`**: Creates blank image
- **`mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian)`**: Raw pixel access
- **`mlx_destroy_image(mlx_ptr, img_ptr)`**: Frees image resources

#### Event Handling
- **`mlx_loop(mlx_ptr)`**: Starts event loop (blocking)
- **`mlx_hook(win_ptr, event, mask, function_ptr, param)`**: Sets event callback
- **`mlx_key_hook(win_ptr, function_ptr, param)`**: Key press callback
- **`mlx_mouse_hook(win_ptr, function_ptr, param)`**: Mouse button callback
- **`mlx_loop_hook(mlx_ptr, function_ptr, param)`**: Loop iteration callback

#### Text Display
- **`mlx_string_put(mlx_ptr, win_ptr, x, y, color, string)`**: Displays text

---

## 🎯 Map Validation System

### Validation Components

```mermaid
flowchart TD
    A[Map File] --> B[Read Lines]
    B --> C[Check Rectangle Shape]
    C --> D[Wall Surrounding]
    D --> E[Element Validation]
    E --> F[Flood Fill Check]
    F --> G[Path Validation]
```

### Validation Rules
1. **File Extension**: Must be `.ber`
2. **Shape**: Rectangular map only
3. **Borders**: Surrounded by walls (`1`)
4. **Elements**: Exactly 1 Player (`P`), 1 Exit (`E`), at least 1 Collectible (`C`)
5. **Path**: All collectibles and exit must be reachable from player position

### Flood Fill Algorithm
**Purpose**: Verify all required elements are accessible from player starting position

**Process**:
1. Create copy of map
2. Find player starting position
3. Recursively mark all reachable floor tiles
4. Verify all collectibles and exit are marked as reachable

---

## 🎨 Graphics System

### Graphics Initialization Flow

```mermaid
flowchart TD
    A[MLX Init] --> B[Window Creation]
    B --> C[Load Textures]
    C --> D[Position Calculation]
    D --> E[Render Initial Map]
```

### Texture Management
- **Tile Size**: 50x50 pixels per game tile
- **Texture Array**:
  - `textures[0]`: Wall texture
  - `textures[1]`: Floor texture
  - `textures[2]`: Player texture
  - `textures[3]`: Collectible texture
  - `textures[4]`: Exit texture

### Window Size Calculation
- **Formula**: `window_width = map_width * 50`, `window_height = map_height * 50`
- **Limit**: Maximum 2550x1400 pixels (51x28 tiles)

---

## 🎮 Game Loop Mechanics

```mermaid
flowchart TD
    A[Key Press] --> B{Movement Key?}
    B -->|Yes| C[Update Player Position]
    B -->|No| D[Check Exit]
    C --> E[Collision Detection]
    E --> F[Collectible Handling]
    F --> G[Map Re-render]
    D --> H[Exit Game]
```

### Input Handling
**Key Mappings** (macOS):
- **ESC**: `53` - Exit game
- **W**: `13` - Move up
- **A**: `0` - Move left
- **S**: `1` - Move down
- **D**: `2` - Move right

### Movement Logic
1. **Input Detection**: Key press triggers callback
2. **Position Calculation**: Determine target position
3. **Collision Check**: Verify move is valid (not into wall)
4. **State Update**: Update player position, collect items
5. **Display Update**: Re-render map with new positions
6. **Win Condition**: Check if all collectibles gathered and exit reached

---

## 🔄 Event System Architecture

```mermaid
%%{init: {'theme': 'dark'}}%%
stateDiagram-v2
    [*] --> GameInitialized
    GameInitialized --> EventLoop : mlx_loop()
    
    EventLoop --> KeyPressed : User Input
    EventLoop --> WindowClose : X Button
    
    KeyPressed --> ESC_Key : Key 53
    KeyPressed --> W_Key : Key 13
    KeyPressed --> A_Key : Key 0  
    KeyPressed --> S_Key : Key 1
    KeyPressed --> D_Key : Key 2
    KeyPressed --> InvalidKey : Other Keys
    
    ESC_Key --> Cleanup : window_exit()
    W_Key --> MoveUp : player_moves()
    A_Key --> MoveLeft : player_moves()
    S_Key --> MoveDown : player_moves()  
    D_Key --> MoveRight : player_moves()
    InvalidKey --> EventLoop
    
    MoveUp --> ValidateMove : Check Collision
    MoveLeft --> ValidateMove
    MoveDown --> ValidateMove
    MoveRight --> ValidateMove
    
    ValidateMove --> UpdatePosition : Valid Move
    ValidateMove --> EventLoop : Invalid Move
    
    UpdatePosition --> CollectItem : On Collectible
    UpdatePosition --> CheckWin : On Exit
    UpdatePosition --> UpdateDisplay : Normal Move
    
    CollectItem --> UpdateDisplay
    CheckWin --> Victory : All Items Collected
    CheckWin --> UpdateDisplay : Items Remaining
    
    UpdateDisplay --> EventLoop : Re-render Map
    Victory --> Cleanup
    WindowClose --> Cleanup
    
    Cleanup --> [*] : Exit Program
```

---

## 🧠 Memory Management

### Memory Allocation Flow

```mermaid
%%{init: {'theme': 'base'}}%%
flowchart TD
    subgraph "Memory Allocation"
        A[t_game Structure] --> B[raw_map malloc]
        B --> C[map_grid ft_split]
        C --> D[MLX Pointers]
        D --> E[Texture Loading]
    end
    
    subgraph "Memory Usage"
        F[Game Execution] --> G[Map Access]
        G --> H[Texture Rendering]
        H --> I[Event Processing]
    end
    
    subgraph "Memory Cleanup"
        J[cleanup_resources] --> K[free_all map_grid]
        K --> L[free raw_map]
        L --> M[mlx_destroy_image textures]
        M --> N[mlx_destroy_window]
        N --> O[Exit Clean]
    end
    
    E --> F
    I --> J
    
    style A fill:#4CAF50,stroke:#388E3C
    style J fill:#F44336,stroke:#D32F2F
    style O fill:#607D8B,stroke:#455A64
```

### Cleanup Process
**Critical**: Always destroy resources before program exit
1. **Free Map Memory**: `free_all()` for map_grid, `free()` for raw_map
2. **Destroy Images**: `mlx_destroy_image()` for all textures
3. **Close Window**: `mlx_destroy_window()`
4. **Close Files**: Close any open file descriptors

---

## ⚠️ Error Handling System

```mermaid
%%{init: {'theme': 'base'}}%%
flowchart TD
    subgraph "Input Validation Errors"
        E1[Invalid Arguments] --> ERR[Error Handler]
        E2[Wrong File Extension] --> ERR
        E3[File Not Found] --> ERR
    end
    
    subgraph "Map Validation Errors"  
        E4[Non-rectangular Map] --> ERR
        E5[Missing Wall Border] --> ERR
        E6[Invalid Element Count] --> ERR
        E7[Unreachable Elements] --> ERR
        E8[Map Too Large] --> ERR
    end
    
    subgraph "System Errors"
        E9[MLX Init Failed] --> ERR
        E10[Window Creation Failed] --> ERR
        E11[Texture Load Failed] --> ERR
        E12[Memory Allocation Failed] --> ERR
    end
    
    ERR --> CLEAN[cleanup_resources]
    CLEAN --> FREE[Free All Memory]
    FREE --> EXIT[Exit with Error Code]
    
    style ERR fill:#F44336,stroke:#D32F2F
    style CLEAN fill:#607D8B,stroke:#455A64
    style EXIT fill:#424242,stroke:#212121
```

### Error Categories
**Input Validation Errors**:
- Invalid arguments (not exactly 2)
- Wrong file extension (not `.ber`)
- File not found or unreadable

**Map Validation Errors**:
- Non-rectangular shape
- Missing wall borders
- Invalid element counts
- Unreachable elements
- Map too large for display

**System Errors**:
- MiniLibX initialization failure
- Window creation failure
- Texture loading failure
- Memory allocation failure

---

## 🔧 File Processing Pipeline

```mermaid
%%{init: {'theme': 'neutral'}}%%
sequenceDiagram
    participant Main
    participant File_Validator
    participant GNL as get_next_line
    participant Split as ft_split
    participant Map_Validator
    participant Flood_Fill
    participant Graphics
    
    Main->>File_Validator: validate_map_file(path)
    File_Validator->>File_Validator: Check .ber extension
    File_Validator->>GNL: Read file line by line
    GNL-->>File_Validator: Return each line
    File_Validator->>File_Validator: Concatenate to raw_map
    File_Validator->>Split: ft_split(raw_map, '\n')
    Split-->>File_Validator: Return map_grid[][]
    
    File_Validator->>Map_Validator: verify_map_shape()
    Map_Validator->>Map_Validator: Check rectangular shape
    Map_Validator->>Map_Validator: Check wall borders
    Map_Validator->>Map_Validator: validate_map_elements()
    Map_Validator->>Map_Validator: Count P=1, E=1, C>=1
    
    Map_Validator->>Flood_Fill: validate_map_path()
    Flood_Fill->>Flood_Fill: Create map copy
    Flood_Fill->>Flood_Fill: Find player position
    Flood_Fill->>Flood_Fill: flood_fill_check(x,y)
    Flood_Fill->>Flood_Fill: Mark reachable areas
    Flood_Fill->>Flood_Fill: verify_remaining_elements()
    Flood_Fill-->>Map_Validator: Path validation result
    
    Map_Validator-->>Main: Validation complete
    Main->>Graphics: build_graphic_map()
    Graphics->>Graphics: Initialize MLX
    Graphics->>Graphics: Load textures
    Graphics->>Graphics: Start game loop
```

---

## 🏗️ Project Structure

```
so_long/
├── Makefile                 # Build system
├── so_long.h               # Header with all definitions
├── so_long.c               # Main program entry
├── process_map_file.c      # Map validation logic
├── draw_map.c              # Graphics and rendering
├── events.c                # Input handling
├── ft_flood_fill.c         # Path validation algorithm
├── get_next_line.c         # File reading utility
├── ft_split.c              # String manipulation
├── textures/               # XPM image files
│   ├── wall.xpm
│   ├── floor.xpm  
│   ├── player.xpm
│   ├── collectible.xpm
│   └── exit.xpm
└── maps/                   # Test map files
    └── *.ber
```

---

## 📊 Key Constants & Definitions

```c
// Buffer and key definitions
#define BUFFER_SIZE 10        // get_next_line buffer
#define ESC_KEY 53           // Escape key code
#define W_KEY 13             // W key movement
#define S_KEY 1              // S key movement  
#define A_KEY 0              // A key movement
#define D_KEY 2              // D key movement
#define ON_DESTROY 17        // Window destroy event
#define TILE_SIZE 50         // Each tile is 50x50 pixels

// Color format examples
#define COLOR_RED 0xFF0000    // Red color
#define COLOR_GREEN 0x00FF00  // Green color
#define COLOR_BLUE 0x0000FF   // Blue color
```

---

## 🎯 Development Best Practices

### Code Organization
1. **Modular Design**: Separate concerns (map validation, graphics, events)
2. **Error Handling**: Comprehensive error checking at every step
3. **Memory Management**: Always pair allocation with deallocation
4. **Resource Cleanup**: Destroy all MiniLibX resources before exit

### Performance Considerations
1. **Image vs Pixel**: Use images for complex graphics, pixel_put for simple elements
2. **Efficient Rendering**: Only re-render when necessary
3. **Memory Usage**: Free unused resources promptly

### 42 School Standards
1. **Norm Compliance**: Follow 42 coding standards
2. **Function Limits**: Keep functions under 25 lines
3. **File Organization**: Logical separation of functionality
4. **Error Messages**: Clear, informative error reporting

---

## 🚀 Getting Started

### Prerequisites
- macOS with MiniLibX installed
- GCC compiler
- Make build system

### Compilation
```bash
make
```

### Usage
```bash
./so_long maps/map.ber
```

### Controls
- **WASD**: Move player
- **ESC**: Exit game
- **Objective**: Collect all items and reach the exit

---

## Author;

🎓 42 Intra: [ymazini](https://profile.intra.42.fr/users/ymazini)
🐙 GitHub: [yomazini](https://github.com/yomazini)
💼 LinkedIn: [Connect with me](https://www.linkedin.com/in/youssef-mazini/)


