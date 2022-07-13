#include"lib_reader.h"

int main(){
    cout<<"_____________HE THONG QUAN LY THU VIEN________________"<<endl;
    char option;
    tree_b b = NULL;
    tree_r r = NULL;
    bool check = loadJSON(b);
    cout<<"f"<<endl;
    b = buildTree(b); 
    loadJSON_reader(r);
    showThuVien(b);
    while(option != 'Q')
    {
        cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout<<"Choose your option:\nA.Book\nB.Reader\nQ.Out\nYour option: ";
        cin>>option;
        switch(option){
            case 'A':{
                int option1;
                while(true){
                    cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
                    cout<<"Choose your option:\n1.Add book\n2.Search book\n0.Quit\nYour option: ";
                    cin>>option1;
                    if(option1 == 1){
                        add_b(b);
                        saveJSON(b);
                    }
                    else if(option1 == 2){    
                        Edit(b);
                    }else if (option1 == 0){
                        break;
                    }else{
                        cout<<"Wrong!!!!";
                    }    
                }
                break;
            }
            case'B':
            {   
                int option2;
                while ((true))
                {
                    cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
                    cout<<"Choose your option:\n1.Search Reader\n2.Add Reader\n0.Quit\nYour option: ";
                    cin>>option2;
                    if(option2 == 1){   
                        editReader(b,r);
                    }else if(option2 == 2){
                        add_r(r);
                        saveJSON_reader(r);
                    }else if(option2 == 0){
                        break;      
                    }else{
                        cout<<"Wrong!!!";
                    }
                
                }
                break;
            }
        }
    }
}