#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QDockWidget>

#include <mainwindow.h>
#include <genericwindowfactory.h>
#include <gamewindow.h>
#include <navigationdisplay.h>
#include <gamedatacontainer.h>
#include <highlighter.h>
#include <defaultvalues.h>
#include <highlightsettings.h>
#include <highlighterthread.h>

class MainWindow;
class GameWindow;
class GenericWindowFactory;
class NavigationDisplay;
class GameDataContainer;
class ClientSettings;
class Highlighter;
class HighlighterThread;

typedef QList<QString> DirectionsList;

class WindowManager : public QObject {
    Q_OBJECT

public:
    WindowManager(QObject *parent = 0);
    ~WindowManager();

    void loadWindows();
    QPlainTextEdit* getGameWindow();
    void paintNavigationDisplay();
    void scriptRunning(bool);
    void updateWindowStyle();
    void initWindowHighlighters();
    void updateWindowColors();
    void setGameWindowFont(QFont);
    void setGameWindowFontColor(QColor);    
    void setDockFontColor(QColor);
    void setDockBackground(QColor);
    void setDockFont(QFont font);
    void copyDock();
    void saveArrivals();
    void reloadSettings();
    void reloadHighlighterSettings();

    QDockWidget* getRoomWindow();
    QDockWidget* getArrivalsWindow();
    QDockWidget* getThoughtsWindow();
    QDockWidget* getExpWindow();
    QDockWidget* getDeathsWindow();
    QDockWidget* getConversationsWindow();

    bool thoughtsVisible;
    bool deathsVisible;
    bool arrivalsVisible;
    bool conversationsVisible;
    bool writePrompt;

public slots:
    void updateConversationsWindow(QString);
    void writeGameText(QByteArray, bool);
    void writeGameWindow(QByteArray);
    void writeScriptText(QByteArray);
    void updateNavigationDisplay(DirectionsList);
    void updateRoomWindowTitle(QString);
    void updateExpWindow();
    void updateRoomWindow();
    void updateDeathsWindow(QString);
    void updateThoughtsWindow(QString);
    void updateArrivalsWindow(QString);

private slots:
    void thoughtsVisibility(bool);    
    void deathsVisibility(bool);
    void arrivalsVisibility(bool);
    void conversationsVisibility(bool);

private:
    GenericWindowFactory* genericWindowFactory;
    MainWindow* mainWindow;
    QPlainTextEdit* gameWindow;
    NavigationDisplay *navigationDisplay;
    GameDataContainer* gameDataContainer;
    ClientSettings* clientSettings;
    Highlighter* highlighter;
    HighlightSettings* settings;
    GeneralSettings* generalSettings;

    QDockWidget* roomWindow;
    QDockWidget* arrivalsWindow;
    QDockWidget* thoughtsWindow;
    QDockWidget* expWindow;
    QDockWidget* deathsWindow;
    QDockWidget* conversationsWindow;
    QList<QDockWidget*> dockWindows;

    HighlighterThread* gameWindowHighlighter;
    HighlighterThread* roomHighlighter;
    HighlighterThread* expHighlighter;
    HighlighterThread* arrivalsHighlighter;
    HighlighterThread* thoughtsHighlighter;
    HighlighterThread* deathsHighlighter;
    HighlighterThread* conversationsHighlighter;
    QList<HighlighterThread*> highlighters;

    QString textColor(QString, QString);
    void setVisibilityIndicator(QDockWidget*, bool, QString);

signals:
    void updateGameWindowSettings();
    void updateRoomSettings();
    void updateExpSettings();
    void updateArrivalsSettings();
    void updateThoughtsSettings();
    void updateDeathsSettings();
    void updateConversationsSettings();
};

#endif // WINDOWMANAGER_H
