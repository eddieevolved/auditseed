#ifndef SEEDNODECONFIGDIALOG_H
#define SEEDNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class SeedNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class SeedNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeedNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:28666", QString privkey="MASTERNODEPRIVKEY");
    ~SeedNodeConfigDialog();

private:
    Ui::SeedNodeConfigDialog *ui;
};

#endif // SEEDNODECONFIGDIALOG_H
