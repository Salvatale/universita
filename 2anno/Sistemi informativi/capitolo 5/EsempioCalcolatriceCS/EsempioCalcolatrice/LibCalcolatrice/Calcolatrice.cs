using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibCalcolatrice
{
    public class Calcolatrice
    {
        public static double Somma(double p_oper1, double p_oper2)
        {
            return p_oper1 + p_oper2;
        } // end method

        public static double Sottrai(double p_oper1, double p_oper2)
        {
            return p_oper1 - p_oper2;
        } // end method

        public static double Moltiplica(double p_oper1, double p_oper2)
        {
            return p_oper1 * p_oper2;
        } // end method

        public static double Dividi(double p_oper1, double p_oper2)
        {
            if (p_oper2 == 0.0)
            {
                return Double.PositiveInfinity;
            }
            else
            {
                return p_oper1 / p_oper2;
            }
            
        } // end method




    } // end class
} // end namespace
