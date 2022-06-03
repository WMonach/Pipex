#include "pipex.h"

void	ft_exec_cmd1(t_grp *pipex, int pipefd[2], char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("8-D");
	if (pid == 0)
		ft_change_fd1(pipex, pipefd, envp);
}

void	ft_change_fd1(t_grp *pipex, int pipefd[2], char **envp)
{
	dup2(pipex->infilefd, STDIN_FILENO);
	perror("8-----D");
	printf("%d\n", pipefd[1]);
	dup2(pipefd[1], STDOUT_FILENO);
	printf("ha\n");
	execve(pipex->cmd1path, pipex->cmd1, envp);
}

void	ft_exec_cmd2(t_grp *pipex, int pipefd[2], char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("8-D");
	if (pid == 0)
		ft_change_fd2(pipex, pipefd, envp);
}

void	ft_change_fd2(t_grp *pipex, int pipefd[2], char **envp)
{
	dup2(pipex->outfilefd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	execve(pipex->cmd2path, pipex->cmd2, envp);
}
