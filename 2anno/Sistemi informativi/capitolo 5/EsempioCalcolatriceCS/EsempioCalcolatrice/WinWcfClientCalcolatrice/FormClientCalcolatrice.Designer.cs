namespace WinWcfClientCalcolatrice
{
    partial class FormClientCalcolatrice
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
            this.btnDividi = new System.Windows.Forms.Button();
            this.btnMoltiplica = new System.Windows.Forms.Button();
            this.btnSottrai = new System.Windows.Forms.Button();
            this.btnSomma = new System.Windows.Forms.Button();
            this.lblRisultato = new System.Windows.Forms.Label();
            this.lblOperando2 = new System.Windows.Forms.Label();
            this.lblOperando1 = new System.Windows.Forms.Label();
            this.txtRisultato = new System.Windows.Forms.TextBox();
            this.txtOperando2 = new System.Windows.Forms.TextBox();
            this.txtOperando1 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnDividi
            // 
            this.btnDividi.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDividi.Location = new System.Drawing.Point(181, 150);
            this.btnDividi.Name = "btnDividi";
            this.btnDividi.Size = new System.Drawing.Size(30, 30);
            this.btnDividi.TabIndex = 19;
            this.btnDividi.Text = "/";
            this.btnDividi.UseVisualStyleBackColor = true;
            this.btnDividi.Click += new System.EventHandler(this.btnDividi_Click);
            // 
            // btnMoltiplica
            // 
            this.btnMoltiplica.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnMoltiplica.Location = new System.Drawing.Point(129, 150);
            this.btnMoltiplica.Name = "btnMoltiplica";
            this.btnMoltiplica.Size = new System.Drawing.Size(30, 30);
            this.btnMoltiplica.TabIndex = 18;
            this.btnMoltiplica.Text = "*";
            this.btnMoltiplica.UseVisualStyleBackColor = true;
            this.btnMoltiplica.Click += new System.EventHandler(this.btnMoltiplica_Click);
            // 
            // btnSottrai
            // 
            this.btnSottrai.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSottrai.Location = new System.Drawing.Point(80, 149);
            this.btnSottrai.Name = "btnSottrai";
            this.btnSottrai.Size = new System.Drawing.Size(30, 30);
            this.btnSottrai.TabIndex = 17;
            this.btnSottrai.Text = "-";
            this.btnSottrai.UseVisualStyleBackColor = true;
            this.btnSottrai.Click += new System.EventHandler(this.btnSottrai_Click);
            // 
            // btnSomma
            // 
            this.btnSomma.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSomma.Location = new System.Drawing.Point(32, 149);
            this.btnSomma.Name = "btnSomma";
            this.btnSomma.Size = new System.Drawing.Size(30, 30);
            this.btnSomma.TabIndex = 16;
            this.btnSomma.Text = "+";
            this.btnSomma.UseVisualStyleBackColor = true;
            this.btnSomma.Click += new System.EventHandler(this.btnSomma_Click);
            // 
            // lblRisultato
            // 
            this.lblRisultato.AutoSize = true;
            this.lblRisultato.Location = new System.Drawing.Point(29, 209);
            this.lblRisultato.Name = "lblRisultato";
            this.lblRisultato.Size = new System.Drawing.Size(51, 13);
            this.lblRisultato.TabIndex = 15;
            this.lblRisultato.Text = "Risultato:";
            // 
            // lblOperando2
            // 
            this.lblOperando2.AutoSize = true;
            this.lblOperando2.Location = new System.Drawing.Point(29, 104);
            this.lblOperando2.Name = "lblOperando2";
            this.lblOperando2.Size = new System.Drawing.Size(66, 13);
            this.lblOperando2.TabIndex = 14;
            this.lblOperando2.Text = "Operando 2:";
            // 
            // lblOperando1
            // 
            this.lblOperando1.AutoSize = true;
            this.lblOperando1.Location = new System.Drawing.Point(29, 39);
            this.lblOperando1.Name = "lblOperando1";
            this.lblOperando1.Size = new System.Drawing.Size(66, 13);
            this.lblOperando1.TabIndex = 13;
            this.lblOperando1.Text = "Operando 1:";
            // 
            // txtRisultato
            // 
            this.txtRisultato.Location = new System.Drawing.Point(155, 206);
            this.txtRisultato.Name = "txtRisultato";
            this.txtRisultato.Size = new System.Drawing.Size(100, 20);
            this.txtRisultato.TabIndex = 12;
            // 
            // txtOperando2
            // 
            this.txtOperando2.Location = new System.Drawing.Point(155, 101);
            this.txtOperando2.Name = "txtOperando2";
            this.txtOperando2.Size = new System.Drawing.Size(100, 20);
            this.txtOperando2.TabIndex = 11;
            // 
            // txtOperando1
            // 
            this.txtOperando1.Location = new System.Drawing.Point(155, 36);
            this.txtOperando1.Name = "txtOperando1";
            this.txtOperando1.Size = new System.Drawing.Size(100, 20);
            this.txtOperando1.TabIndex = 10;
            // 
            // FormClientCalcolatrice
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
            this.Name = "FormClientCalcolatrice";
            this.Text = "Form Client Calcolatrice";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnDividi;
        private System.Windows.Forms.Button btnMoltiplica;
        private System.Windows.Forms.Button btnSottrai;
        private System.Windows.Forms.Button btnSomma;
        private System.Windows.Forms.Label lblRisultato;
        private System.Windows.Forms.Label lblOperando2;
        private System.Windows.Forms.Label lblOperando1;
        private System.Windows.Forms.TextBox txtRisultato;
        private System.Windows.Forms.TextBox txtOperando2;
        private System.Windows.Forms.TextBox txtOperando1;
    }
}

