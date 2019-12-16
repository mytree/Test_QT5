

#include "Test/TestBase.h"

#include "Test/Base/CH02/0201_hello.h"
#include "Test/Base/CH02/0202_hello2.h"
#include "Test/Base/CH02/0203_push_button.h"
#include "Test/Base/CH02/0204_quit.h"
#include "Test/Base/CH02/0205_struct.h"
#include "Test/Base/CH02/0206_myclass.h"
#include "Test/Base/CH03/0301_radio_button.h"
#include "Test/Base/CH03/0302_check_box.h"
#include "Test/Base/CH03/0303_lcd_number.h"
#include "Test/Base/CH03/0304_progress_bar.h"
#include "Test/Base/CH03/0305_text_browser.h"
#include "Test/Base/CH03/0306_line_edit.h"
#include "Test/Base/CH03/0307_combo_box.h"
#include "Test/Base/CH03/0308_spin_box.h"
#include "Test/Base/CH03/0309_slider.h"
#include "Test/Base/CH03/0310_dial.h"
#include "Test/Base/CH04/0401_hbox_layout.h"
#include "Test/Base/CH04/0402_vbox_layout.h"
#include "Test/Base/CH04/0403_grid_layout.h"
#include "Test/Base/CH04/0404_stacked_layout.h"
#include "Test/Base/CH04/0405_frame.h"
#include "Test/Base/CH04/0406_splitter.h"
#include "Test/Base/CH05/0501_main_window.h"
#include "Test/Base/CH05/0502_table_dialog.h"
#include "Test/Base/CH06/0601_validator.h"
#include "Test/Base/CH06/0602_date_time_edit.h"
#include "Test/Base/CH06/0603_date_edit.h"
#include "Test/Base/CH06/0604_calendar.h"
#include "Test/Base/CH06/0605_model.h"
#include "Test/Base/CH06/0606_list_widget.h"
#include "Test/Base/CH06/0607_table_widget.h"
#include "Test/Base/CH06/0608_tree_widget.h"
#include "Test/Base/CH07/0701_test_editor.h"
#include "Test/Base/CH07/0702_dir.h"
#include "Test/Base/CH07/0703_sound.h"
#include "Test/Base/CH08/0801_paint.h"
#include "Test/Base/CH08/0802_gradient.h"
#include "Test/Base/CH08/0803_painter_path.h"
#include "Test/Base/CH08/0804_opengl.h"
#include "Test/Base/CH08/0805_svg.h"
#include "Test/Base/CH09/0901_timer.h"
#include "Test/Base/CH09/0902_thread.h"
#include "Test/Base/CH09/0903_process.h"
#include "Test/Base/CH10/1001_move_event.h"

#include "Test/Ex02/CH01/Ex02_0101_version.h"
#include "Test/Ex02/CH01/Ex02_0102_string.h"
#include "Test/Ex02/CH01/Ex02_0103_date_time.h"

#include "Test/Ex02/CH02/Ex02_0201_absolute.h"
#include "Test/Ex02/CH02/Ex02_0202_vboxlayout.h"
#include "Test/Ex02/CH02/Ex02_0203_buttons.h"
#include "Test/Ex02/CH02/Ex02_0204_nesting.h"
#include "Test/Ex02/CH02/Ex02_0205_form.h"
#include "Test/Ex02/CH02/Ex02_0206_grid.h"
#include "Test/Ex02/CH02/Ex02_0207_review.h"
#include "Test/Ex02/CH03/Ex02_0301_click.h"
#include "Test/Ex02/CH03/Ex02_0302_keypress.h"
#include "Test/Ex02/CH03/Ex02_0303_move.h"
#include "Test/Ex02/CH03/Ex02_0304_disconnect.h"
#include "Test/Ex02/CH03/Ex02_0305_timer.h"
#include "Test/Ex02/CH04/Ex02_0401_line.h"
#include "Test/Ex02/CH04/Ex02_0402_color.h"
#include "Test/Ex02/CH04/Ex02_0403_pattern.h"
#include "Test/Ex02/CH04/Ex02_0404_transparent.h"
#include "Test/Ex02/CH04/Ex02_0405_donut.h"
#include "Test/Ex02/CH04/Ex02_0406_shape.h"
#include "Test/Ex02/CH04/Ex02_0407_line_gradient.h"
#include "Test/Ex02/CH04/Ex02_0408_radial_gradient.h"
#include "Test/Ex02/CH04/Ex02_0409_puff.h"
#include "Test/Ex02/CH05/Ex02_0501_file_size.h"
#include "Test/Ex02/CH05/Ex02_0502_read_file.h"
#include "Test/Ex02/CH05/Ex02_0503_write_file.h"
#include "Test/Ex02/CH05/Ex02_0504_copy_file.h"
#include "Test/Ex02/CH05/Ex02_0505_file_group.h"
#include "Test/Ex02/CH05/Ex02_0506_last_read.h"
#include "Test/Ex02/CH05/Ex02_0507_dir.h"
#include "Test/Ex02/CH05/Ex02_0508_special_path.h"
#include "Test/Ex02/CH05/Ex02_0509_file_path.h"
#include "Test/Ex02/CH05/Ex02_0510_permission.h"
#include "Test/Ex02/CH05/Ex02_0511_list_dir.h"


#include "Test/EventChecker/T001_QTableWidget.h"
#include "Test/EventChecker/T002_MultiScene.h"			// 분할 화면 테스트

int main(int nArgNum, char *ppArgs[]) {

#ifndef __linux__
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	int nRet = 0;

	T002_MultiSceneTest test;
	//T001_QTableWidgetTest test;

	//Ex02_0511_list_dir_test test;
	//Ex02_0510_permission_test test;
	//Ex02_0509_file_path_test test;
	//Ex02_0508_special_path_test test;
	//Ex02_0507_dir_test test;
	//Ex02_0506_last_read_test test;
	//Ex02_0505_file_group_test test;
	//Ex02_0504_copy_file_test test;
	//Ex02_0503_write_file_test test;
	//Ex02_0502_read_file_test test;
	//Ex02_0501_file_size_test test;
	//Ex02_0409_puff_test test;
	//Ex02_0408_radial_gradient_test test;
	//Ex02_0407_line_gradient_test test;
	//Ex02_0406_shape_test test;
	//Ex02_0405_donut_test test;
	//Ex02_0404_transparent_test test;
	//Ex02_0403_pattern_test test;
	//Ex02_0402_color_test test;
	//Ex02_0401_line_test test;
	//Ex02_0305_timer_test test;
	//Ex02_0304_disconnect_test test;
	//Ex02_0303_move_test test;
	//Ex02_0302_keypress_test test;
	//Ex02_0301_click_test test;
	//Ex02_0207_Test_Review test;
	//Ex02_0206_Test_Grid test;
	//Ex02_0205_Test_Form test;
	//Ex02_0204_Test_Nesting test;
	//Ex02_0203_Test_Buttons test;
	//Ex02_0202_Test_VBoxLayout test;
	//Ex02_0201_Test_Absolute test;
	//Ex02_0103_date_time test;
	//Ex02_0102_string test;
	//Ex02_0101_version test;
	
	//C1001_TestMoveEvent test;
	//C0903_TestProcess test;
	//C0902_TestThread test;
	//C0901_TestTimer test;
	//C0805_TestSVG test;
	//C0804_TestOpenGL test;
	//C0803_TestPainterPath test;
	//C0802_TestGradient test;
	//C0801_TestPaint test;
	//C0703_Sound test;
	//C0702_TestDir test;
	//C0701_TestEditor test;
	//C0608_TreeWidget test;
	//C0607_TableWidget test;
	//C0606_ListWidget test;
	//C0605_TestModel test;
	//C0604_Calendar test;
	//C0603_DateEdit test;
	//C0602_DateTimeEdit test;
	//C0601_TestValidator test;
	//C0502_TableDialog test;
	//C0501_MainWindow test;

	//C0406_Splitter test;
	//C0405_Frame test;
	//C0404_StackedLayout test;
	//C0403_GridLayout test;
	//C0402_VBoxLayout test;
	//C0401_HBoxLayout test;

	//C0310_Dial test;
	//C0309_Slider test;
	//C0308_SpinBox test;
	//C0307_ComboBox test;
	//C0306_LineEdit test;
	//C0305_TextBrowser test;
	//C0304_ProgressBar test;
	//C0303_LCD_Number test;
	//C0302_CheckBox test;
	//C0301_RadioButton test;

	//C0206_MyClass test;
	//C0205_Struct test;
	//C0204_Quit test;
	//C0203_PushButton test;
	//C0202_Hello2 test;
	//C0201_Hello test;
	
	nRet = test.OnTest(nArgNum, ppArgs);
	
	return nRet;
}
