using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using WinWcfClientCalcolatrice.ServiceReferenceCalcolatrice;

namespace WinWcfClientCalcolatrice
{
    public partial class FormClientCalcolatrice : Form
    {
        ServiceCalcolatriceClient proxyCalcolatrice =
            new ServiceCalcolatriceClient();

        public FormClientCalcolatrice()
        {
            InitializeComponent();
        }

        private void btnSomma_Click(object sender, EventArgs e)
        {
            txtRisultato.Text = proxyCalcolatrice.Somma(txtOperando1.Text, txtOperando2.Text);
        }

        private void btnSottrai_Click(object sender, EventArgs e)
        {
            txtRisultato.Text = proxyCalcolatrice.Sottrai(txtOperando1.Text, txtOperando2.Text);
        }

        private void btnMoltiplica_Click(object sender, EventArgs e)
        {
            txtRisultato.Text = proxyCalcolatrice.Moltiplica(txtOperando1.Text, txtOperando2.Text);
        }

        private void btnDividi_Click(object sender, EventArgs e)
        {
            txtRisultato.Text = proxyCalcolatrice.Dividi(txtOperando1.Text, txtOperando2.Text);
        }
    }
}
