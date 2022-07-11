#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_grp	*pipex;
	int		i;

	if (ft_check(argc, argv) == -1)
		return (1);
	pipex = malloc(sizeof(t_grp));
	if (pipex == NULL)
		return (1);
	ft_get_init(pipex);
	ft_parsing(pipex, argv, envp, argc - 3);
	i = -1;
	printf("%s\n", pipex->cmdspath[0]);
	while (++i < pipex->pidnbr)
	{
		ft_exec_cmd(pipex, envp, i);
	}
	if (ft_close_fd(pipex, 0) == -1)
		return (1);
	ft_waitpid(pipex);
	return (0);
}

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	ft_waitpid(t_grp *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pidnbr)
		waitpid(pipex->pid[i], NULL, 0);
}

int	ft_close_fd(t_grp *pipex, int i)
{
	if (close(pipex->infilefd) == -1)
		return (-1);
	if (close(pipex->outfilefd) == -1)
		return (-1);
	while (i < (pipex->pidnbr - 1) * 2)
		if (close(pipex->pipefd[i++]) == -1)
			return (-1);
	return (0);
}
