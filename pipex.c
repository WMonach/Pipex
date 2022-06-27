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
	while (++i < pipex->pidnbr)
	{
		ft_exec_cmd(pipex, envp, i);
	}
	if (ft_close_fd(pipex, 0) == -1)
		return (1);
	ft_waitpid(pipex);
	return (0);
}

void	ft_get_init(t_grp *pipex)
{
	pipex->cmd1path = NULL;
	pipex->cmd2path = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->cmdpaths = NULL;
	pipex->pid = NULL;
	pipex->cmdspath = NULL;
	pipex->cmds = NULL;
	pipex->pipefd = NULL;
}

char	*ft_free_spliterr(t_grp *pipex, char **to_free1, char **to_free2)
{
	int	i;

	i = -1;
	while (to_free1[++i] != NULL)
		free(to_free1[i]);
	free(to_free1);
	i = -1;
	while (to_free2[++i] != NULL)
		free(to_free2[i]);
	free(to_free2);
	free(pipex);
	exit(0);
	return (NULL);
}

void	ft_free_split(char **to_free1, char **to_free2)
{
	int	i;

	i = -1;
	while (to_free1[++i] != NULL)
		free(to_free1[i]);
	free(to_free1);
	i = -1;
	while (to_free2[++i] != NULL)
		free(to_free2[i]);
	free(to_free2);
}

void	ft_error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	ft_exit_perror(t_grp *pipex, char *err)
{
	int	i;

	i = 0;
	perror(err);
	free(pipex->cmd1path);
	free(pipex->cmd2path);
	while (pipex->cmd1 && pipex->cmd1[i] != NULL)
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while (pipex->cmd2 && pipex->cmd2[i] != NULL)
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
	i = 0;
	while (pipex->cmdpaths && pipex->cmdpaths[i] != NULL)
		free(pipex->cmdpaths[i++]);
	free(pipex->cmdpaths);
	free(pipex->pid);
	ft_close_fd(pipex, 0);
	free(pipex->pipefd);
	free(pipex);
	exit(0);
}

void	ft_exit_error(t_grp *pipex)
{
	int	i;

	i = 0;
	free(pipex->cmd1path);
	free(pipex->cmd2path);
	while (pipex->cmd1 && pipex->cmd1[i] != NULL)
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while (pipex->cmd2 && pipex->cmd2[i] != NULL)
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
	i = 0;
	while (pipex->cmdpaths && pipex->cmdpaths[i] != NULL)
		free(pipex->cmdpaths[i++]);
	free(pipex->cmdpaths);
	free(pipex->pid);
	ft_close_fd(pipex, 0);
	free(pipex->pipefd);
	free(pipex);
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
	i = 0;
	while (i < (pipex->pidnbr - 1) * 2)
		if (close(pipex->pipefd[i++]) == -1)
			return (-1);
	return (0);
}
