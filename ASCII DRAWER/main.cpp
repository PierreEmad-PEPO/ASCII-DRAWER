#include<bits/stdc++.h>
#include<conio.h>

using namespace std;

void fast()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

ofstream output("Exported output.txt");
ifstream import("import.txt");


struct point
{
    int x,y;
    char char_print;
};



void select_sort(point n[])
{
    if(n[0].x>n[1].x)
        swap(n[0],n[1]);

}


point cursor,temp;
int rows=18,columns=40;
vector<point> pressed(1);
int i=0,j=0,select_count=0,pressed_selected_cnt=0;
bool b=1,prevs=1,pressednow=0,continous=0,v_convert=0,selecting=0/*,selected=1*/;
bool confirm_select=0,one_step=0;
point select[2];
int last_crsr_x=0,last_crsr_y=0;
vector<int> selected_pressed(1);
vector<point> rotation_before(1);
bool rotating=0;
int r1=select[1].x-select[0].x,c1=select[1].y-select[0].y;
int rotation_i,rotation_j;
vector<point> rotated_vect(1);
bool break_inrotation=0;
int temp_rotate_x,temp_rotate_y;
int local_x,local_y;
char print,cursor_char='0';
bool exported_ss=0,clear_flag=0;
vector<point> undo(1);
vector<point> cpd(1);
point cpy;
bool any_key_pressed=0,show_commands=1;
int ascii_char;
point imprt;
string text_import="",tsts="";




void input()
{
    char in;
    in=getch();

    prevs=1;
    temp.x=cursor.x;
    temp.y=cursor.y;


    undo[0]=pressed[0];

    if(continous==1)
        {
            prevs=1;
            for(int cnt=0;cnt<pressed.size();cnt++)
                {
                    if(pressed[cnt].x==cursor.x&&pressed[cnt].y==cursor.y)
                    {
                        prevs=0;
                        break;
                    }
                }
            if(prevs)
            {
                temp.char_print=print;
                pressednow=1,pressed.push_back(temp);
            }
        }


        last_crsr_x=cursor.x;
        last_crsr_y=cursor.y;

    switch(in)
    {

     case 'z':
         system("cls");
         cout<<"\n choose a drawing character\n PRESS :\n";

         for(int as=1;as<=255;as++)
         {
             if(as >=7 && as<=13)
            continue;

            if(as<=99&&as>=1)
                cout<<"| ";
            else cout<<"|";
            as<10?cout<<as<<' ':cout<<as,cout<<"  to choose ( "<<char(as)<<" )   " ;

            if(as%7==0)
                cout<<"\n";
         }
         cin>>ascii_char;
         print=char(ascii_char);

        //cout<<"\nEnter the drawing character\n";
        //cin>>print;
        cursor_char=print;
        any_key_pressed=1;
        break;

    case 'w':
        cursor.x>0?cursor.x--:cursor.x=rows-1;
        one_step=1;
        any_key_pressed=1;
        break;

    case 's':
        cursor.x<rows-1?cursor.x++:cursor.x=0;
        one_step=1;
        any_key_pressed=1;
        break;

    case 'a':
        cursor.y>0?cursor.y--:cursor.y=columns-1;
        one_step=1;
        any_key_pressed=1;
        break;

    case 'd':
        cursor.y<columns-1?cursor.y++:cursor.y=0;
        one_step=1;
        any_key_pressed=1;
        break;

    case 'q':
        continous=!continous;
        if(continous==0)
            cursor_char='0';
        else cursor_char=print;

        any_key_pressed=1;
        break;

    case ' ':

        undo.resize(pressed.size());
            for(int c=1;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }


        for(int cnt=1;cnt<pressed.size();cnt++)
                {
                    if(pressed[cnt].x==cursor.x&&pressed[cnt].y==cursor.y)
                    {
                        cursor_char='0';
                        prevs=0;
                        break;
                    }
                }
        if(prevs)
        {
            temp.char_print=print;
            cursor_char=print;
            pressednow=1,pressed.push_back(temp);

        }

        any_key_pressed=1;
        break;

        case 'x':

        clear_flag=1;
            undo.resize(pressed.size());
            for(int c=1;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }


            cursor_char = 'X';
        for(int cnt=0;cnt<pressed.size();cnt++)
                {
                    if(pressed[cnt].x==cursor.x&&pressed[cnt].y==cursor.y)
                    {
                        pressed.erase(pressed.begin()+cnt,pressed.begin()+cnt+1);
                    }
                }
                        break;

        case 'c':

            clear_flag=1;
            undo.resize(pressed.size());
            for(int c=1;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }


            if(confirm_select && !selecting)
            {
                for(int i=select[0].x;i<=select[1].x;i++)
                {
                    for(int j=select[0].y;j<=select[1].y;j++)
                    {
                        for(int cn=1;cn<pressed.size();cn++)
                        {
                            if(pressed[cn].x==i && pressed[cn].y==j)
                            {
                                pressed.erase(pressed.begin()+cn,pressed.begin()+cn+1);
                            }
                        }
                    }
                }
                selected_pressed.clear();
            }
            else

{

            pressed.erase(pressed.begin(),pressed.end());
            pressed.push_back(temp);
            pressed[0].x=-300;
            pressed[0].y=-300;

}

            any_key_pressed=1;
            break;

        case 'v':

        undo.resize(pressed.size());
            for(int c=0;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }

        if(any_key_pressed==0)
        {
            point temp2;
            //cout<<"GGGGGGGGGGG";
            for(int i=0;i<rows;i++)
            {
                for(int j=0;j<columns;j++)
                {
                    temp2.x=i;
                    temp2.y=j;
                    temp2.char_print=print;
                    pressed.push_back(temp2);
                }
            }
        }
        else
        {


            for(int i=0;i<rows;i++)
            {
                for(int j=0;j<columns;j++)
                {
                    v_convert=0;
                    temp.x=i;
                    temp.y=j;
                    temp.char_print=print;
                    for(int cnt=0;cnt<pressed.size();cnt++)
                    {
                        if(pressed[cnt].x==i&&pressed[cnt].y==j)
                        {
                            pressed.erase(pressed.begin()+cnt,pressed.begin()+cnt+1);
                            v_convert=1;
                            break;
                        }
                    }
                    if(v_convert==0)
                    {pressed.push_back(temp);}

                }
            }
        }

        any_key_pressed=1;
            break;

        case '0':

            selecting=1;
            confirm_select=0;
            select[select_count]=cursor;
            select_count++;
            if(select_count>=2)
            {
                select_sort(select);
                select_count=0;
                selecting=0;
                confirm_select=1;

                if(select[0].y>select[1].y)
                    {
                        swap(select[0].y,select[1].y);
                    }

                last_crsr_x=select[0].x,last_crsr_y=select[0].y;
                cursor = select[0];


                for(int i=select[0].x;i<=select[1].x;i++)
                {
                    for(int j=min(select[0].y,select[1].y);j<=max(select[0].y,select[1].y);j++)
                    {

                        for(int cnt=0;cnt<pressed.size();cnt++)
                        {
                            if(pressed[cnt].x==i&&pressed[cnt].y==j)
                            {
                                selected_pressed.push_back(cnt);
                                pressed_selected_cnt++;
                                break;
                            }
                        }
                    }
                }
            }

            any_key_pressed=1;
        break;


        case '1':
            selecting=0;
            confirm_select=0;
            rotating=0;

            //selected_pressed.resize(1);
            selected_pressed.erase(selected_pressed.begin(),selected_pressed.end());

            select[0].x=-1;
            select[0].y=-1;
            select[1].x=-1;
            select[1].y=-1;
            select_count=0;

            any_key_pressed=1;
        break;

        case '+':

            undo.resize(pressed.size());
            for(int c=1;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }


            r1=select[1].x-select[0].x,c1=select[1].y-select[0].y;
            rotating=1;




    for(int cntt=0;cntt<selected_pressed.size();cntt++)
            {
                temp_rotate_x=pressed[selected_pressed[cntt]].x;
                temp_rotate_y=pressed[selected_pressed[cntt]].y;

                pressed[selected_pressed[cntt]].x=select[0].x+(  temp_rotate_y  -select[0].y);
                pressed[selected_pressed[cntt]].y=select[0].y+r1 -(  temp_rotate_x  -select[0].x);
            }


                    select[1].x+=(c1-r1);
                    select[1].y-=(c1-r1);

            break_inrotation=0;


        any_key_pressed=1;
        break;


        case 'e':

            for(int i=0;i<rows;i++)
            {

                for(int j=0;j<columns;j++)
                {
                    b=1;
                    for(int cnt=0;cnt<pressed.size();cnt++)
                    {
                    if(pressed[cnt].x==i&&pressed[cnt].y==j)
                        {
                            output<<pressed[cnt].char_print;
                            b=0;
                            break;
                        }
                    }
                    if(b)
                        output<<' ';
                }
                output<<endl;
            }

            exported_ss=1;

            any_key_pressed=1;
            break;

        case 'u':
            if(!clear_flag)
            undo.resize(pressed.size());
            else
            {
                pressed.resize(undo.size());
                clear_flag=0;
            }

            for(int c=1;c<undo.size();c++)
            {
                swap(undo[c],pressed[c]);
                //pressed[c]=undo[c];
            }
            any_key_pressed=1;
        break;

        case 'r':

            for(int cntt=0;cntt<selected_pressed.size();cntt++)
                    {
                        cpy=pressed[selected_pressed[cntt]];
                        //cpy.x++;
                        //cpy.y++;
                        pressed.push_back(cpy);
                    }
                last_crsr_x=cursor.x;
                //cursor.x++;


            any_key_pressed=1;
            break;

        case 'h':
            show_commands=!show_commands;
            break;



        case 'm':
            int rd;
            point rd55;
            char cdd;
            for(int i=0;i<rows;i++)
            {
                for(int j=0;j<columns;j++)
                {
                    rd=rand()%20+1;
                    if(rd>11 && j>4 && j<columns-4)
                    {
                        rd55.x=i;
                        rd55.y=j;
                        //while(rad)
                        //rd55=char(rand()%255);
                        rd55.char_print=print;
                        pressed.push_back(rd55);
                    }

                    else if(rd>15)
                    {
                        rd55.x=i;
                        rd55.y=j;
                        rd55.char_print=print;
                        pressed.push_back(rd55);
                    }
                }
            }
            any_key_pressed=1;
            break;


        case 'f':

            undo.resize(pressed.size());
            for(int c=1;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }

            for(int ct=0;ct<selected_pressed.size();ct++)
            {
                pressed[selected_pressed[ct]].y = select[1].y - pressed[selected_pressed[ct]].y + select[0].y;
            }

             any_key_pressed=1;
            break;


            case 'g':

            undo.resize(pressed.size());
            for(int c=1;c<pressed.size();c++)
            {
                undo[c]=pressed[c];
            }

            for(int ct=0;ct<selected_pressed.size();ct++)
            {
                pressed[selected_pressed[ct]].x = select[1].x - pressed[selected_pressed[ct]].x + select[0].x;
            }

             any_key_pressed=1;
            break;

        case 'i':

            ifstream import("import.txt");

            for(int cr=0;cr<rows;cr++)
            {
                tsts=text_import;
                getline(import,text_import);
                //if(text_import==tsts)
                 //   break;
                for(int jjj=0;jjj<text_import.size();jjj++)
                {
                    if(text_import[jjj]!=' ' && jjj<columns)
                    {
                        imprt.x=cr;
                        imprt.y=jjj;
                        imprt.char_print=text_import[jjj];
                        pressed.push_back(imprt);
                    }
                }
                text_import="";

            }
            text_import="";
            tsts="";


             any_key_pressed=1;
        break;

    }

    if(confirm_select && one_step)
                {
                    for(int i=0;i<selected_pressed.size();i++)
                    {
                        pressed[selected_pressed[i]].x+=(cursor.x-last_crsr_x);
                        pressed[selected_pressed[i]].y+=(cursor.y-last_crsr_y);

                        //cout<<"\n"<<pressed[selected_pressed[i]].x<<" "<<pressed[selected_pressed[i]].y<<endl;
                    }
                    select[0].x+=(cursor.x-last_crsr_x);
                    select[0].y+=(cursor.y-last_crsr_y);
                    select[1].x+=(cursor.x-last_crsr_x);
                    select[1].y+=(cursor.y-last_crsr_y);
                    one_step=0;
                }


}



void draw(vector<point> pressed)
{
    int cnt=0;

    cout<<"     ";
    for(i=0;i<=columns+1;i++)
        cout<<'#';

    cout<<endl;


    for(i=0;i<rows;i++)
    {
            cout<<"     #";
        for(j=0;j<columns;j++)
        {


            b=1;


                if(i==cursor.x&&j==cursor.y)
                {
                    if(confirm_select || selecting)
                    {
                        cout<<'|';
                    }
                    else if(pressednow && !continous)
                    {
                        //cursor_char=print;
                        cout<<cursor_char;
                        if(cursor_char=='X' || cursor_char=='0')
                            cursor_char=print;
                        pressednow=0;
                    }
                    else
                   {
                       //cursor_char=print;
                       cout<<cursor_char;
                       if(cursor_char=='X' || cursor_char=='0')
                            cursor_char=print;
                   }
                }
            else
            {
                for(cnt=0;cnt<pressed.size();cnt++)
                {
                    if(pressed[cnt].x==i&&pressed[cnt].y==j)
                    {
                        cout<<pressed[cnt].char_print;
                        b=0;
                        break;
                    }
                }

                if(b)
                {
                        if(selecting && i>=min(select[0].x,cursor.x)&&i<=max(select[0].x,cursor.x) &&
                            j>=min(select[0].y,cursor.y)&&j<=max(select[0].y,cursor.y))
                            {
                                cout<<'.';
                            }
                    else if( confirm_select &&i>=min(select[0].x,select[1].x)&&i<=max(select[0].x,select[1].x) &&
                            j>=min(select[0].y,select[1].y)&&j<=max(select[0].y,select[1].y))
                            {
                                cout<<'.';
                            }
                    else
                    cout<<' ';
                }

            }
        }


        cout<<'#'<<endl;
    }

    cout<<"     ";
    for(i=0;i<=columns+1;i++)
        cout<<'#';

        if(show_commands)
    {
        cout<<"\n\n PRESS :\n\n";

        cout<<"|--------------------------------------------------------------------------------------------------------------|\n";
        cout<<"|                                                                                                              |\n";

        cout<<"|| W A S D  TO MOVE  || SPACE TO DRAW  || X  TO DELETE  || C  TO CLEAR ALL / SELECTED || H TO HIDE COMMANDS    |\n";
        cout<<"|--------------------------------------------------------------------------------------------------------------|\n";
        cout<<"|                                                                                                              |\n";

        cout<<"||  Q  TO CONTINOUS DRAWING  ";
        cout<<"CONTINOUS STATUS : ";
        continous?cout<<"ON   ":cout<<"OFF  ";
        cout<<"||  V  TO INVERT  ";
        cout<<"||  0 TO ";

        if(selecting)
            cout<<"CONFIRM SELECTION              |\n";
       else cout<<"SELECT                         |\n";
        cout<<"|--------------------------------------------------------------------------------------------------------------|\n";
        cout<<"|                                                                                                              |\n";

        cout<<"|| 1 TO DESELECT ";

        cout<<"|| + TO ROTATE SELECTED ";

        cout<<"|| Z TO INPUT THE DRAWING CHARACTER || I TO IMPORT FROM (import.txt)  |\n";
        cout<<"|--------------------------------------------------------------------------------------------------------------|\n";
        cout<<"|                                                                                                              |\n";

        cout<<"||  E TO EXPORT AS TEXT FILE NAMED (\"Exported output.txt\")  ";
        cout<<"||  U TO UNDO  ";
        cout<<"||  R TO COPY || M TO RANDOM DRAW   |\n";
        cout<<"|--------------------------------------------------------------------------------------------------------------|\n";
        cout<<"|                                                                                                              |\n";
        cout<<"||  F TO FLIP HORIZONTALLY  ||  G TO FLIP VERTICALLY                                                           |\n";
        cout<<"|--------------------------------------------------------------------------------------------------------------|\n";

    }
    else
    {
        cout<<"\n\n\nPRESS H TO SHOW COMMANDS \n";
    }

    if(exported_ss)
    {
            cout<<"\n$$$$$$$$$$$$$$$$$$$$$$$$$\n";
            cout<<  "$                       $\n";
            cout<<  "$ EXPORTED SUCCESSFULLY $\n";
            cout<<  "$                       $\n";
            cout<<  "$$$$$$$$$$$$$$$$$$$$$$$$$\n";

            exported_ss=0;
    }



}


int main()
{

    //fast();
    srand(time(0));
    cout<<"Enter the rows and the columns numbers\n";
    cin>>rows>>columns;
    cout<<"Enter the initial drawing character\n";
    cin>>print;
    system("cls");

    cursor.x=rows/2;
    cursor.y=columns/2;
    pressed[0].x=-300;
    pressed[0].y=-300;
    select[0].x=-1;
    select[0].y=-1;
    undo[0].x=-300;
    undo[0].y=-300;


while(1)
    {
        draw(pressed);
        input();
        system("cls");
    }



    return 0;
}
