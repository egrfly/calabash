/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_here_doc_or_string_redirection.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:09:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_here_doc_or_string_redirection(
			t_redirection *redirection)
{
	return (perform_read_or_write_redirection(redirection,
			O_RDONLY, STDIN_FILENO, IS_HERE_DOC));
}
