#include "pipex.h"

void	ft_get_pid(t_grp *pipex, int pidnbr)
{
	pipex->pid = malloc(sizeof(int) * pidnbr);
	if (pipex->pid == NULL)
		ft_exit_perror(pipex, "alloc");
	pipex->pidnbr = pidnbr;
}

void	ft_get_fd(t_grp *pipex, char **argv, int pidnbr)
{
	pipex->infilefd = open(argv[1], O_RDONLY);
	pipex->outfilefd = open(argv[pidnbr + 2],
			O_CREAT | O_RDWR | O_TRUNC, 0000644);
}

char	**ft_get_cmd(char *argcmd)
{
	char	**cmd;

	cmd = ft_split(argcmd, ' ');
	return (cmd);
}

void	ft_get_init(t_grp *pipex)
{
	pipex->pid = NULL;
	pipex->cmdspath = NULL;
	pipex->cmds = NULL;
	pipex->pipefd = NULL;
}
