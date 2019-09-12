#include "bbreaderform.h"
#include "ui_bbreaderform.h"

#include <cassert>
#include <QFileDialog>
#include <future>
#include <Vehicles/Vehicles.h>
#include <QDebug>
#include "EscReader.h"
#include <Telemetry/Telemetry.h>
#include <Telemetry/TelemetryRecorder.h>
#include <QMessageBox>

BbReaderForm::BbReaderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BbReaderForm)
{
    ui->setupUi(this);
}

BbReaderForm::~BbReaderForm()
{
    delete ui;
}

void BbReaderForm::on_pushButtonOpen_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    if(!filePath.isEmpty())
        ui->lineEditFilePath->setText(filePath);
}

void BbReaderForm::on_pushButtonDecode_clicked()
{
    QFile file(ui->lineEditFilePath->text());
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "Can't open file: " + file.errorString(), QMessageBox::Ok);
        return;
    }

    auto vehicle =  Vehicles::instance()->current();
    vehicle->f_telemetry->f_recorder->setValue(true);
    EscReader reader;
    connect(&reader, &EscReader::packet_read, vehicle->protocol, &ProtocolVehicle::unpack);

    ui->progressBar->setMaximum(file.size());
    ui->progressBar->setValue(0);
    auto tp1 = std::chrono::high_resolution_clock::now();
    size_t bytesReaded = 0;
    while(!file.atEnd())
    {
        QByteArray data = file.read(512);
        bytesReaded += data.size();
        reader.push(data);

        auto tp2 = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count() > 100)
        {
            tp1 = tp2;
            qApp->processEvents();
        }
        ui->progressBar->setValue(bytesReaded);
    }
    vehicle->f_telemetry->f_recorder->setValue(false);
}
