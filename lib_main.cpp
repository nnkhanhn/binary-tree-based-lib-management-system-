#include"lib_reader.h"
int main(){
    cout<<"_____________HE THONG QUAN LY THU VIEN________________"<<endl;
    char option;
    tree_b b = NULL;
    tree_r r = NULL;
    bool check = loadJSON(b);
    cout<<"f"<<endl;
    // b = buildTree(b); 
    loadJSON_reader(r);
    showThuVien(b);
    while(option != 'Q')
    {
        cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout<<"Enter an operation:\nA.Manager\nB.Reader\nQ.Quit\nYour operation: ";
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
                        cout<<"Khong hop le!!\nVui long nhap lai!!";
                    }    
                }
            }
            case'B':
            {   
                int option2;
                while ((true))
                {
                    cout<<"\n\n-------------------------------------------------------------------------------------------------------------------------------------------------\n";
                    cout<<"Choose your option:\n1.Borrow book\n2.Return book\n3.Them nguoi doc\nYour option: ";
                    cin>>option2;
                    if(option2 == 1)
                    {   
                        while(true)
                        {
                            int id;
                            cout<<"nhap ID nguoi doc: ";
                            cin>>id;
                            tree_r a = search_reader(r,id);
                            if(a){      
                                borrow_book(a,b);
                                saveJSON(b);
                                saveJSON_reader(r);
                                break;
                            }else{}
                        }
                

                    }
                    else if(option2 == 2)
                    {
                        while(true)
                        {
                            int id;
                            cout<<"nhap ID nguoi doc: ";
                            cin>>id;
                            tree_r a = search_reader(r,id);
                            if(a){      
                                return_book(a,b);
                                saveJSON(b);
                                saveJSON_reader(r);
                                break;
                            }else{}
                        }

                    }
                    else if(option2 == 3)
                    {
                        add_r(r);
                        saveJSON_reader(r);
                    }
                    else if(option2 == 0)
                    {
                        break;
                    }else{
                        cout<<"Khong hop le!!\nVui long nhap lai!!";
                    }
                
                }
                
               
            }
        }
    }
}