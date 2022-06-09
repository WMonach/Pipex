#include "pipex.h"

char	**ft_get_cmd(char *argcmd)
{
	char	**cmd;
	int		i;

	i = 0;
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

void	ft_get_fd(t_grp *pipex, char **argv)
{
	pipex->infilefd = open(argv[1], O_RDONLY);
	pipex->outfilefd = open(argv[4], O_RDWR);
}

void	ft_parsing(t_grp *pipex, char **argv, char **envp, int pidnbr)
{
	ft_get_fd(pipex, argv);
	printf("%d\n", pipex->outfilefd);
	if (pipex->infilefd < 0)
		perror("infile");
	if (pipex->outfilefd < 0)
		perror("outfile");
	ft_get_pid(pipex, pidnbr);
	pipex->cmd1path = ft_get_cmdpath(pipex, argv[2], envp);
	if (pipex->cmd1path == NULL)
		ft_exit_error(pipex);
	pipex->cmd2path = ft_get_cmdpath(pipex, argv[3], envp);
	if (pipex->cmd1path == NULL)
		ft_exit_error(pipex);
	pipex->cmd1 = ft_get_cmd(argv[2]);
	if (pipex->cmd1 == NULL)
		ft_exit_error(pipex);
	pipex->cmd2 = ft_get_cmd(argv[3]);
	if (pipex->cmd2 == NULL)
		ft_exit_error(pipex);
}
