class CFBuilder{
	/*
		CFBuilder serve a risolvere problemi
		Prendo Cognome, Nome, dataNascita, comune, sesso 
		e creo il codiceFiscale dopo aver inserito i vari campi
	*/
	
	private String cognome = null;
	private String nome = null;
	private Date dataNascita = null;
	private String comune = null;
	private Boolean sesso = null;

	public CFBuilder(){}

	public static build(){
		String codiceFiscale = null;

		//richiamo di tutti i metodi che ricavano il codice fiscale
        codiceFiscale = ricavaCognome() +
                ricavaNome() +
                ricavaData() +
                ricavaLuogo();

        codiceFiscale = codiceFiscale + calcolaCarattereControllo();

		return codiceFiscale;
	}

	//CONTROLLO DEL COGNOME
    public String ricavoCognome(){
        String siglaCognome = null;
        String consonantiTrovate = null;
        String vocaliTrovate = null;
        String vocali = "AEIOUaeiou";
        int i = 0;
        int ic = 0; //ic indica il numero di consonanti a cui sono arrivato a mettere
        int iv = 0; //iv indica il numero di vocali a cui sono arrivato a mettere
        int vDaAggiungere = 0;
        String lettera = null;
        String stringaX = "XXX";

        while(i < cognome.length() && ic < 3){
            lettera = cognome.substring(i,1); //prendo la "iesima" lettera del cognome (parto da i e prendo una lettera)
            if(vocali.contains(lettera)){ //controllo se la stringa "vocali" contiene la lettera "lettera" 
                vocaliTrovate = vocaliTrovate + lettera; //concateno in "vocaliTrovate" le vocali che ci sono nel cognome 
                iv++;
            }else{
                consonantiTrovate = consonantiTrovate + lettera; //metto/concateno in consonantiTrovate tutte le consonanti trovate nel cognome 
                ic++;
            }
            i++;
        }

        if(ic<3){
            vDaAggiungere = 3 - ic; //calcolo il numero di vocali da aggiungere sottraendo il numero di consonanti da 3
            if(iv < vDaAggiungere){ //controllo se il numero di vocali trovate è minore del numero di vocali che servono
                siglaCognome = consonantiTrovate + vocaliTrovate + stringaX.substring(0, vDaAggiungere - iv); //in caso positivo aggiungo tante X quante sono le vocali che mancano
        
            }else{
                //altrimenti concateno le vocali che mi servono alle consonanti
                siglaCognome = consonantiTrovate + vocaliTrovate.substring(0, vDaAggiungere); 

            }
        }else{
            //altrimenti non concateno le vocali e lascio che la sigla del cognome sia composta solo da consonanti
            siglaCognome = consonantiTrovate;
        }
        siglaCognome.toUpperCase();
        //il risultato ottenuto è in "siglaCognome"
        return silaCognome;
    }

    //CONTROLLO DEL NOME
    public String ricavoNome(){
        String siglaNome = null;
        String consonantiTrovate = null;
        String vocaliTrovate = null;
        String vocali = "AEIOUaeiou";
        int i = 0;
        int ic = 0; //ic indica il numero di consonanti a cui sono arrivato a mettere
        int iv = 0; //iv indica il numero di vocali a cui sono arrivato a mettere
        int vDaAggiungere = 0;
        String lettera = null;
        String stringaX = "XXX";
        
        while(i < nome.length() && ic < 3){
            lettera = nome.substring(i,1);
            if(vocali.contains(lettera)){

                vocaliTrovate = vocaliTrovate + lettera;
                iv++;
            }else{

                consonantiTrovate = consonantiTrovate + lettera;
                ic++;
            }
            i++;
        }

        if(ic >= 4){  //controllo se il numero di consonanti trovate è maggiore di 3
            //in caso positivo considero la prima, la terza e la quarta consonante e le concateno (regola codice fiscale)
            siglaNome = consonantiTrovate.substring(0,1) + consonantiTrovate.substring(2,1) +consonantiTrovate.substring(3,1);
        }else{
            if(ic == 3){ //altrimenti controllo se il numero di consonanti è uguale a 3
                //in caso positivo prendo tutte le consonanti
                siglaNome = consonantiTrovate;
            }else{
                //calcolo quante vocali mi servono da aggiungere
                vDaAggiungere = 3 - ic;
                if(iv < vDaAggiungere){ //controllo se il numero di vocali trovate è minore del numero di vocali che servono
                    //in caso positivo aggiungo tante X quante sono le vocali che mancano
                    siglaNome = consonantiTrovate + vocaliTrovate + stringaX.substring(0, vDaAggiungere - iv);
                
                }else{
                    //altrimenti concateno le vocali che mi servono alle consonanti
                    siglaNome = consonantiTrovate + vocaliTrovate.substring(0, vDaAggiungere);
                }
            }
        }
        siglaNome.toUpperCase();
        //il risultato ottenuto è in "siglaNome"
        return siglaNome;
    }

    //CONTROLLO DATA NASCITA
    public String ricavoData(){
        String ret = "";
        String lettereMesi = "ABCDEHLMPRST";
        String[] dataArray = dataNascita.split("/");

        //prendo le ultime due cifre dell'anno di nascita
        ret = dataArray[2].substring(2, 4);
        //prendo il carattere corrispondente al mese di nascita
        ret = ret + lettereMesi.charAt(Integer.parseInt(dataArray[1]) - 1);

        //se e' selezionato il sesso femminile, prendo il giorno di nascita e aggiungo 40
        //se e' selezionato il sesso maschile, prendo il giorno di nascita
        if(femmina.isSelected()) {
            int giorno = Integer.parseInt(dataArray[0]) + 40;
            ret = ret + giorno;
        } else {
            ret = ret + dataArray[0];
        }

        return ret;
    }

    public String ricavoCodiceComune(){

        return codiciComuni[codice.getCmbComuneNascita().getSelectedIndex()];
    }


    //CONTROLLO CARATTERE
    public char ricavoCarattere(){
        int val;
        int i = 0;
        int somma = 0;
        //Dichiarazione di un vettore contenente i valori corrispondenti a ogni lettera in posizione dispari, dato che non segue un ordine preciso
        int[] valoriPosDispari = {1, 0, 5, 7, 9, 13, 15, 17, 19, 21, 2, 4, 18, 20, 11, 3, 6, 8, 12, 14, 16, 10, 22, 25, 24};

        for (char c: codiceFinale.toCharArray()) {
            if (i%2 == 1){
                /*
                CONVERSIONE POSIZIONE PARI
                Controllo se il carattere in considerazione è un numero o una lettera
                */
                if (Character.isLetter(c)) {
                    //Se è una lettera il valore sarà corrispondente alla differenza tra il codice ascii del carattere e 65 (codice ascii di 'A')
                    val = (int)c - 65;
                } else {
                    //Se è un numero il valore sarà il numero stesso
                    val = Character.getNumericValue(c);
                }
            } else {
                /*
                CONVERSIONE POSIZIONE DISPARI
                Controllo se il carattere in considerazione è un numero o una lettera
                */
                if (Character.isLetter(c)) {
                    //Se è una lettera l'indice del vettore sarà corrispondente alla differenza tra il codice ascii del carattere e 65 (codice ascii di 'A')
                    val = valoriPosDispari[(int)c - 65];
                } else {
                    //Se è un numero l'indice del vettore sarà il numero stesso
                    val = valoriPosDispari[Character.getNumericValue(c)];
                }
            }

            //Incremento della somma
            somma += val;

            i++;
        }

        //Valore finale: resto della divisione tra la somma dei valori ottenuti in precedenza e 26
        val = somma % 26;

        //Restituzione della lettera in base al resto della divisione
        return (char)(65+val);
    }

	//TUTTE LE SET
	public CFBuilder setCognome(String cognome){
		this.cognome = cognome;
		return this;
	}

	public CFBuilder setNome(String nome){
		this.nome = nome;
		return this;
	}

	public CFBuilder setDataNascita(String dataNascita){
		this.dataNascita = dataNascita;
		return this;
	}

	public CFBuilder setComune(String comune){
		this.comune = comune;
		return this;
	}

	public CFBuilder setSesso(String sesso){
		this.sesso = sesso;
		return this;
	}
}
