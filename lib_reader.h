#include "lib_book.h"
using namespace std;

typedef struct reader{
    int ID;
    char namer[30];
    char sachmuon[30][30];
    int sosachmuon;

} reader;
typedef struct node_reader{
    reader h;
    node_reader *leftr;
    node_reader *rightr;
}node_reader;
typedef node_reader* tree_r;

tree_r initr(reader a);//khởi tạo cây người dùng

void insert_r(tree_r &b,reader a);//thêm người dùng vào cây người dùng
void borrow_book(tree_r &a, tree_b &b);//mượn sách

void return_book(reader &a, tree_b &b);//trả sách

void saveJSON_reader(tree_r a);//lưu dữ liệu vào file

void loadJSON_reader(tree_r &b);//load dữ liệu từ file vào cây nhị phân

///////////////////////////////////////////////////////////////////////////////////////

tree_r initr(reader a){
    tree_r b = new node_reader;
    b->h=a;
    b->leftr = NULL;
    b->rightr = NULL;
    return b;
}

void insert_r(tree_r &b, reader a){
    if(b==NULL)
    {
        b= initr(a);
    }
    else if(b->h.ID==a.ID)
    {
        cout<<"nguoi doc da ton tai"<<endl;
    }
    else if(b->h.ID>a.ID)
    {
        insert_r(b->leftr,a);
    }
    else if(b->h.ID<a.ID)
    {
        insert_r(b->rightr,a);
    }
    
}

void add_r(tree_r &a){
    reader r1;
    char k[30];
    cinChar(k);
    cout<<"ID nguoi doc: ";
    cin>>r1.ID;
    cinChar(k);
    cout<<"Ten nguoi doc: ";
    cinChar(r1.namer);
    r1.sosachmuon = 0;
    insert_r(a,r1);
}

tree_r search_reader(tree_r a,int id ){
    if(a==NULL){
        cout<<"nguoi dung khong ton tai "<<endl;
        return NULL;
    }
    else 
    {
        if(a->h.ID>id)
        {
            search_reader(a->leftr,id);
        }
        else if(a->h.ID<id)
        {
            search_reader(a->rightr,id);
        }
        else{
            return a;
        }
    }
}

void borrow_book(tree_r &a, tree_b &b){
    char kk[30];
    cinChar(kk);
    while(true){
        char s[30];
        cout<<"nhap ten sach muon "<<endl;
        cinChar(s);
        tree_b k=search_b(b,s);
        if(k==NULL){
        }
        else if (a->h.sosachmuon>10)
        {
                cout<<"ban da muon qua so sach quy dinh"<<endl;
                break;
        }
        else if(k->c.Num<=0)
        {
            cout<<"sach nay khong con trong kho"<<endl;
        }else{
            decr_num_book(k);
            strcpy(a->h.sachmuon[a->h.sosachmuon],s);
            a->h.sosachmuon++;
            break;
        }
    }
}

void return_book(tree_r &a, tree_b &b){
    char kk[30];
    cinChar(kk);
    while(true){
        int pos;
        bool key = false;
        char s[30];
        cout<<"nhap ten sach tra "<<endl;
        cinChar(s);
        for(int i=0;i<a->h.sosachmuon;i++){
            if(!strcmp(s,a->h.sachmuon[i])){
                pos = i;
                key = true;
                break;
            }
        }
        if(key){
            tree_b k=search_b(b,s);
            incr_num_book(k);
            for(int i=pos;i<a->h.sosachmuon;i++){
                strcpy(a->h.sachmuon[i],a->h.sachmuon[i+1]);
            }
            a->h.sosachmuon--;
            break;
        }else{
            cout<<"Ban chua muon dau sach nay!"<<endl;
        }
    }
}

// void deleteBook(tree_r &a,int pos){
//     for(int i=pos;i<a->h.sosachmuon;i++){
//         strcpy(a->h.sachmuon[i],a->h.sachmuon[i+1]);
//     }
//     a->h.sosachmuon--;
// }


void vectorData_reader(tree_r a,vector<reader> &vtor){
    if(a!=NULL){
        vtor.push_back(a->h);
        vectorData_reader(a->leftr,vtor);
        vectorData_reader(a->rightr,vtor);
    }
}


void saveJSON_reader(tree_r a){
    vector<reader> vector;
    vectorData_reader(a,vector);
    StringBuffer s;
    PrettyWriter<StringBuffer> writer(s);
    writer.StartArray();
    for(int i=0;i<vector.size();i++)
    {
        writer.StartObject();
        writer.Key("ID");
        writer.Int(vector[i].ID);
        writer.Key("Ten nguoi doc");
        writer.String(vector[i].namer);
        writer.Key("So sach muon");
        writer.Int(vector[i].sosachmuon);
        writer.Key("Sach muon");
        writer.StartArray();
        for(int k=0;k<vector[i].sosachmuon;k++)
        {   
            writer.String(vector[i].sachmuon[k]);
        }
        writer.EndArray();
        writer.EndObject();
    }
    writer.EndArray();
    std::ofstream of("reader_data.json");
    of<<s.GetString();
}


void loadJSON_reader(tree_r &b){
    cout<<"f2";
    std::ifstream ifs ("reader_data.json");
    if(!ifs)
    {
        cout<<"hien tai chua co nguoi dung nao\n";
        return;
    }
    IStreamWrapper isw {ifs};
    Document doc{};
    doc.ParseStream(isw);
    for(int i=0;i<doc.Size();i++){
        reader a;
        a.ID= doc[i]["ID"].GetInt();
        string s = doc[i]["Ten nguoi doc"].GetString();
        strcpy(a.namer,s.c_str());
        a.sosachmuon = doc[i]["So sach muon"].GetInt();
        for(int k=0;k<a.sosachmuon;k++)
        {
            cout<<k;
            s=doc[i]["Sach muon"][k].GetString();
            strcpy(a.sachmuon[k],s.c_str());
        }
        insert_r(b,a);
    }

}