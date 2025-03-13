# So_Long Minimalist 2D Pixel Art Gameplay

Experience the retro charm of So_Long – a minimalist 2D pixel art game built using MiniLibX as part of the 42 curriculum. Navigate creative maps, collect items, and reach the exit in this retro-inspired adventure!

## Gameplay Video
## About So_Long

So_Long is a minimalist 2D pixel art game developed to meet the requirements of the 42 curriculum. In the game, the player navigates through uniquely designed maps, collects in-game items, and finds the exit to win the game.

### Features

- **Minimalist Pixel Art:** Simple yet vibrant design that evokes retro gaming nostalgia.
- **Smooth Gameplay:** Intuitive movement and collision detection.
- **Creative Levels:** Unique map layouts that challenge the player.
- **42 Standards:** Developed following the guidelines and style of the 42 school projects.

[Watch the video on Vimeo](https://player.vimeo.com/video/1065327226))
[![Watch the video on Vimeo](gameplay-thumbnail)](https://vimeo.com/1065327226)
![So_Long Minimalist 2D Pixel Art Gameplay](So_LongMinimalist2DPixelArtGameplay.gif)



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

Key Components Explained:

1. **Map Validation Flow**
```mermaid
flowchart TD
    A[Map File] --> B[Read Lines]
    B --> C[Check Rectangle Shape]
    C --> D[Wall Surrounding]
    D --> E[Element Validation]
    E --> F[Flood Fill Check]
    F --> G[Path Validation]
```

2. **Graphics Initialization**
```mermaid
flowchart TD
    A[MLX Init] --> B[Window Creation]
    B --> C[Load Textures]
    C --> D[Position Calculation]
    D --> E[Render Initial Map]
```

3. **Game Loop Mechanics**
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

4. **Error Handling Cases**
```mermaid
flowchart TD
    A[Invalid Map] --> B[File Structure]
    A --> C[Element Count]
    A --> D[Path Validation]
    B --> E[Non-rectangular]
    B --> F[Missing Walls]
    C --> G[Multiple Players]
    C --> H[No Exit]
    D --> I[Unreachable Elements]
```
