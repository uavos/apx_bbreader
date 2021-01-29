#ifndef BBREADERFORM_H
#define BBREADERFORM_H

#include <QWidget>

namespace Ui {
class BbReaderForm;
}

class BbReaderForm : public QWidget
{
    Q_OBJECT

public:
    explicit BbReaderForm(QWidget *parent = nullptr);
    ~BbReaderForm();

private slots:
    void on_pushButtonOpen_clicked();
    void on_pushButtonDecode_clicked();

private:
    Ui::BbReaderForm *ui;
    QStringList m_files;
    void decode(const QString &path);
};

#endif // BBREADERFORM_H
