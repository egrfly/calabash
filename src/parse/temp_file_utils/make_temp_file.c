/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_temp_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:34:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 17:00:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../execute/execution_utils/execution_utils.h"
#include "../../execute/pipeline_utils/pipeline_utils.h"
#include "../../lex/token_lifecycle/token_lifecycle.h"
#include "../parse.h"
#include "../tree_lifecycle/tree_lifecycle.h"

#define BACKUP_TEMP_FILE_PATH "/tmp/.emily_and_attila_were_here"

static void	execute_external_mktemp(
				int pipe_fd[2],
				t_syntax_tree *syntax_tree,
				t_list *tokens)
{
	static char	*argv[] = {"mktemp", NULL};
	static char	*envp[] = {NULL};

	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	execve("/usr/bin/mktemp", argv, envp);
	destroy_syntax_tree(syntax_tree);
	ft_list_destroy(tokens, (t_action_func)destroy_token);
	exit(GENERAL_FAILURE);
}

static bool	try_open_backup_temp_file(
				char *temp_file_path)
{
	int	fd;

	fd = open(BACKUP_TEMP_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == OPEN_FAILURE)
		return (false);
	close(fd);
	ft_strcpy(temp_file_path, BACKUP_TEMP_FILE_PATH);
	return (true);
}

bool	make_temp_file(
			char *temp_file_path,
			t_syntax_tree *syntax_tree,
			t_list *tokens)
{
	int	pipe_fd[2];
	int	pid;
	int	chars_read;

	if (pipe(pipe_fd) == PIPE_FAILURE)
		return (try_open_backup_temp_file(temp_file_path));
	pid = fork();
	if (pid == FORK_FAILURE)
	{
		close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
		return (try_open_backup_temp_file(temp_file_path));
	}
	if (pid == CHILD_PROCESS_ID)
		execute_external_mktemp(pipe_fd, syntax_tree, tokens);
	waitpid(pid, NULL, NO_OPTIONS);
	chars_read = read(pipe_fd[READ_END], temp_file_path, PATH_MAX);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	if (chars_read <= 1)
		return (try_open_backup_temp_file(temp_file_path));
	temp_file_path[chars_read - 1] = '\0';
	return (true);
}
