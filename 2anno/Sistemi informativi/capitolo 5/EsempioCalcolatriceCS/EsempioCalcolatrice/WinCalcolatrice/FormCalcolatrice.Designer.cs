namespace WinCalcolatrice
{
    partial class FormCalcolatrice
    {
        /// <summary>
        /// Variabile di progettazione necessaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Pulire le risorse in uso.
        /// </summary>
        /// <param name="disposing">ha valore true se le risorse gestite devono essere eliminate, false in caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Codice generato da Progettazione Windows Form

        /// <summary>
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtOperando1 = new System.Windows.Forms.TextBox();
            this.txtOperando2 = new System.Windows.Forms.TextBox();
            this.txtRisultato = new System.Windows.Forms.TextBox();
            this.lblOperando1 = new System.Windows.Forms.Label();
            this.lblOperando2 = new System.Windows.Forms.Label();
            this.lblRisultato = new System.Windows.Forms.Label();
            this.btnSomma = new System.Windows.Forms.Button();
            this.btnSottrai = new System.Windows.Forms.Button();
            this.btnMoltiplica = new System.Windows.Forms.Button();
            this.btnDividi = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtOperando1
            // 
            this.txtOperando1.Location = new System.Drawing.Point(153, 35);
            this.txtOperando1.Name = "txtOperando1";
            this.txtOperando1.Size = new System.Drawing.Size(100, 20);
            this.txtOperando1.TabIndex = 0;
            // 
            // txtOperando2
            // 
            this.txtOperando2.Location = new System.Drawing.Point(153, 100);
            this.txtOperando2.Name = "txtOperando2";
            this.txtOperando2.Size = new System.Drawing.Size(100, 20);
            this.txtOperando2.TabIndex = 1;
            // 
            // txtRisultato
            // 
            this.txtRisultato.Location = new System.Drawing.Point(153, 205);
            this.txtRisultato.Name = "txtRisultato";
            this.txtRisultato.Size = new System.Drawing.Size(100, 20);
            this.txtRisultato.TabIndex = 2;
            // 
            // lblOperando1
            // 
            this.lblOperando1.AutoSize = true;
            this.lblOperando1.Location = new System.Drawing.Point(27, 38);
            this.lblOperando1.Name = "lblOperando1";
            this.lblOperando1.Size = new System.Drawing.Size(66, 13);
            this.lblOperando1.TabIndex = 3;
            this.lblOperando1.Text = "Operando 1:";
            // 
            // lblOperando2
            // 
            this.lblOperando2.AutoSize = true;
            this.lblOperando2.Location = new System.Drawing.Point(27, 103);
            this.lblOperando2.Name = "lblOperando2";
            this.lblOperando2.Size = new System.Drawing.Size(66, 13);
            this.lblOperando2.TabIndex = 4;
            this.lblOperando2.Text = "Operando 2:";
            // 
            // lblRisultato
            // 
            this.lblRisultato.AutoSize = true;
            this.lblRisultato.Location = new System.Drawing.Point(27, 208);
            this.lblRisultato.Name = "lblRisultato";
            this.lblRisultato.Size = new System.Drawing.Size(51, 13);
            this.lblRisultato.TabIndex = 5;
            this.lblRisultato.Text = "Risultato:";
            // 
            // btnSomma
            // 
            this.btnSomma.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSomma.Location = new System.Drawing.Point(30, 148);
            this.btnSomma.Name = "btnSomma";
            this.btnSomma.Size = new System.Drawing.Size(30, 30);
            this.btnSomma.TabIndex = 6;
            this.btnSomma.Text = "+";
            this.btnSomma.UseVisualStyleBackColor = true;
            this.btnSomma.Click += new System.EventHandler(this.btnSomma_Click);
            // 
            // btnSottrai
            // 
            this.btnSottrai.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSottrai.Location = new System.Drawing.Point(78, 148);
            this.btnSottrai.Name = "btnSottrai";
            this.btnSottrai.Size = new System.Drawing.Size(30, 30);
            this.btnSottrai.TabIndex = 7;
            this.btnSottrai.Text = "-";
            this.btnSottrai.UseVisualStyleBackColor = true;
            this.btnSottrai.Click += new System.EventHandler(this.btnSottrai_Click);
            // 
            // btnMoltiplica
            // 
            this.btnMoltiplica.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnMoltiplica.Location = new System.Drawing.Point(127, 149);
            this.btnMoltiplica.Name = "btnMoltiplica";
            this.btnMoltiplica.Size = new System.Drawing.Size(30, 30);
            this.btnMoltiplica.TabIndex = 8;
            this.btnMoltiplica.Text = "*";
            this.btnMoltiplica.UseVisualStyleBackColor = true;
            this.btnMoltiplica.Click += new System.EventHandler(this.btnMoltiplica_Click);
            // 
            // btnDividi
            // 
            this.btnDividi.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDividi.Location = new System.Drawing.Point(179, 149);
            this.btnDividi.Name = "btnDividi";
            this.btnDividi.Size = new System.Drawing.Size(30, 30);
            this.btnDividi.TabIndex = 9;
            this.btnDividi.Text = "/";
            this.btnDividi.UseVisualStyleBackColor = true;
            this.btnDividi.Click += new System.EventHandler(this.btnDividi_Click);
            // 
            // FormCalcolatrice
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.btnDividi);
            this.Controls.Add(this.btnMoltiplica);
            this.Controls.Add(this.btnSottrai);
            this.Controls.Add(this.btnSomma);
            this.Controls.Add(this.lblRisultato);
            this.Controls.Add(this.lblOperando2);
            this.Controls.Add(this.lblOperando1);
            this.Controls.Add(this.txtRisultato);
            this.Controls.Add(this.txtOperando2);
            this.Controls.Add(this.txtOperando1);
            this.Name = "FormCalcolatrice";
            this.Text = "Form Calcolatrice";
            this.Load += new System.EventHandler(this.FormCalcolatrice_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtOperando1;
        private System.Windows.Forms.TextBox txtOperando2;
        private System.Windows.Forms.TextBox txtRisultato;
        private System.Windows.Forms.Label lblOperando1;
        private System.Windows.Forms.Label lblOperando2;
        private System.Windows.Forms.Label lblRisultato;
        private System.Windows.Forms.Button btnSomma;
        private System.Windows.Forms.Button btnSottrai;
        private System.Windows.Forms.Button btnMoltiplica;
        private System.Windows.Forms.Button btnDividi;
    }
}

