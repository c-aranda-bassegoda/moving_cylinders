#include <QApplication>
#include <QSurfaceFormat>

#include "mainwindow.h"

/**
 * @brief main Entry point of the application. Do not modify this file, as it
 * will not be considered in your Themis submission.
 * @param argc Argument count.
 * @param argv Arguments.
 * @return Exit code.
 */
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Request OpenGL 4.1 Core
  QSurfaceFormat glFormat;
  glFormat.setProfile(QSurfaceFormat::CoreProfile);
  glFormat.setVersion(4, 1);
  glFormat.setOption(QSurfaceFormat::DebugContext);

  // Some platforms need to explicitly set the depth buffer size (24 bits)
  glFormat.setDepthBufferSize(24);

  QSurfaceFormat::setDefaultFormat(glFormat);

  MainWindow w;
  w.show();

  return a.exec();
}
