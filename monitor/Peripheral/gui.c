/*
 * ui.c
 *
 *  Created on: Jan 9, 2022
 *      Author: Administrator
 */
#include "gui.h"



#define MASK_WIDTH 100
#define MASK_HEIGHT 45



static void add_mask_event_cb(lv_event_t* e)
{
    static lv_draw_mask_map_param_t m;
    static int16_t mask_id;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    lv_opa_t* mask_map = (lv_opa_t*)lv_event_get_user_data(e);
    if (code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
    }
    else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {
        lv_draw_mask_map_init(&m, &obj->coords, mask_map);
        mask_id = lv_draw_mask_add(&m, NULL);

    }
    else if (code == LV_EVENT_DRAW_MAIN_END) {
        lv_draw_mask_free_param(&m);
        lv_draw_mask_remove_id(mask_id);
    }
}


void signature_area(void)
{
    /* Create the mask of a text by drawing it to a canvas*/
    static lv_opa_t mask_map[MASK_WIDTH * MASK_HEIGHT];

    /*Create a "8 bit alpha" canvas and clear it*/
    lv_obj_t* canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, mask_map, MASK_WIDTH, MASK_HEIGHT, LV_IMG_CF_ALPHA_8BIT);
    lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_TRANSP);

    /*Draw a label to the canvas. The result "image" will be used as mask*/
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = lv_color_white();
    label_dsc.align = LV_TEXT_ALIGN_CENTER;
    lv_canvas_draw_text(canvas, 5, 5, MASK_WIDTH, &label_dsc, "Design by QK in China");

    /*The mask is reads the canvas is not required anymore*/
    lv_obj_del(canvas);

    /* Create an object from where the text will be masked out.
     * Now it's a rectangle with a gradient but it could be an image too*/
    lv_obj_t* grad = lv_obj_create(lv_scr_act());
    lv_obj_set_size(grad, MASK_WIDTH, MASK_HEIGHT);
    lv_obj_set_pos(grad, 125, 160);
    lv_obj_set_style_bg_color(grad, lv_color_hex(0xff0000), 0);
    lv_obj_set_style_bg_grad_color(grad, lv_color_hex(0x0000ff), 0);
    lv_obj_set_style_bg_grad_dir(grad, LV_GRAD_DIR_HOR, 0);
    lv_obj_add_event_cb(grad, add_mask_event_cb, LV_EVENT_ALL, mask_map);
}

lv_obj_t* bar_disk1;
lv_obj_t* bar_disk2;

lv_obj_t* label_disk1;
lv_obj_t* label_disk2;
void creat_disk_bar(void)
{
    bar_disk1 = lv_bar_create(lv_scr_act());
    lv_obj_set_pos(bar_disk1, 140, 52);
    lv_obj_set_size(bar_disk1, 80, 12);
    lv_bar_set_range(bar_disk1, 0, 100);
    lv_bar_set_value(bar_disk1, 0, LV_ANIM_OFF);
    label_disk1 = lv_label_create(lv_scr_act());
    lv_label_set_text(label_disk1, "C:");
    lv_obj_align_to(label_disk1, bar_disk1, LV_ALIGN_OUT_LEFT_MID, -5, 0);


    bar_disk2 = lv_bar_create(lv_scr_act());
    lv_obj_set_pos(bar_disk2, 140, 68);
    lv_obj_set_size(bar_disk2, 80, 12);
    lv_bar_set_range(bar_disk2, 0, 100);
    lv_bar_set_value(bar_disk2, 0, LV_ANIM_OFF);
    label_disk2 = lv_label_create(lv_scr_act());
    lv_label_set_text(label_disk2, "D:");
    lv_obj_align_to(label_disk2, bar_disk2, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}



lv_obj_t* arc_cpu;
lv_obj_t* arc_mem;

lv_obj_t* label_cpu;
lv_obj_t* label_mem;
lv_obj_t* label_cpu_value;
lv_obj_t* label_mem_value;



void creat_arc(void)
{
    /*Create an Arc*/
    arc_cpu = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc_cpu, 100, 100);
    lv_obj_set_pos(arc_cpu, 10, 10);
    lv_arc_set_rotation(arc_cpu, 270);
    lv_arc_set_bg_angles(arc_cpu, 0, 360);
    lv_arc_set_value(arc_cpu  , 0);
    lv_obj_remove_style(arc_cpu, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc_cpu, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    label_cpu = lv_label_create(arc_cpu);
    lv_label_set_text(label_cpu, "CPU");
    lv_obj_center(label_cpu);
    label_cpu_value = lv_label_create(arc_cpu);
    lv_label_set_text(label_cpu_value, "0");
    lv_obj_set_style_text_align(label_cpu_value, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label_cpu_value, LV_ALIGN_CENTER, 0, 15);
    lv_obj_set_width(label_cpu_value, 36);


    arc_mem = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc_mem, 100, 100);
    lv_obj_set_pos(arc_mem, 10, 130);
    lv_arc_set_rotation(arc_mem, 270);
    lv_arc_set_bg_angles(arc_mem, 0, 360);
    lv_arc_set_value(arc_mem, 0);
    lv_obj_remove_style(arc_mem, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc_mem, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    label_mem = lv_label_create(arc_mem);
    lv_label_set_text(label_mem, "MEM");
	lv_obj_center(label_mem);
	label_mem_value = lv_label_create(arc_mem);

	lv_obj_align(label_mem_value, LV_ALIGN_CENTER, 0, 15);
	lv_label_set_text(label_mem_value, "0");
	lv_obj_set_style_text_align(label_mem_value, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_width(label_mem_value, 36);
/*
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc_mem);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);*/
}




void gui_init(void)
{

	creat_disk_bar();
	signature_area();
	creat_arc();

}


void value_update(uint8_t* data)
{
	if(data[0] == 4)
	{
		lv_arc_set_value((lv_obj_t*)arc_cpu, data[1]);
		//lv_label_set_text(label_cpu_value, (const char*)data);
		lv_label_set_text_fmt(label_cpu_value, "%d%%", data[1]);

		lv_arc_set_value((lv_obj_t*)arc_mem, data[2]);
		//lv_label_set_text(label_mem_value, (const char*)data);
		lv_label_set_text_fmt(label_mem_value, "%d%%", data[2]);


	}else{

		lv_label_set_text_fmt(label_disk1, "%c:", data[1]);
		lv_bar_set_value(bar_disk1, data[2], LV_ANIM_OFF);

		lv_label_set_text_fmt(label_disk2, "%c:", data[5]);
		lv_bar_set_value(bar_disk2, data[6], LV_ANIM_OFF);
	}
}

