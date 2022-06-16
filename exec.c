#include "pipex.h"

void	ft_change_fd(t_grp *pipex, char **envp, int pid)
{
	int	i;

	i = -1;
	pipex->fdwrite = pid * 2 + 1;
	pipex->fdread = pipex->fdwrite - 3;
	printf("pidfdmid=%d\nfdread=%d\nfdwrite=%d\n", pid, pipex->fdread, pipex->fdwrite);
	if (dup2(pipex->pipefd[pipex->fdread], 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[pipex->fdwrite], 1) == -1)
		ft_exit_error(pipex);
	if (close(pipex->outfilefd) == -1)
		ft_exit_error(pipex);
	if (close(pipex->infilefd) == -1)
		ft_exit_error(pipex);
	while (++i < pipex->fdread)
		if (close(pipex->pipefd[i]) == -1)
			ft_exit_error(pipex);
	i = pipex->fdread;
	while (++i < pipex->fdwrite)
		if (close(pipex->pipefd[i]) == -1)
			ft_exit_error(pipex);
	i = pipex->fdwrite;
	while (++i < (pipex->pidnbr) * 2)
		if (close(pipex->pipefd[i]) == -1)
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
		if (pid == 0)
			ft_change_fdfirst(pipex, envp, pid);
		if (pid == pipex->pidnbr - 1)
			ft_change_fdlast(pipex, envp, pid);
		else
			ft_change_fd(pipex, envp, pid);
	}
}

void	ft_change_fdfirst(t_grp *pipex, char **envp, int pid)
{
	int	i;

	i = 1;
	if (dup2(pipex->infilefd, 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[1], 1) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[0]) == -1)
		ft_exit_error(pipex);
	if (close(pipex->outfilefd) == -1)
		ft_exit_error(pipex);
	while (++i < (pipex->pidnbr) * 2)
		if (close(pipex->pipefd[i]))
			ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}

void	ft_change_fdlast(t_grp *pipex, char **envp, int pid)
{
	int	i;

	i = -1;
	if (dup2(pipex->outfilefd, 1) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[((pipex->pidnbr - 1) * 2)], 0) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[((pipex->pidnbr - 1) * 2) + 1]) == -1)
		ft_exit_error(pipex);
	if (close(pipex->infilefd) == -1)
		ft_exit_error(pipex);
	while (++i < ((pipex->pidnbr - 1) * 2))
		if (close(pipex->pipefd[i]) == -1)
			ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}

/*
	premier je prend infilefd et pipefd[1] puis le deuxieme, pipefd[0] et pipefd[3], puis ainsi de suite, pipefd[2] pipefd[5]
	jusqu'a le dernier avec pipefd[4] et outfilefd

*/