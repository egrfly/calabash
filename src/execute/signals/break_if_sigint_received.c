/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_if_sigint_received.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:54:32 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 22:55:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "./signals.h"

int	break_if_sigint_received(void)
{
	if (g_signal == SIGINT)
		rl_done = true;
	return (0);
}
