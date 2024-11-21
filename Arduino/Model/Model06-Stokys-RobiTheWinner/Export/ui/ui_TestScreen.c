// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: RobiTheWinnerDisplay

#include "ui.h"

void ui_TestScreen_screen_init(void)
{
    ui_TestScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_TestScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image5 = lv_img_create(ui_TestScreen);
    lv_img_set_src(ui_Image5, &ui_img_arduinoeasy_logoprint_png);
    lv_obj_set_width(ui_Image5, LV_SIZE_CONTENT);   /// 76
    lv_obj_set_height(ui_Image5, LV_SIZE_CONTENT);    /// 18
    lv_obj_set_x(ui_Image5, 1);
    lv_obj_set_y(ui_Image5, 1);
    lv_obj_set_align(ui_Image5, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Container1 = lv_obj_create(ui_TestScreen);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 291);
    lv_obj_set_height(ui_Container1, 50);
    lv_obj_set_x(ui_Container1, 4);
    lv_obj_set_y(ui_Container1, 4);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SCROLLABLE);     /// Flags

    ui_SpinBoxTestBallAmount = lv_spinbox_create(ui_Container1);
    lv_obj_set_width(ui_SpinBoxTestBallAmount, 50);
    lv_obj_set_height(ui_SpinBoxTestBallAmount, 42);
    lv_obj_set_x(ui_SpinBoxTestBallAmount, 55);
    lv_obj_set_y(ui_SpinBoxTestBallAmount, 2);
    lv_spinbox_set_digit_format(ui_SpinBoxTestBallAmount, 2, 0);
    lv_spinbox_set_range(ui_SpinBoxTestBallAmount, 1, 99);
    lv_spinbox_set_cursor_pos(ui_SpinBoxTestBallAmount, 1 - 1);
    lv_spinbox_set_value(ui_SpinBoxTestBallAmount, 5);
    lv_obj_set_style_text_letter_space(ui_SpinBoxTestBallAmount, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_SpinBoxTestBallAmount, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SpinBoxTestBallAmount, &ui_font_SanSerif15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonTestBallAmountDec = lv_btn_create(ui_Container1);
    lv_obj_set_width(ui_ButtonTestBallAmountDec, 51);
    lv_obj_set_height(ui_ButtonTestBallAmountDec, 38);
    lv_obj_set_x(ui_ButtonTestBallAmountDec, 2);
    lv_obj_set_y(ui_ButtonTestBallAmountDec, 4);
    lv_obj_add_flag(ui_ButtonTestBallAmountDec, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonTestBallAmountDec, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelTestBallAmountDec = lv_label_create(ui_ButtonTestBallAmountDec);
    lv_obj_set_width(ui_LabelTestBallAmountDec, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTestBallAmountDec, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTestBallAmountDec, 0);
    lv_obj_set_y(ui_LabelTestBallAmountDec, -1);
    lv_obj_set_align(ui_LabelTestBallAmountDec, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTestBallAmountDec, "-");
    lv_obj_set_style_text_font(ui_LabelTestBallAmountDec, &ui_font_SanSerif17, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonTestBallAmountInc = lv_btn_create(ui_Container1);
    lv_obj_set_width(ui_ButtonTestBallAmountInc, 50);
    lv_obj_set_height(ui_ButtonTestBallAmountInc, 38);
    lv_obj_set_x(ui_ButtonTestBallAmountInc, 106);
    lv_obj_set_y(ui_ButtonTestBallAmountInc, 4);
    lv_obj_add_flag(ui_ButtonTestBallAmountInc, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonTestBallAmountInc, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelTestBallAmountInc = lv_label_create(ui_ButtonTestBallAmountInc);
    lv_obj_set_width(ui_LabelTestBallAmountInc, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTestBallAmountInc, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelTestBallAmountInc, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTestBallAmountInc, "+");
    lv_obj_set_style_text_font(ui_LabelTestBallAmountInc, &ui_font_SanSerif17, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonStartBallOutput = lv_btn_create(ui_Container1);
    lv_obj_set_width(ui_ButtonStartBallOutput, 131);
    lv_obj_set_height(ui_ButtonStartBallOutput, 38);
    lv_obj_set_x(ui_ButtonStartBallOutput, 0);
    lv_obj_set_y(ui_ButtonStartBallOutput, 4);
    lv_obj_set_align(ui_ButtonStartBallOutput, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_ButtonStartBallOutput, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonStartBallOutput, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelStartBallOutput = lv_label_create(ui_ButtonStartBallOutput);
    lv_obj_set_width(ui_LabelStartBallOutput, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelStartBallOutput, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelStartBallOutput, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelStartBallOutput, "Ballabwurf start");

    ui_ButtonStartBallLift = lv_btn_create(ui_TestScreen);
    lv_obj_set_width(ui_ButtonStartBallLift, 131);
    lv_obj_set_height(ui_ButtonStartBallLift, 38);
    lv_obj_set_x(ui_ButtonStartBallLift, 71);
    lv_obj_set_y(ui_ButtonStartBallLift, -50);
    lv_obj_set_align(ui_ButtonStartBallLift, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonStartBallLift, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonStartBallLift, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelStartBallLift = lv_label_create(ui_ButtonStartBallLift);
    lv_obj_set_width(ui_LabelStartBallLift, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelStartBallLift, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelStartBallLift, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelStartBallLift, "Ball-Lift start");

    ui_ButtonStopBallLift = lv_btn_create(ui_TestScreen);
    lv_obj_set_width(ui_ButtonStopBallLift, 131);
    lv_obj_set_height(ui_ButtonStopBallLift, 38);
    lv_obj_set_x(ui_ButtonStopBallLift, 71);
    lv_obj_set_y(ui_ButtonStopBallLift, -50);
    lv_obj_set_align(ui_ButtonStopBallLift, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonStopBallLift, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonStopBallLift, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ButtonStopBallLift, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ButtonStopBallLift, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ButtonStopBallLift, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelStopBallLift = lv_label_create(ui_ButtonStopBallLift);
    lv_obj_set_width(ui_LabelStopBallLift, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelStopBallLift, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelStopBallLift, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelStopBallLift, "Ball-Lift stop");

    lv_obj_add_event_cb(ui_Image5, ui_event_Image5, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonTestBallAmountDec, ui_event_ButtonTestBallAmountDec, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonTestBallAmountInc, ui_event_ButtonTestBallAmountInc, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonStartBallOutput, ui_event_ButtonStartBallOutput, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonStartBallLift, ui_event_ButtonStartBallLift, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonStopBallLift, ui_event_ButtonStopBallLift, LV_EVENT_ALL, NULL);

}