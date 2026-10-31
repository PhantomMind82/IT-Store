#include "materiel.h"

Materiel::Materiel(const QString &numMat, const QString &design, double pu,
                   int stockActuel, int stockInit)
    : m_numMat(numMat), m_design(design), m_pu(pu),
      m_stockActuel(stockActuel), m_stockInit(stockInit)
{
}

QString Materiel::numMat() const      { return m_numMat; }
QString Materiel::design() const      { return m_design; }
double  Materiel::pu() const          { return m_pu; }
int     Materiel::stockActuel() const { return m_stockActuel; }
int     Materiel::stockInit() const   { return m_stockInit; }

void Materiel::setNumMat(const QString &numMat)  { m_numMat = numMat; }
void Materiel::setDesign(const QString &design)  { m_design = design; }
void Materiel::setPu(double pu)                  { m_pu = pu; }
void Materiel::setStockActuel(int stockActuel)   { m_stockActuel = stockActuel; }
void Materiel::setStockInit(int stockInit)       { m_stockInit = stockInit; }
