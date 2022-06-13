#include "pipex.h"

void	ft_change_fd(t_grp *pipex, char **envp, int pid)
{
	int	i;

	i = 0;
	if (dup2(pipex->pipefd[0], 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[3], 1) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[2]) == -1)
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

	i = 0;
	if (dup2(pipex->infilefd, 0) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[1], 1) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[0]) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}

void	ft_change_fdlast(t_grp *pipex, char **envp, int pid)
{
	int	i;

	i = 0;
	if (dup2(pipex->outfilefd, 1) == -1)
		ft_exit_error(pipex);
	if (dup2(pipex->pipefd[2], 0) == -1)
		ft_exit_error(pipex);
	if (close(pipex->pipefd[3]) == -1)
		ft_exit_error(pipex);
	if (execve(pipex->cmdspath[pid], pipex->cmds[pid], envp) == -1)
		ft_exit_error(pipex);
}

/*
	premier je prend infilefd et pipefd[1] puis le deuxieme, pipefd[0] et pipefd[3], puis ainsi de suite, pipefd[2] pipefd[5]
	jusqu'a le dernier avec pipefd[4] et outfilefd

*/