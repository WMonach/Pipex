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
	ft_close_all_fd(pipex, 0);
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

	perror(err);
	i = 0;
	while (pipex->cmdpaths && pipex->cmdpaths[i] != NULL)
		free(pipex->cmdpaths[i++]);
	free(pipex->cmdpaths);
	free(pipex->pid);
	if (pipex->pipefd != NULL)
		ft_close_all_fd(pipex, 0);
	else if (pipex->pipefd == NULL)
		ft_close_fd(pipex);
	free(pipex->pipefd);
	free(pipex->cmds);
	free(pipex);
	exit(0);
}

void	ft_exit_error(t_grp *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmdpaths && pipex->cmdpaths[i] != NULL)
		free(pipex->cmdpaths[i++]);
	free(pipex->cmdpaths);
	free(pipex->pid);
	if (pipex->pipefd != NULL)
		ft_close_all_fd(pipex, 0);
	else if (pipex->pipefd == NULL)
		ft_close_fd(pipex);
	free(pipex->pipefd);
	free(pipex->cmds);
	free(pipex);
	exit(0);
}

void	ft_exit_strerror(t_grp *pipex, char *error)
{
	int	i;

	ft_putstr_fd(error, 0);
	i = 0;
	while (pipex->cmdpaths && pipex->cmdpaths[i] != NULL)
		free(pipex->cmdpaths[i++]);
	free(pipex->cmdpaths);
	free(pipex->pid);
	if (pipex->pipefd != NULL)
		ft_close_all_fd(pipex, 0);
	else if (pipex->pipefd == NULL)
		ft_close_fd(pipex);
	free(pipex->pipefd);
	free(pipex->cmds);
	free(pipex);
	exit(0);
}
