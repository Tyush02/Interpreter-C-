#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> Syntax = {"i_num", "f_num", "s_line", "logic", "when", "cyc", "out"};

void interpreter(std::ifstream& file, std::string File_Name);
int Int_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name);
float Flt_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name);
std::string Strr_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name);
bool Lgt_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name);
void Rew(std::vector<std::string> arr, std::ifstream& file, int chek, std::string File_Name);
void Operations_I(std::vector<std::string> arr, int chek, int value_i, std::string name_i, int inn);
void Error(std::vector<std::string> arr, int chek, int ii, int ff, int ss, int ll);
void Operations_F(std::vector<std::string> arr, int chek, int value_f, std::string name_f, int inn);
void Func_W(std::vector<std::string> arr, int chek, int ii, int ff, int ss, int ll);
void If_Func(std::vector<std::string> arr, int chek, int ii, int ff, std::ifstream& file);

struct Str_I
{
    std::string name;
    std::string type;
    int value;

}intt;
struct Str_F
{
    std::string name;
    std::string type;
    float value;

}fltt;
struct Str_S
{
    std::string name;
    std::string type;
    std::string value;

}stt;
struct Str_L
{
    std::string name;
    std::string type;
    bool value;
}lgt;
std::vector<Str_I> st1;
std::vector<Str_F> st2;
std::vector<Str_S> st3;
std::vector<Str_L> st4;

int main()
{
    std::string File_Name;
    std::cin >> File_Name;
    std::ifstream file;

    file.open(File_Name + ".txt");
    if(file.is_open())
    {
        interpreter(file, File_Name);
    }
    else
    {
        std::cout << "File is not open";
    }

    return 0;
}

void interpreter(std::ifstream& file, std::string File_Name)
{
    int ii = 0, ff = 0, ss = 0, ll = 0;
    int chek = 0;
    while(!file.eof())
    {
        chek++;
        std::string line1, line2;
        std::vector<std::string> arr;
        getline(file, line1);
        if(line1 == "")
        {
            while(line1 == "")
            {
                chek++;
                getline(file, line1);
            }    
        }
        for(int i = 0; i < line1.length(); i++)
        {
            if(line1[i] == ' ')
            {
                line2 = "";
            }
            if (line1[i] != ' ')
            {
                line2 += line1[i];
                if(line1[i + 1] == ' ' || line2 == ":" || line2 == "}" || line2 == "{" || line2 == ")")
                {
                    arr.push_back(line2);
                }
            }
        }
        if(arr[0] == Syntax[0])
        {
            ii = 1;
        }
        if(arr[0] == Syntax[1])
        {
            ff = 1;
        }
        if(arr[0] == Syntax[2])
        {
            ss = 1;
        }
        if(arr[0] == Syntax[3])
        {
            ll = 1;
        }
        Error(arr, chek, ii, ff, ss, ll);
        
        if(arr.size() < 6)
        {
            if(arr[0] == Syntax[0])
            {
                Int_F(arr, chek, file, File_Name);
            }
            if(arr[0] == Syntax[1])
            {
                Flt_F(arr, chek, file, File_Name);
            }
        }
        if(arr[0] == Syntax[2])
        {
            Strr_F(arr, chek, file, File_Name);
        }
        if(arr[0] == Syntax[3])
        {
            Lgt_F(arr, chek, file, File_Name);
        }
        if(arr.size() > 5 && arr[0] != Syntax[4] && arr[0] != Syntax[5] && arr[0] != Syntax[6])
        {
            if(arr[2] == "=" && (arr[4] == "+" || arr[4] == "-" || arr[4] == "/" || arr[4] == "*"))
            {
                if(arr[0] == Syntax[0])
                {
                    if(ii == 1)
                    {
                        for(int i = 0; i < st1.size(); i++)
                        {
                            if(arr[1] == st1[i].name)
                            {
                                std::string name_i = st1[i].name;
                                int value_i = st1[i].value;
                                Operations_I(arr, chek, value_i, name_i, i);
                                break;
                            }
                        }
                        break;
                    }
                }
                if(arr[0] == Syntax[1])
                {
                    if(ff == 1)
                    {
                        for(int i = 0; i < st2.size(); i++)
                        {
                            if(arr[1] == st2[i].name)
                            {
                                std::string name_f = st2[i].name;
                                int value_f = st2[i].value;
                                Operations_F(arr, chek, value_f, name_f, i);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            if(arr[1] == "=" && (arr[3] == "+" || arr[3] == "-" || arr[3] == "/" || arr[3] == "*"))
            {
                if(ii == 1)
                {
                    for(int i = 0; i < st1.size(); i++)
                    {
                        if(arr[0] == st1[i].name)
                        {
                            std::string name_i = st1[i].name;
                            int value_i = st1[i].value;
                            Operations_I(arr, chek, value_i, name_i, i);
                            break;
                        }
                    }
                }
                if(ff == 1)
                {
                    for(int i = 0; i < st2.size(); i++)
                    {
                        if(arr[0] == st2[i].name)
                        {
                            std::string name_f = st2[i].name;
                            int value_f = st2[i].value;
                            Operations_F(arr, chek, value_f, name_f, i);
                            break;
                        }
                    }
                }
            }
        }
        if(arr[0] == Syntax[4])
        {
            If_Func(arr, chek, ii, ff, file);
        }
        if(arr[0] == Syntax[6])
        {
            Func_W(arr, chek, ii, ff, ss, ll);
        }
    }
    
    file.close();
}

int If_Op(int aa, int bb, std::string nsh, float aa2, float bb2, std::string nsh2);

void If_Func(std::vector<std::string> arr, int chek, int ii, int ff, std::ifstream& file)
{
    int aa = 0, bb = 0;
    float aa2 = 0, bb2 = 0;
    std::string nsh = "", nsh2 = "";
    if(arr[1] == "(" && (arr[arr.size() - 1] == ")" || arr[arr.size() - 1] == "{" || arr[arr.size() - 1] == "}"))
    {
        for(int j = 1; j < arr.size(); j++)
        {
            
            if(ii == 1)
            {
                hhh:
                jmm:
                int num = 0;
                if(arr[j] == "<" || arr[j] == ">" || arr[j] == "<=" || arr[j] == ">=" || arr[j] == "==" || arr[j] == "!=")
                {
                    nsh = arr[j];
                    for(int k = 0; k < st1.size(); k++)
                    {
                        if(arr[j - 1] == st1[k].name)
                        {
                            aa = st1[k].value;
                            j++;
                            goto jmp;
                        }
                    }
                    aa = std::stoi(arr[j - 1]);
                    j++;
                    jmp:
                    for(int k = 0; k < st1.size(); k++)
                    {
                        if(arr[j] == st1[k].name)
                        {
                            bb = st1[k].value;
                            j++;
                            goto jpm;
                        }
                    }
                    bb = std::stoi(arr[j]);
                    j++;
                    jpm:
                    num = If_Op(aa, bb, nsh, aa2, bb2, nsh2);
                    if(arr.size() < 8)
                    {
                        j = arr.size() - 1;
                        if(num == 0)
                        {
                            std::string hhhh = "";
                            while(hhhh != "}")
                            {
                                file >> hhhh;
                            }
                        }
                        goto hhh;
                    }
                }
                if(arr[j] == "&&")
                {
                    if(num == 0)
                    {
                        std::string hhhh = "";
                        while(hhhh != "}")
                        {
                            file >> hhhh;
                        }
                    }
                    else{
                        j++;
                        goto jmm;
                    }
                }
              /*  if(arr[j] == "&&" && num == 0)
                {
                    std::string hhhh = "";
                    while(hhhh != "}")
                    {
                        file >> hhhh;
                    }
                }*/
                if(arr[j] == "||")
                {
                    if(num == 1)
                    {
                        j = arr.size() - 1;
                        goto hhh;
                    }
                    else
                    {
                        j++;
                        goto hhh;
                    }
                }
               /* if(arr[j] == "||" && num == 0)
                {
                    std::string hhhh = "";
                    while(hhhh != "}")
                    {
                        file >> hhhh;
                    }
                }*/
            }
            if(ff == 1)
            {
                hhh2:
                jmm2:
                int num = 0;
                if(arr[j] == "<" || arr[j] == ">" || arr[j] == "<=" || arr[j] == ">=" || arr[j] == "==" || arr[j] == "!=")
                {
                    nsh2 = arr[j];
                    for(int k = 0; k < st2.size(); k++)
                    {
                        if(arr[j - 1] == st2[k].name)
                        {
                            aa2 = st2[k].value;
                            j++;
                            goto jmp2;
                        }
                    }
                    aa2 = std::stof(arr[j - 1]);
                    j++;
                    jmp2:
                    for(int k = 0; k < st2.size(); k++)
                    {
                        if(arr[j] == st2[k].name)
                        {
                            bb2 = st2[k].value;
                            j++;
                            goto jpm2;
                        }
                    }
                    bb2 = std::stof(arr[j]);
                    j++;
                    jpm2:
                    num = If_Op(aa, bb, nsh, aa2, bb2, nsh2);
                    if(arr.size() < 8)
                    {
                        j = arr.size() - 1;
                        if(num == 0)
                        {
                            std::string hhhh = "";
                            while(hhhh != "}")
                            {
                                file >> hhhh;
                            }
                        }
                        goto hhh2;
                    }
                }
                if(arr[j] == "&&")
                {
                    if(num == 0)
                    {
                        std::string hhhh = "";
                        while(hhhh != "}")
                        {
                            file >> hhhh;
                        }
                    }
                    else{
                        j++;
                        goto jmm2;
                    }
                }
               /* if(arr[j] == "&&" && num == 0)
                {
                    std::string hhhh = "";
                    while(hhhh != "}")
                    {
                        file >> hhhh;
                    }
                }*/
                if(arr[j] == "||")
                {
                    if(num == 1)
                    {
                        j = arr.size() - 1;
                        goto hhh2;
                    }
                    else
                    {
                        j++;
                        goto hhh2;
                    }
                }
                /*if(arr[j] == "||" && num == 0)
                {
                    std::string hhhh = "";
                    while(hhhh != "}")
                    {
                        file >> hhhh;
                    }
                }*/
            }
            
        }
    }
}

int If_Op(int aa, int bb, std::string nsh, float aa2, float bb2, std::string nsh2)
{
    if(nsh == ">")
    {
        if(aa > bb)
        {
            return 1;
        }
    }
    if(nsh2 == ">")
    {
        if(aa2 > bb2)
        {
            return 1;
        }
    }
    if(nsh == "<")
    {
        if(aa < bb)
        {
            return 1;
        }
    }
    if(nsh2 == "<")
    {
        if(aa2 < bb2)
        {
            return 1;
        }
    }
    if(nsh == ">=")
    {
        if(aa >= bb)
        {
            return 1;
        }
    }
    if(nsh2 == ">=")
    {
        if(aa2 >= bb2)
        {
            return 1;
        }
    }
    if(nsh == "<=")
    {
        if(aa <= bb)
        {
            return 1;
        }
    }
    if(nsh2 == "<=")
    {
        if(aa2 <= bb2)
        {
            return 1;
        }
    }
    if(nsh == "==")
    {
        if(aa == bb)
        {
            return 1;
        }
    }
    if(nsh2 == "==")
    {
        if(aa2 == bb2)
        {
            return 1;
        }
    }
    if(nsh == "!=")
    {
        if(aa != bb)
        {
            return 1;
        }
    }
    if(nsh2 == "!=")
    {
        if(aa2 != bb2)
        {
            return 1;
        }
    }
    return 0;
}

int Int_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name)
{
     intt.type = arr[0];
     std::string arr2 = arr[1]; 
     for(int i = 0; i < arr2.length(); i++)
     {
         if(arr2[0] >= 48 && arr2[0] <= 58)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
         if(arr2[i] > 122 || arr2[i] < 97 && arr2[i] > 90 || arr2[i] < 65 && arr2[i] > 58 || arr2[i] < 48)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
     }
     intt.name = arr2;
     if(arr[2] != "=" && arr[2] != ":")
     {
        std::cout << "\nError on line " << chek;
        exit(-1);
     }
     if(arr[2] == "=")
     {
         std::string arr3 = arr[3];
         for(int j = 0; j < arr3.length(); j++)
         {
             if(arr3[j] < 48 || arr3[j] >= 58)
             {
                std::cout << "\nError on line " << chek;
                exit(-1); 
             }
         }
         int val = std::stoi(arr3);
         intt.value = val;
         st1.push_back(intt);
     }
     if(arr[2] == ":")
     {
         Rew(arr, file, chek, File_Name);
     }
}

float Flt_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name)
{
     fltt.type = arr[0];
     std::string arr2 = arr[1]; 
     for(int i = 0; i < arr2.length(); i++)
     {
         if(arr2[0] >= 48 && arr2[0] <= 58)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
         if(arr2[i] > 122 || arr2[i] < 97 && arr2[i] > 90 || arr2[i] < 65 && arr2[i] > 58 || arr2[i] < 48)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
     }
     fltt.name = arr2;
     if(arr[2] != "=" && arr[2] != ":")
     {
        std::cout << "\nError on line " << chek;
        exit(-1);
     }
     if(arr[2] == "=")
     {
         std::string arr3 = arr[3];
         int num = 0;
         for(int j = 0; j < arr3.length(); j++)
         {
             if(arr3[j] == '.' && j != 0)
             {
                 if(num != 0)
                 {
                     std::cout << "\nError on line " << chek;
                     exit(-1);
                 }
                 num++;
                 continue;
             }
             if(arr3[j] <= 48 || arr3[j] >= 58)
             {
                std::cout << "\nError on line " << chek;
                exit(-1); 
             }
         }
         float val = std::stof(arr3);
         fltt.value = val;
         st2.push_back(fltt);
     }
     if(arr[2] == ":")
     {
         Rew(arr, file, chek, File_Name);
     }
}

std::string Strr_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name)
{
     stt.type = arr[0];
     std::string arr2 = arr[1]; 
     for(int i = 0; i < arr2.length(); i++)
     {
         if(arr2[0] >= 48 && arr2[0] <= 58)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
         if(arr2[i] > 122 || arr2[i] < 97 && arr2[i] > 90 || arr2[i] < 65 && arr2[i] > 58 || arr2[i] < 48)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
     }
     stt.name = arr2;
     if(arr[2] != "=" && arr[2] != ":")
     {
        std::cout << "\nError on line " << chek;
        exit(-1);
     }
     if(arr[2] == "=")
     {
         std::string arr3 = arr[3];
         std::string arr4;
         if(arr3[0] != '['  || arr3[arr3.length() - 1] != ']')
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
         for(int i = 1; i < arr3.length() - 1; i++)
         {
             arr4 += arr3[i];
         }
         stt.value = arr4;
         st3.push_back(stt);
     }
     if(arr[2] == ":")
     {
         Rew(arr, file, chek, File_Name);
     }
}

bool Lgt_F(std::vector<std::string> arr, int chek, std::ifstream& file, std::string File_Name)
{
     lgt.type = arr[0];
     std::string arr2 = arr[1]; 
     for(int i = 0; i < arr2.length(); i++)
     {
         if(arr2[0] >= 48 && arr2[0] <= 58)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
         if(arr2[i] > 122 || arr2[i] < 97 && arr2[i] > 90 || arr2[i] < 65 && arr2[i] > 58 || arr2[i] < 48)
         {
             std::cout << "\nError on line " << chek;
             exit(-1);
         }
     }
     lgt.name = arr2;
     if(arr[2] != "=" && arr[2] != ":")
     {
        std::cout << "\nError on line " << chek;
        exit(-1);
     }
     if(arr[2] == "=")
     {
        if(arr[3] != "yes" && arr[3] != "no")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }  
        if(arr[3] == "yes")
        {
            lgt.value = true;
        }
        if(arr[3] == "no")
        {
            lgt.value = false;
        }
        st4.push_back(lgt);
     }
     if(arr[2] == ":")
     {
         Rew(arr, file, chek, File_Name);
     }
}

void Rew(std::vector<std::string> arr, std::ifstream& file, int chek, std::string File_Name)
{
    std::string line;
    while(!file.eof())
    {
        file >> line;
        if(line == Syntax[4] || line == Syntax[5])
        {
            while(line != "}")
            {
                file >> line;
            }
        }
        if(line == arr[1])
        {
            file >> line;
            if(line == "=")
            {
                file >> line;
                if(arr[0] == Syntax[0])
                {            
                    for(int j = 0; j < line.length(); j++)
                    {
                         if(line[j] <= 48 || line[j] >= 58)
                         {
                            std::cout << "\nError on line " << chek;
                            exit(-1); 
                         }
                    }
                     int val = std::stoi(line);
                     intt.value = val;
                     st1.push_back(intt);
                }
                if(arr[0] == Syntax[1])
                {
                    int num = 0;
                    for(int j = 0; j < line.length(); j++)
                    {
                        if(line[j] == '.' && j != 0)
                        {
                            if(num != 0)
                            {
                                std::cout << "\nError on line " << chek;
                                exit(-1);
                            }
                            num++;
                            continue;
                        }
                        if(line[j] <= 48 || line[j] >= 58)
                        {
                            std::cout << "\nError on line " << chek;
                            exit(-1); 
                        }
                    }
                    float val = std::stof(line);
                    fltt.value = val;
                    st2.push_back(fltt);
                }
                if(arr[0] == Syntax[2])
                {
                    std::string arr4;
                    if(line[0] != '['  || line[line.length() - 1] != ']')
                    {
                        std::cout << "\nError on line " << chek;
                        exit(-1);
                    }
                    for(int i = 1; i < line.length() - 1; i++)
                    {
                        arr4 += line[i];
                    }
                    stt.value = arr4;
                    st3.push_back(stt);
                }
                if(arr[0] == Syntax[3])
                {
                    if(line != "yes" && line != "no")
                    {
                        std::cout << "\nError on line " << chek;
                        exit(-1);
                    }  
                    if(line == "yes")
                    {
                        lgt.value = true;
                    }
                    if(line == "no")
                    {
                        lgt.value = false;
                    }
                    st4.push_back(lgt);
                }
            }
        }
    }
    file.close();
    file.open(File_Name + ".txt");
    int num = 1;
    while (num <= chek)
    {
        getline(file, line);
        num++;
    }
}
void Operations_I(std::vector<std::string> arr, int chek, int value_i, std::string name_i, int inn)
{
    int vaal = 0;
    if(arr[1] == "=")
    {
        if(arr[2] == "+" || arr[2] == "-" || arr[2] == "/" || arr[2] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 2] == "+" || arr[arr.size() - 2] == "-" || arr[arr.size() - 2] == "/" || arr[arr.size() - 2] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[2] == name_i)
        {
            vaal += value_i;
        }
        if(arr[2] != name_i)
        {
            vaal += std::stoi(arr[2]);
        }
        for(int i = 2; i < arr.size() - 1; i++)
        {
            j:
            if(arr[i] == "*")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal *= st1[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal *= std::stoi(arr[i + 1]);
            }
            if(arr[i] == "/")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal /= st1[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal /= std::stoi(arr[i + 1]);
            }
            if(arr[i] == "+")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal += st1[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal += std::stoi(arr[i + 1]);
            }
            if(arr[i] == "-")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal -= st1[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal -= std::stoi(arr[i + 1]);
            }
            
        }
        st1[inn].value = vaal;
    }
    if(arr[2] == "=")
    {
        if(arr[3] == "+" || arr[3] == "-" || arr[3] == "/" || arr[3] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 2] == "+" || arr[arr.size() - 2] == "-" || arr[arr.size() - 2] == "/" || arr[arr.size() - 2] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        for(int i = 0; i < st1.size(); i++)
        {
            if(arr[3] == st1[i].name)
            {
                vaal = st1[i].value;
                goto l;
            }
        }
        vaal = std::stoi(arr[3]);
        l:
        for(int i = 3; i < arr.size() - 1; i++)
        {
            k:
            if(arr[i] == "+")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal += st1[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal += std::stoi(arr[i + 1]);
            }
            if(arr[i] == "-")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal -= st1[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal -= std::stoi(arr[i + 1]);
            }
            if(arr[i] == "*")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal *= st1[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal *= std::stoi(arr[i + 1]);
            }
            if(arr[i] == "/")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st1[j].name)
                    {
                        vaal /= st1[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal /= std::stoi(arr[i + 1]);
            }
        }
        st1[inn].value = vaal;
    }
}

void Operations_F(std::vector<std::string> arr, int chek, int value_f, std::string name_f, int inn)
{
    float vaal = 0;
    if(arr[1] == "=")
    {
        if(arr[2] == "+" || arr[2] == "-" || arr[2] == "/" || arr[2] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 2] == "+" || arr[arr.size() - 2] == "-" || arr[arr.size() - 2] == "/" || arr[arr.size() - 2] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[2] == name_f)
        {
            vaal += value_f;
        }
        if(arr[2] != name_f)
        {
            vaal += std::stof(arr[2]);
        }
        for(int i = 2; i < arr.size() - 1; i++)
        {
            j:
            if(arr[i] == "*")
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal *= st2[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal *= std::stof(arr[i + 1]);
            }
            if(arr[i] == "/")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal /= st2[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal /= std::stof(arr[i + 1]);
            }
            if(arr[i] == "+")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal += st2[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal += std::stof(arr[i + 1]);
            }
            if(arr[i] == "-")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal -= st2[j].value;
                        i++;
                        goto j;
                    }
                }
                vaal -= std::stof(arr[i + 1]);
            }
            
        }
        st2[inn].value = vaal;
    }
    if(arr[2] == "=")
    {
        if(arr[3] == "+" || arr[3] == "-" || arr[3] == "/" || arr[3] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 2] == "+" || arr[arr.size() - 2] == "-" || arr[arr.size() - 2] == "/" || arr[arr.size() - 2] == "*")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        for(int i = 0; i < st2.size(); i++)
        {
            if(arr[3] == st2[i].name)
            {
                vaal = st2[i].value;
                goto l;
            }
        }
        vaal = std::stof(arr[3]);
        l:
        for(int i = 3; i < arr.size() - 1; i++)
        {
            k:
            if(arr[i] == "+")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal += st2[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal += std::stof(arr[i + 1]);
            }
            if(arr[i] == "-")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal -= st2[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal -= std::stof(arr[i + 1]);
            }
            if(arr[i] == "*")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal *= st2[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal *= std::stof(arr[i + 1]);
            }
            if(arr[i] == "/")
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(arr[i + 1] == st2[j].name)
                    {
                        vaal /= st2[j].value;
                        i++;
                        goto k;
                    }
                }
                vaal /= std::stof(arr[i + 1]);
            }
        }
        st2[inn].value = vaal;
    }
}
void Func_W(std::vector<std::string> arr, int chek, int ii, int ff, int ss, int ll)
{
    if(arr[1] != ">")
    {
        std::cout << "\nError on line " << chek;
        exit(-1);
    }
    if(arr.size() > 4)
    {
        for(int i = 1; i < arr.size() - 1; i++)
        {
            if(i % 2 != 0)
            {
                if(arr[i] != ">")
                {
                    std::cout << "\nError on line " << chek;
                    exit(-1);
                }
            }
        }
    }
    for(int i = 1; i < arr.size() - 1; i++)
    {
        if(ii == 1)
        {
            for(int j = 0; j < st1.size(); j++)
            {
                if(arr[i] == st1[j].name)
                {
                    std::cout << st1[j].value;
                    break;
                }
            }
        }
        if(ff == 1)
        {
            for(int j = 0; j < st2.size(); j++)
            {
                if(arr[i] == st2[j].name)
                {
                    std::cout << st2[j].value;
                    break;
                }
            }
        }    
        if(ss == 1)
        {
            for(int j = 0; j < st3.size(); j++)
            {
                if(arr[i] == st3[j].name)
                {
                    std::cout << st3[j].value;
                    break;
                }
            }
        }
        if(ll == 1)
        {
            for(int j = 0; j < st4.size(); j++)
            {
                if(arr[i] == st4[j].name)
                {
                    std::cout << st4[j].value;
                    break;
                }
            }
        }
        if(arr[i] == "p/")
        {
            std::cout << ' ';
            continue;
        }
        if(arr[i] == "n/")
        {
            std::cout << std::endl;
            continue;
        }
        if(arr[i] == ">")
        {
            continue;
        }
        std::string lline = arr[i];
        if(lline[0] != '[' || lline[lline.length() - 1] != ']')
        {
            if(ll == 1)
            {
                for(int j = 0; j < st4.size(); j++)
                {
                    if(lline == st4[j].name)
                    {
                        goto jmp;
                    }
                }
            }
            if(ss == 1)
            {
                for(int j = 0; j < st3.size(); j++)
                {
                    if(lline == st3[j].name)
                    {
                        goto jmp;     
                    }
                }
            }
            if(ff == 1)
            {
                for(int j = 0; j < st2.size(); j++)
                {
                    if(lline == st2[j].name)
                    {
                        goto jmp;     
                    }
                }
            }
            if(ii == 1)
            {
                for(int j = 0; j < st1.size(); j++)
                {
                    if(lline == st1[j].name)
                    {
                        goto jmp;     
                    }
                }
            }
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        jmp:
        if(lline[0] == '[' && lline[lline.length() - 1] == ']')
        {
            for(int k = 1; k < lline.length() - 1; k++)
            {
                if(lline.length() >= 5)
                {
                    if(lline[k] == '|' && lline[k + 1] == 'p' && lline[k + 2] == '|')
                    {
                        std::cout << ' ';
                        k = k + 2;
                        goto jjj;
                    }
                    if(lline[k] == '|' && lline[k + 1] == 'n' && lline[k + 2] == '|')
                    {
                        std::cout << std::endl;
                        k = k + 2;
                        goto jjj;
                    }
                }
                std::cout << lline[k];
                jjj:
                int ko;
            }
        }
    }
}

void Error(std::vector<std::string> arr, int chek, int ii, int ff, int ss, int ll)
{
    if(arr[arr.size() - 1] != ":" && arr[arr.size() - 1] != "}" && arr[arr.size() - 1] != "{" && arr[arr.size() - 1] != ")")
    {
        std::cout << "\nError on line " << chek;
        exit(-1);
    }
    if(arr[0] != Syntax[0] && arr[0] != "{" && arr[0] != "}" && arr[0] != Syntax[1] && arr[0] != Syntax[2] && arr[0] != Syntax[3] && arr[0] != Syntax[4] && arr[0] != Syntax[5] && arr[0] != Syntax[6])
    {
        if(ii == 1)
        {
            for(int i = 0; i < st1.size(); i++)
            {
                if(arr[0] == st1[i].name)
                {
                    goto jmp;
                }
            }
        }
        if(ff == 1)
        {
            for(int i = 0; i < st2.size(); i++)
            {
                if(arr[0] == st2[i].name)
                {
                    goto jmp;
                }
            }
        }
        if(ss == 1)
        {
            for(int i = 0; i < st3.size(); i++)
            {
                if(arr[0] == st3[i].name)
                {
                    goto jmp;
                }
            }
        }
        if(ll == 1)
        {
            for(int i = 0; i < st4.size(); i++)
            {
                if(arr[0] == st4[i].name)
                {
                    goto jmp;
                }
            }
        }
        else
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
    }
    jmp:  
    if(arr.size() >= 2)
    {
        if(arr[arr.size() - 1] == ":" && arr[arr.size() - 2] == "}")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 1] == ":" && arr[arr.size() - 2] == "{")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 1] == ":" && arr[arr.size() - 2] == ")")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 1] == "}" && arr[arr.size() - 2] == ")")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 1] == ")" && arr[arr.size() - 2] == "}")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[arr.size() - 1] == ")" && arr[arr.size() - 2] == "{")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[0] == Syntax[4] && arr[1] != "(")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[0] == Syntax[5] && arr[1] != "(")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
        if(arr[0] == Syntax[6] && arr[1] != ">")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
    }
    
    if(arr[0] == ":" || arr[0] == ")")
    {
        std::cout << "\nError on line " << chek;
        exit(-1);
    }
    for(int i = 0; i < arr.size(); i++)
    {
        if(i == arr.size() - 1)
        {
            break;
        }   
        if(arr[i] == ":")
        {
            std::cout << "\nError on line " << chek;
            exit(-1);
        }
    }

}
