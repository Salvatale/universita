using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// inclusione nostre librerie
using LibCalcolatrice;

namespace ConsoleCalcolatrice
{
    class Program
    {
        static void Main(string[] args)
        {
            double numerosomma, numerodiff, numeromul, numerodiv;

            numerosomma = Calcolatrice.Somma(1.5, 4.0);

            numerodiff = Calcolatrice.Sottrai(10.0, 2.0);

            numeromul = Calcolatrice.Moltiplica(10.0, 6.0);

            numerodiv = Calcolatrice.Dividi(10.0, 2.0);

            Console.WriteLine("Somma " + string.Format("{0:n3}", numerosomma));
            Console.WriteLine("Differenza = " + string.Format("{0:n3}", numerodiff));
            Console.WriteLine("Moltiplicazione = " + string.Format("{0:n3}", numeromul));
            Console.WriteLine("Divisione = " + string.Format("{0:n3}", numerodiv));


            Console.ReadKey();
            
        }
    }
}
