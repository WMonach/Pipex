#include "pipex.h"

void	ft_exec_cmd(t_grp *pipex, char **envp, int pid)
{
	pipex->pid[pid] = fork();
	printf("ha\n");
	if (pipex->pid[pid] < 0)
	{
		perror("error");
		ft_exit_error(pipex);
	}
	if (pipex->pid[pid] == 0)
	{
		if (pid % 2 == 0)
			ft_change_fd1(pipex, envp);
		if (pid % 2 == 1)
			ft_change_fd2(pipex, envp);
	}
}

void	ft_change_fd1(t_grp *pipex, char **envp)
{
	int	i;

	i = 0;
	if (dup2(pipex->infilefd, 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[1], 1) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[0]) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmd1path, pipex->cmd1, envp) == -1)
		ft_exit_error(pipex);
}

void	ft_change_fd2(t_grp *pipex, char **envp)
{
	int	i;

	i = 0;
	if (dup2(pipex->outfilefd, 1) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[0], 0) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[1]) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmd2path, pipex->cmd2, envp) == -1)
		ft_exit_error(pipex);
}
