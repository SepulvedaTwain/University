Εργασία 1.
Ιωάννης Τασσόπουλος Α.Μ.:1115201500155

Δομές: Έχουμε την ενα hashtable όπου το κάθε bucket του έχει μια λίστα απο buckets που μεσα αυτα τα buckets εχουν
τα info ανάλογα με την βάση και έναν pointer για το επόμενο bucket.
DataBase: σε αυτην την δόμη βάζω τους Users, ο καθε user εχει μια λίστα με τα bitcoin που έχει(αν έχει).

BitcoinTreeBase: σε αυτην την βάση βάζουμε τα bicoins, το καθε bitcoin δείχνει σε ενα δέντρο το οποίο μεγαλώνει
με τα transactions αν συμμετέχει το Bitcoin αυτό.

Sender/Receiver:σε αυτες τις βάσεις βαζουμε τους sender/receiver απο τα transactions, καθε sender/receiver έχει
μια λίστα απο transactionNodes όπου αυτά περιέχουν τους pointers στα nodes τως δέντρων των bitcoin που
χρησιμοποιήθηκαν.

TransBase(TransactionBase):σε αυτην την λίστα βάζω τα transactionId(transId) για να μπορώ να κανω έλενχο. 
Επίσης κάθε transId περιέχει μια λίστα απο τα bitcoin που χρησιμοποιηθηκαν για το transaction

Συναρτήσεις: Όλες οι βάσεις λειτουργούν με τον ίδιο τρόπο για τα insert, find, is_Exist. Έχω κάνει και συναρτήσεις
που επιστέφουν το ποσό που έχει ο user, το bitcoin, o sender κτλ.

Date:για τα date έκανα μια class Date και μια Time όπου αναπαρηστούν τις ημερομινίες

Μain: στην main καλούμε μια συνάρτηση που ελένχει αν δώθηκαν ολα τα στοιχεία
μετά καλώ τις συναρτήσεις που διαβάζουν τα files και μετα σε ενα while έχω ένα απλό interface για τον χρήστη

Transaction: δεχεται τον sender,receiver,το ποσο, το date(ειτέ αν υπάρχει ειτέ το δικό μας),δυο λίστες, και τις βάσεις που 
χρειάζονται. Βλέπει αν υπάρχουν οι user μετά αν ο sender έχει το ποσό(έλενχος για το date γινεται πριν την καλέσουμε)
και μετα παει στα bitcoin του sender (αν εχει το ποσό) και ανάλογα με το αν έχει λεφτά στο bitcoin το 
χρησιμοποιεί ή πάει στο επόμενο. Μετά βάζει τα bitcoin στον receiver αν δεν τα εχει( το πόσο είναι το balance
του user στο bitcoin αυτό το βλέπουμε από το δέντρο του bitcoin).Στις λίστες βάζω τους pointers των node 
των δέντρων που χρειάστηκαν και τα bitcoin που χρησιμοποιήθηκαν.

FindEarnings/Payments: παώ στο tranactionNodeList του user στην sender/receiverBase και βλέπω το ποσό bitcoin πήρε/έδωσε
και μετά για κάθε transaction κάνω print το transaction αυτό απο την transBase που το έχει μέσα

walletStatus: απλά επιστρέφει το totalAmount του χρήστη(το οποίο με κάθε transaction ενημερώνεται)

bitCoinStatus: στην BitcoinTreeBase έχουμε εναν counter στο πόσα transaction έχει βρεθέι το Bitcoin, το αρχικό πόσο
είναι στο root, και το unspend ποσό ειναι στό πιο δεξί leaf του δέντρου (αν είναι ο ίδιος user με το root)

traceCoin: ψάχνουμε όλοι την transBase στις λιστες με τα usedBitcoins και σε όποιο transaction έχει υπάρξει
το κανουμε print

***Σημαντικό***

Υπάρχουν μερικα Bugs στην requestTransaction(αλλα γίνεται κανονικά όταν δίνεται ημερομινία) και για κάποιο λογο θέλει ενα " " στο τέλος, το ίδιο και για 
της FindEarnings με το κενό. Έχω ενα θέμα με το πως έκανα το Date και δεν προλαβα να το κάνω debug. Πέρα από αυτά
ΟΛΑ τα υπόλοιπα τρεχουν κανονικά και χωρίς κανένα θέμα.


Οπως και δεν έκανα την requestTransactions για inputs και inputFile για τον ίδιο λόγο με τα dates του requestTransaction.
