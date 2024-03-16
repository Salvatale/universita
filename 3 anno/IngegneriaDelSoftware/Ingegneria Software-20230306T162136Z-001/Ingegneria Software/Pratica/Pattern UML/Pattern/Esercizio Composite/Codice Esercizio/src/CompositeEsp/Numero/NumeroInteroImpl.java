package CompositeEsp.Numero;

public class NumeroInteroImpl implements NumeroIntero {
	public int num;

	public NumeroInteroImpl(int num) {
		this.num = num;
	}

	@Override
	public int getValore() {
		return num;
	}

	@Override
	public NumeroIntero somma(NumeroIntero n) {
		return new NumeroInteroImpl(num + n.getValore());
	}

	@Override
	public NumeroIntero prodotto(NumeroIntero n) {
		return new NumeroInteroImpl(num * n.getValore());
	}
}
