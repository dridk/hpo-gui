#ifndef GENEMODEL_H
#define GENEMODEL_H
#include <QAbstractListModel>
#include <QtSql>
#include <QtCore>

class GeneModel;
class Gene;


struct Gene
{
  QString name;
  QString entrez;
  int occurance = 0;
  int total     = 0;

};



class GeneModel : public QAbstractListModel
{
    Q_OBJECT
public:
    GeneModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;


public Q_SLOTS:
    void load(const QString& hpolist);


private:
    QList<Gene> mGenes;


};

#endif // GENEMODEL_H
