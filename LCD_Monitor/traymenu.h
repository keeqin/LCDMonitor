#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QMenu>


class TrayMenu : public QMenu
{
    Q_OBJECT
public:
    TrayMenu(QWidget *parent);
    void initAction(void);
private:
    QAction *m_pQuitAction;
};

#endif // TRAYMENU_H
