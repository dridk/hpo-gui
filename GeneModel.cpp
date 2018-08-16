#include "GeneModel.h"

GeneModel::GeneModel(QObject *parent)
{

}

int GeneModel::rowCount(const QModelIndex &parent) const
{
    return mGenes.count();
}

int GeneModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant GeneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return mGenes.at(index.row()).name;


    return QVariant();
}

void GeneModel::load(const QString &hpolist)
{

    QHash< QString, QSet<QString>> setList;

    for (QString hpo : hpolist.split(" "))
    {

        setList[hpo] = QSet<QString>();

        QSqlQuery query(QString("SELECT genes.* FROM term_has_genes, genes , terms WHERE term_has_genes.gene_id = genes.id AND term_has_genes.term_id = terms.id "
                                "AND terms.hpo = '%1'"
                                ).arg(hpo));

        while (query.next())
        {

            setList[hpo].insert(query.record().value("name").toString());

        }

//        qDebug()<<query.lastError();
//        qDebug()<<query.lastQuery();

        qDebug()<<"HPO "<<hpo<<setList[hpo];

    }


// EXEMPLE :   HP:0000581 HP:0000537 ptosis et blepharophimosis situs invertus ==>
    QSet<QString> all  = setList[setList.keys().first()];

    for (const QString& hpo : setList.keys())
        all.intersect(setList[hpo]);


    beginResetModel();
    mGenes.clear();

    for (const QString& gene : all)
        mGenes.append({gene,"", 3,3});


    endResetModel();



}
