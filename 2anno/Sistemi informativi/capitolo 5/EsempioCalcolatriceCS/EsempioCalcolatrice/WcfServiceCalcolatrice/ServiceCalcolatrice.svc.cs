using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

using LibCalcolatrice;

namespace WcfServiceCalcolatrice
{
    // NOTA: è possibile utilizzare il comando "Rinomina" del menu "Refactoring" per modificare il nome di classe "Service1" nel codice, nel file svc e nel file di configurazione contemporaneamente.
    // NOTA: per avviare il client di prova WCF per testare il servizio, selezionare Service1.svc o Service1.svc.cs in Esplora soluzioni e avviare il debug.
    public class ServiceCalcolatrice : IServiceCalcolatrice
    {
        public string GetData(int value)
        {
            return string.Format("You entered: {0}", value);
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite == null)
            {
                throw new ArgumentNullException("composite");
            }
            if (composite.BoolValue)
            {
                composite.StringValue += "Suffix";
            }
            return composite;
        }

        public string Somma(string p_oper1, string p_oper2)
        {
            return CalcolatriceStringa.Somma(p_oper1, p_oper2);
        }

        public string Sottrai(string p_oper1, string p_oper2)
        {
            return CalcolatriceStringa.Sottrai(p_oper1, p_oper2);
        }

        public string Moltiplica(string p_oper1, string p_oper2)
        {
            return CalcolatriceStringa.Moltiplica(p_oper1, p_oper2);
        }

        public string Dividi(string p_oper1, string p_oper2)
        {
            return CalcolatriceStringa.Dividi(p_oper1, p_oper2);
        }
    }
}
