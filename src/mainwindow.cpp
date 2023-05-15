#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(AppContext *ctx, QWidget *parent) :
    QMainWindow(parent),
    m_ctx(ctx),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->screenDpiRef = 128;
  this->screenGeo = QApplication::primaryScreen()->availableGeometry();
  this->screenRect = QGuiApplication::primaryScreen()->geometry();
  this->screenDpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
  this->screenDpiPhysical = QGuiApplication::primaryScreen()->physicalDotsPerInch();
  this->screenRatio = this->screenDpiPhysical / this->screenDpiRef;
  qDebug() << QString("%1x%2 (%3 DPI)").arg(
      this->screenRect.width()).arg(this->screenRect.height()).arg(this->screenDpi);

  this->show();

  connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onOpenAboutWindow);
  connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onQuitApplication);

  // example get config value:
  auto test = config()->get(ConfigKeys::Test).toString();
  qDebug() << "config value: " << test;

  // example set config value
  // config()->set(ConfigKeys::Test, "test2");

  this->createQml();
}

void MainWindow::onOpenAboutWindow() {
  m_about = new About(m_ctx, this);
  m_about->show();
}

void MainWindow::onQuitApplication() {
  this->close();
}

void MainWindow::closeEvent(QCloseEvent *event) {
  //event->ignore();
  QApplication::quit();
}

void MainWindow::createQml() {
  if(m_quickWidget != nullptr) return;
  m_quickWidget = new QQuickWidget(this);

  auto *qctx = m_quickWidget->rootContext();
  qctx->setContextProperty("cfg", config());
  qctx->setContextProperty("ctx", m_ctx);
  qctx->setContextProperty("mainWindow", this);

  m_quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
  m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

  // example signal from QML to C++
  connect((QObject*)m_quickWidget->rootObject(), SIGNAL(onExample(int)), this, SLOT(onExample(int)));

  ui->centralWidget->layout()->addWidget(m_quickWidget);
}

void MainWindow::destroyQml() {
  if(m_quickWidget == nullptr) return;
  m_quickWidget->disconnect();
  m_quickWidget->deleteLater();
  m_quickWidget = nullptr;
}

void MainWindow::onExample(int number) {
  qDebug() << "clicked: " + number;
}

MainWindow::~MainWindow() {
  delete ui;
}

