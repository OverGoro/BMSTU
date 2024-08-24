#include <cmath>
#include <QDebug>

#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Exceptions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();

    _facade = std::make_shared<Facade>(Facade());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScene()
{
    _scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    auto cont = ui->graphicsView->contentsRect();
    _scene->setSceneRect(0, 0, cont.width(), cont.height());
    _camInd = 1;

    auto solution(new DrawerSolution<QtFactory, QGraphicsScene>());
    _drawer = solution->createDrawer(_scene);
}

void MainWindow::updateScene()
{
    _drawer->initializeZBuffer(this->width(), this->height());
    ClearScene clear_cmd(_drawer);
    _facade->execute(clear_cmd);

    DrawScene draw_cmd(_drawer);
    try
    {
        _facade->execute(draw_cmd);
    }
    catch(CameraNotSetException e)
    {
        qDebug() << e.what();
    }
}

void MainWindow::checkCamExist()
{
    if (!_cameras.size())
    {
        std::string msg = "No camera found.";
        throw CameraException(msg);
    }
}

void MainWindow::checkModelsExist()
{
    if (!_models.size())
    {
        std::string msg = "No models found.";
        throw ModelException(msg);
    }
}

void MainWindow::checkCamDelete()
{
    if (_cameras.size() <= 1 && _models.size())
    {
        std::string msg = "Can not delete the last camera with the loaded models";
        throw CameraException(msg);
    }
}

void MainWindow::on_addCameraBtn_clicked()
{

    auto id = std::make_shared<size_t>(ui->cameraCB->count());



    double half_width = ui->graphicsView->width() / 2;

    // Расчет screen_dist для x_fov = 60 градусов
    double screen_dist = half_width / tan(qDegreesToRadians(60) / 2);
    qDebug() << screen_dist;
    Point location(0, 0, -screen_dist * 1.5);
    Point direction(0, 0, 100);
    Point up(0, 100, -screen_dist * 1.5);

    double x_fov = atan(ui->graphicsView->width() / 2 / screen_dist) * 2;
    double y_fov = atan(ui->graphicsView->height() / 2 / screen_dist) * 2;
    AddCamera addCMD(location, direction, up, x_fov, y_fov, screen_dist);

    _facade->execute(addCMD);
    _cameras.push_back(*id);

    updateScene();

    auto cam = ui->cameraCB;

    std::string camName = std::string("cam") + std::to_string(_camInd++);
    cam->addItem(QString(camName.data()));

    ui->cameraCB->setCurrentIndex(ui->cameraCB->count() - 1);
}

void MainWindow::on_loadModelBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Добавьте камеру!");
        return;
    }

    auto file = QFileDialog::getOpenFileName(nullptr, "Загрузка модели", "../lab_03/data");

    if (file.isEmpty())
        return;

    std::size_t id = _models.size();
    std::string fileName = file.toStdString();
    LoadModel cmd(fileName);
    // _facade->execute(cmd);

    try
    {
        _facade->execute(cmd);
    }
    catch (const BaseException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при загрузке файла!");
        return;
    }

    _models.push_back(id);
    updateScene();
    ui->modelsCB->addItem(QFileInfo(file.toUtf8().data()).fileName());
    ui->modelsCB->setCurrentIndex(ui->modelsCB->count() - 1);
}

void MainWindow::on_deleteModelBtn_clicked()
{
    try
    {
        checkModelsExist();
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    std::size_t id = _models.at(ui->modelsCB->currentIndex());
    DeleteModel cmd(id);
    _facade->execute(cmd);

    _models.erase(_models.begin() + ui->modelsCB->currentIndex());
    ui->modelsCB->removeItem(ui->modelsCB->currentIndex());

    updateScene();
}

void MainWindow::on_deleteModelsBtn_clicked()
{
    try
    {
        checkModelsExist();
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    for (int i = ui->modelsCB->count() - 1; i >= 0; --i)
    {
        std::size_t id = _models.at(i);
        DeleteModel cmd(id);
        _facade->execute(cmd);

        _models.erase(_models.begin() + i);
        ui->modelsCB->removeItem(i);
    }

    updateScene();
}


void MainWindow::on_cameraCB_currentIndexChanged(int index)
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        return;
    }

    std::size_t id = _cameras.at(index);
    SetCamera cmd(id);
    _facade->execute(cmd);

    updateScene();
}


void MainWindow::on_deleteCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }

    try
    {
        checkCamDelete();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Это последняя камера! Для удаления удалите модели!");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    DeleteCamera cmd(id);
    _facade->execute(cmd);

    _cameras.erase(_cameras.begin() + ui->cameraCB->currentIndex());
    ui->cameraCB->removeItem(ui->cameraCB->currentIndex());

    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        return;
    }

    ui->cameraCB->setCurrentIndex(ui->cameraCB->count() - 1);

    updateScene();
}

void MainWindow::on_upBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    MoveCamera cmd(0, 10, 0, id);

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_rigthBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    MoveCamera cmd(-10, 0, 0, id);

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_downBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    MoveCamera cmd(0, -10, 0, id);

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_leftBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    MoveCamera cmd(10, 0, 0, id);

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_moveBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    MoveModel cmd(
            ui->dxDSB->value(),
            ui->dyDSB->value(),
            ui->dzDSB->value(),
            _models.at(ui->modelsCB->currentIndex()));

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_moveAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    MoveModels cmd(
            ui->dxDSB->value(),
            ui->dyDSB->value(),
            ui->dzDSB->value());

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_scaleBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    ScaleModel cmd(
            ui->kxDSB->value(),
            ui->kyDSB->value(),
            ui->kzDSB->value(),
            _models.at(ui->modelsCB->currentIndex()));

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_scaleAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    ScaleModels cmd(
            ui->kxDSB->value(),
            ui->kyDSB->value(),
            ui->kzDSB->value());

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_rotateBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    RotateModel cmd(
            ui->oxDSB->value() * M_PI / 180,
            ui->oyDSB->value() * M_PI / 180,
            ui->ozDSB->value() * M_PI / 180,
            _models.at(ui->modelsCB->currentIndex()));

    _facade->execute(cmd);
    updateScene();
}

void MainWindow::on_rotateAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    RotateModels cmd(
            ui->oxDSB->value() * M_PI / 180,
            ui->oyDSB->value() * M_PI / 180,
            ui->ozDSB->value() * M_PI / 180);

    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_undoLastAction_clicked()
{

}


void MainWindow::on_rotUpBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    RotateCamera cmd(qDegreesToRadians(5), 0, 0, id);

    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_rotLeftBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    RotateCamera cmd(0, -qDegreesToRadians(5), 0, id);

    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_rotRightBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    RotateCamera cmd(0, qDegreesToRadians(5), 0, id);

    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_rotDownBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    RotateCamera cmd(-qDegreesToRadians(5), 0, 0, id);

    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_pushButton_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Добавьте камеру!");
        return;
    }

    auto file = QFileDialog::getOpenFileName(nullptr, "Загрузка модели", "../lab_03/data");

    if (file.isEmpty())
        return;

    std::size_t id = _models.size();
    std::string fileName = file.toStdString();
    LoadModel cmd(fileName);
    // _facade->execute(cmd);

    try
    {
        _facade->execute(cmd);
    }
    catch (const BaseException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при загрузке файла!");
        return;
    }

    _models.push_back(id);
    updateScene();
    ui->modelsCB->addItem(QFileInfo(file.toUtf8().data()).fileName());
    ui->modelsCB->setCurrentIndex(ui->modelsCB->count() - 1);
}

