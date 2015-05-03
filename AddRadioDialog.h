#ifndef ADDRADIODIALOG_H
#define ADDRADIODIALOG_H

#include <QLineEdit>
#include <QDialog>

class RadioListHandler;

class AddRadioDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddRadioDialog(RadioListHandler *handler, QWidget *parent = 0);

private:
  RadioListHandler *m_radioListHandler;

  QLineEdit m_radioNameEdit;
  QLineEdit m_streamSourceEdit;

signals:

public slots:

    void accept();
};

#endif // ADDRADIODIALOG_H
