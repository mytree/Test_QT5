
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

int main(int nArgNum, char *ppArgs[]) {

	int nRet = 0;
	
	C1001_TestMoveEvent test;
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
