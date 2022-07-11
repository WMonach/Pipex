#include "pipex.h"


char	*ft_get_cmdpathbis(t_grp *pipex, char *path, char **cmd, char **cmdpaths)
{
	path = ft_strjoin(path, cmd[0]);
	if (path == NULL)
		return (ft_free_spliterr(pipex, cmd, cmdpaths));
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
	if (access(cmd[0], X_OK) == 0)
	{
		return (cmd[0]);
	}
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	cmdpaths = ft_split(envp[i] + 5, ':');
	if (cmdpaths == NULL)
		return (NULL);
	i = -1;
	while (cmdpaths[++i] != NULL)
	{
		path = ft_strjoin(cmdpaths[i], "/");
		if (path == NULL)
			return (ft_free_spliterr(pipex, cmd, cmdpaths));
		path = ft_get_cmdpathbis(pipex, path, cmd, cmdpaths);
		if (path != NULL)
		{
			return (path);
		}
	}
	printf("%s: command not found\n", cmd[0]);
	ft_free_split(cmd, cmdpaths);
	ft_exit_error(pipex);
	return (NULL);
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

void	ft_parsing(t_grp *pipex, char **argv, char **envp, int pidnbr)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	ft_get_fd(pipex, argv, pidnbr);
	if (pipex->infilefd < 0)
		ft_exit_perror(pipex, argv[1]);
	if (pipex->outfilefd < 0)
		ft_exit_perror(pipex, argv[pidnbr + 2]);
	ft_get_pid(pipex, pidnbr);
	if (ft_init_pipe(pipex, pidnbr) == 0)
		ft_exit_perror(pipex, ERR_PIPE);
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
	i = -1;
	j = 2;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (pidnbr + 1));
	pipex->cmds[pidnbr] = NULL;
	while (++i < pidnbr)
	{
		pipex->cmds[i] = ft_get_cmd(argv[j++]);
		if (pipex->cmds[i] == NULL)
			ft_exit_error(pipex);
	}
}
