/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 23:42:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 23:44:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_UTILS_H
# define HERE_DOC_UTILS_H

# include <stdbool.h>
# include "../../interface/interface.h"
# include "../../parse/parse.h"

bool	expand_here_doc(
			t_redirection *redirection,
			t_program_vars *program_vars);

#endif
