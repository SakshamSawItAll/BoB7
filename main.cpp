#include <bits/stdc++.h>
#define MAX 25
using namespace std;

int play_matrix[7][7];

int limit[7][7]= {{0,0,0,0,0,0,0},{0,1,2,2,2,1,0},{0,2,3,3,3,2,0},{0,2,3,3,3,2,0},{0,2,3,3,3,2,0},{0,1,2,2,2,1,0},{0,0,0,0,0,0,0}};

int answer_x,answer_y,maxim,player;

int a[7][7],b[7][7],c[7][7],d[7][7],e[7][7],dummy_array[7][7];

/*bool occupy_wall_centre()
{
    if(play_matrix[3][1]==0)
        {
            answer_x=2;answer_y=0;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
    if(play_matrix[1][3]==0)
        {
            answer_x=0;answer_y=2;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
    if(play_matrix[3][5]==0)
        {
            answer_x=2;answer_y=4;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
    if(play_matrix[5][3]==0)
        {
            answer_x=4;answer_y=2;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
    return false;
}*/

int counter()
{
    int i,j;
    int count_orb=0;
    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
        {
            if(b[i][j]/10!=player)
            {
                count_orb+=a[i][j];
            }
        }
    return count_orb;
}

bool check(void)
{
    int i,j;
    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
            if(a[i][j]>limit[i][j])
                return true;
    return false;
}

bool left_wall(int x,int y)
{
    if((x==1 && y!=1 && y!=5))
        return true;
    else
        return false;
}

bool right_wall(int x,int y)
{
    if((x==5 && y!=1 && y!=5))
        return true;
    else
        return false;
}

bool upper_wall(int x,int y)
{
    if((y==1 && x!=1 && x!=5))
        return true;
    else
        return false;
}

bool lower_wall(int x,int y)
{
    if(y==5 && x!=1 && x!=5)
        return true;
    else
        return false;
}

bool tr_corner(int x,int y)
{
    if(y==1 && x==5)
        return true;
    else
        return false;
}

bool tl_corner(int x,int y)
{
    if((y==1 && x==1))
        return true;
    else
        return false;
}

bool br_corner(int x,int y)
{
    if((y==5 && x==5))
        return true;
    else
        return false;
}

bool bl_corner(int x,int y)
{
    if((y==5 && x==1))
        return true;
    else
        return false;
}

bool body(int x,int y)
{
    if(!upper_wall(x,y) &&!lower_wall(x,y) &&!right_wall(x,y) &&!left_wall(x,y) && !tr_corner(x,y) && !tl_corner(x,y) && !br_corner(x,y) && !bl_corner(x,y))
        return true;
    else
        return false;
}

bool occupy_corner(int possible_x[], int possible_y[], int len)
{
    int i;
    for(i=0; i<len; i++)
    {
        if(possible_x[i]-1==0 && possible_y[i]-1==0)
        {
            answer_x=0;
            answer_y=0;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
        else if(possible_x[i]-1==0 && possible_y[i]-1==4)
        {
            answer_x=0;
            answer_y=4;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
        else if(possible_x[i]-1==4 && possible_y[i]-1==0)
        {
            answer_x=4;
            answer_y=0;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
        else if(possible_x[i]-1==4 && possible_y[i]-1==4)
        {
            answer_x=4;
            answer_y=4;
            cout<<answer_x<<" "<<answer_y;
            exit(0);
        }
    }
    return false;

}

int player_orbs(int index_x, int index_y)
{
    return play_matrix[index_x][index_y]%10;
}

int player_id(int index_x, int index_y)
{
    return play_matrix[index_x][index_y]/10;
}

void offence()
{
    int i,j,p,k,l=0;
    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
        {
            b[i][j]=play_matrix[i][j];
            d[i][j]=b[i][j];
        }

    maxim=0;
    for(p=1; p<6; p++)
    {
        for(k=1; k<6; k++)
        {
            for(i=1; i<6; i++)
                for(j=1; j<6; j++)
                {
                    b[i][j]=d[i][j];
                    e[i][j]=0;
                }

            for(i=1; i<6; i++)
                for(j=1; j<6; j++)
                    a[i][j]=b[i][j]%10;

            if(b[p][k]/10==player)
                a[p][k]++;

            int count_start=counter();
            int flag=0;

            while(check())
            {
                flag=1;
                for(i=1; i<6; i++)
                    for(j=1; j<6; j++)
                    {
                        if(a[i][j]>limit[i][j])
                        {
                            if(tr_corner(i,j))
                            {
                                a[i-1][j]++;
                                a[i][j+1]++;
                                a[i][j]-=2;
                                e[i][j]=1;
                                e[i-1][j]=1;
                                e[i][j+1]=1;
                            }
                            else if(tl_corner(i,j))
                            {
                                a[i+1][j]++;
                                a[i][j+1]++;
                                a[i][j]-=2;
                                e[i][j]=1;
                                e[i+1][j]=1;
                                e[i][j+1]=1;
                            }
                            else if(br_corner(i,j))
                            {
                                a[i-1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=2;
                                e[i][j]=1;
                                e[i-1][j]=1;
                                e[i][j-1]=1;
                            }
                            else if(bl_corner(i,j))
                            {
                                a[i+1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=2;
                                e[i][j]=1;
                                e[i+1][j]=1;
                                e[i][j-1]=1;
                            }
                            else if(upper_wall(i,j))
                            {
                                a[i-1][j]++;
                                a[i+1][j]++;
                                a[i][j+1]++;
                                a[i][j]-=3;
                                e[i][j]=1;
                                e[i-1][j]=1;
                                e[i+1][j]=1;
                                e[i][j+1]=1;
                            }
                            else if(lower_wall(i,j))
                            {
                                a[i-1][j]++;
                                a[i+1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=3;
                                e[i][j]=1;
                                e[i-1][j]=1;
                                e[i+1][j]=1;
                                e[i][j-1]=1;
                            }
                            else if(right_wall(i,j))
                            {
                                a[i][j+1]++;
                                a[i][j-1]++;
                                a[i-1][j]++;
                                a[i][j]-=3;
                                e[i][j]=1;
                                e[i][j+1]=1;
                                e[i][j-1]=1;
                                e[i-1][j]=1;
                            }
                            else if(left_wall(i,j))
                            {
                                a[i][j+1]++;
                                a[i][j-1]++;
                                a[i+1][j]++;
                                a[i][j]-=3;
                                e[i][j]=1;
                                e[i][j+1]=1;
                                e[i][j-1]=1;
                                e[i+1][j]=1;
                            }
                            else if(body(i,j))
                            {
                                a[i+1][j]++;
                                a[i][j+1]++;
                                a[i-1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=4;
                                e[i][j]=1;
                                e[i+1][j]=1;
                                e[i][j+1]=1;
                                e[i-1][j]=1;
                                e[i][j-1]=1;
                            }



                        }

                        l++;
                        if(l>1000)
                        {
                            cout<<p-1<<" "<<k-1<<endl;
                            exit(0);
                        }


                    }
            }

            if(flag)
            {
                for(i=1; i<6; i++)
                    for(j=1; j<6; j++)
                    {
                        if(e[i][j]==1)
                        {
                            if(a[i][j])
                                b[i][j]=(player*10)+a[i][j];
                            else
                                b[i][j]=0;
                        }
                    }
            }

            int count_final=counter();

            if(count_final==0)
            {
                cout<<p-1<<" "<<k-1<<endl;
                exit(0);
            }
            if(fabs(count_start-count_final)>maxim)
            {
                maxim=fabs(count_start-count_final);
                answer_x=p-1;
                answer_y=k-1;
            }

        }
    }


}

void print()
{
    int i,j;
    for(i=1; i<6; i++)
    {
        for(j=1; j<6; j++)
            cout<<dummy_array[i][j]<<" ";
        cout<<endl;
    }
}

int temp_minim=25;

void find_min()
{
    int i,j;
    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
            if(dummy_array[i][j]<temp_minim)
                temp_minim=dummy_array[i][j];

}

bool min_check(int i, int j)
{
    if(dummy_array[i][j]==temp_minim)
        return true;
    else
        return false;

}

void random_stack()
{
    int random_index;
    int possible_x[MAX]= {0},possible_y[MAX]= {0};
    int i,j,k=0;
    srand(time(NULL));
    find_min();
    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
        {
            if(player_id(i,j)==0 || (player_id(i,j)==player && player_orbs(i,j)<limit[i][j]))
            {
                if(min_check(i,j))
                {
                    possible_x[k]=i;
                    possible_y[k]=j;
                    k++;
                }
            }
        }
    int check_temp=occupy_corner(possible_x,possible_y,k);
    //occupy_wall_centre();
    if(!check_temp)
    {
        random_index=rand()%k;
        answer_x=possible_x[random_index]-1;
        answer_y=possible_y[random_index]-1;
    }

}


bool no_attack()
{
    offence();
    if(maxim>2)
        return false;
    else
        return true;
}

bool corners_unoccupied()
{
    if(play_matrix[1][1]==0 || play_matrix[1][5]==0 || play_matrix[5][1]==0 || play_matrix[5][5]==0)
        return true;
    else
        return false;
}

int main()
{
    int i,j,p,k,l=0;
    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
            cin>>play_matrix[i][j];

    cin>>player;

    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
        {
            b[i][j]=play_matrix[i][j];
            d[i][j]=b[i][j];
        }

    for(p=1; p<6; p++)
    {
        for(k=1; k<6; k++)
        {
            for(i=1; i<6; i++)
                for(j=1; j<6; j++)
                {
                    b[i][j]=d[i][j];
                }

            for(i=1; i<6; i++)
                for(j=1; j<6; j++)
                    a[i][j]=b[i][j]%10;

            if(b[p][k]/10!=player)
                a[p][k]++;

            while(check())
            {
                for(i=1; i<6; i++)
                    for(j=1; j<6; j++)
                    {
                        if(a[i][j]>limit[i][j])
                        {
                            if(tr_corner(i,j))
                            {
                                a[i-1][j]++;
                                a[i][j+1]++;
                                a[i][j]-=2;
                                c[i][j]++;
                                c[i-1][j]++;
                                c[i][j+1]++;
                            }
                            else if(tl_corner(i,j))
                            {
                                a[i+1][j]++;
                                a[i][j+1]++;
                                a[i][j]-=2;
                                c[i][j]++;
                                c[i+1][j]++;
                                c[i][j+1]++;
                            }
                            else if(br_corner(i,j))
                            {
                                a[i-1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=2;
                                c[i][j]++;
                                c[i-1][j]++;
                                c[i][j-1]++;
                            }
                            else if(bl_corner(i,j))
                            {
                                a[i+1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=2;
                                c[i][j]++;
                                c[i+1][j]++;
                                c[i][j-1]++;
                            }
                            else if(upper_wall(i,j))
                            {
                                a[i-1][j]++;
                                a[i+1][j]++;
                                a[i][j+1]++;
                                a[i][j]-=3;
                                c[i][j]++;
                                c[i-1][j]++;
                                c[i+1][j]++;
                                c[i][j+1]++;
                            }
                            else if(lower_wall(i,j))
                            {
                                a[i-1][j]++;
                                a[i+1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=3;
                                c[i][j]++;
                                c[i-1][j]++;
                                c[i+1][j]++;
                                c[i][j-1]++;
                            }
                            else if(right_wall(i,j))
                            {
                                a[i][j+1]++;
                                a[i][j-1]++;
                                a[i-1][j]++;
                                a[i][j]-=3;
                                c[i][j]++;
                                c[i][j+1]++;
                                c[i][j-1]++;
                                c[i-1][j]++;
                            }
                            else if(left_wall(i,j))
                            {
                                a[i][j+1]++;
                                a[i][j-1]++;
                                a[i+1][j]++;
                                a[i][j]-=3;
                                c[i][j]++;
                                c[i][j+1]++;
                                c[i][j-1]++;
                                c[i+1][j]++;
                            }
                            else if(body(i,j))
                            {
                                a[i+1][j]++;
                                a[i][j+1]++;
                                a[i-1][j]++;
                                a[i][j-1]++;
                                a[i][j]-=4;
                                c[i][j]++;
                                c[i+1][j]++;
                                c[i][j+1]++;
                                c[i-1][j]++;
                                c[i][j-1]++;
                            }
                        }

                        l++;
                        if(l>100)
                        {
                            offence();

                        }
                    }

            }
        }
    }

    for(i=1; i<6; i++)
        for(j=1; j<6; j++)
            dummy_array[i][j]=c[i][j];



    if(no_attack())
    {
        if(corners_unoccupied() && counter()<2)
            random_stack();
        else
            random_stack();
    }
    else
    {
        offence();
    }
    cout<<answer_x<<" "<<answer_y<<endl;
    print();
    return 0;
}
