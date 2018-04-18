/*
 * File      : rtgui_layer.c
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

#include <rtthread.h>
#include <rtgui/region.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/dc.h>
#include <rtgui/rtgui_layer.h>

rtgui_layer_t rtgui_layer_create(struct rtgui_dc_buffer *dc)
{
    //TODO:判断是不是BUFF DC 
    struct rtgui_graphic_driver *driver = rtgui_graphic_driver_get_default();
    rtgui_layer_t layer;

    layer = (rtgui_layer_t)rtgui_malloc(sizeof(struct rtgui_layer));
    if ((layer == RT_NULL) || (driver == RT_NULL))
    {
        return RT_NULL;
    } 
    rt_memset(layer, 0, sizeof(struct rtgui_layer));

    layer->pixel_format = dc->pixel_format;
    layer->alpha_value = dc->pixel_alpha;
    layer->bits_per_pixel = rtgui_color_get_bpp(dc->pixel_format);
    layer->width = dc->width;
    layer->height = dc->height;
    layer->buffer = dc->pixel;

    if (rt_device_control(driver->device, RTGRAPHIC_CTRL_CREATE_LAYER, layer) != RT_EOK)
    {
        rtgui_free(layer);
        return RT_NULL;
    }

    return layer;
}

rt_err_t rtgui_layer_coordinate_set(rtgui_layer_t layer, int x, int y)
{
    if (layer == RT_NULL)
    {
        return -RT_ERROR;
    }

    layer->x = x;
    layer->y = y;

    return RT_EOK;
}

rt_err_t rtgui_layer_alpha_set(rtgui_layer_t layer, rt_uint8_t alpha)
{
    if (layer == RT_NULL)
    {
        return -RT_ERROR;
    }

    layer->alpha_value = alpha;

    return RT_EOK;
}

rt_err_t rtgui_layer_update(rtgui_layer_t layer)
{
    struct rtgui_graphic_driver * driver = rtgui_graphic_driver_get_default();
    
    if (driver == RT_NULL)
    {
        return RT_NULL;
    }

    rtgui_screen_lock(RT_WAITING_FOREVER);
    return rt_device_control(driver->device, RTGRAPHIC_CTRL_UPDATE_LAYER, layer);
    rtgui_screen_unlock();
}

void rtgui_layer_delete(rtgui_layer_t layer)
{
    struct rtgui_graphic_driver * driver = rtgui_graphic_driver_get_default();
    
    if ((layer == RT_NULL) || (driver == RT_NULL))
    {
        return;
    }

    rtgui_screen_lock(RT_WAITING_FOREVER);
    rt_device_control(driver->device, RTGRAPHIC_CTRL_DELETE_LAYER, layer);
    rtgui_screen_unlock();
    rtgui_free(layer);
}
