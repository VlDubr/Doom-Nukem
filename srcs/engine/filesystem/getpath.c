#include "filesystem.h"

char		*getpath(const char *argv0)
{
	char	*r;
	size_t	len;

	len = ft_strlen(argv0);
	while (argv0[len] != '/')
		len--;
	len++;
	r = ft_strsub(argv0, 0, len);
	return (r);
}
