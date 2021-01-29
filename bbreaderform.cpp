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
    m_files = QFileDialog::getOpenFileNames(this, "Open files", QDir::homePath());
    ui->lineEditFilePath->setText(QString("%1 files selected").arg(m_files.size()));
}

void BbReaderForm::on_pushButtonDecode_clicked()
{
    ui->lineEditFilePath->setText(QString("0/%1 files decoded")
                                  .arg(m_files.size()));
    for(int i = 0; i < m_files.size(); i++) {
        decode(m_files[i]);
        ui->lineEditFilePath->setText(QString("%1/%2 files decoded")
                                      .arg(i + 1)
                                      .arg(m_files.size()));
    }
}

void BbReaderForm::decode(const QString &path)
{
    QFile file(path);
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
