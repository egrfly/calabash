/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:32:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/17 23:40:12 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_UTILS_H
# define WORD_UTILS_H

# include <stdbool.h>

bool	is_reserved(char *word);
bool	is_identifier(char *word);
bool	range_is_identifier(char *word, unsigned int start, unsigned int end);

#endif
