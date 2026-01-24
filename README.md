# RP2040_synth
Progetto di sviluppo di un Synth ibrido digitale/analogico con generazione dei suoni tramite DCO controllati da microcontrollori RP2040

## ARCHITETTURA GENERALE
- La struttura è di tipo "modulare" e in questa prima versione può ospitare un numero massimo di 8 moduli voce connessi su un bus parallelo proprietario.
- L'HW a livello schematico è organizzato a "sezioni circuitali", a livello di ingegnerizzazione si può decidere se realizzare delle PCB separate e interconnesse (una per ogni sezione) o raggruppare più sezioni su singole PCB (in base alle scelte costruttive)
- Ogni modulo voce può controllare un massimo di 6 DCO ibridi, 2 DCO Wave Table, 2 LFO e 3 generatori di inviluppo multifase (ispirato agli inviluppi del CASIO CZ101) e relativi VCF e VCA
- Un singolo modulo dovrebbe anche bastare per generare suoni e inviluppi di uno strumento di tipo "parafonico" a 4 voci con 2 DCO/voce (utilizzando RP2350)
  
  ### SEZIONI CIRCUITALI
  - **Encoder di Tastiera:** Controllata da ATmega328 per la scansione della matrice di keybed (Fatar), rilevamento dinamica, aftertouch ed eventuali controlli di tastiera (pitch wheel). 
  - **Interfaccia comandi:** Con o senza mocrocontrollore dedicato, in base alla complessità e tipologia dei comandi da gestire. Al fine di mantenere la compatibilità e intercambiabilità delle sezioni circuitali (per realizzazione versioni diverse di strumenti) ha comunque più senso utilizzare un microcontrollore dedicato anche per le configurazioni più semplici (visto il costo irrisorio).
  - **Main Board:** Sezione di controllo generale dello strumento,del routing dei moduli voce, della comunicazione con l'esterno (MIDI, CV, SYNC), ecc... 

## 

