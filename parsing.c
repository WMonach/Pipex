#include "pipex.h"

char	**ft_get_cmd(char *argcmd)
{
	char	**cmd;

	cmd = ft_split(argcmd, ' ');
	if (cmd == NULL)
		ft_error("ft_get_cmd");
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

void	ft_get_fd(t_grp *pipex, char **argv)
{
	pipex->infilefd = open(argv[1], 0, O_RDONLY);
	pipex->outfilefd = open(argv[4], 0, O_RDONLY);
}

int	ft_parsing(t_grp *pipex, char **argv, char **envp)
{
	ft_get_fd(pipex, argv);
	pipex->cmd1path = ft_get_cmdpath(argv[2], envp);
	// printf("%s\n", pipex->cmd1path);
	printf("%d\n", pipex->infilefd);
	pipex->cmd2path = ft_get_cmdpath(argv[3], envp);
	// printf("%s\n", pipex->cmd2path);
	printf("%d\n", pipex->outfilefd);
	pipex->cmd1 = ft_get_cmd(argv[2]);
	pipex->cmd2 = ft_get_cmd(argv[4]);
	return (1);
}
