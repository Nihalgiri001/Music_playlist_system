#include <iostream>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <string>
#include <cstdlib>

using namespace std;

struct node 
{
    string s;
    struct node* next;
};

node* list = NULL;
node* last = NULL;

int f = -1, r = -1;
int c = 0;
string shown[30];
string backup[30] = 
{
    "Nenu Nenuga", "Nuvvosthanante", "Konte Chooputho",
    "Unnatundi Gundey", "Ye Swapna Lokala Soundaryarasi", "Light Theesko", "Mari Antaga",
    "Bommanu Geesthey", "Guruvaram", "Mujhe Peene Do", "Tum Hi Ho", "Soch Na Sake", 
    "Jeena Jeena", "Kaise Hua", "Pehle Bhi Main", "Ilahi", "Zindagi Aa Raha Hoon Main",
    "Ae Dil Hai Mushkil", "Tum Se Hi", "Stitches", "Take Me Home Country Roads", "All Star",
    "Another Day of Sun", "Carry On My Wayward Son", "Everyday I Wake Up", "Hey There Delilah",
    "I Know You Know", "I Want It That Way", "Santa Barbara Skies"
};

string stack[30];
int top = -1;
int f1 = -1, r1 = -1;

bool in(string s) 
{
    for (int i = 0; i < 30; i++) 
    {
        if (s == backup[i])
            return true;
    }
    return false;
}

bool dupe(string st)
{
    struct node *temp = list;
    while (temp != NULL)
    {
        if (temp->s == st)
            return true;
        temp = temp->next;
    }
    return false;
}

void clr() 
{
    f1 = -1;
    r1 = -1;
    c = 0;
}

void insert_s(string s) 
{
    if (f1 == -1) 
    {
        f1 = 0;
        r1 = 0;
    } 
    else 
    {
        r1++;
    }
    shown[r1] = s;
}

void isin(string s) 
{
    clr();
    for (int i = 0; i < 30; i++) 
    {
        if (backup[i].find(s) != string::npos) 
        {
            c++;
            insert_s(backup[i]);
            cout << c << " " << backup[i] << endl;
        }
    }
    if (c == 0) 
    {
        cout << "No results found" << endl;
        getch();
    }
}

void push(string s) 
{
    stack[++top] = s;
}

void pop() 
{
    if (top >= 0)
        top--;
}

void display() 
{
    cout << "Search history :-" << endl;
    for (int i = top; i >= 0; i--)
        cout << stack[i] << endl;
    getch();
}

void insert(string a) 
{
    if (!dupe(a))
    {
        node* nn = new node;
        nn->s = a;
        nn->next = NULL;
        if (list == NULL) 
        {
            list = nn;
            last = nn;
        } 
        else 
        {
            last->next = nn;
            last = nn;
        }
    }
    else
    {
        cout << "You can't add the same song" << endl;
        getch();
    }
}

void del(string test) 
{
    node* temp = list;
    node* prev = NULL;
    
    if (temp != NULL && temp->s == test) 
    {
        list = temp->next; 
        delete temp;
        return;
    }

    while (temp != NULL && temp->s != test) 
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) 
        return;

    prev->next = temp->next;
    delete temp;
}

void play() 
{
    node* temp = list;
    if (temp == NULL) 
    {
        cout << "The Playlist is empty" << endl;
        getch();
        return;
    }
    char q;
    while (temp != NULL) 
    {
        string song = temp->s + ".wav";
        PlaySound(song.c_str(), NULL, SND_ASYNC);
        cout << "Playing: " << song << endl;
        cout << "Enter > to forward to the next song, ! to stop: ";
        cin >> q;
        if (q == '!') 
        {
            PlaySound(NULL, 0, 0);
            break;
        }
        temp = temp->next;
        if (temp == NULL && q == '>')
        {
            PlaySound(NULL, 0, 0);
            break;
        }
    }
    r = -1;
    f = -1;
}

void show() 
{
    node* temp = list;
    while (temp != NULL) 
    {
        if (!temp->s.empty()) 
        {
            cout << temp->s << endl;
        }
        temp = temp->next;
    }
}

int main() 
{
    string test;
    int op1, op2, ch,t=0;

    do 
    {
        system("cls");
        cout << "Enter 1 to play the songs" << endl
             << "Enter 2 to Add or delete songs" << endl
             << "Enter 3 to see the search history" << endl
             << "Enter 4 to exit the program" << endl
             << "Your choice: ";
        cin >> op1;
        switch (op1) 
        {
        case 1:
            system("cls");
            show();
            cout << "Enter > to forward to the next song" << endl
                 << "Enter ! to end" << endl;
            play();
            break;
        case 2:
            system("cls");
            if(t==0)
            {
            	for(int i=0;i<30;i++)
            	{
            		cout<<backup[i]<<endl;
				}
				t++;
			}
            cout << "Enter 1 to insert songs" << endl
                 << "Enter 2 to delete songs" << endl
                 << "Your choice: ";
            cin >> op2;
            switch (op2) 
            {
            case 1:
                while (true) 
                {
                    clr();
                    system("cls");
                    test = " ";
                    cout << "Enter the song that you want to play and enter {spacebar} to end" << endl;
                    cout << "Your Choice: ";
                    cin.ignore();
                    getline(cin, test);
                    if (test == " ")
                        break;
                    isin(test);
                    push(test);
                    cout << "Enter the song number from the given list: ";
                    cin >> ch;
                    if (ch > 0 && ch <= c)
                        insert(shown[ch - 1]);
                    else
                        cout << "Insert an appropriate song";
                    getch();
                }
                break;
            case 2:
                cout << "Choose a song to delete" << endl;
                cin.ignore();
                getline(cin, test);
                if (in(test)) 
                {
                    del(test);
                    cout << "Song has been deleted" << endl;
                } 
                else 
                {
                    cout << "Song not present in playlist" << endl;
                }
                getch();
                break;
            default: 
            	cout<<"Enter an appropriate option"<<endl;
            	getch();
            }
            break;
        case 3:
            display();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice" << endl << "Choose again" << endl;
            getch();
        }
    } while (op1 != 4);

    return 0;
}