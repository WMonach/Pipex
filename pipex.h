
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_grp
{
	char	*cmd1path;
	char	*cmd2path;
	int		fd1;
	int		fd2;
}	t_grp;
#endif