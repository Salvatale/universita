using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using LibCalcolatrice;

namespace WinCalcolatrice
{
    public partial class FormCalcolatrice : Form
    {
        public FormCalcolatrice()
        {
            InitializeComponent();
        }

        private void FormCalcolatrice_Load(object sender, EventArgs e)
        {

        }

        private void btnSomma_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Somma(
                    txtOperando1.Text,
                    txtOperando2.Text);
        }

        private void btnSottrai_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Sottrai(
                    txtOperando1.Text,
                    txtOperando2.Text);
        }

        private void btnMoltiplica_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Moltiplica(
                    txtOperando1.Text,
                    txtOperando2.Text);

        }

        private void btnDividi_Click(object sender, EventArgs e)
        {
            txtRisultato.Text =
                CalcolatriceStringa.Dividi(
                    txtOperando1.Text,
                    txtOperando2.Text);
        }
    }
}
