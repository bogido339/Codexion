/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/24 18:25:11 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void add_coder_to_heap(t_coder *coder)
{
    if (!get_heap(coder->left_dongle, 0))
        set_heap(coder->left_dongle, coder, 0);
    else
        set_heap(coder->left_dongle, coder, 1);

    if (!get_heap(coder->right_dongle, 0))
        set_heap(coder->right_dongle, coder, 0);
    else
        set_heap(coder->right_dongle, coder, 1);
}

void enqueue_first_time(t_coder *coder)
{
    if (coder->id % 2 != 0 && !get_heap(coder->left_dongle, 0) && !get_heap(coder->right_dongle, 0))
    {
        set_heap(coder->left_dongle, coder, 0);
        set_heap(coder->right_dongle, coder, 0);
    }
    else if (coder->id % 2 == 0 && !get_heap(coder->left_dongle, 1) && !get_heap(coder->right_dongle, 1))
    {
        set_heap(coder->left_dongle, coder, 1);
        set_heap(coder->right_dongle, coder, 1);
    }
    else if (!get_heap(coder->left_dongle, 1) && get_heap(coder->right_dongle, 1))
    {
        set_heap(coder->left_dongle, coder, 1);
        set_heap(coder->right_dongle, coder, 0);
    }
    else
    {
        set_heap(coder->left_dongle, coder, 0);
        set_heap(coder->right_dongle, coder, 1);
    }
    if (coder->first_push)
        coder->first_push = 0;   
}

void dequeue_from_heap(t_coder *coder)
{
    set_heap(coder->left_dongle, get_heap(coder->left_dongle, 1), 0);
    set_heap(coder->left_dongle, NULL, 1);

    set_heap(coder->right_dongle, get_heap(coder->right_dongle, 1), 0);
    set_heap(coder->right_dongle, NULL, 1);
}

void swap_coders(t_dongle *dongle)
{
    t_coder *coder;
    
    coder = get_heap(dongle, 0);
    set_heap(dongle, get_heap(dongle, 1), 0);
    set_heap(dongle, coder, 1);
}

void sort_dongle_heap(t_dongle *dongle)
{
    t_coder *c0;
    t_coder *c1;

    if (!get_heap(dongle, 0) || !get_heap(dongle, 1))
        return;
        
    c0 = get_heap(dongle, 0);
    c1 = get_heap(dongle, 1);

    if (get_compile_time(c0) > get_compile_time(c1))
        swap_coders(dongle);
    else if (get_compile_time(c0) == get_compile_time(c1) && get_compile_count(c0) < get_compile_count(c1))
        swap_coders(dongle);
}