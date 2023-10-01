//Split-up expenses
#include<iostream>
#include<math.h>

using namespace std;


class person
{
    public :

    //Data-members

        char name[15];
        float amtSpent;
        float tobePaid;
        float tobeRec;

    //Function-members

        void input();
        void adjust(float);
        void output();
};

void person :: input()
{
    cin.ignore();
    cout<<"\nEnter name : ";
    cin.getline(name, 15);

    do
    {
        cout<<"\nEnter amount spent (+ve) : ";
        cin>>amtSpent;
    }while(amtSpent<0);
}

void person :: output()
{
    cout<<"\n\nName : "<<name;
    cout<<"\nAmount spent : "<<amtSpent;
    cout<<"\nAmount to be paid : "<<tobePaid;
    cout<<"\nAmount to be received : "<<tobeRec;
}

void person :: adjust(float perHead) //Sets the amount to be paid by referencing per head contribution
{
    if(amtSpent < perHead)
    {
        tobePaid = perHead - amtSpent;
        tobeRec = 0;
    }
    else if(amtSpent > perHead)
    {
         tobeRec = amtSpent - perHead;
         tobePaid = 0;
    }
    else
    {
        tobePaid = 0;
        tobeRec = 0;
    }
}

void bubbleSort(person grp[], int cnt) //Sorts the grp array ascending order of amount spent
{
    person temp;

    for(int i = 0 ; i < cnt-1 ; i++)
    {
        for(int j = 0 ; j < cnt-i-1 ; j++)
        {
            if(grp[j].amtSpent < grp[j+1].amtSpent)
            {
                temp = grp[j];
                grp[j] = grp[j+1];
                grp[j+1] = temp;
            }
        }
    }
}

int main()
{
    int cntPersons = 0;
    float totalAmt = 0;
    float perHead = 0;

    do
    {
        cout<<"\nEnter number of participants (non-zero & +ve) : ";
        cin>>cntPersons;
    }while(cntPersons <= 0);

    person grp[cntPersons];

    for (int i = 0; i < cntPersons; i++)
    {
        cout<<"\nPerson "<<i+1<<" : ";
        grp[i].input();
    }

    for (int i = 0; i < cntPersons; i++)
    {
        totalAmt += grp[i].amtSpent;
    }

    perHead = totalAmt/cntPersons;

    cout<<"\nTotal amount spent : "<<totalAmt;
    cout<<"\nPer head contribution (approx.) : "<< perHead << endl;


    for (int i = 0; i < cntPersons; i++)
    {
        grp[i].adjust(perHead);
        //cout<<"\n"<<grp[i].name<<" needs to pay "<<grp[i].tobePaid;
    }
/*
    for (int i = 0; i < cntPersons; i++)
    {
        grp[i].output();
    }
*/
    bubbleSort(grp,cntPersons);

///*
    cout<<"\nSorted.";

    for (int i = 0; i < cntPersons; i++)
    {
        grp[i].output();
    }
//*/

    //Splitting Algorithm

    cout<<"\n\n ------------ PAYMENTS----------\n\n";

    int frontInd = 0;
    int endInd = cntPersons-1;

    while(frontInd != endInd)
    {
        if( grp[frontInd].tobeRec > 0)
        {
            if( grp[endInd].tobePaid > 0)
            {
                if( grp[frontInd].tobeRec >= grp[endInd].tobePaid )
                {
                    grp[frontInd].tobeRec -= grp[endInd].tobePaid;
                    cout<<"\n PAY :: "<<grp[endInd].name<<" -> "<<grp[frontInd].name<<" "<<grp[endInd].tobePaid;
                    grp[endInd].tobePaid -= grp[endInd].tobePaid;
                }
                else if( grp[frontInd].tobeRec < grp[endInd].tobePaid )
                {
                    grp[endInd].tobePaid -= grp[frontInd].tobeRec;
                    cout<<"\n PAY :: "<<grp[endInd].name<<" -> "<<grp[frontInd].name<<" "<<grp[frontInd].tobeRec;
                    grp[frontInd].tobeRec = 0 ;
                }
            }

            else
                endInd--;
        }

        else
            frontInd++;
    }

    cout<<"\n\nEND CHECK";

    for (int i = 0; i < cntPersons; i++)
    {
        grp[i].output();
    }
    return 0;

}
