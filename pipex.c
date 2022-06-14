#include "pipex.h"

int	main(int argc, char **argv)
{
	t_grp	pipex;

	ft_get_init(&pipex);
	ft_parsing(&pipex, argv, argc);

	return (0);
}

void	ft_get_init(t_grp *pipex)
{
	pipex->cmd1path = NULL;
	pipex->cmd2path = NULL;
}


int	ft_parsing(t_grp *pipex, char **argv, int argc)
{
	ft_find_fd(pipex, argv, argc);
	ft_find_path(pipex, argv, argc);
}

void	ft_find_fd(t_grp *pipex, char **argv, int argc)
{
	pipex->fd1 = open(argv[1], O_RDONLY);
	close(pipex->fd1);
	pipex->fd2 = open(argv[argc - 1], O_RDONLY);
	close(pipex->fd2);
}

void	ft_find_path(t_grp *pipex, char **argv, int argc)
{
	
}