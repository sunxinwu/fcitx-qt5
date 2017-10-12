/*
* Copyright (C) 2017~2017 by CSSlayer
* wengxt@gmail.com
*
* This library is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 2.1 of the
* License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; see the file COPYING. If not,
* see <http://www.gnu.org/licenses/>.
*/

#include "qtkey.h"

#include <QHash>
#include <qnamespace.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
#include <ctype.h>
#include <QString>

const QHash<uint32_t, int> &KeyTbl() {
    static QHash<uint32_t, int> keyTbl{
        std::make_pair(XK_KP_Space, Qt::Key_Space),
        std::make_pair(XK_KP_Tab, Qt::Key_Tab),
        std::make_pair(XK_KP_Enter, Qt::Key_Enter),
        std::make_pair(XK_KP_F1, Qt::Key_F1),
        std::make_pair(XK_KP_F2, Qt::Key_F2),
        std::make_pair(XK_KP_F3, Qt::Key_F3),
        std::make_pair(XK_KP_F4, Qt::Key_F4),
        std::make_pair(XK_KP_Home, Qt::Key_Home),
        std::make_pair(XK_KP_Left, Qt::Key_Left),
        std::make_pair(XK_KP_Up, Qt::Key_Up),
        std::make_pair(XK_KP_Right, Qt::Key_Right),
        std::make_pair(XK_KP_Down, Qt::Key_Down),
        std::make_pair(XK_KP_Page_Up, Qt::Key_PageUp),
        std::make_pair(XK_KP_Page_Down, Qt::Key_PageDown),
        std::make_pair(XK_KP_End, Qt::Key_End),
        std::make_pair(XK_KP_Begin, Qt::Key_Clear),
        std::make_pair(XK_KP_Insert, Qt::Key_Insert),
        std::make_pair(XK_KP_Delete, Qt::Key_Delete),
        std::make_pair(XK_KP_Equal, Qt::Key_Equal),
        std::make_pair(XK_KP_Multiply, Qt::Key_multiply),
        std::make_pair(XK_KP_Add, Qt::Key_Plus),
        std::make_pair(XK_KP_Separator, Qt::Key_Comma),
        std::make_pair(XK_KP_Subtract, Qt::Key_Minus),
        std::make_pair(XK_KP_Decimal, Qt::Key_Period),
        std::make_pair(XK_KP_Divide, Qt::Key_Slash),

        std::make_pair(XK_KP_0, Qt::Key_0),
        std::make_pair(XK_KP_1, Qt::Key_1),
        std::make_pair(XK_KP_2, Qt::Key_2),
        std::make_pair(XK_KP_3, Qt::Key_3),
        std::make_pair(XK_KP_4, Qt::Key_4),
        std::make_pair(XK_KP_5, Qt::Key_5),
        std::make_pair(XK_KP_6, Qt::Key_6),
        std::make_pair(XK_KP_7, Qt::Key_7),
        std::make_pair(XK_KP_8, Qt::Key_8),
        std::make_pair(XK_KP_9, Qt::Key_9),

        std::make_pair(XK_Escape, Qt::Key_Escape),
        std::make_pair(XK_Tab, Qt::Key_Tab),
        std::make_pair(XK_ISO_Left_Tab, Qt::Key_Backtab),
        std::make_pair(XK_BackSpace, Qt::Key_Backspace),
        std::make_pair(XK_Return, Qt::Key_Return),
        std::make_pair(XK_KP_Enter, Qt::Key_Enter),
        std::make_pair(XK_Insert, Qt::Key_Insert),
        std::make_pair(XK_Pause, Qt::Key_Pause),
        std::make_pair(XK_Print, Qt::Key_Print),
        std::make_pair(XK_Sys_Req, Qt::Key_SysReq),
        std::make_pair(XK_Clear, Qt::Key_Clear),
        std::make_pair(XK_Home, Qt::Key_Home),
        std::make_pair(XK_End, Qt::Key_End),
        std::make_pair(XK_Left, Qt::Key_Left),
        std::make_pair(XK_Up, Qt::Key_Up),
        std::make_pair(XK_Right, Qt::Key_Right),
        std::make_pair(XK_Down, Qt::Key_Down),
        std::make_pair(XK_Page_Up, Qt::Key_PageUp),
        std::make_pair(XK_Page_Down, Qt::Key_PageDown),
        std::make_pair(XK_Shift_L, Qt::Key_Shift),
        std::make_pair(XK_Shift_R, Qt::Key_Shift),
        std::make_pair(XK_Control_L, Qt::Key_Control),
        std::make_pair(XK_Control_R, Qt::Key_Control),
        std::make_pair(XK_Meta_L, Qt::Key_Meta),
        std::make_pair(XK_Meta_R, Qt::Key_Meta),
        std::make_pair(XK_Alt_L, Qt::Key_Alt),
        std::make_pair(XK_Alt_R, Qt::Key_Alt),
        std::make_pair(XK_Caps_Lock, Qt::Key_CapsLock),
        std::make_pair(XK_Num_Lock, Qt::Key_NumLock),
        std::make_pair(XK_Scroll_Lock, Qt::Key_ScrollLock),
        std::make_pair(XK_F1, Qt::Key_F1),
        std::make_pair(XK_F2, Qt::Key_F2),
        std::make_pair(XK_F3, Qt::Key_F3),
        std::make_pair(XK_F4, Qt::Key_F4),
        std::make_pair(XK_F5, Qt::Key_F5),
        std::make_pair(XK_F6, Qt::Key_F6),
        std::make_pair(XK_F7, Qt::Key_F7),
        std::make_pair(XK_F8, Qt::Key_F8),
        std::make_pair(XK_F9, Qt::Key_F9),
        std::make_pair(XK_F10, Qt::Key_F10),
        std::make_pair(XK_F11, Qt::Key_F11),
        std::make_pair(XK_F12, Qt::Key_F12),
        std::make_pair(XK_F13, Qt::Key_F13),
        std::make_pair(XK_F14, Qt::Key_F14),
        std::make_pair(XK_F15, Qt::Key_F15),
        std::make_pair(XK_F16, Qt::Key_F16),
        std::make_pair(XK_F17, Qt::Key_F17),
        std::make_pair(XK_F18, Qt::Key_F18),
        std::make_pair(XK_F19, Qt::Key_F19),
        std::make_pair(XK_F20, Qt::Key_F20),
        std::make_pair(XK_F21, Qt::Key_F21),
        std::make_pair(XK_F22, Qt::Key_F22),
        std::make_pair(XK_F23, Qt::Key_F23),
        std::make_pair(XK_F24, Qt::Key_F24),
        std::make_pair(XK_F25, Qt::Key_F25),
        std::make_pair(XK_F26, Qt::Key_F26),
        std::make_pair(XK_F27, Qt::Key_F27),
        std::make_pair(XK_F28, Qt::Key_F28),
        std::make_pair(XK_F29, Qt::Key_F29),
        std::make_pair(XK_F30, Qt::Key_F30),
        std::make_pair(XK_F31, Qt::Key_F31),
        std::make_pair(XK_F32, Qt::Key_F32),
        std::make_pair(XK_F33, Qt::Key_F33),
        std::make_pair(XK_F34, Qt::Key_F34),
        std::make_pair(XK_F35, Qt::Key_F35),
        std::make_pair(XK_Super_L, Qt::Key_Super_L),
        std::make_pair(XK_Super_R, Qt::Key_Super_R),
        std::make_pair(XK_Menu, Qt::Key_Menu),
        std::make_pair(XK_Hyper_L, Qt::Key_Hyper_L),
        std::make_pair(XK_Hyper_R, Qt::Key_Hyper_R),
        std::make_pair(XK_Help, Qt::Key_Help),
        std::make_pair(XK_ISO_Level3_Shift, Qt::Key_AltGr),
        std::make_pair(XK_Multi_key, Qt::Key_Multi_key),
        std::make_pair(XK_Codeinput, Qt::Key_Codeinput),
        std::make_pair(XK_SingleCandidate, Qt::Key_SingleCandidate),
        std::make_pair(XK_MultipleCandidate, Qt::Key_MultipleCandidate),
        std::make_pair(XK_PreviousCandidate, Qt::Key_PreviousCandidate),
        std::make_pair(XK_Mode_switch, Qt::Key_Mode_switch),
        std::make_pair(XK_script_switch, Qt::Key_Mode_switch),
        std::make_pair(XK_Kanji, Qt::Key_Kanji),
        std::make_pair(XK_Muhenkan, Qt::Key_Muhenkan),
        std::make_pair(XK_Henkan, Qt::Key_Henkan),
        std::make_pair(XK_Romaji, Qt::Key_Romaji),
        std::make_pair(XK_Hiragana, Qt::Key_Hiragana),
        std::make_pair(XK_Katakana, Qt::Key_Katakana),
        std::make_pair(XK_Hiragana_Katakana, Qt::Key_Hiragana_Katakana),
        std::make_pair(XK_Zenkaku, Qt::Key_Zenkaku),
        std::make_pair(XK_Hankaku, Qt::Key_Hankaku),
        std::make_pair(XK_Zenkaku_Hankaku, Qt::Key_Zenkaku_Hankaku),
        std::make_pair(XK_Touroku, Qt::Key_Touroku),
        std::make_pair(XK_Massyo, Qt::Key_Massyo),
        std::make_pair(XK_Kana_Lock, Qt::Key_Kana_Lock),
        std::make_pair(XK_Kana_Shift, Qt::Key_Kana_Shift),
        std::make_pair(XK_Eisu_Shift, Qt::Key_Eisu_Shift),
        std::make_pair(XK_Eisu_toggle, Qt::Key_Eisu_toggle),
        std::make_pair(XK_Kanji_Bangou, Qt::Key_Codeinput),
        std::make_pair(XK_Zen_Koho, Qt::Key_MultipleCandidate),
        std::make_pair(XK_Mae_Koho, Qt::Key_PreviousCandidate),
        std::make_pair(XK_Hangul, Qt::Key_Hangul),
        std::make_pair(XK_Hangul_Start, Qt::Key_Hangul_Start),
        std::make_pair(XK_Hangul_End, Qt::Key_Hangul_End),
        std::make_pair(XK_Hangul_Hanja, Qt::Key_Hangul_Hanja),
        std::make_pair(XK_Hangul_Jamo, Qt::Key_Hangul_Jamo),
        std::make_pair(XK_Hangul_Romaja, Qt::Key_Hangul_Romaja),
        std::make_pair(XK_Hangul_Codeinput, Qt::Key_Codeinput),
        std::make_pair(XK_Hangul_Jeonja, Qt::Key_Hangul_Jeonja),
        std::make_pair(XK_Hangul_Banja, Qt::Key_Hangul_Banja),
        std::make_pair(XK_Hangul_PreHanja, Qt::Key_Hangul_PreHanja),
        std::make_pair(XK_Hangul_PostHanja, Qt::Key_Hangul_PostHanja),
        std::make_pair(XK_Hangul_SingleCandidate, Qt::Key_SingleCandidate),
        std::make_pair(XK_Hangul_MultipleCandidate, Qt::Key_MultipleCandidate),
        std::make_pair(XK_Hangul_PreviousCandidate, Qt::Key_PreviousCandidate),
        std::make_pair(XK_Hangul_Special, Qt::Key_Hangul_Special),
        std::make_pair(XK_Hangul_switch, Qt::Key_Mode_switch),
        std::make_pair(XK_dead_grave, Qt::Key_Dead_Grave),
        std::make_pair(XK_dead_acute, Qt::Key_Dead_Acute),
        std::make_pair(XK_dead_circumflex, Qt::Key_Dead_Circumflex),
        std::make_pair(XK_dead_tilde, Qt::Key_Dead_Tilde),
        std::make_pair(XK_dead_macron, Qt::Key_Dead_Macron),
        std::make_pair(XK_dead_breve, Qt::Key_Dead_Breve),
        std::make_pair(XK_dead_abovedot, Qt::Key_Dead_Abovedot),
        std::make_pair(XK_dead_diaeresis, Qt::Key_Dead_Diaeresis),
        std::make_pair(XK_dead_abovering, Qt::Key_Dead_Abovering),
        std::make_pair(XK_dead_doubleacute, Qt::Key_Dead_Doubleacute),
        std::make_pair(XK_dead_caron, Qt::Key_Dead_Caron),
        std::make_pair(XK_dead_cedilla, Qt::Key_Dead_Cedilla),
        std::make_pair(XK_dead_ogonek, Qt::Key_Dead_Ogonek),
        std::make_pair(XK_dead_iota, Qt::Key_Dead_Iota),
        std::make_pair(XK_dead_voiced_sound, Qt::Key_Dead_Voiced_Sound),
        std::make_pair(XK_dead_semivoiced_sound, Qt::Key_Dead_Semivoiced_Sound),
        std::make_pair(XK_dead_belowdot, Qt::Key_Dead_Belowdot),
        std::make_pair(XK_dead_hook, Qt::Key_Dead_Hook),
        std::make_pair(XK_dead_horn, Qt::Key_Dead_Horn),
        std::make_pair(XF86XK_Back, Qt::Key_Back),
        std::make_pair(XF86XK_Forward, Qt::Key_Forward),
        std::make_pair(XF86XK_Stop, Qt::Key_Stop),
        std::make_pair(XF86XK_Refresh, Qt::Key_Refresh),
        std::make_pair(XF86XK_AudioLowerVolume, Qt::Key_VolumeDown),
        std::make_pair(XF86XK_AudioMute, Qt::Key_VolumeMute),
        std::make_pair(XF86XK_AudioRaiseVolume, Qt::Key_VolumeUp),
        std::make_pair(XF86XK_AudioPlay, Qt::Key_MediaPlay),
        std::make_pair(XF86XK_AudioStop, Qt::Key_MediaStop),
        std::make_pair(XF86XK_AudioPrev, Qt::Key_MediaPrevious),
        std::make_pair(XF86XK_AudioNext, Qt::Key_MediaNext),
        std::make_pair(XF86XK_AudioRecord, Qt::Key_MediaRecord),
        std::make_pair(XF86XK_AudioPause, Qt::Key_MediaPause),
        std::make_pair(XF86XK_HomePage, Qt::Key_HomePage),
        std::make_pair(XF86XK_Favorites, Qt::Key_Favorites),
        std::make_pair(XF86XK_Search, Qt::Key_Search),
        std::make_pair(XF86XK_Standby, Qt::Key_Standby),
        std::make_pair(XF86XK_OpenURL, Qt::Key_OpenUrl),
        std::make_pair(XF86XK_Mail, Qt::Key_LaunchMail),
        std::make_pair(XF86XK_AudioMedia, Qt::Key_LaunchMedia),
        std::make_pair(XF86XK_MyComputer, Qt::Key_Launch0),
        std::make_pair(XF86XK_Calculator, Qt::Key_Launch1),
        std::make_pair(XF86XK_Launch0, Qt::Key_Launch2),
        std::make_pair(XF86XK_Launch1, Qt::Key_Launch3),
        std::make_pair(XF86XK_Launch2, Qt::Key_Launch4),
        std::make_pair(XF86XK_Launch3, Qt::Key_Launch5),
        std::make_pair(XF86XK_Launch4, Qt::Key_Launch6),
        std::make_pair(XF86XK_Launch5, Qt::Key_Launch7),
        std::make_pair(XF86XK_Launch6, Qt::Key_Launch8),
        std::make_pair(XF86XK_Launch7, Qt::Key_Launch9),
        std::make_pair(XF86XK_Launch8, Qt::Key_LaunchA),
        std::make_pair(XF86XK_Launch9, Qt::Key_LaunchB),
        std::make_pair(XF86XK_LaunchA, Qt::Key_LaunchC),
        std::make_pair(XF86XK_LaunchB, Qt::Key_LaunchD),
        std::make_pair(XF86XK_LaunchC, Qt::Key_LaunchE),
        std::make_pair(XF86XK_LaunchD, Qt::Key_LaunchF),
        std::make_pair(XF86XK_MonBrightnessUp, Qt::Key_MonBrightnessUp),
        std::make_pair(XF86XK_MonBrightnessDown, Qt::Key_MonBrightnessDown),
        std::make_pair(XF86XK_KbdLightOnOff, Qt::Key_KeyboardLightOnOff),
        std::make_pair(XF86XK_KbdBrightnessUp, Qt::Key_KeyboardBrightnessUp),
        std::make_pair(XF86XK_KbdBrightnessDown, Qt::Key_KeyboardBrightnessDown),
        std::make_pair(XF86XK_PowerOff, Qt::Key_PowerOff),
        std::make_pair(XF86XK_WakeUp, Qt::Key_WakeUp),
        std::make_pair(XF86XK_Eject, Qt::Key_Eject),
        std::make_pair(XF86XK_ScreenSaver, Qt::Key_ScreenSaver),
        std::make_pair(XF86XK_WWW, Qt::Key_WWW),
        std::make_pair(XF86XK_Memo, Qt::Key_Memo),
        std::make_pair(XF86XK_LightBulb, Qt::Key_LightBulb),
        std::make_pair(XF86XK_Shop, Qt::Key_Shop),
        std::make_pair(XF86XK_History, Qt::Key_History),
        std::make_pair(XF86XK_AddFavorite, Qt::Key_AddFavorite),
        std::make_pair(XF86XK_HotLinks, Qt::Key_HotLinks),
        std::make_pair(XF86XK_BrightnessAdjust, Qt::Key_BrightnessAdjust),
        std::make_pair(XF86XK_Finance, Qt::Key_Finance),
        std::make_pair(XF86XK_Community, Qt::Key_Community),
        std::make_pair(XF86XK_AudioRewind, Qt::Key_AudioRewind),
        std::make_pair(XF86XK_BackForward, Qt::Key_BackForward),
        std::make_pair(XF86XK_ApplicationLeft, Qt::Key_ApplicationLeft),
        std::make_pair(XF86XK_ApplicationRight, Qt::Key_ApplicationRight),
        std::make_pair(XF86XK_Book, Qt::Key_Book),
        std::make_pair(XF86XK_CD, Qt::Key_CD),
        std::make_pair(XF86XK_Calculater, Qt::Key_Calculator),
        std::make_pair(XF86XK_ToDoList, Qt::Key_ToDoList),
        std::make_pair(XF86XK_ClearGrab, Qt::Key_ClearGrab),
        std::make_pair(XF86XK_Close, Qt::Key_Close),
        std::make_pair(XF86XK_Copy, Qt::Key_Copy),
        std::make_pair(XF86XK_Cut, Qt::Key_Cut),
        std::make_pair(XF86XK_Display, Qt::Key_Display),
        std::make_pair(XF86XK_DOS, Qt::Key_DOS),
        std::make_pair(XF86XK_Documents, Qt::Key_Documents),
        std::make_pair(XF86XK_Excel, Qt::Key_Excel),
        std::make_pair(XF86XK_Explorer, Qt::Key_Explorer),
        std::make_pair(XF86XK_Game, Qt::Key_Game),
        std::make_pair(XF86XK_Go, Qt::Key_Go),
        std::make_pair(XF86XK_iTouch, Qt::Key_iTouch),
        std::make_pair(XF86XK_LogOff, Qt::Key_LogOff),
        std::make_pair(XF86XK_Market, Qt::Key_Market),
        std::make_pair(XF86XK_Meeting, Qt::Key_Meeting),
        std::make_pair(XF86XK_MenuKB, Qt::Key_MenuKB),
        std::make_pair(XF86XK_MenuPB, Qt::Key_MenuPB),
        std::make_pair(XF86XK_MySites, Qt::Key_MySites),
        std::make_pair(XF86XK_News, Qt::Key_News),
        std::make_pair(XF86XK_OfficeHome, Qt::Key_OfficeHome),
        std::make_pair(XF86XK_Option, Qt::Key_Option),
        std::make_pair(XF86XK_Paste, Qt::Key_Paste),
        std::make_pair(XF86XK_Phone, Qt::Key_Phone),
        std::make_pair(XF86XK_Calendar, Qt::Key_Calendar),
        std::make_pair(XF86XK_Reply, Qt::Key_Reply),
        std::make_pair(XF86XK_Reload, Qt::Key_Reload),
        std::make_pair(XF86XK_RotateWindows, Qt::Key_RotateWindows),
        std::make_pair(XF86XK_RotationPB, Qt::Key_RotationPB),
        std::make_pair(XF86XK_RotationKB, Qt::Key_RotationKB),
        std::make_pair(XF86XK_Save, Qt::Key_Save),
        std::make_pair(XF86XK_Send, Qt::Key_Send),
        std::make_pair(XF86XK_Spell, Qt::Key_Spell),
        std::make_pair(XF86XK_SplitScreen, Qt::Key_SplitScreen),
        std::make_pair(XF86XK_Support, Qt::Key_Support),
        std::make_pair(XF86XK_TaskPane, Qt::Key_TaskPane),
        std::make_pair(XF86XK_Terminal, Qt::Key_Terminal),
        std::make_pair(XF86XK_Tools, Qt::Key_Tools),
        std::make_pair(XF86XK_Travel, Qt::Key_Travel),
        std::make_pair(XF86XK_Video, Qt::Key_Video),
        std::make_pair(XF86XK_Word, Qt::Key_Word),
        std::make_pair(XF86XK_Xfer, Qt::Key_Xfer),
        std::make_pair(XF86XK_ZoomIn, Qt::Key_ZoomIn),
        std::make_pair(XF86XK_ZoomOut, Qt::Key_ZoomOut),
        std::make_pair(XF86XK_Away, Qt::Key_Away),
        std::make_pair(XF86XK_Messenger, Qt::Key_Messenger),
        std::make_pair(XF86XK_WebCam, Qt::Key_WebCam),
        std::make_pair(XF86XK_MailForward, Qt::Key_MailForward),
        std::make_pair(XF86XK_Pictures, Qt::Key_Pictures),
        std::make_pair(XF86XK_Music, Qt::Key_Music),
        std::make_pair(XF86XK_Battery, Qt::Key_Battery),
        std::make_pair(XF86XK_Bluetooth, Qt::Key_Bluetooth),
        std::make_pair(XF86XK_WLAN, Qt::Key_WLAN),
        std::make_pair(XF86XK_UWB, Qt::Key_UWB),
        std::make_pair(XF86XK_AudioForward, Qt::Key_AudioForward),
        std::make_pair(XF86XK_AudioRepeat, Qt::Key_AudioRepeat),
        std::make_pair(XF86XK_AudioRandomPlay, Qt::Key_AudioRandomPlay),
        std::make_pair(XF86XK_Subtitle, Qt::Key_Subtitle),
        std::make_pair(XF86XK_AudioCycleTrack, Qt::Key_AudioCycleTrack),
        std::make_pair(XF86XK_Time, Qt::Key_Time),
        std::make_pair(XF86XK_Hibernate, Qt::Key_Hibernate),
        std::make_pair(XF86XK_View, Qt::Key_View),
        std::make_pair(XF86XK_TopMenu, Qt::Key_TopMenu),
        std::make_pair(XF86XK_PowerDown, Qt::Key_PowerDown),
        std::make_pair(XF86XK_Suspend, Qt::Key_Suspend),
        std::make_pair(XF86XK_ContrastAdjust, Qt::Key_ContrastAdjust),

        std::make_pair(XF86XK_LaunchE, Qt::Key_LaunchG),
        std::make_pair(XF86XK_LaunchF, Qt::Key_LaunchH),

        std::make_pair(XF86XK_TouchpadToggle, Qt::Key_TouchpadToggle),
        std::make_pair(XF86XK_TouchpadOn, Qt::Key_TouchpadOn),
        std::make_pair(XF86XK_TouchpadOff, Qt::Key_TouchpadOff),

        std::make_pair(XF86XK_AudioMicMute, Qt::Key_MicMute),

        std::make_pair(XF86XK_Red, Qt::Key_Red),
        std::make_pair(XF86XK_Green, Qt::Key_Green),
        std::make_pair(XF86XK_Yellow, Qt::Key_Yellow),
        std::make_pair(XF86XK_Blue, Qt::Key_Blue),
        std::make_pair(XF86XK_New, Qt::Key_New),
        std::make_pair(XF86XK_Open, Qt::Key_Open),
        std::make_pair(XK_Find, Qt::Key_Find),
        std::make_pair(XK_Undo, Qt::Key_Undo),
        std::make_pair(XK_Redo, Qt::Key_Redo),
        std::make_pair(XF86XK_Select, Qt::Key_Select),
        std::make_pair(XK_Cancel, Qt::Key_Cancel),
        std::make_pair(XK_Execute, Qt::Key_Execute),
        std::make_pair(XF86XK_Sleep, Qt::Key_Sleep),
    };
    return keyTbl;
}

int keysymToQtKey(uint32_t key) {
    return KeyTbl().value(key, 0);
}

int keysymToQtKey(uint32_t keysym, const QString &text)
{
    int code = 0;
    if (keysym < 128) {
        // upper-case key, if known
        code = isprint((int)keysym) ? toupper((int)keysym) : 0;
    } else if (text.length() == 1 && text.unicode()->unicode() > 0x1f
                                  && text.unicode()->unicode() != 0x7f
                                  && !(keysym >= XK_dead_grave && keysym <= XK_dead_currency)) {
        code = text.unicode()->toUpper().unicode();
    } else {
        // any other keys
        code = keysymToQtKey(keysym);
    }

    return code;
}
