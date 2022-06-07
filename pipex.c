#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_grp	*pipex;
	int		pipefd[2];

	if (argc != 5)
		return (1);
	if (pipe(pipefd) < 0)
		return (1);
	pipex = malloc(sizeof(t_grp));
	ft_get_init(pipex);
	ft_parsing(pipex, argv, envp);
	ft_exec_cmd1(pipex, pipefd, envp);
	ft_exec_cmd2(pipex, pipefd, envp);
	ft_waitpid(pipex);
	close (pipex->outfilefd);
	close (pipex->infilefd);
	return (0);
}

void	ft_get_init(t_grp *pipex)
{
	pipex->cmd1path = NULL;
	pipex->cmd2path = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->cmdpaths = NULL;
}

char	*ft_free_spliterr(char **to_free1, char **to_free2)
{
	int	i;

	i = -1;
	printf("ERROR : split_error\n");
	while (to_free1[++i] != NULL)
		free(to_free1[i]);
	free(to_free1);
	i = -1;
	while (to_free2[++i] != NULL)
		free(to_free2[i]);
	free(to_free2);
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

void	ft_exit_error(t_grp *pipex)
{
	int	i;

	i = 0;
	printf("ERROR : exec_error\n");
	free(pipex->cmd1path);
	free(pipex->cmd2path);
	while (pipex->cmd1[i] != NULL)
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while (pipex->cmd2[i] != NULL)
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
	i = 0;
	while (pipex->cmdpaths[i] != NULL)
		free(pipex->cmdpaths[i++]);
	free(pipex->cmdpaths);
	close(pipex->infilefd);
	close(pipex->outfilefd);
	free(pipex);
	exit(0);
}

void	ft_waitpid(t_grp *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pidnbr)
	{
		waitpid()
	}
}
/*
preparer des fork pour faire des enfants
dans ses enfants on dub les file 1 et 2
pour changer leurs sorties et entrees
quand tout est set on real les execve
qui vont kill les 2 gosses
*/