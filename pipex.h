
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <errno.h>
# include <sys/wait.h>

typedef struct s_grp
{
	char	*cmd1path;
	char	**cmdpaths;
	char	*cmd2path;
	char	**cmdspath;
	char	***cmds;
	int		infilefd;
	int		outfilefd;
	char	**cmd1;
	char	**cmd2;
	int		*pid;
	int		pidnbr;
	int		*pipefd;
	int		fdwrite;
	int		fdread;
}	t_grp;

/*PARSING*/
void	ft_parsing(t_grp *pipex, char **argv, char **envp, int pidnbr);
void	ft_get_init(t_grp *pipex);
void	ft_get_fd(t_grp *pipex, char **argv, int pidnbr);
void	ft_free_split(char **to_free1, char **to_free2);
char	**ft_get_cmd(char *argcmd);
char	*ft_free_spliterr(char **to_free1, char **to_free2);
char	*ft_get_cmdpath(t_grp *pipex, char *argcmd, char **envp);
char	*ft_get_cmdpathbis(char *path, char **cmd, char **cmdpaths);

/*EXEC*/
void	ft_exec_cmd(t_grp *pipex, char **envp, int pid);
void	ft_change_fdfirst(t_grp *pipex, char **envp, int pid);
void	ft_exec_cmd2(t_grp *pipex, char **envp);
void	ft_change_fdlast(t_grp *pipex, char **envp, int pid);
void	ft_change_fd(t_grp *pipex, char **envp, int pid);

void	ft_error(char *str);
void	ft_exit_error(t_grp *pipex);
void	ft_get_pid(t_grp *pipex, int pidnbr);
void	ft_waitpid(t_grp *pipex);
int		ft_check(int argc, char **argv);
void	ft_change_fd_mid(t_grp *pipex, char **envp, int pid);
#endif