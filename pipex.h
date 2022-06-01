
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_grp
{
	char	*cmd1path;
	char	**cmdpaths;
	char	*cmd2path;
	int		infilefd;
	int		outfilefd;
	char	*pathlist;
}	t_grp;

int		ft_parsing(t_grp *pipex, int argc, char **argv, char **envp);
void	ft_get_init(t_grp *pipex);
void	ft_get_fd(t_grp *pipex, int argc, char **argv);
char	*ft_get_cmdpath(char *argcmd, char **envp);
char	*ft_get_cmdpathbis(char *path, char **cmd, char **cmdpaths);
char	*ft_free_spliterr(char **to_free1, char **to_free2);
void	ft_free_split(char **to_free1, char **to_free2);
#endif