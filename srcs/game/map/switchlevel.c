#include "doom.h"

void	switchlevel(t_doom *doom, size_t level)
{
	if (level < doom->mapcount && level >= 0)
	{
		doom->thismap = doom->maps[level];
		doom->player.sector = isinside(
		setfvector2d(doom->thismap.startplayer.pos.x,
		doom->thismap.startplayer.pos.z), doom->thismap, 0);
		doom->player.pos = doom->thismap.startplayer.pos;
		doom->player.rotate = doom->thismap.startplayer.rotate;
	}
}
