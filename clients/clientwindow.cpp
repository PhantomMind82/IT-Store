#include "clientwindow.h"
#include "commun/style.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ClientWindow::ClientWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("CLIENTS"));
    resize(760, 480);
    setStyleSheet(QStringLiteral("QDialog { background: %1; }").arg(Style::FOND_VIOLET));

    auto *module = new QLabel(tr("CLIENTS"), this);
    module->setAlignment(Qt::AlignCenter);
    module->setStyleSheet(QStringLiteral(
        "font-size: 24px; font-weight: bold; letter-spacing: 6px; color: %1;")
        .arg(Style::BLEU));

    auto *message = new QLabel(tr("EN COURS DE DÉVELOPPEMENT"), this);
    message->setAlignment(Qt::AlignCenter);
    message->setWordWrap(true);
    message->setStyleSheet(QStringLiteral(
        "font-size: 40px; font-weight: bold; color: %1;").arg(Style::BLEU_FONCE));

    auto *fermer = new QPushButton(tr("Fermer"), this);
    fermer->setCursor(Qt::PointingHandCursor);
    connect(fermer, &QPushButton::clicked, this, &QDialog::accept);

    auto *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(module);
    layout->addWidget(message);
    layout->addStretch();
    layout->addWidget(fermer, 0, Qt::AlignRight);

    // TODO : remplacer ce contenu par l'interface réelle du module
}
