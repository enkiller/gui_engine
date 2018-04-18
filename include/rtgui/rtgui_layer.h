/*
 * File      : rtgui_layer.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-17     Bomber      first version
 */

#ifndef __RTGUI_LAYER_H__
#define __RTGUI_LAYER_H__

#define RTGRAPHIC_CTRL_CREATE_LAYER          (10)
#define RTGRAPHIC_CTRL_UPDATE_LAYER          (11)
#define RTGRAPHIC_CTRL_DELETE_LAYER          (12)

struct rtgui_layer
{
    rt_uint8_t  pixel_format;                /**< graphic format */
    rt_uint8_t  alpha_value;                 /**< alpha value */

    rt_uint16_t bits_per_pixel;              /**< reserved field */

    rt_uint16_t width;                       /**< width of graphic device */
    rt_uint16_t height;                      /**< height of graphic device */

    rt_uint16_t x;                           /**< coordinatte x */
    rt_uint16_t y;                           /**< coordinatte y */

    rt_uint8_t *buffer;                      /**< frame buffer */

    void *user_data;                         /**< layer index */
};
typedef struct rtgui_layer *rtgui_layer_t;

rtgui_layer_t rtgui_layer_create(struct rtgui_dc_buffer *dc);
rt_err_t rtgui_layer_coordinate_set(rtgui_layer_t layer, int x, int y);
rt_err_t rtgui_layer_alpha_set(rtgui_layer_t layer, rt_uint8_t alpha);
rt_err_t rtgui_layer_update(rtgui_layer_t layer);
void rtgui_layer_delete(rtgui_layer_t layer);

#endif
