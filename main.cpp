#include <iostream>


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
    private:
        string password;
        bool adopter = false;
};

class Species{
    public:
        string name;
};

class Animal {
    public:
        string name;
        Species species;
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
    User currentUser;
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

        if(menu == "login"){
            printf("Kérlek add meg a felhasználónevedet és jelszavadat!");

        }
        
        if(menu == "register"){

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

        if(menu == "log_out"){

        }

        if(menu == "applying_to_internship"){

        }


        //global actions
        if(menu == "animals"){

        }

        if(menu == "exit"){
            run = false;
        }

    }
}