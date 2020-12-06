#ifndef SDT_DEF_H
# define SDT_DEF_H
/* SDL config defines */
# define WIN_NAME "default"
# define WIN_H 0
# define WIN_W 0
# define WIN_X 0
# define WIN_Y 0
# define WIN_FLAGS 0

# define MOUSE_IN 0
# define KEY_IN 0

# define SCREEN_DIVX 5
# define SCREEN_DIVY 5

# define VAL 0

# if WIN_H == 0 || WIN_W == 0
#   error "Window size is not defined in SDT_def.h"
# endif
/* Colors */

# define WHITE 	0xFfFfFf
# define BLACK 0x000000

# define RED 	0xFF0000
# define GREEN 	0x00FF00
# define YELLOW 0xFFFF00
# define ORANGE 0xFF8000
# define VIOLET 0x7F00FF
# define SILVER	0xC0C0C0
# define GREY	0x808080
# define MAROON	0x800000
# define OLIVE	0x808000
# define PURPLE	0x800080
# define TEAL	0x008080
# define NAVY	0x000080

# define B_NUIT 	0x000033
# define B_TERNE	0x000066
# define B_NAVAL	0x000099
# define B_FONCE	0x0000cc
# define BLUE		0x0000ff
# define LIGHT_B	0x3232ff
# define B_PALI 	0x6666ff
# define B_CIEL 	0x9999ff
# define B_PALE 	0xccccff



#endif
