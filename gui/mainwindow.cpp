#include "mainwindow.h"

#include <QAction>
#include <QColor>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QTextStream>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_pMainLayout(new QHBoxLayout),
      m_pMenuBar(new QMenuBar), m_pFileMenu(new QMenu(tr("&File"))),
      m_pChartView(new QtCharts::QChartView) {

  m_pOpenSimulationResult = new QAction(tr("&Open Simulation Result"));
  connect(m_pOpenSimulationResult, &QAction::triggered, this,
          &MainWindow::onOpenSimulationResult);

  m_pFileMenu->addAction(m_pOpenSimulationResult);
  m_pMenuBar->addMenu(m_pFileMenu);

  setMenuBar(m_pMenuBar);

  m_pMainLayout->addWidget(m_pChartView);
  QChart *pChart = m_pChartView->chart();
  //  pChart->createDefaultAxes();
  //  pChart->axes(Qt::Horizontal).first()->setTitleText("Simulation Time");
  //  pChart->axes(Qt::Vertical).first()->setTitleText("Signal Values");

  QWidget *m_pCentralWidget = new QWidget;
  m_pCentralWidget->setLayout(m_pMainLayout);

  setCentralWidget(m_pCentralWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::onOpenSimulationResult() {
  QString path = QFileDialog::getOpenFileName(
      this, tr("Open Simulation Results"), QDir::current().path());

  if (path.isEmpty()) {
    return;
  }

  SignalsMap mp = readSimulationResultsIntoMap(path);
  LineSeriesVec sv = converterSimulationResultsMapIntoLineSeries(mp);

  for (const auto &[name, series] : sv) {
    m_pChartView->chart()->addSeries(series);
  }

  m_pChartView->chart()->createDefaultAxes();
}

SignalsMap MainWindow::readSimulationResultsIntoMap(const QString &crPath) {
  QFile svFile(crPath);
  if (!svFile.open(QFile::ReadOnly)) {
    return SignalsMap();
  }

  SignalsMap mp;
  QTextStream svStream(&svFile);
  QString sigLine;
  while (svStream.readLineInto(&sigLine)) {
    sigLine = sigLine.trimmed();
    if (sigLine.isEmpty()) {
      continue;
    }

    QStringList stringSplitted = sigLine.split(" ");
    QString sigName = stringSplitted[0];
    mp[sigName];
    for (int sigIdx = 1; sigIdx + 1 < stringSplitted.size(); sigIdx += 2) {
      mp[sigName].push_back(SignalValue(stringSplitted[sigIdx].toUInt(),
                                        stringSplitted[sigIdx + 1].toUInt()));
    }
  }

  return mp;
}

LineSeriesVec MainWindow::converterSimulationResultsMapIntoLineSeries(
    const SignalsMap &crSigMap) {

  const qint64 height_offset = 1;
  const qint64 width_offset = 1;

  qint64 current_height = 0;
  qint64 current_width = 0;

  LineSeriesVec result;
  auto it = crSigMap.cbegin();
  for (; it != crSigMap.cend(); ++it) {
    current_width = 0;
    current_height += height_offset;

    QString name = it.key();
    QLineSeries *pSeries = new QLineSeries;

    SignalValues values = *it;
    if (values[0].first) {
      pSeries->append(current_width, current_height + height_offset);

      current_width += width_offset;
      pSeries->append(current_width, current_height + height_offset);
    } else {
      pSeries->append(current_width, current_height);

      current_width += width_offset;
      pSeries->append(current_width, current_height);
    }

    for (int i = 1; i + 1 < values.size(); ++i) {
      if (values[i].first) {
        if (!values[i - 1].first) {
          pSeries->append(current_width, current_height);
          pSeries->append(current_width, current_height + height_offset);
        }

        current_width += width_offset;
        pSeries->append(current_width, current_height + height_offset);
      } else {
        if (values[i - 1].first) {
          pSeries->append(current_width, current_height);
          //          pSeries->append(current_width, current_height +
          //          height_offset);
        }

        current_width += width_offset;
        pSeries->append(current_width, current_height);
      }
    }

    result.push_back(QPair<QString, QLineSeries *>(name, pSeries));
    current_height += 1;
  }

  return result;
}
