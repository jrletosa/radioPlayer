#include "AddRadioDialog.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "RadioManager.h"

AddRadioDialog::AddRadioDialog(RadioListHandler *handler, QWidget *parent)
    : QDialog(parent)
    , m_radioListHandler(handler)
{
    QFormLayout *formLayout= new QFormLayout();
    m_radioNameEdit.setMinimumWidth(200);
    formLayout->addRow("Radio name:", &m_radioNameEdit);
    formLayout->addRow("Stream source:", &m_streamSourceEdit);

    QDialogButtonBox *buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QVBoxLayout *verticalLayout= new QVBoxLayout();
    verticalLayout->addLayout(formLayout);
    verticalLayout->addWidget(buttonBox);
    setLayout(verticalLayout);
}


void AddRadioDialog::accept()
{
    if (m_radioListHandler != NULL)
    {
        m_radioListHandler->setRadio(m_radioNameEdit.text().toStdString(), m_streamSourceEdit.text().toStdString());
    }
    QDialog::accept();
}
