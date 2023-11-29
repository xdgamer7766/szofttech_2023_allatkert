#include <iostream>
#include <fstream>


using namespace std;

bool isInt(const string& str)
{
    bool result = true;
    try
    {
        // Convert string to int
        int n = stoi(str);
    }
    catch (const invalid_argument& e)
    {
        result = false;
    }
    return result;
}

class User {
    public:
        string username;
        string password;
        bool adopter = false;
        bool careTaker = false;
        User(string name, string pass){
            username = name;
            password = pass;
        }
};


class Animal {
    public:
        string name;
        string species;
        bool gender;
        int age;
};



int userInputInt(int max){
    string userIn;
    cin >> userIn;
    if(isInt(userIn)){
        int userInInt = stoi(userIn);
        if(0 < userInInt && userInInt < max+1){
            return userInInt;
        }
    }
    return 0;
}

string userInputString(){
    string userIn;
    cin >> userIn;
    return userIn;
}


int main()
{
    bool run = true;
    string menu = "main_unregistered";
    User nullUser = User("null","null");
    User currentUser = nullUser;
    while(run){

        //unregistered user actions 
        if(menu == "main_unregistered"){
            printf("1. Belépés\n2. Regisztrálás\n3. Állatok megtekintése\n4. Kilépés a programból\n");
            switch (userInputInt(4)){
                //login
                case 1:
                    menu = "login";
                    break;
                //register
                case 2:
                    menu = "register";
                    break;
                //listing animals
                case 3:
                    menu = "animals";
                    break;
                //exit the program
                case 4:
                    menu = "exit";
                    break;
                //bad input
                default:
                    printf("Adj meg helyes értéket");
                    break;
            }
        }

        // login
        if(menu == "login"){
            printf("Kérlek add meg a felhasználónevedet és jelszavadat!");

        }

        //register
        if(menu == "register"){
            printf("Kérlek adj meg egy felhasználónevet!\n");
            string username = userInputString();
            printf("Kérlek adj meg egy jelszót\n");
            string password = userInputString();

            //checking if username already exists
            ifstream userFile("user.txt");
            string oneUser;
            bool canCreateUser = true;
            while (getline(userFile, oneUser)){
                int pos = oneUser.find(" ");
                string thisUser = oneUser.substr(0,pos);
                if(username == thisUser){
                    canCreateUser = false;
                }
            }

            userFile.close();

            //if register can happen
            if(canCreateUser){
                ofstream of("user.txt", ios::app);
                currentUser = User(username,password);
                of <<" \n" << username << " " << password << " false false\n";
                printf("Sikeres regisztráció! \n\n");
                //TODO: wait for user input
                menu = "main_logged_in";
                of.close();
            }else{ // if it can't
                printf("Foglalt felhasználónév!\n\n");
            }
        }


        //registered user actions
        if(menu == "main_logged_in"){
            printf("1. Kilépés\n2. Jelentkezés gyakorlatra\n3. Állatok megtekintése\n4. Kilépés a programból\n");
            switch (userInputInt(4)){
                //logout
                case 1:
                    menu = "logout";
                    break;
                //apply for internship
                case 2:
                    menu = "applying_to_internship";
                    break;
                //listing animals
                case 3:
                    menu = "animals";
                    break;
                //exit the program
                case 4:
                    menu = "exit";
                    break;
                //bad input
                default:
                    printf("Adj meg helyes értéket");
                    break;
            }
        }

        //logout
        if(menu == "log_out"){
            currentUser = nullUser;
            menu = "main_unregistered";

        }

        //applying_to_internship
        if(menu == "applying_to_internship"){

        }

        //animal menu
        if(menu == "animals"){

        }

        //exit from the program
        if(menu == "exit"){
            run = false;
        }

    }
}