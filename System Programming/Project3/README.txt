Ιωαννης Τασσόπουλος sdi1500155

PROJECT3:
Server: Στον server έχω δημιουργήσει 2 λίστες, μια για του clients και μια για τα threads. Αρχικά διαβάζουμε τα arguments που δίνει ο 
χρήστης, μετά δημιουργούμε το access point του σαν server και μέσα σε ενα while περίμενουμε τους clients. Μόλις γίνει accept το connection
τοτε ο server καλεί το log_on thread. Σε αυτό το thread κάνει read για να διαβάσει τι έχει στείλει ο client.
Aν έχει στείλει LOG_ON τότε τον βάζει στην λίστα με τους clients και περιμένει με ενα read ώστε να διαβάσει την 
GET_CLIENT_LIST και μετά ο server βάζει σε ένα buffer όλους τους client που έχει στην λίστα του και τους κάνει write
στον client.Μέτα από αυτό ο server στέλνει σε όλους τους άλλους client που έχει στην λίστα του, κάνοντας connect
στο access point τους, ότι μπήκε ένας νέος client στέλνοντας USER_ON. Μετά ο server ξαναπεριμένει στο while για νέους client
ή για κάποιον client να κάνει LOG_OFF που τότε o server τον "κάνει inactive" στην λίστα και στέλνει σε όλους τους 
υπόλοιπους client που έχει στην λίστα ένα USER_OFF. Τέλος όταν πατάμε ctrl+C τότε κάνουμε pthread_join και ελευθερώνουμε
το mutex(Που το χρησιμοποιούμε όταν πειράζουμε την λίστα με τους clients) και κάνουμε pthread_exit(NULL).

Client: Στον client υπάρχουν 3 λίστες, μία για τους client, μία για τον κυκλικό buffer και μία για το dir του client. Αρχικά διαβάζουμε τα arguments
που δίνει ο χρήστης, μετά κάνουμε connect στον server για να κάνουμε log_on και μετά ζητάμε την client list του
αφού την πάρουμε βάζουμε τις πληροφορίες μέσα στην client list μας και στον κυκλικό Buffer μετά ανοίγουμε το access point του client ώστε 
να μπορεί να δέχεται από άλλους client connect. Υπάρχουν 4 περιπτώσεις: 1. να στείλει ο server USER_ON οπότε τότε βάζουμε τον νέο 
client στην λίστα μας και στον κυκλικό Buffer. 2.  Ο server να στείλει USER_OFF οπότε τότε τον βγάζουμε απο την client list μας.
3. Να στείλει ένας client το GET_FILE_LIST οπότε τότε ετοιμάζουμε κατάλληλα το write μας με τα στοιχεία τις λίστας που έχουμε για το DIR
και τα στέλνουμε. 4. να μας ρωτά να του δώσουμε εάνα αρχείο, εμείς βλέπουμε αν καταρχάς το version είναι το ίδιο ή όχι(αν είναι το ίδιο απλά
κάνουμε write ότι FILE_IS_UP_TO_DATE) και μετά ανάλογα του στέλνουμε το νέο version με τα bytes του αρχείου(δυστυχώς δεν πρόλαβα να υλοποιήσω
όλη την διαδικασία της 4.)
Ενώ το main thread κάνει αυτά o client όταν βλέπει ότι υπάρχει κάτι μέσα στον buffer πράττει ανάλογα και κάνει connect με τους άλλους clients
(όπου τους διαβάζει από τον κυκλικό buffer)
Τέλος όταν πατάμε ctrl+c στέλνουμε στον server LOG_OFF και μετά κάνουμε pthread_join τα threads κάνουμε destroy τα Mutex που τα χρησιμοποιούμε
όταν βάζουμε-βγάζουμε κάτι από τον buffer και την client list

Στο τέλος υπάρχουν κάποια reachable blocks που δεν κατάφερα να τα κάνω debug.