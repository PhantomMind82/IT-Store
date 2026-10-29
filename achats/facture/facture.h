#pragma once

#include <QDialog>
#include <QList>

namespace Ui {
class Facture;
}

class Facture : public QDialog
{
    Q_OBJECT

public:
    explicit Facture(const QList<int> &identifiantsAchats, QWidget *parent = nullptr);
    ~Facture() override;

private slots:
    void genererPdf();

private:
    Ui::Facture *ui;
    QString m_html;
    QString m_numero;
};
