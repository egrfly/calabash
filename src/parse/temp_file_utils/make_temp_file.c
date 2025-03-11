/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_temp_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:34:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/11 02:07:35 by emflynn          ###   ########.fr       */
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
#include "../../execute/path_utils/path_utils.h"
#include "../../execute/pipeline_utils/pipeline_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../lex/token_lifecycle/token_lifecycle.h"
#include "../parse.h"
#include "../tree_lifecycle/tree_lifecycle.h"

#define BACKUP_TEMP_FILE_PATH "/tmp/.emily_and_atti_were_here"

static void	execute_external_mktemp(
				int pipe_fd[2],
				t_syntax_tree *syntax_tree,
				t_list *tokens)
{
	char	*path;

	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	if (get_full_command_path(&path, "mktemp", "/usr/local/bin:/usr/bin:/bin"))
		execve(path, (char *[]){"mktemp", NULL}, (char *[]){NULL});
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
	int	exit_status;
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
	waitpid(pid, &exit_status, NO_OPTIONS);
	if (!WIFEXITED(exit_status) || WEXITSTATUS(exit_status) != SUCCESS)
		return (try_open_backup_temp_file(temp_file_path));
	chars_read = read(pipe_fd[READ_END], temp_file_path, PATH_MAX);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	if (chars_read <= 2)
		return (try_open_backup_temp_file(temp_file_path));
	temp_file_path[chars_read - 1] = '\0';
	return (true);
}
