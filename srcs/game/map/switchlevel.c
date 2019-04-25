#include "doom.h"

void	switchlevel(t_doom *doom, size_t level)
{
	int mus;

	mus = -1;
	if (level < doom->mapcount)
	{
		if ((mus + 1) >= doom->sounds->music_count)
			mus = -1;
		mus++;
		Mix_PlayMusic(doom->sounds->game_mus[mus], -1);
		doom->thismap = doom->maps[level];
		doom->player.sector = isinside(
		setfvector2d(doom->thismap.startplayer.pos.x,
		doom->thismap.startplayer.pos.z), doom->thismap, 0);
		doom->player.pos = doom->thismap.startplayer.pos;
		doom->player.pos.y = doom->thismap.sectors[doom->player.sector].floor
		+ doom->player.height;
		doom->player.rotate = doom->thismap.startplayer.rotate;
	}
}
