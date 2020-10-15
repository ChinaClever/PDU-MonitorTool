#include "home_workwid.h"
#include "ui_home_workwid.h"

Home_WorkWid::Home_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_WorkWid)
{
    ui->setupUi(this);

    initLayout();

    for(int i=0; i<2; ++i) {
        setInsertTextColor(QColor("red"));
        setInsertTextColor(QColor("black"));
        setInsertTextColor(QColor("green"));
    }
}

Home_WorkWid::~Home_WorkWid()
{
    delete ui;
}


void Home_WorkWid::initLayout()
{
    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff ); //垂直滚动条隐藏
    ui->textEdit->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );//水平滚动条隐藏

    QGridLayout *gridLayout = new QGridLayout(this->parentWidget());
    gridLayout->setContentsMargins(0, 7, 0, 0);
    gridLayout->addWidget(this);

    mSetDlg = new Home_SetDlg(this);
}

void Home_WorkWid::setInsertTextColor(const QColor &color)
{
    static int lzy = 0;
    ui->textEdit->moveCursor(QTextCursor::Start);
//    ui->textEdit->insertPlainText(QString::number(lzy++) + "  AAAAAAAAAAAAAAAAA\n");

    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(color);// 前景色(即字体色)设为color色
    QTextCursor cursor = ui->textEdit->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textEdit->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式

    ui->textEdit->insertPlainText(QString::number(lzy++) + " BBBBBBBBBBBBBBBBBBBBBB\n");
}

void Home_WorkWid::on_setBtn_clicked()
{
    mSetDlg->exec();
}
