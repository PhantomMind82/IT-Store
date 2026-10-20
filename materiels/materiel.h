#pragma once

#include <QString>

/** Table Materiel (numMat, design, pu, stockActuel, stockInit) */
class Materiel
{
public:
    Materiel() = default;
    Materiel(const QString &numMat, const QString &design, double pu,
             int stockActuel, int stockInit);

    QString numMat() const;
    QString design() const;
    double  pu() const;
    int     stockActuel() const;
    int     stockInit() const;

    void setNumMat(const QString &numMat);
    void setDesign(const QString &design);
    void setPu(double pu);
    void setStockActuel(int stockActuel);
    void setStockInit(int stockInit);

private:
    QString m_numMat;
    QString m_design;
    double  m_pu = 0.0;
    int     m_stockActuel = 0;
    int     m_stockInit = 0;
};
