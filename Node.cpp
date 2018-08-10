#include "Node.h"

Node::Node(int nodeId, Node *parent)
    :mParent(parent)
{

    setNodeId(nodeId);

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
