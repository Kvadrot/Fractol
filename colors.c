/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:37:16 by itykhono          #+#    #+#             */
/*   Updated: 2024/06/30 17:40:25 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#define NUM_COLORS 42

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    RGB colors[NUM_COLORS];
} ColorSet;

// Predefined colors array
RGB predefined_colors[NUM_COLORS] = {
    {255, 0, 0}, {255, 127, 0}, {255, 255, 0}, {127, 255, 0}, {0, 255, 0}, 
    {0, 255, 127}, {0, 255, 255}, {0, 127, 255}, {0, 0, 255}, {127, 0, 255},
    {255, 0, 255}, {255, 0, 127}, {127, 0, 0}, {127, 63, 0}, {127, 127, 0},
    {63, 127, 0}, {0, 127, 0}, {0, 127, 63}, {0, 127, 127}, {0, 63, 127},
    {0, 0, 127}, {63, 0, 127}, {127, 0, 127}, {127, 0, 63}, {63, 0, 0},
    {63, 31, 0}, {63, 63, 0}, {31, 63, 0}, {0, 63, 0}, {0, 63, 31},
    {0, 63, 63}, {0, 31, 63}, {0, 0, 63}, {31, 0, 63}, {63, 0, 63},
    {63, 0, 31}, {255, 255, 255}, {192, 192, 192}, {128, 128, 128}, {64, 64, 64}, {0, 0, 0}
};

// Initialize the ColorSet struct with predefined colors
void init_color_set(ColorSet *color_set) {
    for (int i = 0; i < NUM_COLORS; ++i) {
        color_set->colors[i] = predefined_colors[i];
    }
}