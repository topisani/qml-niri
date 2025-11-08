#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QtQmlIntegration/qqmlintegration.h>

class Workspace : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
    Q_PROPERTY(quint64 id MEMBER id CONSTANT);
    Q_PROPERTY(quint8 index MEMBER index CONSTANT);
    Q_PROPERTY(QString name MEMBER name CONSTANT);
    Q_PROPERTY(QString output MEMBER output CONSTANT);
    Q_PROPERTY(bool isActive MEMBER isActive CONSTANT);
    Q_PROPERTY(bool isFocused MEMBER isFocused CONSTANT);
    Q_PROPERTY(bool isUrgent MEMBER isUrgent CONSTANT);
    Q_PROPERTY(quint64 activeWindowId MEMBER activeWindowId CONSTANT);

public:
    explicit Workspace(QObject *parent = nullptr): QObject(parent) {}

    quint64 id = 0;
    quint8 index ;
    QString name;
    QString output;
    bool isActive;
    bool isFocused;
    bool isUrgent;
    quint64 activeWindowId;
};

class WorkspaceModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(Workspace *focusedWorkspace READ focusedWorkspace NOTIFY focusedWorkspaceChanged)

public:
    using value_type = Workspace*;

    enum WorkspaceRoles {
        IdRole = Qt::UserRole + 1,
        IndexRole,
        NameRole,
        OutputRole,
        IsActiveRole,
        IsFocusedRole,
        IsUrgentRole,
        ActiveWindowIdRole
    };
    Q_ENUM(WorkspaceRoles)

    explicit WorkspaceModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    Workspace* focusedWorkspace() const { return m_focusedWorkspace; }

public slots:
    void handleEvent(const QJsonObject &event);

signals:
    void countChanged();
    void focusedWorkspaceChanged();

private:
    void handleWorkspacesChanged(const QJsonArray &workspaces);
    void handleWorkspaceActivated(quint64 id, bool focused);
    void handleWorkspaceUrgencyChanged(quint64 id, bool urgent);
    void handleWorkspaceActiveWindowChanged(quint64 workspaceId, const QJsonValue &activeWindowId);

    Workspace* parseWorkspace(const QJsonObject &obj);
    int findWorkspaceIndex(quint64 id) const;

    QList<Workspace*> m_workspaces;
    Workspace* m_focusedWorkspace = nullptr;
};
