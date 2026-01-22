# RP2040_synth
Progetto di sviluppo di un Synth ibrido digitale/analogico con generazione dei suoni tramite DCO controllati da microcontrollori RP2040

## ARCHITETTURA GENERALE
La struttura è di tipo "modulare" e può essere composta da un numero massimo di 8 moduli connessi su un bus parallelo proprietario.
Ogni modulo voce può controllare un massimo di 8 DCO 2 Wave Table, 2 LFO e 3 generatori di inviluppo a 8 fasi (modello ispirato al sistema di modulazione di fase implementato sulla serie CASIO CZ).
Un singolo modulo dovrebbe bastare per generare suoni e inviluppi di uno strumento di tipo "parafonico" a 4 voci con 2 DCO/voce (con RP2040) o 3 DCO/voce (con RP2350).

## Projects

### [Guitar](../master/guitar)

* *Project type: Arduino IDE (.ino)*

Simple "guitar" where I used a distance sensor to map distance to a tone and play it through a piezo. You can read more about this project on my [blog](http://engineerish.com/post/148459701886/arduino-guitar).

### [Party Glasses](../master/party-glasses)

* *Project type: Arduino IDE (.ino)*
