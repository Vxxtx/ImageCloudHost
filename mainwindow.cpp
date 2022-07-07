#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <filesystem>
#include "QListWidgetItem"
#include "QMessageBox"
#include <thread>
#include <iostream>

namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_refreshBtn_clicked()
{
    folders_amount = 0;
    files_amount = 0;

    std::string path_s = ui->pathEdit->text().toStdString();

    Folders.clear();
     ui->folderList->clear();

    Folder base_folder = Folder(path_s);
    Folders.push_back(base_folder);

    get_subfolders(base_folder);
    ui->folders_files_amount->setText(QString("Found %1 folders containing %2 images").arg(folders_amount).arg(files_amount));
}

void MainWindow::get_subfolders(Folder& folder)
{
    for (const auto& entry : fs::directory_iterator(folder.path)) {
         if (entry.is_directory()) {
            Folder new_folder = Folder(entry.path().string());
            Folders.push_back(new_folder);

            ++folders_amount;
            try
            {
                get_subfolders(new_folder);
            }
            catch (const fs::filesystem_error& e ) {} // Exception when å,ä,ö appears, TODO: figure this out
            continue;
        }

        if (entry.is_regular_file()) {
            std::string extension_string = fs::path(entry.path().extension()).string();

            if (extension_string == ".png" || extension_string == ".jpg" || extension_string == ".bmp") {
                folder.files.push_back(entry.path().string());

                QListWidgetItem* new_item = new QListWidgetItem();
                new_item->setText(QString::fromStdString(entry.path().string()));
                ui->folderList->addItem(new_item);
                ++files_amount;
            }
        }
    }
}
