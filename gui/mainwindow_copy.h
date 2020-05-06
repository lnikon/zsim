#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// ZSim includes
#include <logic_value_defs.hpp>
#include <net.hpp>

// Qt includes
#include <QAbstractTableModel>
#include <QListView>
#include <QMainWindow>
#include <QPair>
#include <QTableView>
#include <QVector>

// Qt widgets
class QLabel;
class QPushButton;
class QMenu;
class QColor;
class QAction;
class QToolBar;
class QMenuBar;
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFormLayout;
class QAbstractItemModel;
class QModelIndex;

using TimeValueType = quint64;
using SignalValueType = logic_value_type_ns::logic_value_t;
using SignalTimePoint = QPair<TimeValueType, SignalValueType>;
using SignalTimeSeries = QVector<SignalTimePoint>;

struct Signal {
  QString m_name;
  QColor m_color;
  SignalTimeSeries m_data;
};
using Signals = QVector<Signal>;

// This is a main model for all widgets
class SignalListModel : public QAbstractTableModel {
  Q_OBJECT
public:
  explicit SignalListModel(QObject *parent = Q_NULLPTR);
  int columnCount(const QModelIndex &parent) const;
  int rowCount(const QModelIndex &parent) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex());
  void addData(const Signal &signal);

private:
  Signals m_signals;
};

// Represents each signal name and associated color
class SignalInformationBar {};

// Paints colored digital waveform
class SignalListViewNamed : public QListView {
  Q_OBJECT
};

// Lists signal
class SignalListViewPainted : public QTableView {
  Q_OBJECT
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void onOpenSimulationResult();

private:
  QHBoxLayout *m_pMainLayout;
  QMenuBar *m_pMenuBar;
  QMenu *m_pFileMenu;
  QAction *m_pOpenSimulationResult;
  QToolBar *m_pToolBar;

  SignalListModel *m_pSignalModel;
  SignalInformationBar *m_pInformationBar;
  SignalListViewNamed *m_pSignalListViewNamed;
  SignalListViewPainted *m_pSignalsListPainted;
};
#endif // MAINWINDOW_H
