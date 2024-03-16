package unipr.aldo.graphic;

import javax.swing.*;  //classi grafiche
import javax.swing.border.TitledBorder;

import java.awt.*;  //classi grafiche (* = importa tutto)

public class GUI_prova extends JFrame{ //superclasse JFrame che ha metodi virtuali, che vado a modificare
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public JLabel lblRisultato = new JLabel (""); //public JLable = tipo;  () nome della label 
	public JTextField txtOperatoreUno = new JTextField ("0"); //casella di testo con dentro 0 (manca la posizione)
	public JTextField txtOperatoreDue = new JTextField ("1");
	
	
	
	
	public GUI_prova () {  //"costruttore del frame" 
		//voglio usare il costruttore della JFrame (costruttore del padre)
		super("operazioni aritmetiche"); //il frame è una finestra e questo è il nome della finestra 
		setLayout(new BorderLayout()); //layout è come vengono rappresentati gli oggetti grafici; BorderLayout ce ne sono altri;
		//abbiamo settato titolo e stile; adesso dobbiamo settare la dimensione della finestra
		setSize(600,400);
		//scelgo anche la posizione nello schermo 
		setLocation(100,200);
		
		//PANNELLO SUD (per ricordare la posizione su cui lavoriamo)
		JPanel pan1 = new JPanel();  //anche il pannello ha un layout da settare
		pan1.setLayout(new FlowLayout(FlowLayout.CENTER)); //pan1.setLayout è il layout di pan1; posizionato al centro ma non è all'interno della GUI
		add(pan1,BorderLayout.SOUTH); //così abbiamo aggiunto il pannello e gli abbiamo detto di stare a basso
		//il pannello è vuoto, serve un bottone
		JButton esci = new JButton( "esci" );
		pan1.add(esci); //aggiungo il bottone al pannello (probabilmente centrato per via del FlowLayout)
		ListenerEsci e = new ListenerEsci(this);  //il costruttore Listener ha un parametro di tipo GUI_prova, quindi qui metto this (che è un GUI_prova)
		//creo un altra classe (2^) chiamata ListenerEsci
		//sopra abbiamo creato un listener; ora dobbiamo applicarlo al bottone
		esci.addActionListener(e);
		
		//PANNELLO EST
		JPanel pan2 = new JPanel();
		pan2.setBorder(new TitledBorder ("Operazioni")); //diamo un bordo e un titolo
		pan2.setLayout(new GridLayout(3,1,50,50)); //Grid: 4 parametri per creare griglie (righe, colonne, spazio tra righe (pixel), spazio tra colonne)
		
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
		pan3.add(txtOperatoreUno,1); //posiziono i testi creati all'inizio
		JLabel lbl2 = new JLabel("secondo operando");
		pan3.add(lbl2,2);
		pan3.add(txtOperatoreDue,3); //posiziono i testi creati all'inizio
		
		//PANNELLO RISULTATI
		pan4.setBorder(new TitledBorder("risultato"));
		pan4.add(lblRisultato); //posiziono i testi creati all'inizio
	}
	
	public void Esci() {
		System.exit(0);
	}
	
	public void Somma() {
		double s = Double.parseDouble(txtOperatoreUno.getText())  +  Double.parseDouble(txtOperatoreDue.getText()); //converto i testi in double e li sommo
		//devo stampare il risultato nella lbl del risultato
		lblRisultato.setText(Double.toString(s));
	}
}