#include <stdio.h>
#include <stdlib.h>

// test commit 

typedef struct //party struct
{
    char party_name[3];
    int representation_for_party;
    int *ipVotesByPolitical_Parties;//it will be deleted.
    int Sum_Of_Votes_p;
}political_party;

typedef struct // state struct
{
    char state_name[20];
    int representation_for_state;//total
    int *ipVotesByState;
    int*representation_each_party_and_state;
    int *ip_temp;
    int control_total_rep;//while ile toplam temsilci sayısını kontrol entmek için.
}state;
int find_largest_number(state * spState,int boyut,int i);
int main()
{
    FILE*oylar =fopen("oylar.txt","r");
    FILE *oylar2=fopen("sonuçlar.txt","w");
    if(oylar==NULL)
    {
        printf("Error reading file!");
        exit(0);
    }
    int iDam,iCount_Of_party,iCount_Of_State,i=0,j=0,total=0;
    fscanf(oylar,"%d",&iDam);
    fscanf(oylar,"%d",&iCount_Of_party);

    political_party *spPolitical_party=malloc(sizeof(political_party)*iCount_Of_party);
    for(i=0;i<iCount_Of_party;i++)
    {
        fscanf(oylar,"%s",spPolitical_party[i].party_name);
    }
    fscanf(oylar,"%d",&iCount_Of_State);

    state*spState=malloc(sizeof(state)*iCount_Of_State);
	for(i=0;i<iCount_Of_State;i++)
    {
        fscanf(oylar,"%s%d",spState[i].state_name,&spState[i].representation_for_state);
    }
    int count=0;
	for(i=0;i<iCount_Of_State;i++)
	{
        spState[i].ipVotesByState = malloc(sizeof(int)*iCount_Of_party);
        spState[i].ip_temp = malloc(sizeof(int)*iCount_Of_party);
        spState[i].representation_each_party_and_state=malloc(sizeof(int)*iCount_Of_party);

        for(j=0;j<iCount_Of_party;j++)
            {
                spPolitical_party[j].ipVotesByPolitical_Parties=malloc(sizeof(int)*iCount_Of_State);
                fscanf(oylar,"%d",&spState[i].ipVotesByState[j]);
				total+=spState[i].ipVotesByState[j];//total votes
            }
	}
    for(count=0;count<iCount_Of_party;count++)
        {
           spPolitical_party[count].Sum_Of_Votes_p=0;
        }
        fprintf(oylar2,"total vote:%d\n",total);//toplam oy
    count=0;
    spPolitical_party[count].Sum_Of_Votes_p=0;
    while(count<iCount_Of_party)//her bir partinin toplam oyu ve oy yüzdeleri bulundu.
    {

        for(i=0;i<iCount_Of_State;i++)
        {
            spPolitical_party[count].Sum_Of_Votes_p+=spState[i].ipVotesByState[count];
        }
        count++;
	}
		for(j=0;j<iCount_Of_party;j++)//Baraj altýnda kalan oylarý sýfýrlar.
        {
            if(((float)spPolitical_party[j].Sum_Of_Votes_p/total*100)<iDam)
            {
                for(i=0;i<iCount_Of_State;i++)
                {
                    spState[i].ipVotesByState[j]=0;
                }
            }
        }
       for(i=0;i<iCount_Of_State;i++)//her yerdeki temsilci sayıları sıfırlandı// hatali!!!!
        {
            for(j=0;j<iCount_Of_party;j++)
            {
                spPolitical_party[j].representation_for_party=0;
                spState[i].representation_each_party_and_state[j]=0;
                spState[i].control_total_rep=0;
            }
		}
        for(i=0;i<iCount_Of_State;i++)
        {
            for(j=0;j<iCount_Of_party;j++)
            {
            	spState[i].ip_temp[j]=spState[i].ipVotesByState[j]/1;//Tüm oyları tempe attık.Artık temple işlem yapacağız.
            }
        }
    int max_index;
        for(i=0;i<iCount_Of_State;i++)
        {
			while(spState[i].control_total_rep<spState[i].representation_for_state)
			{

	            	max_index = find_largest_number(spState, iCount_Of_party, i);//tempteki en büyük değerleri verir.indisini verir.
	                spState[i].representation_each_party_and_state[max_index]++;
	                spState[i].control_total_rep++;
	                spState[i].ip_temp[max_index]=spState[i].ipVotesByState[max_index]/(spState[i].representation_each_party_and_state[max_index]+1);
			}
        }
        count=0;
        while(count<iCount_Of_party)
        {
            for(i=0;i<iCount_Of_State;i++)
                {
                    spPolitical_party[count].representation_for_party+=spState[i].representation_each_party_and_state[count];
	            }
            	fprintf(oylar2,"\n%s-%d delegate-%d vote- %.2f vote rate \n",spPolitical_party[count].party_name,spPolitical_party[count].representation_for_party,spPolitical_party[count].Sum_Of_Votes_p,(float)spPolitical_party[count].Sum_Of_Votes_p/total*100);//total bak.
                count++;
		}
		for(i=0;i<iCount_Of_State;i++)
        {
			fprintf(oylar2,"\n  %s -",spState[i].state_name);
                for(j=0;j<iCount_Of_party;j++)
                {

	            	fprintf(oylar2," %d",spState[i].representation_each_party_and_state[j]);
	            }
        }
    fclose(oylar);
    fclose(oylar2);
    free(spState);
    free(spPolitical_party);
    return 0;
}

int find_largest_number(state* spState,int iCount_Of_party,int i)//max. bulan fonk.
	{
			int max_index;
            int j;
			int largest= spState[i].ip_temp[0];
			max_index=0;
			for(j=0;j<iCount_Of_party;j++)
			{
				if(spState[i].ip_temp[j]>largest)
				{
					largest=spState[i].ip_temp[j];
					max_index=j;
				}
			}
	return max_index;
	}
	void print (int x)
	{
		printf("%d",x);
	}

