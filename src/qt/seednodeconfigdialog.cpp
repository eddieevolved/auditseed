#include "seednodeconfigdialog.h"
#include "ui_seednodeconfigdialog.h"

#include <QModelIndex>

SeedNodeConfigDialog::SeedNodeConfigDialog(QWidget *parent, QString nodeAddress, QString privkey) :
    QDialog(parent),
    ui(new Ui::SeedNodeConfigDialog)
{
    ui->setupUi(this);
    QString desc = "rpcallowip=127.0.0.1<br>rpcuser=REPLACEME<br>rpcpassword=REPLACEME<br>staking=0<br>server=1<br>listen=1<br>port=REPLACEMEWITHYOURPORT<br>masternode=1<br>masternodeaddr=" + nodeAddress + "<br>masternodeprivkey=" + privkey + "<br>";
    ui->detailText->setHtml(desc);
}

SeedNodeConfigDialog::~SeedNodeConfigDialog()
{
    delete ui;
}
