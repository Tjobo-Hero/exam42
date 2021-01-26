#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void		write_error(char *text1, char *text2, bool die){
	for (int i = 0; text1[i]; ++i)
		write(2, &text1[i], 1);
	for (int i = 0; text2[i]; ++i)
		write(2, &text2[i], 1);
	write(2, "\n", 1);
	if (die)
		exit(1);
}

void		function_cd(char **argv, int *i){
	int start = *i;
	
	while (argv[*i] && strcmp(argv[*i], ";") && strcmp(argv[*i], "|"))
		(*i)++;
	if (*i - start != 2)
		return(write_error("error: cd: bad arguments", "", false));
	if (chdir(argv[start + 1]) == -1)
		write_error("error: cd: cannot change directory to ", argv[start + 1], false);
}

bool		function_run(char **argv, int *i, int *previous_fd, char **envp){
	int fd[2] = {0, 1};
	int tmp = *previous_fd;
	int start = *i;
	bool end = true;

	while (argv[*i] && strcmp(argv[*i], ";") && strcmp(argv[*i], "|"))
		(*i)++;
	if (argv[*i])
		if (argv[*i][0] == '|')
			end = false;
	argv[*i] = NULL;
	if (end == false && pipe(fd) == -1)
		write_error("error: fatal", "", true);
	*previous_fd = fd[0];
	fd[0] = tmp; 
	int pid = fork();
	if (pid == -1)
		write_error("error: fatal", "", true);
	if (pid == 0){
		if (fd[0] != 0){
			if (dup2(fd[0], 0) == -1)
				write_error("error: fatal", "", true);
			if (close(fd[0]) == -1)
				write_error("error: fatal", "", true);
		}
		if (fd[1] != 1){
			if (dup2(fd[1], 1) == -1)
				write_error("error: fatal", "", true);
			if (close(fd[1]) == -1)
				write_error("error: fatal", "", true);
		}
		if (execve(argv[start], argv + start, envp) == -1)
			write_error("error: cannot execute ", argv[start], true);
	}
	if (fd[0] != 0)
		if (close(fd[0]) == -1)
			write_error("error: fatal", "", true);
	if (fd[1] != 1)
		if (close(fd[1]) == -1)
			write_error("error: fatal", "", true);
	return (end);
}

int			main(int argc, char **argv, char **envp){
	int process = 0;
	int previous_fd = 0;

	for (int i = 1; i < argc; ++i){
		if (!strcmp(argv[i], "cd"))
			function_cd(argv, &i);
		else if (strcmp(argv[i], ";")){
			process++;
			if (function_run(argv, &i, &previous_fd, envp))
				for (; process; process--)
					waitpid(-1, NULL, 0);
		}
	}
	for (; process; process--)
		waitpid(-1, NULL, 0);
	return (0);
}