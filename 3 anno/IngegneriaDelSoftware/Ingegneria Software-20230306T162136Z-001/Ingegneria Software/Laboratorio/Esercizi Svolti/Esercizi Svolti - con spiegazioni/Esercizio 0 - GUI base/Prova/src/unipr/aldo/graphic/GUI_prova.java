package unipr.aldo.graphic;

import javax.swing.*;  
import javax.swing.border.TitledBorder;
import java.awt.*; 

public class GUI_prova extends JFrame{ 
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public JLabel lblRisultato = new JLabel (""); 
	public JTextField txtOperatoreUno = new JTextField ("0"); 
	public JTextField txtOperatoreDue = new JTextField ("1");
	
	public GUI_prova () {  
		super("operazioni aritmetiche"); 
		setLayout(new BorderLayout()); 
		setSize(600,400);
		setLocation(100,200);
		
		//PANNELLO SUD
		JPanel pan1 = new JPanel(); 
		pan1.setLayout(new FlowLayout(FlowLayout.CENTER)); 
		add(pan1,BorderLayout.SOUTH); 
		JButton esci = new JButton( "esci" );
		pan1.add(esci); //aggiungo il bottone al pannello
		ListenerEsci e = new ListenerEsci(this);  
		esci.addActionListener(e);
		
		//PANNELLO EST
		JPanel pan2 = new JPanel();
		pan2.setBorder(new TitledBorder ("Operazioni")); 
		pan2.setLayout(new GridLayout(3,1,50,50)); 
		
		JButton somma = new JButton ("+");
		pan2.add(somma);
		ListenerSomma s = new ListenerSomma(this);
		somma.addActionListener(s);
		add(pan2,BorderLayout.EAST);
		
		//PANNELLO CENTER
		JPanel panContenitore = new JPanel();
		add(panContenitore,BorderLayout.CENTER);
		panContenitore.setLayout(new GridLayout(2,1,10,10));
		JPanel pan3 = new JPanel();
		JPanel pan4 = new JPanel();
		panContenitore.add(pan3,0);
		panContenitore.add(pan4,1);
		
		//PANNELLO DATI
		pan3.setBorder(new TitledBorder("Dati"));
		pan3.setLayout(new GridLayout(4,1));
		JLabel lbl1 = new JLabel("primo operando");
		pan3.add(lbl1,0);
		pan3.add(txtOperatoreUno,1);
		JLabel lbl2 = new JLabel("secondo operando");
		pan3.add(lbl2,2);
		pan3.add(txtOperatoreDue,3);
		
		//PANNELLO RISULTATI
		pan4.setBorder(new TitledBorder("risultato"));
		pan4.add(lblRisultato);
	}
	
	public void Esci() {
		System.exit(0);
	}
	
	public void Somma() {
		double s = Double.parseDouble(txtOperatoreUno.getText())  +  Double.parseDouble(txtOperatoreDue.getText());
		lblRisultato.setText(Double.toString(s));
	}
}