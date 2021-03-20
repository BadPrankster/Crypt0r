/*
Projektarbeit im Visual Studio 2019
Lucas Wirz-Vitiuk
Januar bis März 2021
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {

	/*
	TO-DO:
	- Ein- und Ausgabe via Datei
	- Programm wiederholen
	*/

	// Crypt0r V0.8

	// Eingabe-Variabeln definieren
	char select, cipher;
	string input;
	bool check = false;

	// Satzzeichen
	const char punctuation[] = { ' ', '.', ',', ':', ';', '?', '!', '-', '_', '(', ')',
                                     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	// Alphabet definieren
	const char alphabet[] = { ' ', '.', ',', ':', ';', '?', '!', '-', '_', '(', ')',
                                  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                  '\x8E', '\x99', '\x9A',
                                  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                  '\x84', '\x94', '\x81' };

	// Umgedrehtes Alphabet definieren
	const char alphabet_reversed[] = { ' ', '.', ',', ':', ';', '?', '!', '-', '_', '(', ')',
                                           '9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
                                           'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P', 'O', 'N', 'M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A',
                                           '\x99', '\x9A', '\x8E',
                                           'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q', 'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a',
                                           '\x94', '\x81', '\x84' };

	// Morse-Code definieren
	string morse[] = { "/", ".-.-.-", "--..--", "---...", "-.-.-.", "..--..", "-.-.--", "-....-", "..--.-", "-.--.", "-.--.-",
                           "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",
                           ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
                           ".-.-", "---.", "..--" };

	// Trennzeichen definieren
	char delimiter = ' ';

	// Hilfsvariabeln zum Splitten der Eingabe
	vector<string> tokens;
	int pos;
	string token;

	// Hilfsvariabeln für Geheimalphabet
	int x = 0;
	int y = 0;

	// Zählvariable fürs Splitten
	int z = 1;

	// Variabeln für Passworteingabe
	int key;
	string keyword;
	char password[26 * 4];
	char alphabet_secret[sizeof(alphabet)];

	// Variabeln für Schleifen
	int i, j, k, l;

	// Programmbeginn
	while (check == false) {

		// Abfrage zum Ver- oder Entschlüsseln
		cout << endl << "   1  -  Chiffrieren";
		cout << endl << "   2  -  De-Chiffrieren" << endl;
		cout << endl << "   > ";
		cin >> select;

		// Eingabe zusätzlicher Werte verhindern
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		// Fehleingabe verhindern
		if ((select != '1') && (select != '2')) {
			system("cls");
			cout << endl << "   Falsche Eingabe, Bitte wiederholen!" << endl;
		}
		else check = true;
	}

	// Abfrage zur Ver- oder Entschlüsselungsmethode
	check = false;
	while (check == false) {

		cout << endl << "   1  -  ASCII-Code";
		cout << endl << "   2  -  Morse-Code";
		cout << endl << "   3  -  Alphabet umdrehen";
		cout << endl << "   4  -  C\x84sar-Verschl\x81sselung";
		cout << endl << "   5  -  Vigenere-Verschl\x81sselung";
		cout << endl << "   6  -  Passwort-Verschl\x81sselung" << endl;
		cout << endl << "   > ";
		cin >> cipher;

		// Eingabe zusätzlicher Werte verhindern
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		// Fehleingabe verhindern
		if ((cipher != '1') && (cipher != '2') && (cipher != '3') && (cipher != '4') && (cipher != '5') && (cipher != '6')) {
			system("cls");
			cout << endl << "   Falsche Eingabe, Bitte wiederholen!" << endl;
		}
		else check = true;
	}

	if (cipher == '4') {

		// Abfrage für Zahlenschlüssel (Cäsar-Verschlüsselung)
		check = false;
		while (check == false) {

			cout << endl << "   Bitte eine Zahl als Schl\x81ssel f\x81r die C\x84sar-Verschl\x81sselung eingeben" << endl;
			cout << endl << "   > ";
			cin >> key;

			// Fehleingabe verhindern
			if (!cin) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				system("cls");
				cout << endl << "   Falsche Eingabe, Bitte wiederholen!" << endl;
			}
			else {
				check = true;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
		}
	}

	if ((cipher == '5') || (cipher == '6')) {

		// Abfrage für Passwort (Vigenere-Verschlüsselung und Geheimalphabetisierung)
		cout << endl << "   Bitte ein Wort als Schl\x81ssel ";
		if (cipher == '5') cout << "f\x81r die Vigenere-Verschl\x81sselung";
		if (cipher == '6') cout << "f\x81r die Geheimalphabetisierung";
		cout << " eingeben" << endl;
		cout << endl << "   > ";

		if (cipher == '5') getline(cin, keyword);

		if (cipher == '6') {

			cin >> password;

			// Passwort in Geheimalphabet einfügen (Duplikate entfernen)
			for (k = 0; k < sizeof(password); k++) {
				check = true;
				for (l = 0; l < sizeof(alphabet_secret); l++) {
					if (alphabet_secret[l] == password[k]) {
						check = false;
						break;
					}
				}
				if (check) alphabet_secret[k - x] = password[k];
				else x++;
			}

			// Position für den Rest des Alphabets finden
			for (k = 0; k < sizeof(alphabet); k++) {
				for (l = 0; l < sizeof(alphabet_secret); l++) {
					if (alphabet[k] == alphabet_secret[l]) {
						y++;
						break;
					}
				}
			}

			// Rest des Alphabets in Geheimalphabet einfügen
			x = 0;
			for (k = 0; k < sizeof(alphabet); k++) {
				check = true;
				for (l = 0; l < sizeof(alphabet_secret); l++) {
					if (alphabet[k] == alphabet_secret[l]) {
						check = false;
						break;
					}
				}
				if (check) alphabet_secret[k + y - x] = alphabet[k];
				else x++;
			}

			// Eingabe zusätzlicher Werte verhindern
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
	}

	// TO-DO: Abfrage zur Ein- und Ausgabe via Datei
	// Abfrage zur Texteingabe (sowohl unverschlüsselt als auch verschlüsselt)
	cout << endl << endl << "   Text eingeben" << endl << endl << "   > ";

	getline(cin, input);

	if (cipher == '5') {

		// Falls nötig, Passort verlängern (Vigenere-Verschlüsselung)
		while (input.size() >= keyword.size()) {
			keyword += keyword;
		}
	}

	// Verarbeitung und Ausgabe des verschlüsselten Textes
	if (select == '1') {

		cout << endl << endl << "   Der chiffrierte Text lautet: " << endl;
		cout << endl << "   > ";

		// Schleife für jeden Buchstaben der Eingabe
		for (i = 0; i < input.length(); i++) {

			// Eingabe als Zahl darstellen (ASCII-Code)
			if (cipher == '1') {
				cout << int(input[i]) << delimiter;
			}

			if ((cipher == '2') || (cipher == '3') || (cipher == '6')) {

				// Innere Schleife für jeden Buchstaben des Alphabets
				check = false;
				for (j = 0; j < sizeof(alphabet); j++) {

					if (cipher == '2') {

						// Umlaute in Grossbuchstaben umwandeln
						if ((input[i]) == '\x81') (input[i]) = '\x9A';
						if ((input[i]) == '\x84') (input[i]) = '\x8E';
						if ((input[i]) == '\x94') (input[i]) = '\x99';

						// Eingabe zuweisen (Morse-Code)
						if (toupper(input[i]) == alphabet[j]) {
							cout << morse[j];
							break;
						}
					}

					// Eingabe zuweisen (Alphabet umdrehen)
					if (cipher == '3') {
						if (input[i] == alphabet[j]) {
							cout << alphabet_reversed[j];
							check = true;
							break;
						}
					}

					// Eingabe zuweisen (Passwort-Verschlüsselung)
					if (cipher == '6') {
						if (input[i] == alphabet[j]) {
							cout << alphabet_secret[j];
							check = true;
							break;
						}
					}
				}

				// Trennzeichen zwischen Wörter einfügen (Morse-Code)
				if (cipher == '2') {
					if (i < input.length() - 1) cout << delimiter;
				}

				// Eingabe beibehalten, falls diese nicht umgewandelt wurde
				if ((cipher == '3') || (cipher == '6')) {
					if (check == false) cout << input[i];
				}
			}

			if ((cipher == '4') || (cipher == '5')) {

				// Satzzeichen beibehalten
				for (j = 0; j < sizeof(punctuation); j++) {
					if (input[i] == punctuation[j]) cout << input[i];
				}

				if (cipher == '4') {

					// Eingabe umwandeln (Cäsar-Verschlüsselung)
					if (isupper(input[i])) cout << char(((int(input[i]) - 65 + key) % 26) + 65);
					if (islower(input[i])) cout << char(((int(input[i]) - 65 + key - 6) % 26) + 97);
				}

				if (cipher == '5') {

					// Eingabe umwandeln (Vigenere-Verschlüsselung)
					keyword[i] = toupper(keyword[i]);
					if (isupper(input[i])) cout << char(((int(input[i]) + int(keyword[i])) % 26) + 65);
					if (islower(input[i])) cout << char(((int(input[i]) + int(keyword[i]) - 6) % 26) + 97);
				}
			}
		}
	}

	// Verarbeitung und Ausgabe des unverschlüsselten Textes
	if (select == '2') {

		cout << endl << endl << "   Der dechiffrierte Text lautet: " << endl;
		cout << endl << "   > ";

		// Schleife für jeden Buchstaben der Eingabe
		for (i = 0; i < input.length(); i++) {

			// Zählen der Platzhalter
			if ((cipher == '1') || (cipher == '2')) {
				if (input[i] == delimiter) z++;
			}

			if ((cipher == '3') || (cipher == '6')) {

				// Innere Schleife für jeden Buchstaben des Alphabets
				check = false;
				for (j = 0; j < sizeof(alphabet); j++) {

					if (cipher == '3') {

						// Eingabe zuweisen (Alphabet umdrehen)
						if (input[i] == alphabet_reversed[j]) {
							cout << alphabet[j];
							check = true;
						}
					}

					if (cipher == '6') {

						// Eingabe zuweisen (Passwort-Verschlüsselung)
						if (input[i] == alphabet_secret[j]) {
							cout << alphabet[j];
							check = true;
						}
					}
				}

				// Eingabe beibehalten, falls diese nicht umgewandelt wurde
				if (check == false) cout << input[i];
			}

			if ((cipher == '4') || (cipher == '5')) {

				// Satzzeichen beibehalten
				for (j = 0; j < sizeof(punctuation); j++) {
					if (input[i] == punctuation[j]) cout << input[i];
				}

				// Eingabe zurück umwandeln (Cäsar-Verschlüsselung)
				if (cipher == '4') {
					if (isupper(input[i])) cout << char(((int(input[i]) - 65 - key + 2080000000) % 26) + 65);
					if (islower(input[i])) cout << char(((int(input[i]) - 65 - key - 6 + 2080000000) % 26) + 97);
				}

				// Eingabe zurück umwandeln (Vigenere-Verschlüsselung)
				if (cipher == '5') {
					keyword[i] = toupper(keyword[i]);
					if (isupper(input[i])) cout << char(((int(input[i]) - int(keyword[i]) + 26) % 26) + 65);
					if (islower(input[i])) cout << char(((int(input[i]) - int(keyword[i]) + 20) % 26) + 97);
				}
			}
		}

		if ((cipher == '1') || (cipher == '2')) {

			// Splitten der Eingabe
			for (k = 0; k < z; k++) {
				pos = input.find(delimiter);
				token = input.substr(0, pos);
				tokens.push_back(token);
				input.erase(0, pos + 1);
			}

			// Schleife für alle gesplitteten Strings
			for (i = 0; i < z; i++) {

				// String als Buchstabe darstellen (ASCII-Code)
				if (cipher == '1') {
					cout << char(stoi(tokens[i]));
				}

				if (cipher == '2') {

					// Innere Schleife für jeden Buchstaben des Morse-Codes
					for (j = 0; j < (sizeof(morse) / sizeof(string)); j++) {

						// String als Buchstabe darstellen (Morse-Code)
						if (tokens[i].compare(morse[j]) == 0) {
							cout << alphabet[j];
							break;
						}
					}
				}
			}
		}
	}

	// TO-DO: Abfrage zum Wiederholen des Programms
	// Programmende
	cout << endl << endl;
	return 0;
}
