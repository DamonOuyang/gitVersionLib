#ifndef REMINDERINFODLG_H
#define REMINDERINFODLG_H

#include <QWidget>
#include <QGraphicsWidget>

class ReminderInfoDlg : public QGraphicsWidget
{
    Q_OBJECT

public:
    ReminderInfoDlg(QGraphicsWidget *parent = 0);
    ~ReminderInfoDlg();
};

#endif // REMINDERINFODLG_H
