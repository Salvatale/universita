using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LibCalcolatrice;

namespace ConsoleCalcolatriceStringa
{
    class Program
    {
        static void Main(string[] args)
        {
            string operando1 = args[0];
            string operatore = args[1];
            string operando2 = args[2];

            string risultato = string.Empty;

            switch (operatore)
            {
                case "+":
                {
                    risultato =
                        CalcolatriceStringa.Somma(
                            operando1,
                            operando2);
                    break;
                }

                case "-":
                {
                    risultato =
                        CalcolatriceStringa.Sottrai(
                            operando1,
                            operando2);
                    break;
                }

                case "*":
                {
                    risultato =
                        CalcolatriceStringa.Moltiplica(
                            operando1,
                            operando2);
                    break;
                }

                case "/":
                {
                    risultato =
                        CalcolatriceStringa.Dividi(
                            operando1,
                            operando2);
                    break;
                }

                default:
                {
                    risultato = "ERRORE: operatore non previsto";
                    break;
                }

            } // end switch
                    
            
            Console.WriteLine("Risultato = " + risultato);
        } // end Main
    } // end class
} // end namespace
