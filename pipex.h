#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <errno.h>
# include <sys/wait.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_ENVP "Environment"
# define ERR_CMD "Command not found: "

typedef struct s_grp
{
	char	**cmdspath;
	char	***cmds;
	int		infilefd;
	int		outfilefd;
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
char	*ft_free_spliterr(t_grp *pipex, char **to_free1, char **to_free2);
char	*ft_get_cmdpath(t_grp *pipex, char *argcmd, char **envp);
char	*ft_get_cmdpathbis(t_grp *pipex, char *path, char **cmd,
			char **cmdpaths);
void	ft_open_file(int pidnbr, char **argv, t_grp *pipex);
void	ft_init_cmds(int pidnbr, char **argv, t_grp *pipex);
void	ft_init_cmdspath(int pidnbr, char **argv, char **envp, t_grp *pipex);
int		ft_init_pipe(t_grp *pipex, int pidnbr);

/*EXEC*/
void	ft_exec_cmd(t_grp *pipex, char **envp, int pid);
void	ft_change_fdfirst(t_grp *pipex, char **envp, int pid);
void	ft_exec_cmd2(t_grp *pipex, char **envp);
void	ft_change_fdlast(t_grp *pipex, char **envp, int pid);
void	ft_change_fd(t_grp *pipex, char **envp, int pid);

void	ft_get_pid(t_grp *pipex, int pidnbr);
void	ft_waitpid(t_grp *pipex);
int		ft_check(int argc, char **argv);
void	ft_change_fd_mid(t_grp *pipex, char **envp, int pid);
int		ft_close_all_fd(t_grp *pipex, int i);
int		ft_close_fd(t_grp *pipex);

void	ft_exit_strerror(t_grp *pipex, char *error);
void	ft_error(char *str);
void	ft_exit_perror(t_grp *pipex, char *err);
void	ft_exit_error(t_grp *pipex);
int		ft_free_all(t_grp *pipex);
char	*exit_cmdpath(char **cmd, char **cmdpaths, t_grp *pipex);
char	*free_cmd_without_path(char **cmd);
#endif