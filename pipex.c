#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_grp	*pipex;

	pipex = malloc(sizeof(t_grp));
	ft_get_init(pipex);
	ft_parsing(pipex, argc, argv, envp);
	// ft_exec_cmd1(pipex);
	close (pipex->outfilefd);
	close (pipex->infilefd);
	return (0);
}

int	ft_parsing(t_grp *pipex, int argc, char **argv, char **envp)
{
	ft_get_fd(pipex, argc, argv);
	pipex->cmd1path = ft_get_cmdpath(argv[2], envp);
	printf("%s\n", pipex->cmd1path);
	printf("%d\n", pipex->infilefd);
	pipex->cmd2path = ft_get_cmdpath(argv[3], envp);
	printf("%s\n", pipex->cmd2path);
	printf("%d\n", pipex->outfilefd);
	return (1);
}

void	ft_get_init(t_grp *pipex)
{
	pipex->cmd1path = NULL;
	pipex->cmd2path = NULL;
	pipex->pathlist = NULL;
}

void	ft_get_fd(t_grp *pipex, int argc, char **argv)
{
	pipex->infilefd = open(argv[1], 0, O_RDONLY);
	pipex->outfilefd = open(argv[argc - 1], 0, O_RDONLY);
}

char	*ft_get_cmdpath(char *argcmd, char **envp)
{
	char	**cmd;
	char	*path;
	char	**cmdpaths;
	int		i;

	i = 0;
	cmd = ft_split(argcmd, ' ');
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	cmdpaths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (cmdpaths[++i] != NULL)
	{
		path = ft_strjoin(cmdpaths[i], "/");
		if (path == NULL)
			return (ft_free_spliterr(cmd, cmdpaths));
		path = ft_get_cmdpathbis(path, cmd, cmdpaths);
		if (path != NULL)
			return (path);
	}
	// ft_free_split(cmd, cmdpaths);
	return ("ha tu m'as eu batard");
}

char	*ft_get_cmdpathbis(char *path, char **cmd, char **cmdpaths)
{
	path = ft_strjoin(path, cmd[0]);
	if (path == NULL)
		return (ft_free_spliterr(cmd, cmdpaths));
	if (access(path, X_OK) == 0)
	{
		ft_free_split(cmd, cmdpaths);
		return (path);
	}
	return (NULL);
}

char	*ft_free_spliterr(char **to_free1, char **to_free2)
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

void	ft_exec_cmd1(t_grp *pipex)
{
	fork();
	ft_change_fd1(pipex);
}

void	ft_change_fd1(t_grp *pipex)
{
	pipe(pipefd);
	dup2(pipex->infilefd, 0);
	dup2(p, 1);
}

/*
preparer des fork pour faire des enfants
dans ses enfants on dub les file 1 et 2
pour changer leurs sorties et entrees
quand tout est set on real les execve
qui vont kill les 2 gosses
*/