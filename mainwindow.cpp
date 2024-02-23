#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox_loading->setChecked(ui->x_switch_btn->loading());
    ui->checkBox_slide->setChecked(ui->x_switch_btn->animation());
    ui->checkBox_text->setChecked(ui->x_switch_btn->showText());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_set_on_clicked()
{
    ui->x_switch_btn->setChecked(true);
}


void MainWindow::on_btn_set_off_clicked()
{
    ui->x_switch_btn->setChecked(false);
}


void MainWindow::on_checkBox_loading_stateChanged(int arg1)
{
    if(arg1){
        ui->x_switch_btn->setLoading(true);
        ui->btn_set_on->setDisabled(false);
        ui->btn_set_off->setDisabled(false);
    }else{
        ui->x_switch_btn->setLoading(false);
        ui->btn_set_on->setDisabled(true);
        ui->btn_set_off->setDisabled(true);
    }
}


void MainWindow::on_checkBox_slide_stateChanged(int arg1)
{
    if(arg1){
        ui->x_switch_btn->setAnimation(true);
    }else{
        ui->x_switch_btn->setAnimation(false);
    }
}


void MainWindow::on_checkBox_text_stateChanged(int arg1)
{
    if(arg1){
        ui->x_switch_btn->setShowText(true);
    }else{
        ui->x_switch_btn->setShowText(false);
    }
}

