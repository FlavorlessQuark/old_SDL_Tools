# include "SDT_update.c"

static void	SDT_Render()
{
	C_Dict	objs;
	int 		size;
	int			i;

	objs = SDT_SceneGet()->objects;
	size = objs.size;
	i = 0;
	while (i < size)
	{
		/* This might need to be a linked list too >.< */
	}
}

static void	SDT_Events();
static void	SDT_Inputs();

void	SDT_Update()
{
	SDT_Inputs();
	SDT_Events();
	SDT_Render();
}
