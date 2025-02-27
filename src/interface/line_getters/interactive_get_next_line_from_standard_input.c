/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_get_next_line_from_standard_inp        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:09:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 23:45:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

char	*interactive_get_next_line_from_standard_input(void *arg)
{
	(void)arg;
	return (readline("\033[36m>\033[0m "));
}
