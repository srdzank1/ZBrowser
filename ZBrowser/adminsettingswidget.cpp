#include "adminsettingswidget.h"
#include "ui_adminsettingswidget.h"

AdminSettingsWidget::AdminSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminSettingsWidget)
{
    ui->setupUi(this);
}

AdminSettingsWidget::~AdminSettingsWidget()
{
    delete ui;
}
