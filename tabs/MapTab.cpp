#include "MapTab.h"
#include <QtGui>

MapTab::MapTab(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    sceneView = new QGraphicsView();
    sceneView->setScene(scene);
    scene->setSceneRect(sceneView->rect());
    mainLayout = new QGridLayout();

    mainLayout->addWidget(sceneView,0,0,8,4);
    ipEdit = new QLineEdit("192.168.0.2");
    portEdit = new QLineEdit("2005");
    QHBoxLayout * netEditLayout = new QHBoxLayout();
    netEditLayout->addWidget(new QLabel("IP:"));
    netEditLayout->addWidget(ipEdit, 3);
    netEditLayout->addWidget(new QLabel("Порт:"));
    netEditLayout->addWidget(portEdit, 1);
//    mainLayout->addLayout(netEditLayout, 0,4,1,1);

    sendButton=new QPushButton("Начать передачу");
    connect(sendButton,SIGNAL(clicked()),SLOT(sendToKate()));
    mainLayout->addWidget(sendButton,1,4,1,1);

    QPushButton *findButton=new QPushButton("Сохранить в файл...");
    connect(findButton,SIGNAL(clicked()),SLOT(saveMapToFile()));
    mainLayout->addWidget(findButton,2,4,1,1);

    networkLog = new QTextEdit();
    networkLog->setReadOnly(true);
    mainLayout->addWidget(networkLog,3,4,1,1);

    setLayout(mainLayout);
}

void MapTab::saveMapToFile()
{
//    const QRgb OBSTACLE_COLOR = qRgb(255, 0, 0),
//               ROBOT_COLOR	  = qRgb(0, 255, 0);
//    const char FREE_AREA_SYM	  = '0',
//               ROBOT_AREA_SYM	  = '2',
//               OBSTACLE_AREA_SYM  = '1';
    QString fileName = QFileDialog::getSaveFileName(this, "Введите имя файла:", QDir::currentPath(), "*.txt");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream mapFileStream(&file);
//    mapFileStream << currentMap.image.width() << " " << currentMap.image.height() << "\n";
//    for(int i = 0; i<currentMap.image.height(); i++)
//    {
//        for(int j = 0; j<currentMap.image.width(); j++)
//        {
//            if(currentMap.image.pixel(j, i) == OBSTACLE_COLOR)
//                mapFileStream << OBSTACLE_AREA_SYM;
//            else if(currentMap.image.pixel(j, i) == ROBOT_COLOR)
//                mapFileStream << ROBOT_AREA_SYM;
//            else
//                mapFileStream << FREE_AREA_SYM;
//        }
//        mapFileStream << "\n";
//    }
    file.close();
}
void MapTab::sendToKate()
{
    sendButton->setEnabled(false);
    QString ipAddress = ipEdit->text();
    int port = portEdit->text().toInt();
    kateSocket = new QTcpSocket(this);
    connect(kateSocket, SIGNAL(connected()), SLOT(connectedToKate()));
    connect(kateSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(errorFromKate(QAbstractSocket::SocketError)));
    networkLog->append("Подключение к " + ipAddress + ":" + QString().number(port) + "...");
    kateSocket->connectToHost(ipAddress, port);
}
void MapTab::connectedToKate()
{
    networkLog->append("Подключение успешно");
    sendButton->setText("Отключить");
//    QString sendString = "";
//    const QRgb OBSTACLE_COLOR = qRgb(255, 0, 0),
//               ROBOT_COLOR	  = qRgb(0, 255, 0);
//    const char FREE_AREA_SYM	  = '0',
//               ROBOT_AREA_SYM	  = '2',
//               OBSTACLE_AREA_SYM  = '1';
//    sendString += QString::number(currentMap.image.width()) + " " + QString::number(currentMap.image.height()) + " ";
//    for(int i = 0; i<currentMap.image.height(); i++)
//    {
//        for(int j = 0; j<currentMap.image.width(); j++)
//        {
//            if(currentMap.image.pixel(j, i) == OBSTACLE_COLOR)
//                sendString += OBSTACLE_AREA_SYM;
//            else if(currentMap.image.pixel(j, i) == ROBOT_COLOR)
//                sendString += ROBOT_AREA_SYM;
//            else
//                sendString += FREE_AREA_SYM;
//        }
//    }
//    sendString += "\n";
//    QTextStream out(&sendString, QIODevice::WriteOnly);
//    QByteArray byteArray = sendString.toAscii();
//    const char *sendCString = byteArray.data();
//    kateSocket->write(sendCString);
//    kateSocket->flush();
//    kateSocket->close();
}
void MapTab::errorFromKate(QAbstractSocket::SocketError error)
{
    networkLog->append("Ошибка подключения");
    sendButton->setEnabled(true);
}
void MapTab::resizeEvent(QResizeEvent *ev)
{
    scene->setSceneRect(sceneView->rect());
    QWidget::resizeEvent(ev);
}

void MapTab::wheelEvent(QWheelEvent *ev)
{
    double scaleStep = ev->delta() / 120;
    sceneView->scale(scaleStep, scaleStep);
}

void MapTab::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Plus)
    {
        sceneView->scale(1.2, 1.2);
        scene->setSceneRect(scene->itemsBoundingRect());
    }
    else if(ev->key() == Qt::Key_Minus)
    {
        sceneView->scale(0.8, 0.8);
        scene->setSceneRect(scene->itemsBoundingRect());
    }
}
MapTab::~MapTab()
{
}

void MapTab::renewMap(int size, QSize gridSize, QVector<double> &factors)
{
    scene->clear();
    for(int i = 0; i < gridSize.width(); i++)
    {
        for(int j = 0; j < gridSize.height(); j++)
        {
            QGraphicsRectItem *item = new QGraphicsRectItem();
            item->setRect(i * size, j * size, size, size);
            int brightness = 255 - factors[i + j] * 255;
            if(brightness < 0)
            {
                brightness = 0;
            }
            item->setBrush(QBrush(QColor(255, brightness, brightness)));
            scene->addItem(item);
        }
    }
}
