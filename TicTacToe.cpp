#include <iostream>
#include <vector>
#include <string>
using namespace std;

void makeMove(int position, bool& player1, vector<char>& fields) {
    fields.at(position - 1) = player1 ? 'X' : 'O';
}

int toNumber(char c) {
    return int(c) - int('0');
}

bool isCorrect(char eingabe, vector<char>& fields) {

/*
- Eingabe länger als ein Zeichen
- Eingabe war keine Zahl
- Eingabe war eine Null
- Das Feld war schon benutzt
*/

    // if (eingabe.size() > 1) {
    //     cout << "Die Zahl darf nur aus einer Ziffer bestehen!" << endl;
    //     return false;
    // }
    if (!isdigit(eingabe)) {
        cout << "Gib bitte eine Zahl ein!" << endl;
        return false;
    }

    int position = toNumber(eingabe);
    if (position == 0) {
        cout << "Die Zahl 0 ist ungültig. Bitte gib eine andere ein!" << endl;
        return false;
    }
    else if (!isdigit(fields.at(position - 1))) {
        cout << "Das Feld wurde schon verwendet!" << endl;
        return false;
    }

    return true;
}

void draw(vector<char> fields) {
    for (unsigned i = 0; i < fields.size(); i++) {
        cout << fields.at(i);
        if ((i + 1) % 3) {
            cout << "|";
        }
        else {
            cout << endl;
        }
    }
}

bool wonHorizontally(vector<char> fields, char playerChar) {
    for (unsigned int i = 0; i < 3; i++) {
        char curChar = fields.at(i * 3);
        if (!isdigit(curChar) && (curChar == playerChar)) {
            curChar = fields.at(i * 3 + 1);
            if (!isdigit(curChar) && (curChar == playerChar)) {
                curChar = fields.at(i * 3 + 1 + 1);
                if (!isdigit(curChar) && (curChar == playerChar)) {
                    return true;
                }
            }
        }
    }
    return false; 
}

bool wonVertically(vector<char> fields, char playerChar) {
    for (unsigned int i = 0; i < 3; i++) {
        char curChar = fields.at(i);
        if (!isdigit(curChar) && (curChar == playerChar)) {
            curChar = fields.at(i + 3);
            if (!isdigit(curChar) && (curChar == playerChar)) {
                curChar = fields.at(i + 3 + 3);
                if (!isdigit(curChar) && (curChar == playerChar)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool wonDiagonally(vector<char> fields, char playerChar) {
    for (unsigned int i = 1; i < 3; i++) {
        char curChar = fields.at(4);
        if (!isdigit(curChar) && (curChar == playerChar)) {
            curChar = fields.at(4 - (2 * i));
            if (!isdigit(curChar) && (curChar == playerChar)) {
                curChar = fields.at(4 + (2 * i));
                if (!isdigit(curChar) && (curChar == playerChar)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isGameOver(vector<char> fields, bool isPlayer1) {
    char playerChar = isPlayer1 ? 'X' : 'O';
    if (wonHorizontally(fields, playerChar)) {
        cout << "Won Horizontally" << endl;
        return true;
    }
    else if (wonVertically(fields, playerChar)) {
        cout << "Won Vertically" << endl;
        return true;
    }
    else if (wonDiagonally(fields, playerChar)) {
        cout << "Won Diagonally" << endl;
        return true;
    }
    return false;
}

int main() {
    string player1Name;
    string player2Name;
    cout << "Spieler 1 Name: ";
    cin >> player1Name;
    cout << "Spieler 2 Name: ";
    cin >> player2Name;

    bool player1 = true;
    vector<char> fields{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int roundsLeft = 9;

    draw(fields);
    while (roundsLeft) {
        cout << (player1 ? player1Name : player2Name) << " ist dran!" << endl;
        char eingabe;
        do {
            cin >> eingabe;
        } while (!isCorrect(eingabe, fields));

        int position = toNumber(eingabe);
        cout << "position" << position << endl;
        makeMove(position, player1, fields);
        draw(fields);
        if (isGameOver(fields, player1)) {
            break;
        }
        player1 = !player1;
        roundsLeft -= 1;
    }

    if (isGameOver(fields, player1)) {
        cout << (player1 ? player1Name : player2Name) << " has won! Congratulation!" << endl;
    }
    else { 
        cout << "Unentschieden!" << endl;
    }
    return 0;
}