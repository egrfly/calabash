/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:44:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 20:58:28 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./interface/interface.h"

volatile sig_atomic_t	g_signal;

int	main(int argc, char **argv, char **envp)
{
	return (interface(argc, argv, envp));
}
