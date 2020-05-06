#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// ZSim includes
//#include <logic_value_defs.hpp>
//#include <net.hpp>

// Qt includes
#include <QAbstractTableModel>
#include <QListView>
#include <QMainWindow>
#include <QMap>
#include <QPair>
#include <QTableView>
#include <QVector>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

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

using namespace QtCharts;

using SignalValue = QPair<quint64, quint64>;
using SignalValues = QVector<SignalValue>;
using SignalsMap = QMap<QString, SignalValues>;

using LineSeriesVec = QVector<QPair<QString, QLineSeries *>>;

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
  QtCharts::QChartView *m_pChartView;

  SignalsMap readSimulationResultsIntoMap(const QString &crPath);
  LineSeriesVec
  converterSimulationResultsMapIntoLineSeries(const SignalsMap &crSigMap);
};
#endif // MAINWINDOW_H
