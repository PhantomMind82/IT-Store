#include "supprimerachat.h"
#include "ui_supprimerachat.h"

#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSvgRenderer>
#include <QVariantList>

static bool executer(const QString &sql, const QVariantList &valeurs)
{
    QSqlQuery q;
    q.prepare(sql);
    for (const QVariant &valeur : valeurs)
        q.addBindValue(valeur);
    return q.exec();
}

SupprimerAchat::SupprimerAchat(int idAchat, QWidget *parent)
    : QDialog(parent), ui(new Ui::SupprimerAchat), m_idAchat(idAchat)
{
    ui->setupUi(this);

    QSvgRenderer renderer(QStringLiteral(":/achats/assets/corbeille-rouge.svg"));
    QPixmap icone(48, 48);
    icone.fill(Qt::transparent);
    if (renderer.isValid()) {
        QPainter painter(&icone);
        renderer.render(&painter);
    } else {
        qWarning() << "Impossible de charger le SVG de suppression";
    }
    ui->iconeCorbeille->setPixmap(icone);

    QSqlQuery q;
    q.prepare("SELECT c.nom, m.designation, a.qte, a.id_materiel, a.numero_commande "
              "FROM achat a "
              "JOIN client c ON c.id_client = a.id_client "
              "JOIN materiel m ON m.id_materiel = a.id_materiel "
              "WHERE a.id_achat = ?");
    q.addBindValue(m_idAchat);
    q.exec();

    if (q.next()) {
        m_quantite = q.value(2).toInt();
        m_idMateriel = q.value(3).toInt();
        m_numeroCommande = q.value(4).toString();
        ui->labelSupprimerTitre->setText("Supprimer cet article ?");
        ui->labelSupprimerDesc->setText(
            QString("Seul l'article %1 (quantité : %2) sera supprimé de la commande %3 de %4. Sa quantité sera remise en stock; les autres articles resteront dans la commande.")
                .arg(q.value(1).toString())
                .arg(m_quantite)
                .arg(m_numeroCommande, q.value(0).toString()));
    }

    connect(ui->btnAnnulerSup, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnConfirmerSup, &QPushButton::clicked, this, &SupprimerAchat::onConfirmer);
}

SupprimerAchat::~SupprimerAchat()
{
    delete ui;
}

void SupprimerAchat::onConfirmer()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.transaction()) {
        QMessageBox::warning(this, "Suppression", "Impossible de démarrer la suppression.");
        return;
    }

    const bool stockMisAJour = executer(
        "UPDATE materiel SET stock_actuel = stock_actuel + ? WHERE id_materiel = ?",
        {m_quantite, m_idMateriel});
    QSqlQuery supprimerArticle;
    supprimerArticle.prepare("DELETE FROM achat WHERE id_achat = ? AND numero_commande = ?");
    supprimerArticle.addBindValue(m_idAchat);
    supprimerArticle.addBindValue(m_numeroCommande);
    const bool articleSupprime = stockMisAJour
        && supprimerArticle.exec()
        && supprimerArticle.numRowsAffected() == 1;

    if (!articleSupprime || !database.commit()) {
        database.rollback();
        QMessageBox::warning(this, "Suppression", "Impossible de supprimer cet article.");
        return;
    }

    accept();
}