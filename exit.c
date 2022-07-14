#include "pipex.h"

char	*exit_cmdpath(char **cmd, char **cmdpaths, t_grp *pipex)
{
	ft_putstr_fd(cmd[0], 0);
	ft_putstr_fd(": command not found\n", 0);
	ft_free_split(cmd, cmdpaths);
	ft_exit_error(pipex);
	return (NULL);
}

void	ft_exit_strerror(t_grp *pipex, char *error)
{
	int	i;

	ft_putstr_fd(error, 0);
	if (pipex->cmds != NULL)
		free_cmd(pipex);
	if (pipex->cmdspath != NULL)
	{
		i = -1;
		while (pipex->cmdspath[++i] != NULL)
			free(pipex->cmdspath[i]);
		free(pipex->cmdspath);
	}
	ft_delone((void *)(pipex->pid));
	if (pipex->pipefd != NULL)
		ft_close_all_fd(pipex, 0);
	else if (pipex->pipefd == NULL)
		ft_close_fd(pipex);
	ft_delone((void *)(pipex->pipefd));
	free(pipex);
	exit(0);
}

void	ft_exit_error(t_grp *pipex)
{
	int	i;

	if (pipex->cmds != NULL)
		free_cmd(pipex);
	if (pipex->cmdspath != NULL)
	{
		i = -1;
		while (pipex->cmdspath[++i] != NULL)
			free(pipex->cmdspath[i]);
		free(pipex->cmdspath);
	}
	ft_delone((void *)(pipex->pid));
	if (pipex->pipefd != NULL)
		ft_close_all_fd(pipex, 0);
	else if (pipex->pipefd == NULL)
		ft_close_fd(pipex);
	ft_delone((void *)(pipex->pipefd));
	free(pipex);
	exit(0);
}

void	ft_exit_perror(t_grp *pipex, char *err)
{
	int	i;

	perror(err);
	if (pipex->cmds != NULL)
		free_cmd(pipex);
	if (pipex->cmdspath != NULL)
	{
		i = -1;
		while (pipex->cmdspath[++i] != NULL)
			free(pipex->cmdspath[i]);
		free(pipex->cmdspath);
	}
	if (pipex->pid != NULL)
		free(pipex->pid);
	if (pipex->pipefd != NULL)
		ft_close_all_fd(pipex, 0);
	else if (pipex->pipefd == NULL)
		ft_close_fd(pipex);
	if (pipex->pipefd != NULL)
		free(pipex->pipefd);
	free(pipex);
	exit(0);
}

void	free_cmd(t_grp *pipex)
{
	int	i;
	int	j;


	i = -1;
	while (pipex->cmds[++i] != NULL)
	{
		j = -1;
		while (pipex->cmds[i][++j] != NULL)
			free(pipex->cmds[i][j]);
		free(pipex->cmds[i]);
	}
	free(pipex->cmds);
}