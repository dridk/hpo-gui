#ifndef GENEMODEL_H
#define GENEMODEL_H
#include <QAbstractListModel>
#include <QtSql>

class GeneModel;
class Gene;


struct Gene
{
  QString name;
  QString entrez;
  int occurance;
  int total;

};



class GeneModel : public QAbstractListModel
{
    Q_OBJECT
public:
    GeneModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;


public Q_SLOTS:
    void load(const QString& hpolist);


private:
    QList<Gene> mGenes;


};

#endif // GENEMODEL_H
