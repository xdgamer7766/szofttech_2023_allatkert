#include <iostream>


using namespace std;




int main()
{
    bool run = true;
    string menu = "main_unregistered";
    string userInput = ""; 
    while(run){
            //unregistered user actions 
        if(menu == "main_unregistered"){
            printf("1. Belépés\n2. Regisztrálás\n3. Állatok megtekintése\n4. Kilépés a programból\n");
        }

        if(menu == "login"){

        }
        if(menu == "register"){

        }


            //registered user actions
        if(menu == "main_logged_in"){
            printf("1. Kilépés\n2. Jelentkezés gyakorlatra\n3. Állatok megtekintése\n4. Kilépés a programból\n");
            
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