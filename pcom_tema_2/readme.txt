Tema Protocoale de comunicatii 2

Am creat o structura Client pentru a retine informatii despre fiecare client.Astfel,
retin id-ul sau,topicurile la care este abonat,socketul pe care il primeste odata
ce se conecteaza,topicurile la care se face store and forward si mesajele pe care
trebuie sa le primeasca odata ce se conecteaza.

Am creat o structura Message pentru a separa informatiile primite de la clientul
UDP:51 de bytes pentru topic,1 byte pentru tipul de date,1501 pentru continutul
propriu zis al mesajului.

Pentru a trimite mai repede mesajele clientilor,am creat 3 mapuri:unul cu clienti
si cheie dupa id,altul cu clienti si cheia dupa socket si inca unul cu toate 
topicurile de care sunt interesati clienti cu cheia un string cu numele topicului.
Odata ce un client se aboneaza la un topic,acestuia ii este adaugat id-ul in lista
corespunzatoare topicului dorit.Pastrez o lista cu topicurile la care e abonat un
client pentru a putea adauga din nou un client in mapul in functie de socket,atunci
cand acesta se reconecteaza,pe cel vechi fiind nevoit sa il sterg datorita schim-
barii socket-ului.

Cand primesc date de la un client udp,extrag topic-ul si il folosesc in map-ul
available_topics pentru a ajunge la vectorul cu id-ul clientilor abonati la 
acest topic,de unde apoi trimit catre fiecare client conectat.Pentru cei 
neconectati,dar cu optiune store and forward bifata,adaug mesajul in coada
clientilor respecitivi.Odata ce un client se reconecteaza,aceasta coada este
golita si toate mesajele sunt trimise catre el.

Daia Gabriel Petru 321CB 