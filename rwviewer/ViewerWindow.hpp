#ifndef _VIEWERWINDOW_HPP_
#define _VIEWERWINDOW_HPP_
#include <core/Logger.hpp>
#include <engine/GameData.hpp>
#include <engine/GameWorld.hpp>

// Prevent Qt from conflicting with glLoadGen on macOS
#include "OpenGLCompat.h"

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QOpenGLContext>
#include <QOffscreenSurface>

#include <memory>

class ViewerWidget;
class ViewerInterface;
class GameRenderer;

class ViewerWindow : public QMainWindow {
    Q_OBJECT
    QOpenGLContext* context_;
    QOffscreenSurface* hiddenSurface;
    QTabWidget* views;

    Logger engineLog;

    std::unique_ptr<GameData> gameData;
    std::unique_ptr<GameWorld> gameWorld;
    std::unique_ptr<GameRenderer> renderer;

public:
    ViewerWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    ~ViewerWindow();

    virtual void showEvent(QShowEvent*);
    virtual void closeEvent(QCloseEvent*);

    ViewerWidget* createViewer();

public slots:
    void loadGame();

    void loadGame(const QString& path);

signals:
    void gameLoaded(GameWorld*, GameRenderer*);

private slots:
    void openRecent();
    void showObjectModel(uint16_t object);

private:
    QList<QAction*> recentGames;
    QAction* recentSep;
    void updateRecentGames();

    void createMenus();
    bool setupEngine();
    void createDefaultViews();

    bool makeCurrent();
};

#endif
