#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verylong.h"

VeryLong num_first;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_plus_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    QString button_text = button->text();

    QString current_text = ui->result_show->text();

    QString new_text = current_text + button_text;

    // Перетворити новий текст у рядок
    string new_label_str = new_text.toStdString();

    // Створити об'єкт VeryLong з новим рядком
    VeryLong all_numbers(new_label_str);

    // Вивести новий текст на екран
    ui->result_show->setText(new_text);
}

void MainWindow::operations()
{
    string all_numbers;
    QString new_label;
    if(ui->result_show->text().contains('-')){
        all_numbers = (ui->result_show->text()).toStdString();
        all_numbers.erase(0, 1);

    } else {

      all_numbers= (ui->result_show->text()).toStdString();
      all_numbers = "-" + all_numbers;
    }

      new_label = QString::fromStdString(all_numbers);
      ui->result_show->setText(new_label);
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();
    num_first = ui->result_show->text().toStdString();
    ui->result_show->setText("");
    button->setChecked(true);
}


void MainWindow::on_pushButton_del_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->result_show->setText("");
}


void MainWindow::on_pushButton_equal_clicked()
{
    VeryLong label_number;
    QString inputText = ui->result_show->text();
    VeryLong num_second(inputText.toStdString());
    QString new_label;

    if(ui->pushButton_plus->isChecked()){

      label_number = num_first.operator+(num_second);
      ui->pushButton_plus->setChecked(false);

    } else if(ui->pushButton_minus->isChecked()){

      label_number = num_first - num_second;
      ui->pushButton_minus->setChecked(false);


    }else if(ui->pushButton_divide->isChecked()){

      if(num_second == VeryLong("0")){
          ui->result_show->setText("Division by zero");
          return;
      } else {
      label_number = num_first / num_second;
      ui->pushButton_divide->setChecked(false);
      }
    }else if(ui->pushButton_mult->isChecked()){

      label_number = num_first * num_second;
      ui->pushButton_mult->setChecked(false);

    }
    new_label = QString::fromStdString(label_number.toString());
    ui->result_show->setText(new_label);
}

