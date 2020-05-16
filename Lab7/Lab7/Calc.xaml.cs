using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace Lab7
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Calc : Page
    {
        Operations calc = new Operations();
        public Calc()
        {
            this.InitializeComponent();
        }
        private void HamburgerButton_Click_1(object sender, RoutedEventArgs e)
        {
            Split1.IsPaneOpen = !Split1.IsPaneOpen;
        }
        private void MenuButton1_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(MainPage));
        }
        private void check_length()     //      функция проверки числа
        {
            try
            {

                if (double.Parse(IOtextBox.Text) >= 4000000 || double.Parse(IOtextBox.Text) <= -2000000)   //сравнение числа с границами
                {
                    IOtextBox.Text = IOtextBox.Text.Remove(IOtextBox.Text.Length - 1, 1);      //удаление последней добавленной цифры
                }
            }
            catch (System.FormatException e)
            {

                calc.tmp = 0;
                IOtextBox.Text = "";
                
                calc.op_num = -1;
                calc.prev_op = -1;
            }
        }
        private void num_0_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 0;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_1_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 1;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_2_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 2;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_3_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 3;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_4_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 4;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_5_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 5;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_6_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 6;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_7_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 7;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_8_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 8;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void num_9_Click(object sender, RoutedEventArgs e)
        {
            IOtextBox.Text = IOtextBox.Text + 9;      //добавление в текстбокс цифры
            check_length();     //вызов функции проверки числа
        }

        private void cos_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")        //проверка на пустой текстбокс
            {
                if (calc.op_num == -1)
                    calc.tmp = double.Parse(IOtextBox.Text);             //добавление числа во временную переменную
                else
                    calc.calculate(IOtextBox.Text);
                calc.cos();     //вызов функции расчета косинуса
                calc.op_num = 5;    //метка действия
                IOtextBox.Text = calc.tmp.ToString("g3");        //вывод результата в текстбокс (с форматированием)
            }
        }

        private void add_Click(object sender, RoutedEventArgs e)
        {
            if (calc.op_num == -1)      //Проверка метки операции
                calc.op_num = 1;        //(в случае, если действий в очереди нет)
            calc.calculate(IOtextBox.Text);      //вызов функции расчета
            IOtextBox.Text = String.Empty; ;       //очистка тестбокса
            calc.op_num = 1;        //установка метки операции
            Historylabel.Text = calc.tmp.ToString("g3") + "+";        //установка метки истории выполнения
        }

        private void sub_Click(object sender, RoutedEventArgs e)
        {
            if (calc.op_num == -1)      //Проверка метки операции
                calc.op_num = 2;         //(в случае, если действий в очереди нет)
            calc.calculate(IOtextBox.Text);      //вызов функции расчета
            IOtextBox.Text = String.Empty; ;       //очистка тестбокса
            calc.op_num = 2;        //установка метки операции
            Historylabel.Text = calc.tmp.ToString("g3") + "-";        //установка метки истории выполнения
        }

        private void fin_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text == "0" && calc.op_num == 4)       //проверка условия
            {

                Historylabel.Text = "";       //очистка метки
                IOtextBox.Text = "";     //очистка тестбокса
                errorLabel.Text = "Деление на 0 невозможно";        //вывод уведомления об ошибке
                calc.tmp = 0;       //очистка временной переменной 
                calc.op_num = -1;       //сброс метки действия
                calc.prev_op = -1;      //сброс метки предыдущего действия
            }
            else
            {
                calc.calculate(IOtextBox.Text);      //вызов функции расчета
                IOtextBox.Text = calc.tmp.ToString("g3");       //форматированный вывод результата
                Historylabel.Text = "";       //очистка метки
                calc.tmp = 0;         //очистка временной переменной 
                calc.prev_op = -1;      //сброс метки предыдущего действия
            }

        }

        private void mul_Click(object sender, RoutedEventArgs e)
        {
            if (calc.op_num == -1)      //Проверка метки операции
                calc.op_num = 3;         //(в случае, если действий в очереди нет)
            calc.calculate(IOtextBox.Text);      //вызов функции расчета
            //IOtextBox.Text = calc.tmp.ToString("g3");       //форматированный вывод результата
            IOtextBox.Text = String.Empty;       //очистка тестбокса
            calc.op_num = 3;        //установка метки операции
            Historylabel.Text = calc.tmp.ToString("g3") + "×";        //установка метки истории выполнения
        }

        private void div_Click(object sender, RoutedEventArgs e)
        {
            if (calc.op_num == -1)      //Проверка метки операции
                calc.op_num = 4;         //(в случае, если действий в очереди нет)
            if (IOtextBox.Text == "0")
            {

                Historylabel.Text = "";       //очистка метки
                IOtextBox.Text = "";     //очистка тестбокса
                errorLabel.Text = "Деление на 0 невозможно";        //вывод уведомления об ошибке
                calc.tmp = 0;       //очистка временной переменной 
                calc.op_num = -1;       //сброс меткидействия
                calc.prev_op = -1;      //сброс метки предыдущего действия
            }
            else
            {
                calc.calculate(IOtextBox.Text);      //вызов функции расчета
                IOtextBox.Text = calc.tmp.ToString("g3");       //форматированный вывод результата
                IOtextBox.Text = String.Empty;       //очистка тестбокса
                calc.op_num = 4;        //установка метки операции
                Historylabel.Text = calc.tmp.ToString("g3") + "÷";        //установка метки истории выполнения
            }
        }

        private void clear_Click(object sender, RoutedEventArgs e)
        {
            calc.tmp = 0;       //очистка временной переменной
            calc.op_num = -1;       //установка метки операции
            calc.prev_op = -1;      //установка метки операции
            Historylabel.Text = "";       //очистка метки
            IOtextBox.Text = "";     //очистка тестбокса
            errorLabel.Text = "";       //очистка метки
        }

        private void back_Click(object sender, RoutedEventArgs e)
        {
            int length = IOtextBox.Text.Length - 1;     //задание длины измененной строки
            string tmp_txt = IOtextBox.Text;        //копирование строки во временную переменную
            IOtextBox.Text = String.Empty;     //очистка тестбокса

            for (int i = 0; i < length; i++)     //цикл вывода цифр числа
            {
                IOtextBox.Text = IOtextBox.Text + tmp_txt[i];       //форматированный вывод результата
                if (IOtextBox.Text[IOtextBox.Text.Length - 1] == '+' || IOtextBox.Text[IOtextBox.Text.Length - 1] == '-')
                {
                    calc.tmp = 0;
                    IOtextBox.Text = "";
                    Historylabel.Text = "";
                    errorLabel.Text = "Ошибка ввода";
                    calc.op_num = -1;
                    calc.prev_op = -1;
                    break;
                }
            }
            if (IOtextBox.Text == "")
            {
                Historylabel.Text = "";
                calc.tmp = 0;
                calc.op_num = -1;
                calc.prev_op = -1;
            }
        }

        private void divx_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")       //проверка на пустой текстбокс
            {
                if (IOtextBox.Text == "0")      //проверка наличия нуля в текстбоксе
                {

                    Historylabel.Text = "";       //очистка метки
                    IOtextBox.Text = "";     //очистка тестбокса
                    
                    errorLabel.Text = "Деление на 0 невозможно";        //вывод уведомления об ошибке
                    calc.tmp = 0;          //очистка временной переменной 
                    calc.op_num = -1;       //установка метки операции
                    calc.prev_op = -1;      //установка метки операции
                }
                else
                {
                    if (calc.op_num == -1)
                        calc.tmp = double.Parse(IOtextBox.Text);        //помещение числа из тестбокса во временную переменну
                    else
                        calc.calculate(IOtextBox.Text);
                    calc.divx();        //вызов функции расчета деления на х
                    calc.op_num = 6;        //установка метки операции
                    Historylabel.Text = "";

                    IOtextBox.Text = calc.tmp.ToString("g3");       //форматированный вывод результата
                }
            }
        }

        private void square_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")       //проверка текстбокса на пустоту
            {
                if (calc.op_num == -1)
                    calc.tmp = double.Parse(IOtextBox.Text);        //помещение числа из тестбокса во временную переменну
                else
                    calc.calculate(IOtextBox.Text);
                calc.square();      //вызов функции расчета возведения в квадрат
                calc.op_num = 7;        //установка метки операции
                Historylabel.Text = "";
                IOtextBox.Text = calc.tmp.ToString("g3");       //форматированный вывод результата
            }
        }

        private void plusmin_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")
            {
                double tmp = double.Parse(IOtextBox.Text);                //помещение числа из тестбокса во временную переменну
                tmp = tmp * (-1);     //вызов функции смены знака
                IOtextBox.Text = tmp.ToString("g3");       //форматированный вывод результата
            }
        }

        private void IOtextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (IOtextBox.Text == "NaN")
            {
                calc.tmp = 0;
                IOtextBox.Text = String.Empty;
                Historylabel.Text = "";
                errorLabel.Text = "Введено не число";
                calc.op_num = -1;
                calc.prev_op = -1;
            }
            else if (errorLabel.Text == "Деление на 0 невозможно" || errorLabel.Text == "Введено не число")
            { }
            else
                errorLabel.Text = "";       //очистка метки ошибки
        }
       
        private void MenuButton2_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(Calc));
        }

        private void MenuButton3_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(About));
        }
        private void sin_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")        //проверка на пустой текстбокс
            {
                if (calc.op_num == -1)
                    calc.tmp = double.Parse(IOtextBox.Text);             //добавление числа во временную переменную
                else
                    calc.calculate(IOtextBox.Text);
                calc.sin();     //вызов функции расчета косинуса
                calc.op_num = 5;    //метка действия
                IOtextBox.Text = calc.tmp.ToString("g3");        //вывод результата в текстбокс (с форматированием)
            }
        }
        private void tan_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")        //проверка на пустой текстбокс
            {
                if (calc.op_num == -1)
                    calc.tmp = double.Parse(IOtextBox.Text);             //добавление числа во временную переменную
                else
                    calc.calculate(IOtextBox.Text);
                calc.tan();     //вызов функции расчета косинуса
                calc.op_num = 5;    //метка действия
                IOtextBox.Text = calc.tmp.ToString("g3");        //вывод результата в текстбокс (с форматированием)
            }
        }
        private void cor_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")        //проверка на пустой текстбокс
            {
                if (calc.op_num == -1)
                    calc.tmp = double.Parse(IOtextBox.Text);             //добавление числа во временную переменную
                else
                    calc.calculate(IOtextBox.Text);
                calc.cor();     //вызов функции расчета косинуса
                calc.op_num = 5;    //метка действия
                IOtextBox.Text = calc.tmp.ToString("g3");        //вывод результата в текстбокс (с форматированием)
            }
        }
        private void log_Click(object sender, RoutedEventArgs e)
        {
            if (IOtextBox.Text != "")        //проверка на пустой текстбокс
            {
                if (calc.op_num == -1)
                    calc.tmp = double.Parse(IOtextBox.Text);             //добавление числа во временную переменную
                else
                    calc.calculate(IOtextBox.Text);
                calc.log();     //вызов функции расчета косинуса
                calc.op_num = 5;    //метка действия
                IOtextBox.Text = calc.tmp.ToString("g3");        //вывод результата в текстбокс (с форматированием)
            }
        }

    }
}
