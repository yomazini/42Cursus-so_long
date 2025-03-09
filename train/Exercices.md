Here’s a **detailed breakdown of each MLX function**, including explanations, examples, and exercises to help you understand and practice each one. After the exercises, I’ll provide the solutions.

---

### **1. `mlx_init()`**
#### **Explanation**:
- Initializes the MLX library.  
- Must be called before any other MLX function.  
- Returns a pointer to the MLX instance (`void *`).  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    if (!mlx) {
        ft_printf("Error\nMLX initialization failed\n");
        return (1);
    }
    return (0);
}
```

#### **Exercise**:
Write a program that initializes MLX and prints "MLX initialized successfully" if it works, or "MLX initialization failed" if it fails.

---

### **2. `mlx_new_window()`**
#### **Explanation**:
- Creates a new window.  
- Parameters: MLX instance, width, height, and title.  
- Returns a pointer to the window (`void *`).  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    if (!win) {
        ft_printf("Error\nWindow creation failed\n");
        return (1);
    }
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Create a program that opens a window with a title "My First Window" and a size of 500x500 pixels.

---

### **3. `mlx_loop()`**
#### **Explanation**:
- Starts the event loop, keeping the window open.  
- Blocks execution until the window is closed.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Modify the previous program to print "Window is running..." before calling `mlx_loop()`.

---

### **4. `mlx_xpm_file_to_image()`**
#### **Explanation**:
- Loads an XPM image file into memory.  
- Parameters: MLX instance, file path, and pointers to store width/height.  
- Returns a pointer to the image (`void *`).  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    if (!img) {
        ft_printf("Error\nFailed to load texture\n");
        return (1);
    }
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Load an XPM image and print its width and height to the terminal.

---

### **5. `mlx_put_image_to_window()`**
#### **Explanation**:
- Draws an image onto the window.  
- Parameters: MLX instance, window pointer, image pointer, and X/Y coordinates.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 100, 100);
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Load an XPM image and display it at the center of the window.

---

### **6. `mlx_destroy_image()`**
#### **Explanation**:
- Frees memory allocated for an image.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 100, 100);
    mlx_destroy_image(mlx, img);
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Load an image, display it, and then destroy it after 5 seconds (use `sleep(5)`).

---

### **7. `mlx_hook()`**
#### **Explanation**:
- Registers a callback for specific events (e.g., key press, window close).  

#### **Example**:
```c
#include <mlx.h>

int close_window(void *param) {
    ft_printf("Window closed\n");
    exit(0);
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_hook(win, 17, 0, close_window, mlx); // 17 = DestroyNotify
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Register a key press hook and print the keycode when a key is pressed.

---

### **8. `mlx_pixel_put()`**
#### **Explanation**:
- Draws a single pixel on the window.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_pixel_put(mlx, win, 100, 100, 0xFF0000); // Red pixel
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Draw a 10x10 red square at the top-left corner of the window.

---

### **9. `mlx_get_data_addr()`**
#### **Explanation**:
- Gets the memory address of an image for direct pixel manipulation.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    int bpp, size_line, endian;
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Modify the pixel data of an image to make it grayscale.

---

### **10. `mlx_clear_window()`**
#### **Explanation**:
- Clears the window.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_clear_window(mlx, win);
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Clear the window and then draw a green pixel at (200, 200).

---

### **11. `mlx_destroy_window()`**
#### **Explanation**:
- Closes and destroys a window.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_destroy_window(mlx, win);
    return (0);
}
```

#### **Exercise**:
Create a window, wait 3 seconds, and then close it.

---

### **12. `mlx_loop_hook()`**
#### **Explanation**:
- Registers a callback for the main loop.  

#### **Example**:
```c
#include <mlx.h>

int render_frame(void *param) {
    ft_printf("Rendering frame...\n");
    return (0);
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_loop_hook(mlx, render_frame, mlx);
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Print "Frame rendered" every second using `mlx_loop_hook()`.

---

### **13. `mlx_string_put()`**
#### **Explanation**:
- Draws a string on the window.  

#### **Example**:
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_string_put(mlx, win, 100, 100, 0xFFFFFF, "Hello, World!");
    mlx_loop(mlx);
    return (0);
}
```

#### **Exercise**:
Display your name in the center of the window.

---

### **Solutions**
Here are the solutions to all the exercises:

#### **1. `mlx_init()`**
```c
#include <mlx.h>
#include <stdio.h>

int main() {
    void *mlx = mlx_init();
    if (mlx)
        printf("MLX initialized successfully\n");
    else
        printf("MLX initialization failed\n");
    return (0);
}
```

#### **2. `mlx_new_window()`**
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 500, 500, "My First Window");
    mlx_loop(mlx);
    return (0);
}
```

#### **3. `mlx_loop()`**
```c
#include <mlx.h>
#include <stdio.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    printf("Window is running...\n");
    mlx_loop(mlx);
    return (0);
}
```

#### **4. `mlx_xpm_file_to_image()`**
```c
#include <mlx.h>
#include <stdio.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    if (img)
        printf("Image loaded: %dx%d\n", img_width, img_height);
    else
        printf("Failed to load image\n");
    mlx_loop(mlx);
    return (0);
}
```

#### **5. `mlx_put_image_to_window()`**
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, (800 - img_width) / 2, (600 - img_height) / 2);
    mlx_loop(mlx);
    return (0);
}
```

#### **6. `mlx_destroy_image()`**
```c
#include <mlx.h>
#include <unistd.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 100, 100);
    sleep(5);
    mlx_destroy_image(mlx, img);
    mlx_loop(mlx);
    return (0);
}
```

#### **7. `mlx_hook()`**
```c
#include <mlx.h>
#include <stdio.h>

int handle_keypress(int keycode, void *param) {
    printf("Key pressed: %d\n", keycode);
    return (0);
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_hook(win, 2, 1L << 0, handle_keypress, mlx); // 2 = KeyPress
    mlx_loop(mlx);
    return (0);
}
```

#### **8. `mlx_pixel_put()`**
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            mlx_pixel_put(mlx, win, x, y, 0xFF0000); // Red pixel
        }
    }
    mlx_loop(mlx);
    return (0);
}
```

#### **9. `mlx_get_data_addr()`**
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &img_width, &img_height);
    int bpp, size_line, endian;
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    for (int y = 0; y < img_height; y++) {
        for (int x = 0; x < img_width; x++) {
            int pixel = y * size_line + x * (bpp / 8);
            data[pixel] = (data[pixel] + data[pixel + 1] + data[pixel + 2]) / 3; // Grayscale
        }
    }
    mlx_put_image_to_window(mlx, win, img, 100, 100);
    mlx_loop(mlx);
    return (0);
}
```

#### **10. `mlx_clear_window()`**
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_clear_window(mlx, win);
    mlx_pixel_put(mlx, win, 200, 200, 0x00FF00); // Green pixel
    mlx_loop(mlx);
    return (0);
}
```

#### **11. `mlx_destroy_window()`**
```c
#include <mlx.h>
#include <unistd.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    sleep(3);
    mlx_destroy_window(mlx, win);
    return (0);
}
```

#### **12. `mlx_loop_hook()`**
```c
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

int render_frame(void *param) {
    static int frame = 0;
    printf("Frame rendered: %d\n", frame++);
    sleep(1);
    return (0);
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_loop_hook(mlx, render_frame, mlx);
    mlx_loop(mlx);
    return (0);
}
```

#### **13. `mlx_string_put()`**
```c
#include <mlx.h>

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "so_long");
    mlx_string_put(mlx, win, 350, 300, 0xFFFFFF, "Your Name");
    mlx_loop(mlx);
    return (0);
}
```

---

Let me know if you need further clarification or additional exercises!

-------

Here’s a **final project** that ties together all the MLX functions you’ve learned. The goal is to create a simple interactive program that demonstrates the use of all the MLX functions in a cohesive way.

---

### **Project: Mini Graphics Editor**
#### **Description**:
Create a simple graphics editor where:
1. A window opens with a blank canvas.
2. You can draw pixels by clicking the mouse.
3. You can clear the canvas by pressing the `C` key.
4. You can load and display an image by pressing the `L` key.
5. You can exit the program by pressing `ESC` or clicking the close button.

---

### **Pseudo Code**
```plaintext
1. Initialize MLX and create a window.
2. Load an image (e.g., "textures/wall.xpm") and store its data.
3. Register hooks:
   - Mouse click: Draw a pixel at the clicked position.
   - Key press:
     - 'C': Clear the window.
     - 'L': Display the loaded image.
     - 'ESC': Exit the program.
   - Window close: Exit the program.
4. Start the MLX loop.
```

---

### **Program Code**
```c
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *img_data;
    int     img_width;
    int     img_height;
    int     bpp;
    int     size_line;
    int     endian;
} t_data;

int handle_mouse(int button, int x, int y, t_data *data) {
    if (button == 1) { // Left click
        mlx_pixel_put(data->mlx, data->win, x, y, 0xFF0000); // Draw red pixel
    }
    return (0);
}

int handle_key(int keycode, t_data *data) {
    if (keycode == 53) // ESC key
        exit(0);
    else if (keycode == 8) { // C key
        mlx_clear_window(data->mlx, data->win);
    }
    else if (keycode == 37) { // L key
        mlx_put_image_to_window(data->mlx, data->win, data->img, 100, 100);
    }
    return (0);
}

int close_window(t_data *data) {
    exit(0);
}

int main() {
    t_data data;

    // Initialize MLX and window
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 800, 600, "Mini Graphics Editor");

    // Load image
    data.img = mlx_xpm_file_to_image(data.mlx, "textures/wall.xpm", &data.img_width, &data.img_height);
    if (!data.img) {
        printf("Error\nFailed to load image\n");
        return (1);
    }
    data.img_data = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);

    // Register hooks
    mlx_hook(data.win, 2, 1L << 0, handle_key, &data); // Key press
    mlx_hook(data.win, 4, 1L << 2, handle_mouse, &data); // Mouse click
    mlx_hook(data.win, 17, 0, close_window, &data); // Window close

    // Start MLX loop
    mlx_loop(data.mlx);

    return (0);
}
```

---

### **Explanation of the Code**
1. **Initialization**:
   - `mlx_init()` initializes the MLX library.
   - `mlx_new_window()` creates a window.

2. **Image Loading**:
   - `mlx_xpm_file_to_image()` loads an XPM image.
   - `mlx_get_data_addr()` gets the image data for potential manipulation.

3. **Event Handling**:
   - `mlx_hook()` registers callbacks for:
     - Key press (`handle_key`): Handles `ESC`, `C`, and `L` keys.
     - Mouse click (`handle_mouse`): Draws pixels on click.
     - Window close (`close_window`): Exits the program.

4. **Drawing**:
   - `mlx_pixel_put()` draws pixels on mouse click.
   - `mlx_put_image_to_window()` displays the loaded image when `L` is pressed.
   - `mlx_clear_window()` clears the canvas when `C` is pressed.

5. **Main Loop**:
   - `mlx_loop()` keeps the program running and processes events.

---

### **How It Works**
1. Run the program, and a window titled "Mini Graphics Editor" opens.
2. Click anywhere in the window to draw red pixels.
3. Press `C` to clear the canvas.
4. Press `L` to display the loaded image at (100, 100).
5. Press `ESC` or click the close button to exit.

---

### **Solution**
The code above is the complete solution. It integrates all the MLX functions you’ve learned into a single, interactive program.

---

### **Exercises to Extend the Project**
1. **Add Color Selection**:
   - Allow the user to select a color (e.g., using number keys) before drawing.

2. **Save the Canvas**:
   - Add a key (e.g., `S`) to save the current canvas as an image file.

3. **Image Manipulation**:
   - Allow the user to modify the loaded image (e.g., grayscale, invert colors).

4. **Undo Functionality**:
   - Implement an undo feature to remove the last drawn pixel.

---

Let me know if you need further clarification or help with extending the project!

