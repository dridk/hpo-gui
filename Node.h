#ifndef NODE_H
#define NODE_H
#include <QtCore>
#include <QtSql>

class Node;
class Node
{
public:
    Node(int nodeId, Node * parent = nullptr);
    ~Node();

    void addChild(Node * child);
    Node * child(int row);

    int childCount() const;

    int row() const;
    Node * parent() const;
    int nodeId() const;
    void setNodeId(int nodeId);

    QString name() const;

    QString term() const;

    void loadChild();

    bool hasChildren();

//private:

    int mNodeId = -1;
    QString mName;
    QString mTerm;
    int mLeft = -1;
    int mRight = -1;
    int mDepth = -1 ;
    QString mHpo;
    Node * mParent = nullptr;
    QList<Node*> mChilds;

    int mFetchChildCount;

    bool mCanFetchMode = false;

};

#endif // NODE_H
