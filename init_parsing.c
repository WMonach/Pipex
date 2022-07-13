#include "pipex.h"

void	ft_init_cmds(int pidnbr, char **argv, t_grp *pipex)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (pidnbr + 1));
	if (pipex->cmds == NULL)
		ft_exit_error(pipex);
	pipex->cmds[pidnbr] = NULL;
	pipex->cmds[0] = NULL;
	while (++i < pidnbr)
	{
		pipex->cmds[i] = ft_get_cmd(argv[j++]);
		if (pipex->cmds[i] == NULL)
			ft_exit_error(pipex);
	}
}

void	ft_init_cmdspath(int pidnbr, char **argv, char **envp, t_grp *pipex)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	pipex->cmdspath = (char **)malloc(sizeof(char *) * (pidnbr + 1));
	if (pipex->cmdspath == NULL)
		ft_exit_error(pipex);
	pipex->cmdspath[pidnbr] = NULL;
	while (++i < pidnbr)
	{
		pipex->cmdspath[i] = ft_get_cmdpath(pipex, argv[j++], envp);
		if (pipex->cmdspath[i] == NULL)
			ft_exit_perror(pipex, ERR_CMD);
	}
}

int	ft_init_pipe(t_grp *pipex, int pidnbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pipex->pipefd = malloc(sizeof(int) * ((pidnbr - 1) * 2));
	while (i < pidnbr - 1)
	{
		if (pipe(pipex->pipefd + j) < 0)
			return (0);
		j += 2;
		i++;
	}
	return (1);
}
