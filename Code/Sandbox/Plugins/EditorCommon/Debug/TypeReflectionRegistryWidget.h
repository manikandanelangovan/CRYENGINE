// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

#include "EditorFramework/Editor.h"

#include <CryType/Type.h>
#include <QAbstractItemModel>

struct ITypeDesc;
class QFilteringPanel;
class QAdvancedTreeView;
class QAttributeFilterProxyModel;

class CTypeReflectionRegistryModel : public QAbstractItemModel
{
public:
	enum EColumn : int32
	{
		eColumn_TypeIndex = 0,
		eColumn_Size,
		eColumn_Label,
		eColumn_Description,
		eColumn_Guid,
		eColumn_FullQualifiedName,
		eColumn_Registered,
		eColumn_Source,
		eColumn_COUNT,
	};

public:
	CTypeReflectionRegistryModel(QObject* parent = nullptr);
	virtual ~CTypeReflectionRegistryModel() final;

	// QAbstractItemModel
	virtual QVariant    data(const QModelIndex& index, int role = Qt::DisplayRole) const final;
	virtual QVariant    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;
	virtual int         rowCount(const QModelIndex& parent = QModelIndex()) const final;

	virtual int         columnCount(const QModelIndex& parent = QModelIndex()) const final                { return eColumn_COUNT; }
	virtual QModelIndex parent(const QModelIndex& index) const final                                      { return QModelIndex(); }
	virtual bool        hasChildren(const QModelIndex& parent = QModelIndex()) const final                { return !parent.isValid(); }
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const final { return createIndex(row, column, nullptr); }
	// ~QAbstractItemModel

protected:
	static const int                     s_attributeCount;
	static const CItemModelAttribute     s_columnAttributes[eColumn_COUNT];

	std::map<Cry::Type::CTypeId, string> m_typeRegistries;

private:
	void GenerateDataCache();
};

class CTypeReflectionRegistryWidget : public QWidget
{
public:
	CTypeReflectionRegistryWidget(QWidget* parent = nullptr);
	virtual ~CTypeReflectionRegistryWidget() final;

	QAdvancedTreeView* GetView() const;

private:
	QAdvancedTreeView*            m_pView;
	CTypeReflectionRegistryModel* m_pModel;
	QAttributeFilterProxyModel*   m_pFilter;
	QFilteringPanel*              m_pFilteringPanel;
};

class CTypeReflectionRegistryDockable : public CDockableEditor
{
public:
	CTypeReflectionRegistryDockable(QWidget* pParent = nullptr);
	virtual ~CTypeReflectionRegistryDockable() final;

	// CEditor
	virtual const char* GetEditorName() const override { return "Type Reflection Registry"; }
	virtual void        SetLayout(const QVariantMap& state) override;
	virtual QVariantMap GetLayout() const override;
	// ~CEditor

private:
	CTypeReflectionRegistryWidget* m_pTypeReflectionRegistryWidget;
};