#include "traymenu.h"
#include <QDebug>
#include <QIcon>
#include <QApplication>
TrayMenu::TrayMenu(QWidget *parent) : QMenu(parent)
{
    initAction();
}


void TrayMenu::initAction(void)
{
    m_pQuitAction = new QAction(QIcon(":/icon/quit.jpg"), "Quit", this);
    addAction(m_pQuitAction);
    connect(m_pQuitAction, &QAction::triggered, this, &QApplication::quit);
}


