/** @file
 *
 * VBox frontends: Qt GUI ("VirtualBox"):
 * UIModalWindowManager class definition
 */

/*
 * Copyright (C) 2013 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

#ifndef __UIModalWindowManager_h__
#define __UIModalWindowManager_h__

/* Qt includes: */
#include <QObject>
#include <QWidget>
#include <QList>

/* Object which contains stack(s) of guarded-pointer(s)
 * to the current top-level modal-window(s)
 * which could be used to determine top-level modal-dialog(s): */
class UIModalWindowManager : public QObject
{
    Q_OBJECT;

public:

    /* Static API: Create/destroy stuff: */
    static void create();
    static void destroy();

    /* API: Access stuff: */
    QWidget* realParentWindow(QWidget *pPossibleParentWidget);
    bool isWindowInTheModalWindowStack(QWidget *pWindow);
    bool isWindowOnTheTopOfTheModalWindowStack(QWidget *pWindow);

    /* API: Register stuff: */
    void registerNewParent(QWidget *pWindow, QWidget *pParentWindow = 0);

    /* API: Main application window stuff: */
    QWidget* mainWindowShown() const;
    QWidget* networkManagerOrMainWindowShown() const;

private slots:

    /* Handler: Stack cleanup stuff: */
    void sltRemoveFromStack(QObject *pObject);

private:

    /* Constructor/destructor: */
    UIModalWindowManager();
    ~UIModalWindowManager();

    /* Helper: Stack stuff: */
    bool contains(QWidget *pParentWindow, bool fAsTheTopOfStack = false);

    /* Variables: */
    QList<QList<QWidget*> > m_windows;
    static UIModalWindowManager* m_spInstance;

    /* Static API: Instance stuff: */
    static UIModalWindowManager* instance();
    friend UIModalWindowManager& windowManager();
};

/* Shortcut to the static UIModalWindowManager::instance() method: */
inline UIModalWindowManager& windowManager() { return *(UIModalWindowManager::instance()); }

#endif /* !__UIModalWindowManager_h__ */
