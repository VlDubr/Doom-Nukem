#include "doom.h"

t_anim			setanim(t_tga *frame, int maxframe)
{
	t_anim r;

	r.frame = frame;
	r.thisframe = frame[0];
	r.maxframe = maxframe;
	r.countframe = 0;
	r.state = 0;
	return (r);
}

void			startanim(t_anim *anim)
{
	anim->state = 1;
}

void			stopanim(t_anim *anim)
{
	anim->state = 0;
	anim->countframe = 0;
}

void			pauseanim(t_anim *anim)
{
	anim->state = 2;
}

void			unpauseanim(t_anim *anim)
{
	anim->state ^= 2;
}

void			nextframe(t_anim *anim)
{
	anim->countframe++;
	if (anim->countframe >= anim->maxframe)
		anim->countframe = 0;
	anim->thisframe = anim->frame[anim->countframe];
}

void			previousframe(t_anim *anim)
{
	anim->countframe--;
	if (anim->countframe <= 0)
		anim->countframe = anim->maxframe - 1;
	anim->thisframe = anim->frame[anim->countframe];
}
