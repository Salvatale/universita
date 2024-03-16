using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibCalcolatrice
{
    public class CalcolatriceStringa : Calcolatrice
    {
        static double StringToDouble(string p_stringa)
        {
            double valore = 0.0;
            try
            {
                valore = Convert.ToDouble(p_stringa);
            }
            catch (Exception e)
            {
                valore = 0.0;
            }
            return valore;
        }

        static string DoubleToString(double p_double)
        {
            return string.Format("{0:n2}", p_double);
        }

        public static string Somma(string p_stringa1, string p_stringa2)
        {
            double oper1, oper2, risdouble;

            oper1 = StringToDouble(p_stringa1);
            oper2 = StringToDouble(p_stringa2);

            risdouble = Somma(oper1, oper2);

            return DoubleToString(risdouble);
        }

        public static string Sottrai(string p_stringa1, string p_stringa2)
        {
            double oper1, oper2, risdouble;

            oper1 = StringToDouble(p_stringa1);
            oper2 = StringToDouble(p_stringa2);

            risdouble = Sottrai(oper1, oper2);

            return DoubleToString(risdouble);
        }

        public static string Moltiplica(string p_stringa1, string p_stringa2)
        {
            double oper1, oper2, risdouble;

            oper1 = StringToDouble(p_stringa1);
            oper2 = StringToDouble(p_stringa2);

            risdouble = Moltiplica(oper1, oper2);

            return DoubleToString(risdouble);
        }

        public static string Dividi(string p_stringa1, string p_stringa2)
        {
            double oper1, oper2, risdouble;

            oper1 = StringToDouble(p_stringa1);
            oper2 = StringToDouble(p_stringa2);

            risdouble = Dividi(oper1, oper2);

            return DoubleToString(risdouble);
        }
    }
}
