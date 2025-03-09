// trainng on mlx funcs 

# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ex 1 
// int main()
// {
// 	void	*mlx;
// 	mlx = mlx_init();
// 	if (mlx)
// 		printf("\nGreat done mlx run succefully %d\n",(int)mlx);
// 	else
// 		printf("\nops not mkx fail %d\n",(int)mlx);	
// }


// ex 2 && ex 3
// mlx_xpmfilr to img to add Load an XPM image and print its width and height to the terminal.

// int main() {
//     void *mlx = mlx_init();
//     void *win = mlx_new_window(mlx, 800, 600, "so_long");
//     int img_width, img_height;
//     void *img = mlx_xpm_file_to_image(mlx, "wall.xpm", &img_width, &img_height);
//     mlx_put_image_to_window(mlx, win, img, (800 - img_width) / 2, (600 - img_height) / 2);
// 	sleep(5);
// 	mlx_destroy_image(mlx,img);
//     mlx_loop(mlx);
//     return (0);
// }


// int handle_keypress(int keypressed) {
//     printf("Key pressed: %d\n", keypressed);
// 	if (keypressed == 3)
// 	{
// 		exit(1);
// 	}
//     return (0);
// }

// int main() {
//     void *mlx = mlx_init();
//     void *win = mlx_new_window(mlx, 800, 600, "so_long");
//     mlx_hook(win, 2, 1L << 0, handle_keypress, mlx); // 2 = KeyPress
//     mlx_loop(mlx);
//     return (0);
// }

// int main()
// {
// 	void *mlx = mlx_init();
// 	void *window = mlx_new_window(mlx,800,800,"put 10*10 red pix");
// 	mlx_pixel_put(mlx, window, 100, 100, 0xFF0000);
// 	int i, j;
// 	i = -1;
// 	while(++i <= 10)
// 	{
// 		j = -1;
// 		while(++j <= 10 )
// 		{
// 			mlx_pixel_put(mlx, window, i, j, 0xFF0000);
// 		}
// 	}
// 	mlx_loop(mlx);
// 	return (0);
// }

// int main() {
//     void *mlx = mlx_init();
//     void *win = mlx_new_window(mlx, 800, 600, "so_long");
//     int img_width, img_height;
//     void *img = mlx_xpm_file_to_image(mlx, "wall.xpm", &img_width, &img_height);
//     int bpp, size_line, endian;
//     char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
//     for (int y = 0; y < img_height; y++) {
//         for (int x = 0; x < img_width; x++) {
//             int pixel = y * size_line + x * (bpp / 10);
//             data[pixel] = (data[pixel] + data[pixel + 1] + data[pixel + 2]) / 3; // Grayscale
//         }
//     }
//     mlx_put_image_to_window(mlx, win, img, 100, 100);
//     mlx_loop(mlx);
//     return (0);
// }



// int render_frame() {
//     printf("...\n");
//     return (0);
// }

// int main() {
//     void *mlx = mlx_init();
//     void *win = mlx_new_window(mlx, 800, 600, "so_long");
// 	(void)win;
//     mlx_loop_hook(mlx, render_frame, mlx);
//     mlx_loop(mlx);
//     return (0);
// }

//Project: Mini Graphics Editor
// will add if left cursor add in green color 
/* ---------- */
//struct
typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	char *img_data;
	int img_wid;
	int img_hei;
	int bpp;
	int size_len;
	int endian;
}t_data;

// handing mouse 
int mouse_handle(int button, int x, int y, t_data *data)
{
	if (button == 1)
		mlx_pixel_put(data->mlx,data->win, x, y ,0xFF0000);
//#00FF00 green
	else if (button == 2)
		mlx_pixel_put(data->mlx,data->win, x, y ,0x00FF00);
	return (0);
}
// handing keys  
int handle_key(int key, t_data *data)
{
	if (key == 53) // ESC key
		exit (0);
	else if (key == 8) // C
		mlx_clear_window(data->mlx, data->win);
	else if (key == 37) // lL
		mlx_put_image_to_window(data->mlx,data->win, data->img,50,50);
	return 0;
	}
//close window
int close_window()
{
	exit(0);
}
// main function

int main()
{
	t_data data;
	// intlize mlx and window
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx,800,600, "Mini Graphics Editor");
	// load img xpm and protect it
	data.img = mlx_xpm_file_to_image(data.mlx , "wall.xpm",&data.img_wid,&data.img_hei);
	if (!data.img)
		return(printf("\nFailed to load the image. \n"),1);
	// data image data to edit
	data.img_data = mlx_get_data_addr(data.img,&data.bpp,&data.size_len,&data.endian);
	// register hooks 
	mlx_hook(data.win,2,1L<<0,handle_key,&data);
	mlx_hook(data.win, 4, 1L<<2, mouse_handle,&data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	// start mlx loop
	mlx_loop(data.mlx);

	
}
