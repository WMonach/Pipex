#include "pipex.h"

void	ft_exec_cmd1(t_grp *pipex, int pipefd[2], char **envp)
{
	int	pid;

	pipex->pid[0] = fork();
	if (pid < 0)
		ft_exit_error(pipex);
	if (pid == 0)
		ft_change_fd1(pipex, pipefd, envp);
}

void	ft_change_fd1(t_grp *pipex, int pipefd[2], char **envp)
{
	int	i;

	i = 0;
	close(pipefd[0]);
	if (dup2(pipex->infilefd, STDIN_FILENO) == -1)
		ft_exit_error(pipex);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_exit_error(pipex);
	close(pipefd[1]);
	if (execve(pipex->cmd1path, pipex->cmd1, envp) == -1)
		ft_exit_error(pipex);
}

void	ft_exec_cmd2(t_grp *pipex, int pipefd[2], char **envp)
{
	int	pid;

	pipex->pid[1] = fork();
	if (pid < 0)
		ft_exit_error(pipex);
	if (pid == 0)
		ft_change_fd2(pipex, pipefd, envp);
}

void	ft_change_fd2(t_grp *pipex, int pipefd[2], char **envp)
{
	int	i;

	i = 0;
	close(pipefd[1]);
	if (dup2(pipex->outfilefd, STDOUT_FILENO) == -1)
		ft_exit_error(pipex);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_exit_error(pipex);
	close(pipefd[0]);
	if (execve(pipex->cmd2path, pipex->cmd2, envp) == -1)
		ft_exit_error(pipex);
}
