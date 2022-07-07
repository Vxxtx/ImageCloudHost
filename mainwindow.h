#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Folder {
    std::string path;
   // std::vector<Folder> subfolders {};
    std::vector<std::string> files {};

    Folder(std::string in_folder_name)
        : path(in_folder_name)
    {

    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_refreshBtn_clicked();

    void get_subfolders(Folder& path);

private:
    Ui::MainWindow *ui;
    std::vector<Folder> Folders {};

    int folders_amount {0};
    int files_amount {0};

};
#endif // MAINWINDOW_H
