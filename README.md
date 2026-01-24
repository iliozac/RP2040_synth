# RP2040_synth
Progetto di sviluppo di un Synth ibrido digitale/analogico con generazione dei suoni tramite DCO controllati da microcontrollori RP2040

## ARCHITETTURA GENERALE HW
- La struttura è di tipo "modulare" e in questa prima versione può ospitare un numero massimo di 8 moduli voce connessi su un bus parallelo proprietario.
- L'HW a livello schematico è organizzato a "sezioni circuitali" separate, connesse tra loro tramite bus seriali (ttl Midi, I2C, SPI, ecc...). In fase di ingegnerizzazione si può decidere se realizzare PCB separate (una per ogni sezione), interconnesse tramite cablaggi o raggruppare più sezioni su singole PCB per ottimizzare i costi di produzione.
- Ogni modulo voce può controllare un massimo di 6 DCO ibridi, 2 DCO Wave Table, 2 LFO e 3 generatori di inviluppo multifase (ispirato agli inviluppi del CASIO CZ101) e relativi VCF e VCA
- Un singolo modulo dovrebbe anche bastare per generare suoni e inviluppi di un eventuale strumento "parafonico" a 4 voci con 2 DCO/voce (utilizzando RP2350)
  
  ### SEZIONI CIRCUITALI
  - **Encoder di Tastiera:** Controllata da ATmega328 per la scansione della matrice di keybed (Fatar), rilevamento dinamica, aftertouch ed eventuali controlli di tastiera (pitch wheel). 
  - **Interfaccia comandi:** Con o senza mocrocontrollore dedicato, in base alla complessità e tipologia dei comandi da gestire. Al fine di mantenere la compatibilità e intercambiabilità delle sezioni circuitali (per realizzazione versioni diverse di strumenti) ha comunque più senso utilizzare un microcontrollore dedicato anche per le configurazioni più semplici (visto il costo irrisorio).
  - **Main Board:** Sezione di controllo generale dello strumento,del routing dei moduli voce, della comunicazione con l'esterno (MIDI, CV, SYNC), ecc... 

## ORGANIZZAZIONE SVILUPPO FW
- Il Fw viene sviluppato e testato per ogni modulo o sezione circuitale procedendo per step in modo da testare singolarmemnte i moduli e procedere progressivamente allo sviluppo.
- l'ordine propoosto per lo sviluppo dei moduli dovrebbe essere:
    1. Fw ATmega328 per sezione scansione keybed con dinamica e comunicazione seriale (ttl Midi).
    2. Fw RP2040/RP2350 per moduli voce, incluso il routing interno al singolo modulo.
    3. Fw RP2040/RP2350 per routing moduli voci, gestione effetti generali (riverberi, ecc...) e comunicazione con esterno (Midi, Cv, Sync)
       

