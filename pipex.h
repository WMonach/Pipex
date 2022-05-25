
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

typedef struct s_grp
{
	char	*cmd1path;
	char	*cmd2path;
	int		infilefd;
	int		outfilefd;
}	t_grp;
#endif