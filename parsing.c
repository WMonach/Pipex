#include "pipex.h"

char	**ft_get_cmd(char *argcmd)
{
	char	**cmd;

	cmd = ft_split(argcmd, ' ');
	return (cmd);
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

char	*ft_get_cmdpath(t_grp *pipex, char *argcmd, char **envp)
{
	char	**cmd;
	char	*path;
	char	**cmdpaths;
	int		i;

	i = 0;
	cmd = ft_split(argcmd, ' ');
	if (cmd == NULL)
		return (NULL);
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	cmdpaths = ft_split(envp[i] + 5, ':');
	if (cmd == NULL)
		return (NULL);
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
	printf("command not found: %s\n", cmd[0]);
	ft_free_split(cmd, cmdpaths);
	ft_exit_error(pipex);
	return ("ha tu m'as eu batard");
}

void	ft_get_pid(t_grp *pipex, int pidnbr)
{
	pipex->pid = malloc(sizeof(int) * pidnbr);
	if (pipex->pid == NULL)
		ft_exit_error(pipex);
	pipex->pidnbr = pidnbr;
}

void	ft_get_fd(t_grp *pipex, char **argv, int pidnbr)
{
	pipex->infilefd = open(argv[1], O_RDONLY);
	pipex->outfilefd = open(argv[pidnbr + 2], O_RDWR);
}

int	ft_init_pipe(t_grp *pipex, int pidnbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pipex->pipefd = malloc(sizeof(int) * ((pidnbr) * 2));
	while (i < pidnbr)
	{
		if (pipe(pipex->pipefd + j) < 0)
			return (0);
		j += 2;
		i++;
	}
	// i = 0;
	// while (i < (pidnbr) * 2)
	// {
	// 	printf("%d\n", pipex->pipefd[i]);
	// 	i++;
	// }

	return (1);
}

void	ft_parsing(t_grp *pipex, char **argv, char **envp, int pidnbr)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	ft_get_fd(pipex, argv, pidnbr);
	if (pipex->infilefd < 0)
		perror("infile");
	if (pipex->outfilefd < 0)
		perror("outfile");
	ft_get_pid(pipex, pidnbr);
	if (ft_init_pipe(pipex, pidnbr) == 0)
	{
		printf("pipe error\n");
		ft_exit_error(pipex);
	}
	pipex->cmdspath = (char **)malloc(sizeof(char *) * (pidnbr + 1));
	while (++i < pidnbr)
	{
		pipex->cmdspath[i] = ft_get_cmdpath(pipex, argv[j++], envp);
		if (pipex->cmdspath[i] == NULL)
			ft_exit_error(pipex);
	}
	i = -1;
	j = 2;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (pidnbr + 1));
	while (++i < pidnbr)
	{
		pipex->cmds[i] = ft_get_cmd(argv[j++]);
		if (pipex->cmds[i] == NULL)
			ft_exit_error(pipex);
	}
}

/*

*/
