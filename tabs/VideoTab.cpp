#include "VideoTab.h"

#include "camera/IPCamera.h"
#pragma comment(lib,"Control.lib")

VideoTab::VideoTab(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    video = new VideoView();
	QTimer* videoTimer = new QTimer(this);
    connect(videoTimer, SIGNAL(timeout()), video, SLOT(repaint()));
	videoTimer->setInterval(50);
	videoTimer->start();

    QPushButton *fixSceneButton = new QPushButton("Зафиксировать сцену");

    connect(fixSceneButton,SIGNAL(clicked()),SLOT(fixScene()));

    mainLayout = new QGridLayout();
	QGridLayout *externLayout=new QGridLayout();
	QVBoxLayout *videoLayout=new QVBoxLayout();

    videoScene = new QGraphicsScene(this);
    videoView = new QGraphicsView(videoScene);
    if(video->getCamera()->Enabled())
	{
        videoScene->addWidget(video);
		videoScene->setSceneRect(videoView->rect());
		videoLayout->addWidget(videoView);
        createFuzzyControls();
	}
	else
	{
        fixSceneButton->setEnabled(false);
		QLabel *noVideo=new QLabel();
		QPalette palette;
		palette.setBrush(noVideo->backgroundRole(),QBrush(Qt::black));
		palette.setColor(QPalette::WindowText,Qt::white);
		noVideo->setPalette(palette);
		noVideo->setAutoFillBackground(true);
        noVideo->setText("Видео недоступно");
		noVideo->setAlignment(Qt::AlignCenter);
        noVideo->resize(500,400);
        videoScene->addWidget(noVideo);
        videoScene->setSceneRect(videoView->rect());
        videoLayout->addWidget(videoView);
	}
	externLayout->addLayout(videoLayout,0,0);
	mainLayout->addLayout(externLayout,0,0,3,3);
    mainLayout->addWidget(fixSceneButton,0,3,1,1);

	setLayout(mainLayout);
}

void VideoTab::createFuzzyControls()
{
	fuzzyGrid = new FuzzyGrid(videoScene);
    QGroupBox *fuzzyControls = new QGroupBox("Нечеткая логика:");
	QGridLayout *fuzzyLayout = new QGridLayout();
    QCheckBox *showGridBox = new QCheckBox("Показывать сетку");
	connect(showGridBox, SIGNAL(stateChanged(int)), fuzzyGrid, SLOT(showGrid(int)));
	fuzzyLayout->addWidget(showGridBox, 0, 0, 1, 1);
    QLabel *gridSizeLabel = new QLabel("Размер сетки:");
	fuzzyLayout->addWidget(gridSizeLabel, 1, 0, 1, 1);
	QRadioButton *oneSize = new QRadioButton("1");
	connect(oneSize, SIGNAL(toggled(bool)), SLOT(radioToggled(bool)));
	QRadioButton *twoSize = new QRadioButton("2");
	connect(twoSize, SIGNAL(toggled(bool)), SLOT(radioToggled(bool)));
	QRadioButton *fourSize = new QRadioButton("4");
	connect(fourSize, SIGNAL(toggled(bool)), SLOT(radioToggled(bool)));
	oneSize->setChecked(true);
	fuzzyLayout->addWidget(oneSize, 2, 0, 1, 1);
	fuzzyLayout->addWidget(twoSize, 3, 0, 1, 1);
	fuzzyLayout->addWidget(fourSize, 4, 0, 1, 1);
//	QPushButton *calcButton = new QPushButton("Âûïîëíèòü ðàñ÷åò");
    QCheckBox *showFactorsBox = new QCheckBox("Показывать факторы");
//	connect(calcButton, SIGNAL(clicked()), fuzzyGrid, SLOT(doCalculations()));
	connect(showFactorsBox, SIGNAL(stateChanged(int)), fuzzyGrid, SLOT(showFactors(int)));
	fuzzyLayout->addWidget(showFactorsBox, 5, 0, 1, 1);
	
	fuzzyControls->setLayout(fuzzyLayout);
    mainLayout->addWidget(fuzzyControls, 1,3,1,1);

    QTimer* factorsTimer = new QTimer(this);
    connect(factorsTimer, SIGNAL(timeout()), SLOT(renewFactors()));
    factorsTimer->setInterval(1000);
    factorsTimer->start();
    //QTimer::singleShot(30000, this, SLOT(renewFactors()));
}

void VideoTab::radioToggled(bool checked)
{
	if(checked == false)
	{
		return;
	}
	int size = dynamic_cast<QRadioButton*>(sender())->text().toInt();
    fuzzyGrid->setGranulaSize(size);
}

void VideoTab::renewFactors()
{
    fuzzyGrid->doCalculations();
    if(fuzzyGrid->sceneFixed())
    {
        int granulaSize = fuzzyGrid->granulaSize();
        QSize gridSize = fuzzyGrid->gridSize();
        QVector<double>& fuzzyFactors = fuzzyGrid->fuzzyFactors();
        emit factorsChanged(granulaSize, gridSize, fuzzyFactors);
    }
}

void VideoTab::fixScene()
{
	QSound sound("Resources/snapshot.wav");
	sound.play();
    fuzzyGrid->fixStaticScene();
}

void VideoTab::paintEvent(QPaintEvent *ev)
{
    QSize dimensions = video->getCamera()->getVideoDimensions();
//    video->resize(dimensions);
    videoScene->setSceneRect(videoScene->itemsBoundingRect());
}

void VideoTab::keyPressEvent(QKeyEvent *ev)
{
	if(ev->key() == Qt::Key_Plus)
	{
		videoView->scale(1.2, 1.2);
		videoScene->setSceneRect(videoScene->itemsBoundingRect());
	}
	else if(ev->key() == Qt::Key_Minus)
	{
		videoView->scale(0.8, 0.8);
		videoScene->setSceneRect(videoScene->itemsBoundingRect());
	}
}

VideoTab::~VideoTab()
{
}
