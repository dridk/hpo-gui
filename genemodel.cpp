#include "genemodel.h"

GeneModel::GeneModel(QObject *parent)
{

}

int GeneModel::rowCount(const QModelIndex &parent) const
{
    return mGenes.count();
}

int GeneModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant GeneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){

        if (index.column() == 0)
        return mGenes.at(index.row()).name;

        if (index.column() == 1)
            return mGenes.at(index.row()).occurance;

    }


    return QVariant();
}

void GeneModel::sort(int column, Qt::SortOrder order)
{

    beginResetModel();

    qSort(mGenes.begin(), mGenes.end(), [this, column, order](const Gene& a, const Gene& b)
    {

        bool res;

        if (column == 0)
            res = (a.name > b.name);

        else
            res = (a.occurance > b.occurance);

        return order ? res : !res;


    });

    endResetModel();

}

void GeneModel::load(const QString &hpolist)
{

   QHash<QString, Gene> list;

   QStringList hpos = hpolist.split(" ");

    for (QString hpo : hpos)
    {

        QSqlQuery query(QString("SELECT genes.* FROM term_has_genes, genes , terms WHERE term_has_genes.gene_id = genes.id AND term_has_genes.term_id = terms.id "
                                "AND terms.hpo = '%1'"
                                ).arg(hpo));

        while (query.next())
        {

            QString geneName = query.record().value("name").toString();

            if (!list.contains(geneName)){
                list[geneName].name = geneName;
                list[geneName].occurance = 1;
                list[geneName].total = hpos.size();
            }

            else
                list[geneName].occurance ++ ;

        }

    }


    beginResetModel();
    // EXEMPLE :   HP:0000581 HP:0000537 ptosis et blepharophimosis situs invertus ==>


    mGenes = list.values();

    endResetModel();

}
