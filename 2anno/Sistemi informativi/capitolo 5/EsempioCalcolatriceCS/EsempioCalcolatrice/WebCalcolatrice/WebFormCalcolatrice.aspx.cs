using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using LibCalcolatrice;

namespace WebCalcolatrice
{
    public partial class WebFormCalcolatrice : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnSomma_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
               CalcolatriceStringa.Somma(
                   txtOperando1.Text,
                   txtOperando2.Text);
        }

        protected void btnSottrai_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Sottrai(
                    txtOperando1.Text,
                    txtOperando2.Text);
        }

        protected void btnMoltiplica_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Moltiplica(
                    txtOperando1.Text,
                    txtOperando2.Text);
        }

        protected void btnDividi_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Dividi(
                    txtOperando1.Text,
                    txtOperando2.Text);
        }
    }
}