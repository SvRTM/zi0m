/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "gui/io/InputDevice.cpp"
#include "gui/io/MonitorDevice.cpp"

#include "gui/kernel/additional.cpp"
#include "gui/kernel/ApplicationBase.cpp"
#include "gui/kernel/EventCtrl.cpp"

#include "gui/text/font/PT_Serif_AA_14pt_Regular.cpp"
#include "gui/text/font/Terminus_11pt_Regular.cpp"
#include "gui/text/font/Terminus_24pt_Regular.cpp"
#include "gui/text/font/Tinos_AA_11pt_Regular.cpp"

#include "gui/text/TextCharacters.cpp"

#include "gui/widgets/AbstractButtonASize.cpp"
#include "gui/widgets/AbstractButton.cpp"
#include "gui/widgets/AbstractTextWidget.cpp"
#include "gui/widgets/Button.cpp"
#include "gui/widgets/CheckBox.cpp"
#include "gui/widgets/GroupBox.cpp"
#include "gui/widgets/Label.cpp"
#include "gui/widgets/p_checkbox.cpp"
#include "gui/widgets/RadioButton.cpp"
#include "gui/widgets/Widget.cpp"


#ifdef PLATFORM_WIN32
    #include "samples/pc/win/win32.cpp"
#elif PLATFORM_LINUX
    #include "samples/pc/linux/x11.cpp"
#endif
#include "samples/pc/SimBase.cpp"

#include "samples/pc/Application.cpp"
#include "samples/pc/EmuLcd.cpp"
#include "samples/pc/EmuTouch.cpp"
#include "samples/pc/main.cpp"

#include "samples/Buttons.cpp"
#include "samples/GroupBoxs.cpp"
#include "samples/Labels.cpp"
#include "samples/MainWindow.cpp"
