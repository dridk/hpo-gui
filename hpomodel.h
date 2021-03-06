#ifndef HPOMODEL_H
#define HPOMODEL_H
#include <QAbstractItemModel>
#include <QtSql>
#include "node.h"

class HpoModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    HpoModel(QObject * parent = nullptr);
    ~HpoModel();

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QVariant data(const QModelIndex &index, int role) const;

    void setDatabase(const QString& database);


    bool canFetchMore(const QModelIndex& index) const override;

    void fetchMore(const QModelIndex& parent) override;

     bool hasChildren(const QModelIndex &parent = QModelIndex()) const;

    Qt::ItemFlags flags(const QModelIndex &index) const override;


    Node * nodeFromIndex(const QModelIndex& index) const;


    Node * rootNode() const;

    void setRoot(Node * node);

public Q_SLOTS:
    void search(const QString& search = QString());


private:
    QSqlDatabase mDb;

    Node * mRootNode = nullptr;

};

#endif // HPOMODEL_H
