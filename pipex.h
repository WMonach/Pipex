
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_grp
{
	char	*cmd1path;
	char	*cmd2path;
	int		infilefd;
	int		outfilefd;
	char	*pathlist;
}	t_grp;

int		ft_parsing(t_grp *pipex, int argc, char **argv);
void	ft_get_init(t_grp *pipex);
void	ft_get_fd(t_grp *pipex, int argc, char **argv);
void	ft_get_cmdpath(t_grp *pipex, int argc, char **argv);
#endif