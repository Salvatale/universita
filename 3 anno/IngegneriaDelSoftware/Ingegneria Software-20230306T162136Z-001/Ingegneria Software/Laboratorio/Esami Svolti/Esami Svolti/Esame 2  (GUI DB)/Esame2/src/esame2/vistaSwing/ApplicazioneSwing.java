package esame2.vistaSwing;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import esame2.database.DatabaseManager;
import esame2.modello.Studente;
import esame2.vista.Applicazione;

public class ApplicazioneSwing implements Applicazione {
	public DatabaseManager databaseManager;
	public int indice;

	@Override
	public void pannelloStudenti() {
		// DataBase
		databaseManager = new DatabaseManager();

		// PANNELLO - PRINCIPALE
		JPanel pannelloPrincipale = new JPanel();
		pannelloPrincipale.setLayout(new BorderLayout());

		// PANNELLO - BASSO
		JPanel pannelloBasso = new JPanel();
		pannelloPrincipale.add(pannelloBasso, BorderLayout.SOUTH);

		// Bottone Salva
		JButton salva = new JButton();
		salva.setEnabled(false);
		salva.setText("Salva");
		pannelloBasso.add(salva, BorderLayout.WEST);

		// Bottone Esci
		JButton esci = new JButton();
		esci.setText("Esci");
		pannelloBasso.add(esci, BorderLayout.EAST);

		// PANNELLO - ALTO
		JPanel pannelloAlto = new JPanel();
		pannelloAlto.setLayout(new FlowLayout(FlowLayout.RIGHT));
		pannelloPrincipale.add(pannelloAlto, BorderLayout.NORTH);

		// Bottone Indietro
		JButton indietro = new JButton();
		indietro.setText("Indietro");
		pannelloAlto.add(indietro);

		// Bottone Avanti
		JButton avanti = new JButton();
		avanti.setText("Avanti");
		pannelloAlto.add(avanti);

		// PANNELLO - CENTRO
		JPanel pannelloCentro = new JPanel();
		pannelloCentro.setLayout(new GridLayout(6, 1));
		pannelloPrincipale.add(pannelloCentro, BorderLayout.CENTER);

		// Label
		JLabel lblMatricola = new JLabel();
		JLabel lblCognome = new JLabel();
		JLabel lblNome = new JLabel();
		lblMatricola.setText("Matricola");
		lblCognome.setText("Cognome");
		lblNome.setText("Nome");

		// TextField
		JTextField txtMatricola = new JTextField();
		txtMatricola.setEnabled(false);
		JTextField txtCognome = new JTextField();
		JTextField txtNome = new JTextField();

		// Aggiungo a tabella
		pannelloCentro.add(lblMatricola, 0);
		pannelloCentro.add(txtMatricola, 1);
		pannelloCentro.add(lblCognome, 2);
		pannelloCentro.add(txtCognome, 3);
		pannelloCentro.add(lblNome, 4);
		pannelloCentro.add(txtNome, 5);

		
		// FINESTRA
		JFrame finestra = new JFrame();
		finestra.add(pannelloPrincipale, BorderLayout.NORTH);
		finestra.setSize(400, 300);
		finestra.setVisible(true);
		
		// Imposto lo studente di inizio:
		indice = 0;
		impostaStudente(indice, txtMatricola, txtCognome, txtNome, indietro, avanti, salva);

		
		// LISTENER
		// finestra (chiusura)
		finestra.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				esci();
			}
		});

		// Esci
		esci.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				esci();
			}
		});
		
		// Indietro
		indietro.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				indice--;
				impostaStudente(indice, txtMatricola, txtCognome, txtNome, indietro, avanti, salva);
			}
		});
		
		// Avanti
		avanti.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				indice++;
				impostaStudente(indice, txtMatricola, txtCognome, txtNome, indietro, avanti, salva);
			}
		});
		
		// Salva
		salva.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				salva.setEnabled(false);
				if(!salva(Integer.parseInt(txtMatricola.getText()), txtCognome.getText(), txtNome.getText())) {
					JOptionPane.showMessageDialog(finestra, "Impossibile modificare lo studente!", "Errore", JOptionPane.ERROR_MESSAGE);
					impostaStudente(indice, txtMatricola, txtCognome, txtNome, indietro, avanti, salva);
				}
			}
		});
		
		// txtCognome
				txtCognome.addKeyListener(new KeyListener() {
					@Override
					public void keyTyped(KeyEvent e) { }
					@Override
					public void keyReleased(KeyEvent e) {
						salva.setEnabled(true);
					}
					@Override
					public void keyPressed(KeyEvent e) { }
				});
		
		// txtNome
		txtNome.addKeyListener(new KeyListener() {
			@Override
			public void keyTyped(KeyEvent e) { }
			@Override
			public void keyReleased(KeyEvent e) {
				salva.setEnabled(true);
			}
			@Override
			public void keyPressed(KeyEvent e) { }
		});
		
	}

	@Override
	public boolean salva(int matricola, String cognome, String nome) {
		Studente studente = new Studente(matricola, cognome, nome);
		if(!databaseManager.modificaStudente(studente))
			return false;
		return true;
	}

	@Override
	public void esci() {
		System.out.println("esci");
		System.exit(0);
	}

	public void impostaStudente(int indice, JTextField matricola, JTextField cognome, JTextField nome, JButton indietro, JButton avanti, JButton salva) {
		List<Studente> studenti = databaseManager.ricaricaStudenti();
		
		// Controlli per evitare errori nel caso vengano cancellati studenti mentre l'applicazione è in funzione.
		if (studenti.isEmpty()) {
			matricola.setText("Nessuno studente");
			cognome.setText("Nessuno studente");
			nome.setText("Nessuno studente");
			matricola.setEnabled(false);
			cognome.setEnabled(false);
			nome.setEnabled(false);
			salva.setEnabled(false);
			indice = 0;
			avanti.setEnabled(false);
			indietro.setEnabled(false);
		} else {
			if (indice >= studenti.size()-1)   // Se indice punta all'ultimo elemento o piu':
				avanti.setEnabled(false);
			if (indice == 0)   // Se indice punta al primo elemento:
				indietro.setEnabled(false);
			
			if (indice >= studenti.size())   // Se l'indice punta fuori dal range:
				indice = studenti.size()-1;
			Studente studente = studenti.get(indice);
			matricola.setText(Integer.toString(studente.getMatricola()));
			cognome.setText(studente.getCognome());
			nome.setText(studente.getNome());
			//nome.setText(studente.getNome());
			
			if(indice > 0)
				indietro.setEnabled(true);
			if(indice < studenti.size()-1)
				avanti.setEnabled(true);
		}
		
	}

}
