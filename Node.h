#ifndef NODE_H
#define NODE_H
#include <QtCore>
#include <QtSql>


/*! \class Node
 *
 * This class contains Node from HPO terms as a tree data structure.
 *
 * \example
 * Create node from first node sql id = 1
 * Node * node = new Node(1)
 * node->loadChild()
 * node->child(0)->loadChild()
 *
 */

class Node;
class Node
{
public:
    /*!
     * \brief Node
     * \param id     : sql node id
     * \param parent : Node parent
     */
    Node(int id, Node * parent = nullptr);
    Node(const QString& hpo = QString(), Node * parent = nullptr);
    ~Node();

    /*!
     * \brief addChild
     * \param child to append
     * add node child
     */
    void addChild(Node * child);

    /*!
     * \brief child
     * \param row
     * \return Node child from current node
     */
    Node * child(int row);

    /*!
     * \brief childCount
     * \return how many child from current node
     */
    int childCount() const;

    int fetchCount() const;

    /*!
     * \brief row
     * \return row index
     */
    int row() const;

    /*!
     * \brief parent
     * \return parent
     */
    Node * parent() const;

    /*!
     * \brief setNodeId
     * Load node information from sql ID
     * \param nodeId
     */
    void setNodeId(int nodeId);


    int nodeId() const;
    int left() const;
    int right() const;
    int depth() const;
    QString name() const;
    QString term() const;
    QString hpo() const;


    /*!
     * \brief loadChild
     * Load children from current node
     */
    void loadChild();

    /*!
     * \brief hasChildren
     * \return true if it's possible to fetch children
     */
    bool hasChildren();


    /*!
     * \brief idFromTerm
     * \param term
     * \return sql id from hpo term
     */
    quint32 idFromTerm(const QString& term);

    static QList<Node*> createNode(const QString& term);



private:
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
