#include "pipex.h"

int	main(int argc, char **argv)
{
	t_grp	*pipex;

	pipex = malloc(sizeof(t_grp));
	ft_get_init(pipex);
	ft_parsing(pipex, argc, argv);
	return (0);
}

int	ft_parsing(t_grp *pipex, int argc, char **argv)
{
	ft_get_fd(pipex, argc, argv);
	ft_get_cmdpath(pipex, argc, argv);
	return (1);
}

void	ft_get_init(t_grp *pipex)
{
	pipex->cmd1path = NULL;
	pipex->cmd2path = NULL;
	pipex->pathlist = NULL;
}

void	ft_get_fd(t_grp *pipex, int argc, char **argv)
{
	pipex->infilefd = open(argv[1], 0, O_RDONLY);
	close (pipex->infilefd);
	pipex->outfilefd = open(argv[argc - 1], 0, O_RDONLY);
	close (pipex->outfilefd);
	// printf("%d\n", pipex->outfilefd);
	// printf("%d\n", pipex->infilefd);
}

void	ft_get_cmdpath(t_grp *pipex, int argc, char **argv)
{
	pipex->pathlist = malloc(sizeof(t_grp) * ());
	while (pipex)
	{
	}
	/*
	trouver les differents PATH a tester et les rentrer dans pathlist en l'allouant
	ensuite utiliser dans une boucle while les differents PATH avec access et partir
	en n'oubliant pas de free pathlist
	*/
}

