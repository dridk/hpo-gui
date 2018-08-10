#include "Node.h"

Node::Node(int id, Node * parent)
    :mParent(parent)
{
    qDebug()<<"const";

    setNodeId(id);
}

Node::Node(const QString &hpo, Node *parent)
    :mParent(parent)
{
    // this is the first node "all"
    if (hpo.isEmpty())
        setNodeId(1);

    quint32 id = idFromTerm(hpo);

    qDebug()<<"ID "<<id;
    if (!id)
        setNodeId(1);

    setNodeId(id);

}

Node::~Node()
{
    qDeleteAll(mChilds);
}

void Node::addChild(Node *child)
{
    mChilds.append(child);
}

Node *Node::child(int row)
{
    return mChilds.value(row);
}

int Node::childCount() const
{
    return mChilds.count();
}

int Node::fetchCount() const
{
    return qAbs(right() - left()) / 2;
}



int Node::row() const
{

    if (mParent)
        mParent->mChilds.indexOf(const_cast<Node*>(this));

    return 0;
}

Node *Node::parent() const
{
    return mParent;
}

int Node::nodeId() const
{
    return mNodeId;
}

void Node::setNodeId(int nodeId)
{
    mNodeId = nodeId;


    QString q = QString("SELECT nodes.id, nodes.left, nodes.right, nodes.depth, terms.name, terms.hpo FROM nodes, terms WHERE nodes.term_id = terms.id AND nodes.id = %1").arg(nodeId);
    QSqlQuery query(q);

    if (query.next())
    {
        mName   = query.record().value("name").toString();
        mNodeId = query.record().value("id").toInt();
        mHpo    = query.record().value("hpo").toString();
        mDepth  = query.record().value("depth").toInt();

        mLeft   = query.record().value("left").toInt();
        mRight  = query.record().value("right").toInt();


    }


    // can fetch more
    //    q = QString("SELECT COUNT(*) FROM nodes WHERE nodes.left > %1 AND nodes.right < %2 AND depth == %3").arg(mLeft).arg(mRight).arg(mDepth+1);

    //    query.exec(q);

    //    if (query.next())
    //    {
    //       mFetchChildCount =  query.record().value(0).toInt();


    //    }

}

QString Node::name() const
{
    return mName;
}


QString Node::term() const
{
    return mTerm;
}

void Node::loadChild()
{

    mChilds.clear();
    QString q = QString("SELECT nodes.id FROM nodes WHERE nodes.left > %1 AND nodes.right < %2 AND depth == %3").arg(mLeft).arg(mRight).arg(mDepth+1);

    QSqlQuery query(q);

    while (query.next())
    {
        int nodeId = query.record().value(0).toInt();
        addChild(new Node(nodeId,this));

    }

}

bool Node::hasChildren()
{
    int diff = qAbs(mLeft - mRight);
    return qAbs(mLeft - mRight) > 1;
}

quint32 Node::idFromTerm(const QString &term)
{
    QString q = QString("SELECT nodes.id FROM terms, nodes WHERE terms.hpo = '%1' AND nodes.term_id = nodes.id ").arg(term);
    QSqlQuery query(q);

    if (query.next())
    {
        return query.record().value(0).toInt();
    }

    qDebug()<<query.lastQuery();
    return 0;

}

QList<Node *> Node::createNode(const QString &term)
{

}

QString Node::hpo() const
{
    return mHpo;
}

int Node::depth() const
{
    return mDepth;
}

int Node::right() const
{
    return mRight;
}

int Node::left() const
{
    return mLeft;
}

