#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#include <stdlib.h>


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

string appendVector(vector<string> v)
{
    string returnString = "";
    for(int i = 0; i < v.size(); i++){
        returnString = returnString + " " + v.at(i);
    }
    return returnString;
}

class User {
    public:
        string username;
        string password;
        bool adopter = false;
        bool careTaker = false;
        bool intern = false;
        vector<string> adoptedAnimals = {};
        User(string name, string pass){
            username = name;
            password = pass;
        }
        void adoptAnimal(string animalName){
            adoptedAnimals.push_back(animalName);
            adopter = true;
        }
};


class Animal {
    public:
        string name;
        string species;
        string gender;
        int age;
        Animal(string n, string s, bool g, int a){
            name = n;
            species = s;
            age = a;
            if(g) {
                gender = "Male";
            }else{
                gender = "Female";
            }
        }
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
    Animal nullAnimal = Animal("null","null",0,0);
    Animal selectedAnimal = nullAnimal;
    string selectedAnimalName = "";
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
            printf("Kérlek add meg a felhasználónevet!\n");
            string username = userInputString();
            printf("Kérlek add meg a jelszavad\n");
            string password = userInputString();

            //checking if username already exists
            ifstream userFile("user.txt");
            string oneUser;
            bool canLogin = false;
            while (getline(userFile, oneUser)){
                int pos = oneUser.find(" ");
                string thisUser = oneUser.substr(0,pos);
                int pos0 = oneUser.substr(pos + 1).find(" ");
                string thisPassword = oneUser.substr(pos).substr(1,pos0);
                if(username == thisUser && password == thisPassword){
                    canLogin = true;
                    currentUser = User(username,password);
                    if(oneUser.substr(pos0).find("0") == std::string::npos){
                        currentUser.adopter = true;
                        //TODO: add User's adopted animals
                    }
                    if(oneUser.substr(pos0).find("true") != std::string::npos&& oneUser.substr(pos0).find("0") != std::string::npos){
                        currentUser.careTaker = true;
                    }

                }
            }

            if(canLogin){
                cout << "Sikeresen bejelentkezett!\n";
                if(currentUser.careTaker){
                    menu = "careTaker";
                }else{
                    menu = "main_logged_in";
                }
                
            }

            userFile.close();

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
                of <<" \n" << username << " " << password << " false false 0\n";
                printf("Sikeres regisztráció! \n\n");
                menu = "main_logged_in";
                of.close();
            }else{ // if it can't
                printf("Foglalt felhasználónév!\n\n");
            }
        }

        //caretaker
        if(menu == "careTaker"){
            printf("1. Kilépés\n2. Gyakorlatra való jelentkezések átnézése\n3. Állatok megtekintése\n4. Új állat hozzáadása az adatbázishoz\n5. Gyakorlatozók átnézése\n6. Élő videó megtekintése\n7. Kilépés a programból\n");
            switch (userInputInt(6)){
                //logout
                case 1:
                    menu = "logout";
                    break;
                //look at internship offers
                case 2:
                    menu = "internships";
                    break;
                //listing animals
                case 3:
                    menu = "animals";
                    break;
                //listing animals
                case 4:
                    menu = "addAnimal";
                    break;
                //listing interns
                case 5:
                    menu = "interns";
                    break;
                // live videos
                case 6:   
                    menu = "careTakerLive";
                    break;
                //exit the program
                case 7:
                    menu = "exit";
                    break;
                //bad input
                default:
                    printf("Adj meg helyes értéket\n");
                    break;
            }
        }

        //registered user actions
        if(menu == "main_logged_in"){
            printf("1. Kilépés\n2. Jelentkezés gyakorlatra\n3. Állatok megtekintése\n4. Kilépés a programból\n");
            if (currentUser.adopter){
                printf("5. Örökbefogadott állatok megnézése\n");
            }
            switch (userInputInt(5)){
                //logout
                case 1:
                    menu = "log_out";
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
                case 5:
                    if(currentUser.adopter){
                        menu = "adoptedAnimals";
                    }else{
                        printf("Adj meg helyes értéket\n");
                    }
                    break;
                //bad input
                default:
                    printf("Adj meg helyes értéket\n");
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
            printf("Ha szeretnél gyakorlatra jelentkezni add meg a nevedet, ha szeretnél kilépni adj me egy számot\n");
            string userInput = userInputString();
            if(isInt(userInput)){
                menu = "main_logged_in";
            }else{
                ofstream of("intern.txt", ios::app);
                of <<" \n" << currentUser.username << " " << userInput << " false\n";
                printf("Sikeres jelentkezés! \n\n");
                menu = "main_logged_in";
                of.close();
            }
        }

        //reviewing internships
        if(menu == "internships"){}

        //list inters
        if(menu == "interns"){}

        //animal menu
        if(menu == "animals"){
            ifstream animalFile("animal.txt");
            string oneAnimal;
            while (getline(animalFile, oneAnimal)){
                cout << oneAnimal << "\n";
            }
            if(currentUser.careTaker){
                cout << "Ha törölni szeretnél egy állatot add meg a nevét, ha kiakarsz lépni adj egy számot.\n";         
            }else{
                cout << "Ha örökbe szeretnél fogadni egy állatot add meg a nevét, ha kiakarsz lépni adj egy számot.\n";

            }
            string animalName = userInputString();
            if(isInt(animalName)){
                if (currentUser.careTaker){
                    menu = "careTaker";
                }
                menu = "main_logged_in";
            }else{
                if(currentUser.careTaker){
                    menu = "deleteAnimal";
                }else{
                    menu = "adoptAnimal";
                }
                selectedAnimalName = animalName;
            }
            animalFile.close();
        }

        //add animal
        if(menu == "addAnimal"){
            cout << "Add meg az állat nevét";
            string animalName = userInputString();

            ifstream animalFile("animal.txt");
            string oneAnimal;
            bool canAddAnimal = true;
            while (getline(animalFile, oneAnimal)){
                int pos = oneAnimal.find(" ");
                string thisAnimal = oneAnimal.substr(0,pos);
                if(animalName == thisAnimal){
                    canAddAnimal = false;
                }
            }

            animalFile.close();

            if(canAddAnimal){
                ofstream of("animal.txt", ios::app);
                cout << "Add meg az állat faját";
                string species = userInputString();
                cout << "Add meg az állat nemét (1 - Hím / 0 - Nőstény)";
                bool gender = userInputInt(1);
                cout << "Add meg az állat korát";
                int age = stoi(userInputString());
                Animal thisAnimal = Animal(animalName,species,gender,age);
                
                of <<" \n" << thisAnimal.name << " " << thisAnimal.species << " " << thisAnimal.gender << " "<< thisAnimal.age << "\n";
                printf("Állat sikeresen hozzáadva az adatbázishoz! \n\n");
                menu = "careTaker";
                of.close();
            }else{
                printf("Foglalt állatnév!\n\n");
            }
        }

        //delete animal
        if(menu == "deleteAnimal"){
            cout << "Biztos kiszeretnéd törölni az állatot? (1 - igen / 0 - nem)";
            int userInput = userInputInt(1);
            if(userInput == 1){
                ifstream animalFile("animal.txt");
                string oneAnimal;
                int n = 0;
                while (getline(animalFile, oneAnimal)){
                    int pos = oneAnimal.find(" ");
                    string thisAnimal = oneAnimal.substr(0,pos);
                    if(selectedAnimalName == thisAnimal){
                        break;
                    }
                    n++;
                }
                
                ifstream is("animal.txt"); 
                ofstream ofs; 
                ofs.open("temp.txt", ofstream::out);

                char c; 
                int line_no = 1; 
                while (is.get(c)){ 
                    if (c == '\n') 
                    line_no++; 
                    if (line_no != n) 
                        ofs << c; 
                } 
            
                ofs.close(); 
                is.close(); 
                remove("animal.txt"); 
                rename("temp.txt", "animal.txt");
                menu = "careTaker";
            }else{
                menu = "animals";
            }
        }

        //adopt animal
        if(menu == "adoptAnimal"){
            cout << "Biztos örökbeszeretnéd fogadni az állatot? (1 - igen / 0 - nem)\n";
            int userInput = userInputInt(1);
            if(userInput == 1){                
                ifstream is("user.txt"); 
                ofstream ofs; 
                ofs.open("temp.txt", ofstream::out);
                string intern = "false";
                if(currentUser.intern){
                    intern = "true";
                }
                string adoptedAnimals = "0";
                string strNew = currentUser.username + " " + currentUser.password + " false " + intern +" "+  selectedAnimalName;
                if(currentUser.adoptedAnimals.size()){
                    adoptedAnimals = appendVector(currentUser.adoptedAnimals);
                    strNew = currentUser.username + " " + currentUser.password + " false " + intern + " " + adoptedAnimals + " " + selectedAnimalName;

                }
                string strReplace = currentUser.username + " " + currentUser.password + " false " + intern + " " + adoptedAnimals;
                string strTemp;
                while(is >> strTemp){
                    if(strTemp == strReplace){
                        strTemp = strNew;
                    }
                    ofs << strTemp;
                }
            
                ofs.close(); 
                is.close(); 
                remove("user.txt"); 
                 rename("temp.txt", "user.txt");
                menu = "main_logged_in";
            }else{
                menu = "animals";
            }
        }

        //live video of animal
        if(menu == "liveVideo"){
            int randomAction = rand() % 10 +1;
            if(randomAction < 4){
                cout << selectedAnimalName << " éppen alszik\n\n";
            }
            if (randomAction > 4 && randomAction < 7){
                cout << selectedAnimalName << " éppen játszik\n\n";
            }
            if (randomAction > 7){
                cout << selectedAnimalName << " Nem látszik a kamerákon\n\n";
            }

            cout << "Ha kiszeretnél lépni nyomj 1-est. \n Ha szeretnéd még nézni nyomj 0-ást.\n";
            int userInput = userInputInt(1);
            if(userInput){
                if(currentUser.careTaker){
                    menu = "careTakerLive";
                }else{
                menu = "adoptedAnimals";
                }
            }
        }

        //adopted animals
        if(menu == "adoptedAnimals"){
            for (int i = 0; i< currentUser.adoptedAnimals.size(); i++){
                cout << currentUser.adoptedAnimals.at(i) << "\n";
            }
            cout << "Ha szeretnéd valamelyiköjüket élőben látni írd be a nevüket\nHa vissza szeretnél lépni írj be egy számot\n";
            string userInput = userInputString();
            if(isInt(userInput)){
                menu = "main_logged_in";
            }else{
                bool canLook = false;
                for (int i = 0; i< currentUser.adoptedAnimals.size(); i++){
                    if(currentUser.adoptedAnimals.at(i) == userInput){
                        canLook = true;
                    }
                }
                if(canLook){
                    selectedAnimalName = userInput;
                    menu = "liveVideo";
                }else{
                    cout << "Nincsen ilyen nevü örökbefogadott állatod\n";
                }
            }
        }

        //care taker live video with animals
        if(menu == "careTakerLive"){
            ifstream animalFile("animal.txt");
            string oneAnimal;
            while (getline(animalFile, oneAnimal)){
                cout << oneAnimal << "\n";
            }
            cout << "Ha szeretnéd valamelyiköjüket élőben látni írd be a nevüket\nHa vissza szeretnél lépni írj be egy számot\n";
            string userInput = userInputString();
            if(isInt(userInput)){
                menu = "careTaker";
            }else{
                selectedAnimalName = userInput;
                menu = "liveVideo";
            }
        }

        //exit from the program
        if(menu == "exit"){
            run = false;
        }

    }
}