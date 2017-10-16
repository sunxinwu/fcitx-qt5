/***************************************************************************
 *   Copyright (C) 2012~2013 by CSSlayer                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef QFCITXPLATFORMINPUTCONTEXT_H
#define QFCITXPLATFORMINPUTCONTEXT_H

#include "fcitxinputcontextproxy.h"
#include "fcitxqtdbustypes.h"
#include "fcitxwatcher.h"
#include <QDBusConnection>
#include <QDBusServiceWatcher>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QPointer>
#include <QRect>
#include <QWindow>
#include <qpa/qplatforminputcontext.h>
#include <unordered_map>
#include <xkbcommon/xkbcommon-compose.h>

class FcitxQtConnection;
class QFileSystemWatcher;
enum FcitxKeyEventType { FCITX_PRESS_KEY, FCITX_RELEASE_KEY };

enum FcitxCapabilityFlags {
    CAPACITY_NONE = 0,
    CAPACITY_CLIENT_SIDE_UI = (1 << 0),
    CAPACITY_PREEDIT = (1 << 1),
    CAPACITY_CLIENT_SIDE_CONTROL_STATE = (1 << 2),
    CAPACITY_PASSWORD = (1 << 3),
    CAPACITY_FORMATTED_PREEDIT = (1 << 4),
    CAPACITY_CLIENT_UNFOCUS_COMMIT = (1 << 5),
    CAPACITY_SURROUNDING_TEXT = (1 << 6),
    CAPACITY_EMAIL = (1 << 7),
    CAPACITY_DIGIT = (1 << 8),
    CAPACITY_UPPERCASE = (1 << 9),
    CAPACITY_LOWERCASE = (1 << 10),
    CAPACITY_NOAUTOUPPERCASE = (1 << 11),
    CAPACITY_URL = (1 << 12),
    CAPACITY_DIALABLE = (1 << 13),
    CAPACITY_NUMBER = (1 << 14),
    CAPACITY_NO_ON_SCREEN_KEYBOARD = (1 << 15),
    CAPACITY_SPELLCHECK = (1 << 16),
    CAPACITY_NO_SPELLCHECK = (1 << 17),
    CAPACITY_WORD_COMPLETION = (1 << 18),
    CAPACITY_UPPERCASE_WORDS = (1 << 19),
    CAPACITY_UPPERCASE_SENTENCES = (1 << 20),
    CAPACITY_ALPHA = (1 << 21),
    CAPACITY_NAME = (1 << 22),
    CAPACITY_GET_IM_INFO_ON_FOCUS = (1 << 23),
};

/** message type and flags */
enum FcitxMessageType {
    MSG_TYPE_FIRST = 0,
    MSG_TYPE_LAST = 6,
    MSG_TIPS = 0,      /**< Hint Text */
    MSG_INPUT = 1,     /**< User Input */
    MSG_INDEX = 2,     /**< Index Number */
    MSG_FIRSTCAND = 3, /**< First candidate */
    MSG_USERPHR = 4,   /**< User Phrase */
    MSG_CODE = 5,      /**< Typed character */
    MSG_OTHER = 6,     /**< Other Text */
    MSG_NOUNDERLINE =
        (1 << 3), /**< backward compatible, no underline is a flag */
    MSG_HIGHLIGHT = (1 << 4),                 /**< highlight the preedit */
    MSG_DONOT_COMMIT_WHEN_UNFOCUS = (1 << 5), /**< backward compatible */
    MSG_REGULAR_MASK = 0x7                    /**< regular color type mask */
};

enum FcitxKeyState {
    FcitxKeyState_None = 0,
    FcitxKeyState_Shift = 1 << 0,
    FcitxKeyState_CapsLock = 1 << 1,
    FcitxKeyState_Ctrl = 1 << 2,
    FcitxKeyState_Alt = 1 << 3,
    FcitxKeyState_Alt_Shift = FcitxKeyState_Alt | FcitxKeyState_Shift,
    FcitxKeyState_Ctrl_Shift = FcitxKeyState_Ctrl | FcitxKeyState_Shift,
    FcitxKeyState_Ctrl_Alt = FcitxKeyState_Ctrl | FcitxKeyState_Alt,
    FcitxKeyState_Ctrl_Alt_Shift =
        FcitxKeyState_Ctrl | FcitxKeyState_Alt | FcitxKeyState_Shift,
    FcitxKeyState_NumLock = 1 << 4,
    FcitxKeyState_Super = 1 << 6,
    FcitxKeyState_ScrollLock = 1 << 7,
    FcitxKeyState_MousePressed = 1 << 8,
    FcitxKeyState_HandledMask = 1 << 24,
    FcitxKeyState_IgnoredMask = 1 << 25,
    FcitxKeyState_Super2 = 1 << 26,
    FcitxKeyState_Hyper = 1 << 27,
    FcitxKeyState_Meta = 1 << 28,
    FcitxKeyState_UsedMask = 0x5c001fff
};

struct FcitxQtICData {
    FcitxQtICData(FcitxWatcher *watcher)
        : capability(0), proxy(new FcitxInputContextProxy(watcher, watcher)),
          surroundingAnchor(-1), surroundingCursor(-1) {}
    FcitxQtICData(const FcitxQtICData &that) = delete;
    ~FcitxQtICData() {
        if (proxy) {
            delete proxy;
        }
    }
    QFlags<FcitxCapabilityFlags> capability;
    FcitxInputContextProxy *proxy;
    QRect rect;
    QString surroundingText;
    int surroundingAnchor;
    int surroundingCursor;
};

class ProcessKeyWatcher : public QDBusPendingCallWatcher {
    Q_OBJECT
public:
    ProcessKeyWatcher(const QKeyEvent &event, QWindow *window,
                      const QDBusPendingCall &call, QObject *parent = 0)
        : QDBusPendingCallWatcher(call, parent),
          m_event(event.type(), event.key(), event.modifiers(),
                  event.nativeScanCode(), event.nativeVirtualKey(),
                  event.nativeModifiers(), event.text(), event.isAutoRepeat(),
                  event.count()),
          m_window(window) {}

    virtual ~ProcessKeyWatcher() {}

    const QKeyEvent &keyEvent() { return m_event; }

    QWindow *window() { return m_window.data(); }

private:
    QKeyEvent m_event;
    QPointer<QWindow> m_window;
};

struct XkbContextDeleter {
    static inline void cleanup(struct xkb_context *pointer) {
        if (pointer)
            xkb_context_unref(pointer);
    }
};

struct XkbComposeTableDeleter {
    static inline void cleanup(struct xkb_compose_table *pointer) {
        if (pointer)
            xkb_compose_table_unref(pointer);
    }
};

struct XkbComposeStateDeleter {
    static inline void cleanup(struct xkb_compose_state *pointer) {
        if (pointer)
            xkb_compose_state_unref(pointer);
    }
};

class FcitxQtInputMethodProxy;

class QFcitxPlatformInputContext : public QPlatformInputContext {
    Q_OBJECT
public:
    QFcitxPlatformInputContext();
    virtual ~QFcitxPlatformInputContext();

    virtual bool filterEvent(const QEvent *event) Q_DECL_OVERRIDE;
    virtual bool isValid() const Q_DECL_OVERRIDE;
    virtual void invokeAction(QInputMethod::Action,
                              int cursorPosition) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual void commit() Q_DECL_OVERRIDE;
    virtual void update(Qt::InputMethodQueries quries) Q_DECL_OVERRIDE;
    virtual void setFocusObject(QObject *object) Q_DECL_OVERRIDE;
    virtual QLocale locale() const Q_DECL_OVERRIDE;

public Q_SLOTS:
    void cursorRectChanged();
    void commitString(const QString &str);
    void updateFormattedPreedit(const FcitxFormattedPreeditList &preeditList,
                                int cursorPos);
    void deleteSurroundingText(int offset, uint nchar);
    void forwardKey(uint keyval, uint state, bool type);
    void createInputContextFinished();
    void cleanUp();
    void windowDestroyed(QObject *object);
    void updateCurrentIM(const QString &name, const QString &uniqueName,
                         const QString &langCode);

private:
    bool processCompose(uint keyval, uint state, bool isRelaese);
    QKeyEvent *createKeyEvent(uint keyval, uint state, bool isRelaese);

    void addCapability(FcitxQtICData &data,
                       QFlags<FcitxCapabilityFlags> capability,
                       bool forceUpdate = false) {
        QFlags<FcitxCapabilityFlags> newcaps = data.capability | capability;
        if (data.capability != newcaps || forceUpdate) {
            data.capability = newcaps;
            updateCapability(data);
        }
    }

    void removeCapability(FcitxQtICData &data,
                          QFlags<FcitxCapabilityFlags> capability,
                          bool forceUpdate = false) {
        QFlags<FcitxCapabilityFlags> newcaps = data.capability & (~capability);
        if (data.capability != newcaps || forceUpdate) {
            data.capability = newcaps;
            updateCapability(data);
        }
    }

    void updateCapability(const FcitxQtICData &data);
    void commitPreedit(QPointer<QObject> input = qApp->focusObject());
    void createICData(QWindow *w);
    FcitxInputContextProxy *validIC();
    FcitxInputContextProxy *validICByWindow(QWindow *window);
    bool filterEventFallback(uint keyval, uint keycode, uint state,
                             bool isRelaese);

    FcitxWatcher *m_watcher;
    QString m_preedit;
    QString m_commitPreedit;
    FcitxFormattedPreeditList m_preeditList;
    int m_cursorPos;
    bool m_useSurroundingText;
    bool m_syncMode;
    QString m_lastSurroundingText;
    int m_lastSurroundingAnchor = 0;
    int m_lastSurroundingCursor = 0;
    std::unordered_map<QWindow *, FcitxQtICData> m_icMap;
    QPointer<QWindow> m_lastWindow;
    QPointer<QObject> m_lastObject;
    bool m_destroy;
    QScopedPointer<struct xkb_context, XkbContextDeleter> m_xkbContext;
    QScopedPointer<struct xkb_compose_table, XkbComposeTableDeleter>
        m_xkbComposeTable;
    QScopedPointer<struct xkb_compose_state, XkbComposeStateDeleter>
        m_xkbComposeState;
    QLocale m_locale;
private slots:
    void processKeyEventFinished(QDBusPendingCallWatcher *);
};

#endif // QFCITXPLATFORMINPUTCONTEXT_H
