using System;

namespace Lab7
{
    public class Operations     //класс операций
    {
        /// <summary>
        /// Временная переменная
        /// </summary>
        double temp;     //временная переменная 
                         /// <summary>
                         /// Переменная текущей операции
                         /// </summary>
        int Op_num;          //переменная метки операции
                             /// <summary>
                             /// Переменная предыдущей операции
                             /// </summary>
        int last_op;             //переменная метки предыдущей операции
                                 /// <summary>
                                 /// Конструктор
                                 /// </summary>
        public Operations()             //конструктор по умолчанию
        {
            temp = 0;
            Op_num = -1;
            last_op = -1;
        }
        public double tmp          //свойство временной переменной
        {
            get { return temp; }
            set { temp = value; }

        }
        public int op_num          //свойство метки операции
        {
            get { return Op_num; }
            set { Op_num = value; }
        }
        public int prev_op          //свойство метки предыдущей операции
        {
            get { return last_op; }
            set { last_op = value; }
        }
        /// <summary>
        /// Функция расчета
        /// </summary>
        public void calculate(string text)          //функция расчета
        {


            if (last_op == -1 && text == "")        //проверка на пустой текст и не выполнение никакой операции
                text = "0";          //вставка нуля в текст
            else if (text == "")                      //если тест пуст – выход из функции
                return;
            double a = double.Parse(text);      //преобразование текста в дабл
            if (tmp == 0 && last_op == -1)          //проверка на пустоту временной переменной и отсутствие выполненых операций
            {
                tmp = a;          //занесение введенного числа во временную переменную
            }
            else
            {
                switch (op_num)          //выбор и выполнение операции в зависимости от метки операции
                {
                    case 1:
                        tmp = tmp + a;          //сумма
                        break;
                    case 2:
                        tmp = tmp - a;          //разница
                        break;
                    case 3:
                        tmp = tmp * a;          //умножение
                        break;
                    case 4:
                        tmp = tmp / a;           //деление
                        break;
                }
            }

            last_op = op_num;          //занесение метки текущей операции в преыдущую
        }

        /// <summary>
        /// Функция деления 1 на х
        /// </summary>
        public void divx()           //функция деления 1 на введенное число
        {
            tmp = 1 / tmp;
        }
        /// <summary>
        /// Функция квадрата
        /// </summary>
        public void square()          //функция возведения в квадрат
        {
            tmp = tmp * tmp;
        }
        /// <summary>
        /// Функция косинуса
        /// </summary>
        public void cos()          //функция косинуса
        {
            tmp = Math.Cos(tmp);
        }
        public void sin()          //функция косинуса
        {
            tmp = Math.Sin(tmp);
        }
        public void tan()          //функция косинуса
        {
            tmp = Math.Tan(tmp);
        }
        /// <summary>
        /// Функция смена знака
        /// </summary>
        public void plusmin()          //функция смены знака
        {
            tmp = tmp * (-1);
        }
        public void cor()
        {
            tmp = Math.Sqrt(tmp);
        }
        public void log()
        {
            tmp = Math.Log(tmp);
        }

    }
}
        