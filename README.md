# SensorNode
Nella versione 0.2, l'ultima di cui è stato fatto il commit, è cablata nel codice la seguente configurazione del
nodo sensore:

numSensors = 3

-> ID 1: configurato con allarme

-> ID 2: configurato con allarme e confidenzialità

-> ID 3: nè allarme nè confidenzialità

Precisamente, questa configurazione è cablata nella funzione initSensor, locata nel file SensorNode.c.
Quando implementeremo la configurabilità sarà sufficiente sostituire questa funzione con una che prende in 
ingresso una configurazione (già parsata oppure no poi vediamo) e configura il sensore di conseguenza.
