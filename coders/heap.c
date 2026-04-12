/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:02:01 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/12 10:01:43 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void add_coder_in_last_the_heep(t_coder *coder)
{
    if (!coder->left_dongle->heap[0])
        coder->left_dongle->heap[0] = coder;
    else
        coder->left_dongle->heap[1] = coder;

    if (!coder->right_dongle->heap[0])
        coder->right_dongle->heap[0] = coder;
    else
        coder->right_dongle->heap[1] = coder;
    
    
}

int is_first_coder_in_heep(t_coder *coder)
{
    if (coder->left_dongle->heap[0] == coder && coder->right_dongle->heap[0] == coder)
        return 1;
    else
        return 0;
}

void pop_in_start_the_heep(t_coder *coder)
{
    coder->left_dongle->heap[0] = coder->left_dongle->heap[1];
    coder->right_dongle->heap[0] = coder->right_dongle->heap[1];
    coder->left_dongle->heap[1] = NULL;
    coder->right_dongle->heap[1] = NULL;
    
}
