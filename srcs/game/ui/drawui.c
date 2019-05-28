#include "doom.h"

void	drawui(t_doom *doom)
{
	drawbar(doom->win->pixels, setbar(setrgba(255, 255, 0, 0), setfvector2d(0, 0),
	setfvector2d(flerp(0, 200, ((float)1 / doom->player.maxstamina)
	* doom->player.stamina), 10)));
	drawbar(doom->win->pixels, setbar(setrgba(255, 0, 255, 0), setfvector2d(0, 10),
	setfvector2d(flerp(0, 200, ((float)1 / doom->player.maxhealth)
	* doom->player.health), 10)));
	drawoptionmenu(doom);
}
