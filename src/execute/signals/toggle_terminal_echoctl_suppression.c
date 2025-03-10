/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_terminal_echoctl_suppression.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:27:20 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 18:45:18 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include "ft_string.h"

void	toggle_terminal_echoctl_suppression(bool disable_echoctl)
{
	static struct termios	original_settings;
	static struct termios	current_settings;
	static bool				initialized = false;

	if (!initialized)
	{
		tcgetattr(STDIN_FILENO, &original_settings);
		ft_memcpy(&current_settings, &original_settings,
			sizeof(struct termios));
		current_settings.c_lflag &= ~(ECHOCTL);
		initialized = true;
	}
	if (disable_echoctl)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &current_settings);
	else
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_settings);
}
