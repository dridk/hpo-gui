#include "HpoModel.h"

HpoModel::HpoModel(QObject *parent)
    :QAbstractItemModel(parent)
{
}

HpoModel::~HpoModel()
{
    if (mRootNode)
        delete mRootNode;
}

int HpoModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int HpoModel::rowCount(const QModelIndex &parent) const
{
    Node * parentNode;

    if (!parent.isValid())
        parentNode = mRootNode;
    else
        parentNode = static_cast<Node*>(parent.internalPointer());

    return parentNode->childCount();



}

QModelIndex HpoModel::index(int row, int column, const QModelIndex &parent) const
{

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node *parentItem;

    if (!parent.isValid())
        parentItem = mRootNode;
    else
        parentItem = static_cast<Node*>(parent.internalPointer());

    Node *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex HpoModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Node *childItem = static_cast<Node*>(index.internalPointer());
    Node *parentItem = childItem->parent();


    if (parentItem == mRootNode)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant HpoModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    Node * node = static_cast<Node*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {

        if (index.column() == 0)
            return node->hpo();


        if (index.column() == 1)
            return node->name();

    }

    if (role == Qt::CheckStateRole && index.column() == 0)
        return Qt::Unchecked;


    return QVariant();
}

void HpoModel::setDatabase(const QString &database)
{
    beginResetModel();

    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(database);

    if (!mDb.open())
        qDebug()<<"cannot open database";

    //    SELECT left, right, terms.name FROM nodes, terms
    //    WHERE nodes.depth = 1 AND nodes.term_id = terms.id




    mRootNode = new Node("HP:0012823");


    mRootNode->loadChild();



    // mRootNode->child(0)->loadChild();
    //    mRootNode->child(0)->child(0)->loadChild();



    endResetModel();


}

bool HpoModel::canFetchMore(const QModelIndex &index) const
{
    if (index == QModelIndex())
        return false;


    Node * node = static_cast<Node*>(index.internalPointer());

    if (node->hasChildren() && node->childCount() == 0)
        return true;

    return false;


}

void HpoModel::fetchMore(const QModelIndex &parent)
{

    qDebug()<<"fetch mode " <<parent;

    Node * node ;
    if (parent == QModelIndex())
        node = mRootNode;
    else
        node = static_cast<Node*>(parent.internalPointer());

    int count = node->fetchCount();

    beginInsertRows(parent,0, count);

    node->loadChild();

    endInsertRows();

    //endResetModel();

}

bool HpoModel::hasChildren(const QModelIndex &parent) const
{

    if (parent == QModelIndex())
        return mRootNode->hasChildren();


    Node * node = static_cast<Node*>(parent.internalPointer());

    return node->hasChildren();

}

Qt::ItemFlags HpoModel::flags(const QModelIndex &index) const
{

    return Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled;
}

Node *HpoModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index == QModelIndex())
        return mRootNode;
    return static_cast<Node*>(index.internalPointer());
}

//bool HpoModel::canFetchMore(const QModelIndex &index) const
//{

//    return false;

//    if (!index.isValid())
//        return false;

//  //  Node * node = static_cast<Node*>(parent.internalPointer());

//   return true;

//    return false;
//}


//void HpoModel::fetchMore(const QModelIndex &parent) const
//{

//}


