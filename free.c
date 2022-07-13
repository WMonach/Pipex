#include "pipex.h"

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

void	ft_exit_perror(t_grp *pipex, char *err)
{
	int	i;
	int	j;

	perror(err);
	if (pipex->cmds != NULL)
	{
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

void	ft_exit_error(t_grp *pipex)
{
	int	i;
	int	j;

	if (pipex->cmds != NULL)
	{
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
	if (pipex->cmdspath != NULL)
	{
		i = -1;
		while (pipex->cmdspath[++i] != NULL)
			free(pipex->cmdspath[i]);
		free(pipex->cmdspath);
	}
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

void	ft_exit_strerror(t_grp *pipex, char *error)
{
	int	i;
	int	j;

	ft_putstr_fd(error, 0);
	if (pipex->cmds != NULL)
	{
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

int	ft_free_all(t_grp *pipex)
{
	int	i;
	int	j;

	if (pipex->cmds != NULL)
	{
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
	if (pipex->cmdspath != NULL)
	{
		i = -1;
		while (pipex->cmdspath[++i] != NULL)
			free(pipex->cmdspath[i]);
		free(pipex->cmdspath);
	}
	free(pipex->pid);
	if (pipex->pipefd != NULL)
		free(pipex->pipefd);
	free(pipex);
	return (1);
}
