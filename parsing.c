#include "pipex.h"

char	*ft_get_cmdpathbis(t_grp *pipex, char *path, char **cmd,
	char **cmdpaths)
{
	char	*paths;


	paths = ft_strjoin(path, cmd[0]);
	free(path);
	if (paths == NULL)
		return (ft_free_spliterr(pipex, cmd, cmdpaths));
	if (access(paths, X_OK) == 0)
	{
		ft_free_split(cmd, cmdpaths);
		return (paths);
	}
	free(paths);
	return (NULL);
}

char	*ft_get_cmdpath(t_grp *pipex, char *argcmd, char **envp)
{
	char	**cmd;
	char	*path;
	char	**cmdpaths;
	int		i;

	cmd = ft_split(argcmd, ' ');
	if (cmd == NULL)
		return (NULL);
	if (access(cmd[0], X_OK) == 0)
		return (free_cmd_without_path(cmd));
	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	cmdpaths = ft_split(envp[i] + 5, ':');
	if (cmdpaths == NULL)
	{
		ft_free_split(cmd, cmdpaths);
		return (NULL);
	}
	i = -1;
	while (cmdpaths[++i] != NULL)
	{
		path = ft_strjoin(cmdpaths[i], "/");
		if (path == NULL)
			return (ft_free_spliterr(pipex, cmd, cmdpaths));
		path = ft_get_cmdpathbis(pipex, path, cmd, cmdpaths);
		if (path != NULL)
			return (path);
	}
	return (exit_cmdpath(cmd, cmdpaths, pipex));
}

void	ft_parsing(t_grp *pipex, char **argv, char **envp, int pidnbr)
{
	ft_get_fd(pipex, argv, pidnbr);
	ft_open_file(pidnbr, argv, pipex);
	ft_get_pid(pipex, pidnbr);
	if (ft_init_pipe(pipex, pidnbr) == 0)
		ft_exit_perror(pipex, ERR_PIPE);
	ft_init_cmdspath(pidnbr, argv, envp, pipex);
	ft_init_cmds(pidnbr, argv, pipex);
}

void	ft_open_file(int pidnbr, char **argv, t_grp *pipex)
{
	if (pipex->infilefd < 0)
		ft_exit_perror(pipex, argv[1]);
	if (pipex->outfilefd < 0)
		ft_exit_perror(pipex, argv[pidnbr + 2]);
}

char	*free_cmd_without_path(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i] != NULL)
		free(cmd[i]);
	free(cmd);
	return (cmd[0]);
}

char	*exit_cmdpath(char **cmd, char **cmdpaths, t_grp *pipex)
{
	ft_putstr_fd(cmd[0], 0);
	ft_putstr_fd(": command not found\n", 0);
	ft_free_split(cmd, cmdpaths);
	ft_exit_error(pipex);
	return (NULL);
}
