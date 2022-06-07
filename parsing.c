#include "pipex.h"

char	**ft_get_cmd(char *argcmd)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(argcmd, ' ');
	if (cmd == NULL)
	{
		while (cmd[i] != NULL)
			free(cmd[i++]);
		free(cmd);
		return (NULL);
	}
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
	ft_free_split(cmd, cmdpaths);
	return ("ha tu m'as eu batard");
}

void	ft_get_pid(t_grp *pipex)
{
	pipex->pid = malloc(sizeof(int) * 3);
	pipex->pidnbr = 2;
}

void	ft_get_fd(t_grp *pipex, char **argv)
{
	pipex->infilefd = open(argv[1], 0, O_RDONLY);
	pipex->outfilefd = open(argv[4], 0, O_RDONLY);
}

void	ft_parsing(t_grp *pipex, char **argv, char **envp)
{
	ft_get_fd(pipex, argv);
	ft_get_pid(pipex);
	pipex->cmd1path = ft_get_cmdpath(argv[2], envp);
	if (pipex->cmd1path == NULL)
		ft_exit_error(pipex);
	pipex->cmd2path = ft_get_cmdpath(argv[3], envp);
	if (pipex->cmd1path == NULL)
		ft_exit_error(pipex);
	pipex->cmd1 = ft_get_cmd(argv[2]);
	if (pipex->cmd1 == NULL)
		ft_exit_error(pipex);
	pipex->cmd2 = ft_get_cmd(argv[3]);
	if (pipex->cmd2 == NULL)
		ft_exit_error(pipex);
}
