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
    return nodeFromIndex(parent)->childCount();
}

QModelIndex HpoModel::index(int row, int column, const QModelIndex &parent) const
{

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node * parentNode;

    parentNode = nodeFromIndex(parent);

    Node * node = parentNode->child(row);
    if (node)
        return createIndex(row, column, node);
    else
        return QModelIndex();
}

QModelIndex HpoModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Node * node      = static_cast<Node*>(index.internalPointer());
    Node *parentNode = node->parent();

    if (parentNode == mRootNode)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);
}

QVariant HpoModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    Node * node = nodeFromIndex(index);

    if (role == Qt::DisplayRole)
    {

        if (index.column() == 0)
            return node->hpo();


        if (index.column() == 1)
            return node->name();

    }

//    if (role == Qt::CheckStateRole && index.column() == 0)
//        return Qt::Unchecked;


    return QVariant();
}

void HpoModel::setDatabase(const QString &database)
{

    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(database);

    if (!mDb.open())
        qDebug()<<"cannot open database";

    //    SELECT left, right, terms.name FROM nodes, terms
    //    WHERE nodes.depth = 1 AND nodes.term_id = terms.id



    load();




}

bool HpoModel::canFetchMore(const QModelIndex &index) const
{
    if (index == QModelIndex())
        return false;


    Node * node = nodeFromIndex(index);

    if (node->hasChildren() && node->childCount() == 0)
        return true;

    return false;


}

void HpoModel::fetchMore(const QModelIndex &parent)
{

    qDebug()<<"fetch mode " <<parent;

    Node * node = nodeFromIndex(parent);

    int count = node->fetchCount();

    beginInsertRows(parent,0, count);

    node->loadChild();

    endInsertRows();

    //endResetModel();

}

bool HpoModel::hasChildren(const QModelIndex &parent) const
{
    Node * node = nodeFromIndex(parent);
    return node->hasChildren();
}

Qt::ItemFlags HpoModel::flags(const QModelIndex &index) const
{

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

Node *HpoModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index == QModelIndex())
        return mRootNode;
    return static_cast<Node*>(index.internalPointer());
}

void HpoModel::load(const QString &search)
{

    beginResetModel();

    if (mRootNode)
        delete mRootNode;

    mRootNode = new Node();


    // load All
    if (search.isEmpty())
        mRootNode->addChild(new Node(1));

    // load only with search terms
    else {
        for (Node * node : Node::createNode(search))
            mRootNode->addChild(node);
    }

    endResetModel();



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


