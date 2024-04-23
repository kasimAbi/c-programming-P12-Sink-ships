/**********************************************************/
/* Autor: Kasim Mermer                                    */
/* Datum: 25.12.2016									  */
/* Projekt: P12											  */
/* Beschreibung: Schiffe versenken						  */
/**********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<time.h>

// Definitionen
#define GROESSE 10

// Funktionsdeklarationen
int pruefen(char[GROESSE]);
int** array_setzen(int**, int, int);
void array_ausgeben(int**, int, int);
int** schiffe_setzen(int**, int, int);
int zahl_eingabe();
int** array_verdecken(int**, int, int);
int** verdeckt_eingeben(int**, int** , int, int);
void spielen(int**, int**, int, int);

// hauptfunktion
int main(void)
{	// Deklarationen/ Initialisierungen.
	srand(time(NULL));
	int beenden = 0, zeile = 0, spalte = 0, aufhalten = 0;
	int **feld = 0;
	int **feld2 = 0;
	int index = 0, index2 = 0;
	// endlosschleife. solange beenden ungleich 1 ist wird das programm nciht beendet.
	while (beenden != 1)
	{
		printf("Zeilenanzahl eingeben(min. 10/max 20):\t");
		// funktionsaufruf für die zeilen
		zeile = zahl_eingabe();
		// kontrolliert ob der wert im gültigen bereich ist
		if (zeile > 9 && zeile < 21)
		{
			printf("Spaltenanzahl eingeben(min. 10/max 40):\t");
			// funktionsaufruf für die spalten
			spalte = zahl_eingabe();
			// kontrolliert ob der wert im gültigen bereich ist
			if (spalte > 9 && spalte < 41)
			{
				// Funktionsaufrufe
				feld = array_setzen(feld, zeile, spalte);
				feld2 = array_setzen(feld, zeile, spalte);
				feld = array_verdecken(feld, zeile, spalte);
				feld2 = array_verdecken(feld2, zeile, spalte);
				feld2 = schiffe_setzen(feld2, zeile, spalte);
				spielen(feld, feld2, zeile, spalte);
				// löscht die addressen die der pc für das programm genutzt hat. das heißt sie werden geleert und können für was
				// anderes genutzt werden.
				free(feld);
				free(feld2);
			}
			// fehlerausgabe der spalten
			else
			{
				printf("Fehler bei der Spaltenangabe\n");
			}
		}
		// fehlerausgabe der zeilen
		else
		{
			printf("Fehler bei der Zeilenangabe\n");
		}
		printf("\nwenn sie ihr programm beenden moechten,\ndann geben sie bitte eine 1 ein:\t");
		// programm fragt ob das programm beendet werden soll
		beenden = zahl_eingabe();
		// Löscht Commandozeile.
		system("cls");
	}
	// rückgabewert
	return 0;
}

// Das eigentliche Spiel
void spielen(int **feld, int **feld2, int zeile, int spalte)
{
	// Deklatarionen / Initialisierungen
	int auswahl = 0, aufhalten = 0, ende = 0, pruefen = 0, spielzuege = 0, index = 0, index2 = 0;
	// Endlosschleife mit zwei end Bedingungen
	while (auswahl != 2 && ende != 25)
	{
		// Variablen Initialisierungen/ Deklarationen
		ende = 0;
		pruefen = 0;
		system("cls");
		// funktionsaufruf zum ausgeben des arrays feld[][]
		array_ausgeben(feld, zeile, spalte);
		// menue
		printf("\nGeben sie fuer\n (0) spielen\n (1) cheaten\n (2) beenden\ndie enstprechenden Nummern ein:\t");
		// funktionsaufruf für die auswahl
		auswahl = zahl_eingabe();
		if (auswahl == 1)
		{
			system("cls");
			// zum cheaten
			array_ausgeben(feld2, zeile, spalte);
			aufhalten = zahl_eingabe();
		}
		else if (auswahl == 0)
		{
			// zum einfügen der koordinaten. funktionsaufruf für das 2D- feld und dann wird das auch gespeichert.
			feld = verdeckt_eingeben(feld, feld2, zeile, spalte);
			// spielzüge wird hochgezählt
			spielzuege++;
			// Kontrolliert ob alle Schiffe getroffen wurden.
			for (index = 0; index < zeile; index++)
			{
				for (index2 = 0; index2 < spalte; index2++)
				{
					if (feld[index][index2] == 6)
					{
						// wieviele schiffe getroffen wurden. also 1 schiff sind 5 "v's". wenn 25 v's vorhanden sind, dann sind
						// alle schiffe getroffen.
						ende++;
					}
					// für den seltenen fall das es nur 4 schiffe in dem spielfeld gibt, wird nochmal geprüft. 1 ist ein schiffsteil.
					if (feld2[index][index2] == 1)
					{
						pruefen++;
					}
				}
			}
			// Wenn alle Schiffe versenkt wurden, dann verabschiedet sich das Programm.
			if (ende == 25)
			{
				printf("Herzlichen Glueckwunsch. Sie haben nun alle Schiffe versenkt.\nDafuer haben sie nur %i Spielzuege benoetigt.\nSie duerfen nun das Spiel von vorn starten.\n\n", spielzuege);
			}
			// wenn 4 schiffe versenkt wurden und es keine weiteren schiffe mehr vorhanden sind
			else if (ende == 20 && pruefen == 20)
			{
				printf("Herzlichen Glueckwunsch. Sie haben nun alle Schiffe versenkt.\nDafuer haben sie nur %i Spielzuege benoetigt.\nSie duerfen nun das Spiel von vorn starten.\n\n", spielzuege);
				// ende ist die endbedingung.
				ende = 25;
			}
		}
		// fehlerausgabe
		else if (auswahl < 0 || auswahl > 2)
		{
			printf("Sie haben etwas falsches eingegeben.\n\n");
			// um das programm vor dem schnellen beenden aufzuhalten
			aufhalten = zahl_eingabe();
			system("cls");
		}
		else
		{
			// wenn der user das programm beendet hat
			printf("\nIhre Spielzuege: %i", spielzuege);
			printf("\n\n\n\nDas Programm startet von vorne wenn sie nciht die 1 eingeben.\n");
		}
	}
}

// Zur Eingabe der Zahlen.
int zahl_eingabe(void)
{
	// Array/ Variablen		Deklarationen/ Initalisierungen
	char eingabe[GROESSE] = { 0 };
	int wert = 0;
	// Array eingabe als zeichenkette
	fgets(eingabe, GROESSE, stdin);
	// funktionsaufruf
	wert = pruefen(eingabe);
	// wenn wert = 1
	if (wert == 1)
	{
		// dann wandelt das programm die eingabe(string) in einen integer wert um und speichert es in die Variable wert ab.
		wert = atoi(eingabe);
	}
	// gibt dann wert zurück
	return wert;
}

// setzt das zweiDimensionale Array zusammen und gibt es dann zurück.
int** array_setzen(int **feld, int zeile, int spalte)
{
	// Variablen Deklaration/ Initialisierung
	int index = 0;
	// setzt zeilenanzahl als pointer von feld
	feld = (int**)malloc(zeile * sizeof(int*));
	for (index = 0; index < zeile; index++)
	{
		// anschließend gibt er allen zeilen eine anzahl von integer größen bzw. werten.
		feld[index] = (int*)malloc(spalte * sizeof(int));
	}
	// gibt dann feld überarbeitet zurück
	return feld;
}

// setzt einfach alle koordinaten auf 5. 5 steht für freies feld.
int** array_verdecken(int **feld, int zeile, int spalte)
{
	// Variablen Deklaration/ Initialisierungen
	int index = 0, index2 = 0;
	for (index = 0; index < spalte; index++)
	{
		for (index2 = 0; index2 < zeile; index2++)
		{
			feld[index2][index] = 5;
		}
	}
	// anschließend gibt er feld zurück
	return feld;
}

// funktion:
// der nutzer gibt die koordinaten für das verdeckte spielfeld ein.
int** verdeckt_eingeben(int **feld, int **feld2, int zeile, int spalte)	
{
	// Variablen Deklarationen/ Initialisierungen
	int index = 0, index2 = 0, wert_zeile = 0, wert_spalte = 0, ende = 0;

	// Endlosschleife
	while (ende != 1)
	{
		printf("Geben sie die Koordinaten fuer die Zeile ein:\t");
		// funktionsaufruf
		wert_zeile = zahl_eingabe();
		// solange kein gültiger wert eingegeben wurde von dem nutzer
		while (wert_zeile > zeile || wert_zeile <= 0)
		{
			printf("Zahl erneut eingeben fuer Zeile:\t");
			// funktionsaufruf
			wert_zeile = zahl_eingabe();
		}
		printf("Geben sie nun die Koordinaten fuer die Spalte ein:\t");
		// funktionsaufruf
		wert_spalte = zahl_eingabe();
		// solange kein gültiger wert eingegeben wurde von dem nutzer
		while (wert_spalte > spalte || wert_spalte <= 0)
		{
			printf("Zahl erneut eingeben fuer Zeile:\t");
			// funktionsaufruf
			wert_spalte = zahl_eingabe();
		}
		// löscht commandozeile
		system("cls");
		// weil die arrays ab 0 beginnen
		wert_zeile--;
		wert_spalte--;
		// überprüft ob der wert schon einmal eingegeben wurde
		if (feld[wert_zeile][wert_spalte] == 5)
		{
			// wenn ja wird ende auf 1 gesetzt und die endlosschleife für die erste while schleife wird verlassen.
			ende = 1;
		}
		// wenn nciht dann kommt eine fehlermeldung und der user muss die koordinaten erneut eingeben
		else
		{
			system("cls");
			// damit der user weiß welche koordinaten fehlen.
			array_ausgeben(feld, zeile, spalte);
			printf("\nSie haben bereits genutze Koordinaten eingegeben.\nGeben sie andere Koordinaten ein.\n\n");
		}
	}
	// überprüft ob es sich bei den eingegebenen koordinaten ein schiff vorhanden war
	if (feld2[wert_zeile][wert_spalte] == 1)
	{
		// wenn ja wird aus der 1 eine 4. 4 bedeutet bei mir: schiff getroffen
		feld[wert_zeile][wert_spalte] = 4;
	}
	else
	{
		// wenn nein wird aus der 1 eine 3. 3 bedeutet bei mir: kein schiff dort vorhanden
		feld[wert_zeile][wert_spalte] = 3;
	}
	// ist dafür da, dass wenn ein schiff 5 mal getroffen wurde, das in dem Programm als versenkt gezeigt wird. 6 bedeutet bei mir
	// versenkt. für versetzt wird dann in der commandozeile ein V gezeigt.
	index2 = 0;
	// für spalten
	for (index = 0; index < spalte; index++)
	{
		// überprüft ob ein treffer vorliegt
		if (feld[wert_zeile][index] == 4)
		{
			// wenn ja wird index2 hochgezählt.
			index2++;
			// wenn index2 5 mal hintereinander hochgezählt wurde, wird bei den koordinaten die 4 mit einem 6 überschrieben. 6 = versenkt (V).
			if (index2 == 5)
			{
				for (index2 = 0; index2 < 5; index2++)
				{
					feld[wert_zeile][(index - 4) + index2] = 6;
				}
			}
		}
		// andernfalls wird index2 zurückgesetetzt.
		else
		{
			index2 = 0;
		}
	}
	// ist dafür da, dass wenn ein schiff 5 mal getroffen wurde, das in dem Programm als versenkt gezeigt wird. 6 bedeutet bei mir
	// versenkt. für versetzt wird dann in der commandozeile ein V gezeigt.
	index2 = 0;
	// für zeilen
	for (index = 0; index < zeile; index++)
	{
		// überprüft ob ein treffer vorliegt
		if (feld[index][wert_spalte] == 4)
		{
			// wenn ja wird index2 hochgezählt.
			index2++;
			// wenn index2 5 mal hintereinander hochgezählt wurde, wird bei den koordinaten die 4 mit einem 6 überschrieben. 6 = versenkt (V).
			if (index2 == 5)
			{
				for (index2 = 0; index2 < 5; index2++)
				{
					feld[(index - 4) + index2][wert_spalte] = 6;
				}
			}
		}
		// andernfalls wird index2 zurückgesetetzt.
		else
		{
			index2 = 0;
		}
	}
	// feld wird zurückgegeben.
	return feld;
}

// funktion
void array_ausgeben(int **feld, int zeile, int spalte)
{
	// variablen Deklarationen/ Initialisierungen
	int index = 0, index2 = 0;
	printf("\n\n\t");
	// die zeilen werden hier in die commandozeile eingefügt. dient dazu dem nutzer mit den koordinaten zu helfen.
	for (index = 0; index < zeile; index++)
	{
		if (index < 9)
		{
			printf("  %i", index + 1);
		}
		else
		{
			// macht ein leerzeichen damit die zahlen in der commandozeile auch sich anpassen.
			printf(" %i", index + 1);
		}
	}
	printf("\n\n");
	// überprüft den gesamten array
	for (index = 0; index < spalte; index++)
	{
		// für spalten koordinaten. soll wie oben die zeilen hier die spalten zählen und dem nutzer zeigen
		printf("%i\t", index + 1);
		for (index2 = 0; index2 < zeile; index2++)
		{
			if (feld[index2][index] == 1)	// vorhandene Schiffe	1 = x
			{
				printf("  x");
			}
			if (feld[index2][index] == 2)	// vorhandene Schiffe	2 = -
			{
				printf("  -");
			}
			if (feld[index2][index] == 3)	// Wenn kein treffer	3 = O
			{
				printf("  O");
			}
			if (feld[index2][index] == 4)	// Bei einem Treffer	4 = T
			{
				printf("  T");
			}
			if (feld[index2][index] == 5)	// Nichts vorhanden		5 = .
			{
				printf("  .");
			}
			if (feld[index2][index] == 6)	// Versenkte Schiffe	6 = V
			{
				printf("  V");
			}
		}
		printf("\n");
	}
}

// funktion
int** schiffe_setzen(int** feld, int zeile, int spalte)
{
	//Variablen Deklarationen/ Initialisierungen
	int index = 0, index2 = 0, index3 = 0, wert = 0, fertig = 0, zeile_setzen = 0, spalte_setzen = 0;

	// 5 schiffe werden gesetzt.
	for (fertig = 0; fertig < 5; fertig++)
	{
		// entscheidet ob waagerecht oder senkrecht gesetzt wird.
		wert = rand() % 2;
		// wert = 1;	// zur Kontrollzwecke falls 5 Schiffe nciht passen.
		if (wert == 0)
		{
			// wo das Schiff anfaengt.
			zeile_setzen = rand() % zeile;
			spalte_setzen = rand() % spalte;
			// -5 wegen den Anzahl von den Bild- Speichern von den Schiffen
			if (zeile_setzen > zeile - 5)		
			{
				// Damit die Schiffe nciht die Grenze überschreiten
				zeile_setzen = zeile_setzen - 5;		
			}
			// damit die Schiffe die sicherheitsgrenzen und auf ein anderes schiff nciht gesetzt werden können
			for (index = zeile_setzen; index < zeile_setzen + 5; index++)
			{
				for (index = zeile_setzen; index < zeile_setzen + 5; index++)
				{
					if (feld[index][spalte_setzen] == 1 || feld[index][spalte_setzen] == 2)
					{
						// eine gültigkeitsbedingung damit man weiß ob da was gesetzt wurde.
						index2 = 1;
					}
				}
				// wenn die obige bedingung erfüllt ist, also die schiffe sich nciht überschneiden oder sicherheitsgrenze
				// nciht üebrschritten wurde, dann führt das programm die if- bedingung aus.
				if (index2 == 0)
				{
					// setzt die sicherheitsgrenzen und das schiff ein
					for (index = zeile_setzen; index < zeile_setzen + 5; index++)
					{
						// 1 soll heißen das dass schiff gesetzt ist. also ein teil des schiffes von 5
						feld[index][spalte_setzen] = 1;
						// überprüft die randbedingung
						if (spalte_setzen != 0);
						{
							feld[index][spalte_setzen - 1] = 2;
						}
						// überprüft die randbedingung
						if (spalte_setzen < spalte - 1)
						{
							feld[index][spalte_setzen + 1] = 2;
						}
						// überprüft die randbedingung
						if (zeile_setzen != 0)
						{
							feld[zeile_setzen - 1][spalte_setzen] = 2;
						}
						// überprüft die randbedingung
						if (zeile_setzen + 5 < zeile && index == zeile_setzen + 4)
						{
							feld[zeile_setzen + 5][spalte_setzen] = 2;
						} 
					}
				}
				// wenn die bedingung für die if- bedingung nicht erfüllt ist und index2 = 1 ist.
				else
				{
					index2 = 0;
					fertig--;
				}
			}
		}
		// Hier beginnt fuer die Senkrechten Schiffe
		else
		{
			// wo das Schiff anfaengt.
			zeile_setzen = rand() % zeile;
			spalte_setzen = rand() % spalte;
			// -5 wegen den Anzahl von den Bild- Speichern von den Schiffen
			if (spalte_setzen > spalte - 5)
			{
				spalte_setzen = spalte_setzen - 5;
			}
			// zur kontrolle ob die stellen besetzt sind.
			for (index = spalte_setzen; index < spalte_setzen + 5; index++)
			{
				if (feld[zeile_setzen][index] == 1 || feld[zeile_setzen][index] == 2)
				{
					// eine gültigkeitsbedingung damit man weiß ob da was gesetzt wurde.
					index2 = 1;		
				}
			}
			if (index2 == 0)
			{
				for (index = spalte_setzen; index < spalte_setzen + 5; index++)
				{
					// 1 soll heißen das dass schiff gesetzt ist. also ein teil des schiffes von 5
					feld[zeile_setzen][index] = 1;
					// überprüft die randbedingung
					if (zeile_setzen != 0)
					{
						feld[zeile_setzen - 1][index] = 2;
					}
					// überprüft die randbedingung
					if (zeile_setzen < zeile - 1)
					{
						feld[zeile_setzen + 1][index] = 2;
					}
					// überprüft die randbedingung
					if (spalte_setzen != 0)
					{
						feld[zeile_setzen][spalte_setzen - 1] = 2;
					}
					// überprüft die randbedingung
					if (spalte_setzen + 5 < spalte && index == spalte_setzen + 4)
					{
						feld[zeile_setzen][spalte_setzen + 5] = 2;
					}
				}
			}
			// wenn die bedingung für die if- bedingung nicht erfüllt ist und index2 = 1 ist.
			else
			{
				index2 = 0;
				fertig--;
			}
		}
		// counter damit das programm nciht zu einem logischen fehler kommt
		index3++;
		// der counter überschritten, bedeutet das kein 5.tes Schiff mehr passt und das programm verlässt nun die funktion.
		if (index3 == 1000)
		{
			printf("\n\n5 Schiffe passen nciht rein.\n\n");
			fertig = 5;
		}
	}
	// feld wird zurückgegeben
	return feld;
}

// funktionsaufruf für pruefen
int pruefen(char eingabe[GROESSE]) {		// ein string wurde übergeben. ein integer wert wird übergeben
	int laenge = 0, fehler = 0, index = 0;	// initialisierungen
	laenge = strlen(eingabe);		// um herauszufinden wie groß der string ist
	if (eingabe[0] == '+') {		// überprüft ob ein + am anfang steht um es abzufangen
		laenge -= 2;		// wenn ja dann dekrementiert er die länge um 2
		for (index = 0; index < laenge; index++) {		// dient dazu um den + weg zu machen und um die zahlen zu vertauschen
			eingabe[index] = eingabe[index + 1];		// tauscht den ersten wert des arrays mit dem nächsten
			eingabe[index + 1] = 0;		// setzt den nächsten wert des arrays auf 0
		}
	}
	else {		// wenn die obige bedingung nicht erfüllt wurde dann führt er das aus
		laenge -= 1;	// länge wird um 1 dekrementiert. (länge--)
	}
	for (index = 0; index < laenge; index++) {		// dient dazu um alle string- zeichen zu überprüfen ob auch alle zahlen sind
		if (isdigit(eingabe[index]) == 0) {	// wenn eine 0 zurückgegeben wurde(also false) dann ist die stelle des arrays KEINE zahl und
			fehler++;		// die variable fehler wird incrementiert
		}
	}
	index = 45;		// index wird auf 45 gesetzt. 45 ist die Fehlereingabe. weil alles über 40 ein ungueltiger wert ist.
	if (fehler == 0) {		// wenn fehler = 0 ist dann führt er die schleife aus
		index = 1;		// wandelt den string in einen integer wert um und setzt es mit index gleich
	}
	fehler = 0;	// setzt fehler = 0
	return index;	// gibt index wieder zurück
}			// ende........