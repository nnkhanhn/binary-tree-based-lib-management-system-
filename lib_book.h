#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/ostreamwrapper.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;
using namespace rapidjson;

int numbook=100;//so sach co san trong kho
int numboo1;
using namespace std;
typedef struct BookInf{
    char name[30];
    char author[30];
    char nxb[30];
    char theloai[30];
    int sotrang;
    int PubYear;
    int Num;
    char vitri[30];
} book;

typedef struct node{
    book c;
    node *left;
    node *right;
}node_b;
typedef node_b* tree_b;

int compare(book a,book b);//so sanh 2 string

void delete_all(tree_b b);//xóa cây

tree_b init(book a);//khởi tạo cây

void insert_b(tree_b &b,book a);//thêm sách/node vào cây

void loadbook(tree_b &b);//tải dữ liệu từ file text vào cây

void add_b(tree_b &b,book a);//thêm sách vào cây 

void save_b(book b);//lưu dữ liệu sách vào file

node_b* search_b(tree_b b,char n[30]);//tìm kiếm sách theo tên





void storeBSTNodes(tree_b root, vector<tree_b> &nodes);//lưu các node vào trong vector
tree_b buildTreeUtil(vector<tree_b> &nodes, int start, int end);//xây dựng cây
tree_b buildTree(tree_b root);//dựng cây nhị phân can bằng


int compare(book a,book b){
    return strcmp(a.name,b.name);
}
void delete_all(tree_b b){
    if(b==NULL) return;
    delete_all(b->left);
    delete_all(b->right);
    delete(b);
}
tree_b init(book a){
    tree_b b = new node_b;
    b->c=a;
    b->left=NULL;
    b->right=NULL;
    return b;
}

void display_book(book b){
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"\n"<<"|"<< left<< setw(10)<<b.name<< left<< setw(10)<< b.author<< left<< setw(15)<< b.nxb  << 
    left<< setw(11)<< b.theloai<< left<< setw(11)<< b.sotrang<< left<< setw(15)<< b.PubYear
    << left<< setw(20)<< b.Num<< left<< setw(10)<< b.vitri<< endl;
}
void display_tree(node_b *b){
    if(b!=NULL){
        display_book(b->c);
        display_tree(b->left);
        //display_book(b->c);
        display_tree(b->right);
    }
}
void showThuVien(tree_b b){
    cout<<"\n\n"<<"--------------------------------------------------------------------DANH SACH THU VIEN--------------------------------------------------------------------";
    cout<<"\n"<< left<< setw(10)<< "|Ten Sach"<< left<< setw(10)<< "|Tac gia"<< left<< setw(15)<< "|Nha xuat ban"
    << left<< setw(11)<< "|The loai"<< left<< setw(11)<< "|So trang"<< left<< setw(15)<< "|Nam xuat ban"<< left<< setw(20)<< "|So sach con lai"<< left<< setw(10)<< "|Vi tri|"<< endl;
    display_tree(b);
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"\n\n";
}


void insert_b(tree_b &b,book a){
    if(b==NULL)
    {
        // cout<<"NULL"<<endl;
        b=init(a);
    }
    else if(compare(b->c,a)==0)
    {
        cout<<"sach nay da co "<<endl;
    }
    else if(compare(b->c,a)>0)
    {
        insert_b(b->left,a);
    }
    else if(compare(b->c,a)<0)
    {
        insert_b(b->right,a);
    }
}


void cinChar(char *a)
{ 
    for(int i=0;; i++)
    {
        *(a+i*sizeof(char))=getchar();
 
        if(*(a+i*sizeof(char))=='\n')
        {
            *(a+i*sizeof(char))='\0';
            break;
        }
 
    }
}
void add_b(tree_b &b){
    book a;
    char k[30];
    cinChar(k);
    cout<<"Ten sach: ";
    cinChar(a.name);
    cout<<"Tac gia: ";
    cinChar(a.author);
    cout<<"Nha xuat ban: ";
    cinChar(a.nxb);
    cout<<"The loai: ";
    cinChar(a.theloai);
    cout<<"So trang: ";
    cin>>a.sotrang;
    cout<<"Nam xuat ban: ";
    cin>>a.PubYear;
    cout<<"So sach con lai: ";
    cin>>a.Num;
    cinChar(k);
    cout<<"Vi tri: ";
    cinChar(a.vitri);
    insert_b(b,a);
}

void vectorData(tree_b b,vector<book> &vtor){
    if(b!=NULL){
        vtor.push_back(b->c);
        vectorData(b->left,vtor);
        vectorData(b->right,vtor);
    }
}

void saveJSON(tree_b b){
    vector<book> vector;
    vectorData(b,vector);
    StringBuffer s;
    PrettyWriter<StringBuffer> writer(s);
    writer.StartArray();
    for(int i=0;i<vector.size();i++){
        writer.StartObject();
        writer.Key("Ten");
        writer.String(vector[i].name);
        writer.Key("Tac gia");
        writer.String(vector[i].author);
        writer.Key("Nha xuat ban");
        writer.String(vector[i].nxb);
        writer.Key("The loai");
        writer.String(vector[i].theloai);
        writer.Key("So trang");
        writer.Int(vector[i].sotrang);
        writer.Key("Nam xuat ban");
        writer.Int(vector[i].PubYear);
        writer.Key("So sach con lai");
        writer.Int(vector[i].Num);
        writer.Key("Vi tri");
        writer.String(vector[i].vitri);
        writer.EndObject();
    }
    writer.EndArray();
    std::ofstream of("data.json");
    of << s.GetString();
}

bool loadJSON(tree_b &b){
    std::ifstream ifs ("data.json");
    if(!ifs){
        cout<<"Hien tai chua co sach trong kho!!!\n";
        return false;
    }    
    IStreamWrapper isw { ifs };
    Document doc {};
    doc.ParseStream( isw );
    for(int i = 0;i < doc.Size();i++){
        book a;
        string s = doc[i]["Ten"].GetString();
        strcpy(a.name, s.c_str());
        s = doc[i]["Tac gia"].GetString();
        strcpy(a.author,s.c_str());
        s = doc[i]["Nha xuat ban"].GetString();
        strcpy(a.nxb,s.c_str());
        s = doc[i]["The loai"].GetString();
        strcpy(a.theloai,s.c_str());
        a.sotrang = doc[i]["So trang"].GetInt();
        a.PubYear = doc[i]["Nam xuat ban"].GetInt();
        a.Num = doc[i]["So sach con lai"].GetInt();
        s = doc[i]["Vi tri"].GetString();
        strcpy(a.vitri,s.c_str());
        insert_b(b,a);
    }
    return true;
}

node_b* search_b(tree_b b,char n[30]){
    if( b == NULL){
        cout<<"Sach khong ton tai trong thu vien!!"<<endl;
        return NULL;
    }
    else
    {
        if(strcmp(b->c.name,n)>0){
            search_b(b->left,n);
        }
        else if(strcmp(b->c.name,n)<0){
            search_b(b->right,n);
        }
        else{
            return b;
        }
    }
}

void edit(node_b *b){
    book a;
    a = b->c;
    cout<<"\nNhap thong tin muon sua: \n";
    char k[30];
    cinChar(k);
    cout<<"Tac gia: ";
    cinChar(a.author);
    cout<<"Nha xuat ban: ";
    cinChar(a.nxb);
    cout<<"The loai: ";
    cinChar(a.theloai);
    cout<<"So trang: ";
    cin>>a.sotrang;
    cout<<"Nam xuat ban: ";
    cin>>a.PubYear;
    cout<<"So sach con lai: ";
    cin>>a.Num;
    cinChar(k);
    cout<<"Vi tri: ";
    cinChar(a.vitri);
    b->c = a;
}

void swapNode(tree_b &x,tree_b &y){
    if(y->left != NULL){
        swapNode(x,y->left);
    }else{
        x->c = y->c;
        x = y;
        y = y->right;
    }
}

void deleteBook(tree_b &b,book t){
    if(b == NULL){
        return;
    }
    else{
        if(compare(b->c,t)>0){
            deleteBook(b->left,t);
        }else if(compare(b->c,t)<0){
            deleteBook(b->right,t);
        }else{
            node_b *x = b;
            if(b->left == NULL){
                b = b->right;
            }else if(b->right == NULL){
                b = b->left;
            }else{
                swapNode(x,b->right);
            }
            delete(x);
        }
    }
    saveJSON(b);
}

void Edit(tree_b& b){
    char k[30];
    cinChar(k);
    while(true){
        char name[30];
        cout<<"Enter book's name: ";
        cinChar(name);
        node_b *book = search_b(b,name);
        if(book){
            cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout<<"       BOOK\n"<<endl;
            cout<<"Ten sach: "<<book->c.name<<endl;;
            cout<<"Tac gia: "<<book->c.author<<endl;
            cout<<"Nha xuat ban: "<<book->c.nxb<<endl;
            cout<<"The loai: "<<book->c.theloai<<endl;
            cout<<"So trang: "<<book->c.sotrang<<endl;
            cout<<"Nam xuat ban: "<<book->c.PubYear<<endl;
            cout<<"So sach con lai: "<<book->c.Num<<endl;
            cout<<"Vi tri: "<<book->c.vitri<<endl;
            int choice;
            while(true){
                cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout<<"You want?\n1.Edit book\n2.Delete book\n0.Quit\nYour choice: ";
                cin>>choice;
                if(choice == 1){
                    edit(book);
                    saveJSON(b);
                    cout<<"Sua thong tin sach thanh cong!!.\n";
                    break;
                }else if(choice == 2){
                    deleteBook(b,book->c);
                    cout<<"Da xoa!!";
                    break;
                }else if(choice == 0){
                    break;
                }
            }
            break;
        }else{
        }
    }
}

void incr_num_book(tree_b &b){
    b->c.Num+=1;
}
void decr_num_book(tree_b &b){
    b->c.Num-=1;
}
void storeBSTNodes(tree_b root, vector<tree_b> &nodes)
{
    // Base case
    if (root==NULL)
        return;
 
    // Store nodes in Inorder (which is sorted
    // order for BST)
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
}
tree_b buildTreeUtil(vector<tree_b> &nodes, int start, int end)
{
    // base case
    if (start > end)
        return NULL;
 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    tree_b root = nodes[mid];
 
    /* Using index in Inorder traversal, construct
       left and right subtress */
    root->left  = buildTreeUtil(nodes, start, mid-1);
    root->right = buildTreeUtil(nodes, mid+1, end);
 
    return root;
}
tree_b buildTree(tree_b root)
{
    // Store nodes of given BST in sorted order
    vector<tree_b> nodes;
    storeBSTNodes(root, nodes);
 
    // Constructs BST from nodes[]
    int n = nodes.size();
    return buildTreeUtil(nodes, 0, n-1);
}

