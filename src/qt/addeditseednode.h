#ifndef ADDEDITSEEDNODE_H
#define ADDEDITSEEDNODE_H

#include <QDialog>

namespace Ui {
class AddEditSeedNode;
}


class AddEditSeedNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditSeedNode(QWidget *parent = 0);
    ~AddEditSeedNode();

protected:

private Q_SLOTS:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditSeedNode *ui;
};

#endif // ADDEDITSEEDNODE_H
