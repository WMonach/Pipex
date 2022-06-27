#include "pipex.h"

void	ft_change_fd(t_grp *pipex, char **envp, int pid)
{
	pipex->fdwrite = (pid * 2) + 1;
	pipex->fdread = pipex->fdwrite - 3;
	dprintf(2, "fd read and write = %d, %d\n", pipex->fdread, pipex->fdwrite);
	if (dup2(pipex->pipefd[pipex->fdread], 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[pipex->fdwrite], 1) == -1)
		ft_exit_error(pipex);
	if (ft_close_fd(pipex, 0) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}

void	ft_exec_cmd(t_grp *pipex, char **envp, int pid)
{
	pipex->pid[pid] = fork();
	if (pipex->pid[pid] < 0)
	{
		perror("error");
		ft_exit_error(pipex);
	}
	if (pipex->pid[pid] == 0)
	{
		printf("pipex->pidnbr=%d\n", pipex->pidnbr);
		if (pid == 0)
			ft_change_fdfirst(pipex, envp, pid);
		else if (pid == pipex->pidnbr - 1)
			ft_change_fdlast(pipex, envp, pid);
		else
			ft_change_fd(pipex, envp, pid);
	}
}

void	ft_change_fdfirst(t_grp *pipex, char **envp, int pid)
{
	if (dup2(pipex->infilefd, 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[1], 1) == -1)
		ft_exit_error(pipex);
	if (ft_close_fd(pipex, 0) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}

void	ft_change_fdlast(t_grp *pipex, char **envp, int pid)
{
	if (dup2(pipex->outfilefd, 1) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[pid * 2 - 2], 0) == -1)
		ft_exit_error(pipex);
	if (ft_close_fd(pipex, 0) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}
